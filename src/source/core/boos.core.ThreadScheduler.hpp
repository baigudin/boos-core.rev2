/**
 * Thread tasks scheduler.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
extern void* __bss__;

namespace core
{
  class ThreadScheduler : public TimerInterrupt, public api::InterruptHandler
  {
    typedef ThreadTask Task;

  public:

    /** 
     * Constructor.
     */
    ThreadScheduler() : TimerInterrupt( reinterpret(this) ),
      register_ (),
      last_     (NULL),
      current_  (NULL),
      core_     (Core::config()),
      timer_    (getTimer()){
      setConstruct( construct() );
    }

    /** 
     * Destructor.
     */
    virtual ~ThreadScheduler()
    {
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
          case Task::BLOCKED: 
          {
            if(!current_->block_->isBlocked()) 
              if(current_->status(Task::RUNNABLE) == false) 
                return switchToTerminate();
          }
          break;
          case Task::SLEEPING: 
          {
            if(Core::nanoTime() >= current_->sleep_)
            {
              current_->sleep_ = 0;
              if(current_->status(Task::RUNNABLE) == false) 
                return switchToTerminate();
            }
          }
          break;             
          case Task::RUNNING: 
          {
            if(current_->status(Task::RUNNABLE) == false) 
              return switchToTerminate();
          }
          break;
          case Task::RUNNABLE: 
          {
            if(current_->status(Task::RUNNING) == false) 
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

     * @param task started task.
     */
    void start(Task* task)
    {
      if(task == NULL) return;
      if(!isConstructed()) return;
      bool is = global().disable();
      if(isTask(task)) return global().enable(is);
      if(task->status_ != Task::NEW) return global().enable(is);        
      if(task->status(Task::RUNNABLE) == false ) return global().enable(is);    
      // Set default registers value
      Register::Init init;
      init.start  = reinterpret_cast<int32>(runTask);
      init.arg[0] = reinterpret_cast<int64>(this);
      init.page   = reinterpret_cast<int32>(&__bss__);
      init.stack  = reinterpret_cast<int32>(task->stack_.tos());    
      task->register_.initialize(init);
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
    void remove(Task* task)
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
    void join(Task* task)
    {
      if(task == NULL) return;
      if(!isConstructed()) return;
      if(!isTask(task)) return;
      while(task->status_ != Task::DEAD) jump();
    }

    /**
     * Blocks current task on given resourse and yeilds the task.
     *
     * @param res pointer to resource.
     */  
    void blockCurrentTask(api::Resource& res)
    {
      bool is = global().disable();
      if(current_->status(Task::BLOCKED) == false) return global().enable(is);
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
      if(current_->status(Task::SLEEPING) == false) return global().enable(is);
      current_->sleep_ = Core::nanoTime() + millis * 1000000 + nanos;
      jump();
      global().enable(is);
    }

    /**
     * Returns a pointer to the currently executing task.
     *
     * @return the executable task.
     */
    Task* currentTask()
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
      global().enable(true);      
	  jump();
      global().disable();
    }

  private:

    /** 
     * Constructor.
     *
     * @return boolean result.
     */
    bool construct()
    {
      if(!isConstructed()) return false;
	  if(!register_.isConstructed()) return false;
	  // Set self register for contex store
	  setRegister(&register_);
      timer_.setCount(0);
      timer_.setPeriod(core_.quant);
      timer_.start();
      return true;
    }

    /**
     * Runs a method of Runnable interface start vector.
     */  
    static void runTask(ThreadScheduler* scheduler)
    {
      // Invoke the member function through the pointer
      void(ThreadScheduler::*run)() = &ThreadScheduler::run;
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
      current_->status(Task::DEAD);
      // Calculate the count of alive tasks
      int32 alive = 0;
      Task* task = last_;
      while(true)
      {
        if(task->status_ != Task::DEAD) alive++;
        task = task->next_;
        if(last_ == task) break;
      }
      if(alive != 0) while(true) jump();  
      // Set a temporary resister structure for storing current context to it.
      // PC will never be set to position after the method jump(), because
      // pointer to current task is set to NULL. By this action
      // scheduler interrupt handler sets restore context which was saved
      // while jump() in execute() method. That is why program will be returned
      // to execute an execute() method of this class.
      Register reg = register_;
      setRegister(&reg);
      current_ = NULL;
      jump();
    }

    /** 
     * Test if the task is a task of scheduler.
     *
     * @param task testing task.
     * @return boolean result.
     */      
    bool isTask(Task* task)
    {
      if(task == NULL) return false;
      if(last_ == NULL) return false;
      Task* temp = last_;
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
    void switchToTask(Task* task)
    {
      setRegister(&task->register_);
      timer_.setCount(0);
      timer_.setPeriod(task->priority_ * core_.quant);
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
      setRegister(&register_);
      timer_.setCount(0);
      timer_.setPeriod();
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
    static api::InterruptHandler& reinterpret(ThreadScheduler* cls)
    {
      return *cls;
    }

    Register                    register_;
    api::Timer&                 timer_;
    CoreConfig                  core_;
    Task*                       last_;
    Task*                       current_;
  };
}
