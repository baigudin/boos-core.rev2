/**
 * Thread tasks scheduler.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_SCHEDULER_HPP_
#define BOOS_CORE_SCHEDULER_HPP_

#include "boos.core.SchedulerTask.hpp"
#include "boos.core.Core.hpp"
#include "boos.core.TimerInterrupt.hpp"
#include "boos.core.chip.Register.hpp"
#include "boos.core.epi.Interrupt.hpp"
  
namespace core
{
  class Scheduler : public TimerInterrupt, public ::api::InterruptHandler
  {
    typedef TimerInterrupt Parent;
    using Parent::start;

  public:

    /** 
     * Constructor.
     */
    Scheduler() : TimerInterrupt( reinterpret(this) ),
      register_ (),
      last_     (NULL),
      current_  (NULL),
      core_     (Core::configuration()){
      setConstruct( construct() );
    }

    /** 
     * Destructor.
     */
    virtual ~Scheduler()
    {
    }
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const
    {
      return this->Parent::isConstructed();
    }

    /** 
     * Hardware interrupt handler.
     */      
    virtual void handler()
    {
      if(current_ == NULL) return switchToTerminate();
      //Select next thread:
      while(true)
      {
        switch(current_->status_)
        {
          case SchedulerTask::BLOCKED: 
          {
            if(!current_->block_->isBlocked()) 
              if(current_->status(SchedulerTask::RUNNABLE) == false) 
                return switchToTerminate();
          }
          break;
          case SchedulerTask::SLEEPING: 
          {
            int64 cur = Core::nanoTime();
            if(cur >= current_->sleep_)
            {
              current_->sleep_ = 0;
              if(current_->status(SchedulerTask::RUNNABLE) == false) 
                return switchToTerminate();
            }
          }
          break;             
          case SchedulerTask::RUNNING: 
          {
            if(current_->status(SchedulerTask::RUNNABLE) == false) 
              return switchToTerminate();
          }
          break;
          case SchedulerTask::RUNNABLE: 
          {
            if(current_->status(SchedulerTask::RUNNING) == false) 
              return switchToTerminate();
            else
              return switchToTask(current_);
          }
        }    
        current_ = current_->next_;
      }
    }

    /**
     * Begins to execute a task.
     *
     * @param task started task.
     */
    void start(SchedulerTask* task)
    {
      if(task == NULL) return;
      if(!isConstructed()) return;
      bool is = global().disable();
      if(isTask(task)) return global().enable(is);
      if(task->status_ != SchedulerTask::NEW) return global().enable(is);        
      if(task->status(SchedulerTask::RUNNABLE) == false ) return global().enable(is);    
      // Set default registers value
      int32 entry = reinterpret_cast<int32>(runTask);
      int32 arg = reinterpret_cast<int32>(this);
      task->register_.initialize(task->stack_, entry, arg, 0);
      // Link the task
      if(last_ != NULL) last_->link(task);
      last_ = task;
      global().enable(is);
    }

    /**
     * Removes the first occurrence of the specified task.
     *
     * @param task removing task.
     */
    void remove(SchedulerTask* task)
    {
      if(task == NULL) return;
      if(!isConstructed()) return;
      bool is = global().disable();
      if(!isTask(task)) return global().enable(is);
      // Removable task can not be the current
      if(task == current_)
      {
        current_ = NULL;
        jump();
      }
      // In this case we have only one task
      if(!last_->isLinked()) 
      {
        last_ = NULL;
      }
      else
      {
        if(last_ == task) last_ = last_->prev_;
        task->unlink();
      }
      global().enable(is);
    }

    /**
     * Yields to next task.
     */
    void yield()
    {
      if(isConstructed()) jump();
    }

    /**
     * Waits for this thread to die.
     *
     * @param task.
     */
    void join(SchedulerTask* task)
    {
      if(task == NULL) return;
      if(!isConstructed()) return;
      if(!isTask(task)) return;
      while(task->status_ != SchedulerTask::DEAD) jump();
    }

    /**
     * Blocks current task on given resourse and yeilds the task.
     *
     * @param res pointer to resource.
     */  
    void blockCurrentTask(::api::Resource& res)
    {
      bool is = global().disable();
      if(current_->status(SchedulerTask::BLOCKED) == false) return global().enable(is);
      current_->block_ = &res;
      jump();
      global().enable(is);
    }

    /**
     * Causes the currently executing thread to sleep.
     *
     * @param millis a time to sleep in milliseconds.
     * @param nanos  an additional nanoseconds to sleep.
     */  
    void sleepCurrentTask(int64 millis, int64 nanos)
    {
      bool is = global().disable();
      if(current_->status(SchedulerTask::SLEEPING) == false) return global().enable(is);
      current_->sleep_ = Core::nanoTime() + millis * 1000000 + nanos;
      jump();
      global().enable(is);
    }

    /**
     * Returns a pointer to the currently executing task.
     *
     * @return the executable task.
     */
    SchedulerTask* currentTask()
    {
      return current_;
    }

    /**
     * Initiates an execution of thread tasks.
     */  
    void execute()
    {
      if(current_ != NULL) return;
      current_ = last_;
      // Set timer counter to zero and clear interrupt flag,
      // because the timer might have been worked.
      setCount(0);      
      clear();
      global().enable(true);      
      jump();
      global().disable();
    }

  private:

    /** 
     * Constructor.
     *
     * @return true if object has been constructed successfully.
     */
    bool construct()
    {
      if(!isConstructed()) return false;
      if(!register_.isConstructed()) return false;
      // Set this class register for storing contex
      // when first scheduler timer interrupt is occured
      Interrupt::extension().setRegister(register_);
      setCount(0);
      setPeriod(core_.quant);
      start();
      enable(true);
      return true;
    }

    /**
     * Runs a method of Runnable interface start vector.
     */  
    static void runTask(Scheduler* scheduler)
    {
      // Invoke the member function through the pointer
      void(Scheduler::*run)() = &Scheduler::run;
      (scheduler->*run)();
      // This PC is not allowable
      while(true);
    }

    /**
     * Runs a method of Runnable interface start vector.
     */  
    void run()
    {
      current_->target_->run();
      global().disable();
      current_->status(SchedulerTask::DEAD);
      // Calculate the count of alive tasks
      int32 alive = 0;
      SchedulerTask* task = last_;
      while(true)
      {
        if(task->status_ != SchedulerTask::DEAD) alive++;
        task = task->next_;
        if(last_ == task) break;
      }
      if(alive != 0) while(true) jump();  
      // Set a temporary resister structure for storing current context to it.
      // PC will never be set to position after the method jump(), because
      // pointer to current task is set to NULL. By this action
      // scheduler interrupt handler sets restore context which was saved
      // by jump() method in execute() method. That is why the program will be 
      // returned to execute an execute() method of this class.
      chip::Register reg = register_;
      Interrupt::extension().setRegister(reg);
      current_ = NULL;
      jump();
    }

    /** 
     * Test if the task is a task of scheduler.
     *
     * @param task testing task.
     * @return boolean result.
     */      
    bool isTask(SchedulerTask* task)
    {
      if(task == NULL) return false;
      if(last_ == NULL) return false;
      SchedulerTask* temp = last_;
      do{
        if(task == temp) return true;
        temp = temp->next_;
      }while(temp != last_);
      return false;
    }

    /** 
     * Switch to task.
     *
     * Method should be called in interrupt handler.
     *
     * @param task
     */      
    void switchToTask(SchedulerTask* task)
    {
      Interrupt::extension().setRegister(task->register_);
      Parent::setCount(0);
      Parent::setPeriod(task->priority_ * core_.quant);
    }

    /** 
     * Terminates tasks execution.
     * 
     * Method terminates an execution of all tasks. 
     * It should be called in interrupt handler.
     */      
    void switchToTerminate()
    {
      current_ = NULL;
      Interrupt::extension().setRegister(register_);
      Parent::setCount(0);
      Parent::setPeriod();
    }

    /**
     * Fixs a collision to call a TimerInterrupt constructor.
     *
     * Method gives to compiler an understanding about what should be called.
     * The parent constructor will called, just not a copy constructor.
     *
     * @param cls pointer to this class.
     * @return the reference to InterruptHandler interface of given class.
     */
    static ::api::InterruptHandler& reinterpret(Scheduler* cls)
    {
      return *cls;
    }

    /**
     * Register for storing core state.
     */
    chip::Register register_;

    /**
     * Copy of the core configuration.
     */
    Configuration core_;
    
    /**
     * Last task of tasks list.
     */    
    SchedulerTask* last_;
    
    /**
     * Current executing task.
     */        
    SchedulerTask* current_;

  };
}
#endif // BOOS_CORE_SCHEDULER_HPP_
