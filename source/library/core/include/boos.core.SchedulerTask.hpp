/**
 * Scheduler task.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_SCHEDULER_TASK_HPP_
#define BOOS_CORE_SCHEDULER_TASK_HPP_
 
#include "boos.core.Thread.hpp"
#include "boos.core.chip.Register.hpp"
#include "boos.util.Stack.hpp"
 
namespace core
{
  class SchedulerTask : public Object<>
  {
     friend class Scheduler;

  public:

    /** 
     * Constructor.
     *
     * @param thread pointer to thread class.
     * @param target pointer to executable target.
     * @param count  int64 type elements number of stack size.     
     * @param id     task ID.
     */
    SchedulerTask(Thread* thread, ::api::Runnable* target, int32 count, int32 id) :
      prev_     (this),
      next_     (this),
      thread_   (thread),
      target_   (target),
      register_ (),
      stack_    (::util::Stack<int64>::ED, count),
      status_   (UNDEF),
      id_       (id),
      priority_ (Thread::NORM_PRIORITY){
      setConstruct( construct() );      
    }

    /** 
     * Destructor.
     */
    virtual ~SchedulerTask()
    {
    }

    /**
     * Returns this thread priority.
     *
     * @return priority value.
     */  
    int32 priority()
    {
      return priority_;
    }  
    
    /**
     * Sets this thread priority.
     *
     * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY].
     */  
    void priority(int32 priority)
    {
      if(!isConstructed()) return;
      if(priority > Thread::MAX_PRIORITY) priority = Thread::MAX_PRIORITY;
      else if(priority < Thread::MIN_PRIORITY) priority = Thread::MIN_PRIORITY;
      priority_ = priority;
    }

    /**
     * Returns the task ID.
     *
     * @return task ID.
     */
    int32 id()
    {
      return id_;
    }

    /**
     * Returns the task thread.
     *
     * @return task thread.
     */
    Thread* thread()
    {
      return thread_;
    }

  private:

    /** 
     * Thread task available statuses.
     */
    enum Status
    {
      UNDEF    = 0,
      NEW      = 1,
      RUNNABLE = 2,
      RUNNING  = 3,
      WAITING  = 4,
      BLOCKED  = 5,
      SLEEPING = 6,
      DEAD     = 7
    };

    /** 
     * Constructor.
     *
     * @return true if object has been constructed successfully.
     */
    bool construct()
    {
      if(!isConstructed()) return false;
      if(!stack_.isConstructed()) return false;
      if(!register_.isConstructed()) return false;
      return status(NEW);
    }

    /**
     * Sets status of thread.
     *
     * @param status new status of this thread.
     * @return true if status is changed.
     */
    bool status(Status status)
    {
      if(!isConstructed()) return false;
      bool set = false;
      switch(status_)
      {
        // Current status is UNDEF
        case UNDEF:
        {
          switch(status)
          {
            case NEW: set = true;
          }              
        }
        break;
        // Current status is NEW
        case NEW:      
        {
          switch(status)
          {
            case RUNNABLE: set = true;
          }      
        }
        break;
        // Current status is RUNNABLE
        case RUNNABLE:
        {
          switch(status)
          {
            case RUNNING: set = true;
          }        
        }
        break;
        // Current status is RUNNING
        case RUNNING:
        {
          switch(status)
          {
            case RUNNABLE:
            case DEAD:
            case SLEEPING: 
            case BLOCKED: set = true;
          }
        }
        break;
        // Current status is WAITING
        case WAITING:
        {
        }
        break;
        // Current status is BLOCKED
        case BLOCKED:
        {
          switch(status)
          {
            case RUNNABLE: set = true;
          }      
        }
        break;
        // Current status is SLEEPING
        case SLEEPING:
        {
          switch(status)
          {
            case RUNNABLE: set = true;
          }      
        }
        break;
        // Current status is DEAD
        case DEAD:
        {
        }
        break;
      }
      if(set == true) status_ = status;
      return set;
    }

    /**
     * Links a given task after this.
     *
     * @param task pointer to linking task.
     */
    void link(SchedulerTask* task)
    {
      if(!isConstructed()) return;
      next_->prev_ = task;
      task->next_ = next_;
      next_ = task;
      task->prev_ = this;
    }

    /**
     * Unlinks this task.
     */
    void unlink()
    {
      if(!isConstructed()) return;
      next_->prev_ = prev_;
      prev_->next_ = next_;
      prev_ = this;
      next_ = this;
    }

    /**
     * Tests if this task is linked with other.
     */
    bool isLinked()
    {
      return next_ == this && prev_ == this ? false : true;
    }
    
    /**
     * Previous task.
     */
    SchedulerTask* prev_;
    
    /**
     * Next task.
     */    
    SchedulerTask* next_;
    
    /**
     * Linked thread object
     */        
    Thread* thread_;
    
    /**
     * User executing runnable interface.
     */        
    ::api::Runnable* target_;
    
    /**
     * Given blocked resource.
     */        
    ::api::Resource* block_;
    
    /**
     * CPU state registers.
     */        
    chip::Register register_;
    
    /**
     * Thread stack.
     */        
    ::util::Stack<int64> stack_;
    
    /**
     * Current status.
     */        
    Status status_;
    
    /**
     * Current identifier.
     */        
    int32 id_;
    
    /**
     * Current priority.
     */        
    int32 priority_;
    
    /**
     * Wake up time in nanoseconds.
     */        
    int64 sleep_;
    
  };
}
#endif // BOOS_CORE_SCHEDULER_TASK_HPP_
