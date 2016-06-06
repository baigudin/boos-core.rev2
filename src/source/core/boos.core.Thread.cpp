/**
 * Thread class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2015 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Register.hpp"
#include "boos.core.Stack.hpp"
#include "boos.core.Core.hpp"
#include "boos.core.TimerInterrupt.hpp"
#include "boos.core.Thread.hpp"
#include "boos.core.ThreadTask.hpp"
#include "boos.core.ThreadScheduler.hpp"

namespace core
{
  ThreadScheduler*  Thread::scheduler_ = NULL;

  /** 
   * Constructor.
   */
  Thread::Thread() :
    task_ (NULL){
    setConstruct( construct(this) );  
  }
  
  /** 
   * Constructor.
   *
   * @param target an interface whose run method is invoked when this thread is started.
   */
  Thread::Thread(api::Runnable& target) :
    task_ (NULL){
    setConstruct( construct(&target) );  
  }
  
  /** 
   * Destructor.
   */
  Thread::~Thread()
  {
    if(scheduler_ != NULL) scheduler_->remove(task_);
    delete task_;
  }
  
  /**
   * Causes this thread to begin execution.
   */
  void Thread::start()
  {
    if( isConstructed() ) scheduler_->start(task_);
  }
  
  /**
   * Waits for this thread to die.
   */  
  void Thread::join()
  {
    if( isConstructed() ) scheduler_->join(task_);
  }
  
  /**
   * Causes the currently executing thread to sleep.
   *
   * @param millis a time to sleep in milliseconds.
   * @param nanos  an additional nanoseconds to sleep.
   */  
  void Thread::sleep(int64 millis, int32 nanos)
  {
    if(scheduler_ == NULL) return;
    scheduler_->sleepCurrentTask(millis, nanos);
  }
  
  /**
   * Blocks current thread on given resource and yields the task.
   *
   * @param res pointer to resource.
   */  
  void Thread::block(api::Resource& res)
  {
    if(scheduler_ == NULL) return;
    scheduler_->blockCurrentTask(res);
  }

  /**
   * Returns the identifier of currently executing thread.
   *
   * @return thread identifier.
   */  
  int32 Thread::getCurrentThreadId()
  {
    if(scheduler_ == NULL) return 0;
    ThreadTask* task = scheduler_->currentTask();
    return task != NULL ? task->id() : 0;
  }  

  /**
   * Returns a pointer to the currently executing thread.
   *
   * @return the executable thread.
   */
  Thread* Thread::currentThread()
  {
    if(scheduler_ == NULL) return NULL;
    ThreadTask* task = scheduler_->currentTask();
    return task != NULL ? task->thread() : NULL;
  }

  /**
   * Yields to next thread.
   */
  void Thread::yield()
  {
    if(scheduler_ != NULL) scheduler_->yield();
  }
  
  /**
   * Returns this thread priority.
   *
   * @return priority value.
   */  
  int32 Thread::getPriority()
  {
    return isConstructed() ? task_->priority() : -1;
  }  
  
  /**
   * Sets this thread priority.
   *
   * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY].
   */  
  void Thread::setPriority(int32 priority)
  {
    if( isConstructed() ) task_->priority(priority);
  }
  
  /** 
   * Returns the switchable interface for global thread switch controlling.
   *
   * @return switchable interface.
   */ 
  api::Switchable& Thread::global()
  {
    if(scheduler_ == NULL) Core::fail();
    return *scheduler_;
  }
  
  
  /**
   * Running default method.
   */  
  void Thread::run()
  {
  }

  /**
   * Initiates an execution of threads.
   */  
  void Thread::execute()
  {
    if(scheduler_ != NULL) scheduler_->execute();
  }
  
  /**
   * Constructor of this class.
   */
  bool Thread::construct(api::Runnable* target)
  {
    if(!isConstructed()) return false;  
    if(!isConstructed(scheduler_)) return false;
    task_ = new ThreadTask(this, target, Core::config().threadStackSize);
    return isConstructed(task_) ? true : false;
  }
 
  /**
   * Initialization.
   *
   * @return true if no errors.
   */
  bool Thread::init()
  {
    int32 stage = 0;
    while(true)
    {
      // Stage 1
      stage++;
      scheduler_ = new ThreadScheduler();
      if(!isConstructed(scheduler_)) break;
      // Stage complete
      stage = 0;
      break;
    }
    switch(stage)
    {
      case  1: delete scheduler_; scheduler_ = NULL;
      default: return false;
      case  0: return true;
    }
  }
  
  /**
   * Deinitialization.
   */
  void Thread::deinit()
  {
    delete scheduler_;
    scheduler_ = NULL;    
  }  
}
