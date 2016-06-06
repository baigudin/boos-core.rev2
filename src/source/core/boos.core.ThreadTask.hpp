/**
 * Thread scheduler.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
namespace core
{
  class ThreadTask : public Object<>
  {

  public:

    /** 
     * Constructor.
     *
     * @param thread pointer to thread class.
     * @param target pointer to executable target.
     * @param size   size of stack in bytes has to be aligned to eight.
     */
    ThreadTask(Thread* thread, api::Runnable* target, size_t size) :
      prev_     (this),
      next_     (this),
      thread_   (thread),
      target_   (target),
      register_ (),
      stack_    (size),
      status_   (UNDEF),
      id_       (0),
      priority_ (Thread::NORM_PRIORITY){
      setConstruct( construct() );      
    }

    /** 
     * Destructor.
     */
    virtual ~ThreadTask()
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
     * @return boolean result.
     */
    bool construct()
    {
      if(!isConstructed()) return false;
      if(!stack_.isConstructed()) return false;
      if(!register_.isConstructed()) return false;
      if(idCount_ <= 0) return false;
      id_ = idCount_++;
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
    void link(ThreadTask* task)
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

    static int32              idCount_;
    ThreadTask*               prev_;
    ThreadTask*               next_;
    Thread*                   thread_;
    api::Runnable*            target_;
    api::Resource*            block_;
    Register                  register_;
    Stack                     stack_;
    Status                    status_;
    int32                     id_;
    int32                     priority_;
    int64                     sleep_;

    friend class              ThreadScheduler;
  };

  int32                       ThreadTask::idCount_ = 1;  
}
