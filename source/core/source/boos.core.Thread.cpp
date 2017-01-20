/**
 * Thread class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2015 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Thread.hpp"
#include "boos.core.Scheduler.hpp"
#include "boos.target.Register.hpp"
#include "boos.util.Stack.hpp"

namespace core
{
  /** 
   * Constructor.
   *
   * Constructs this thread as the task for executing.
   */
  Thread::Thread() : Parent(),
    target_   (NULL),
    block_    (NULL),
    register_ (NULL),
    stack_    (NULL),
    id_       (++idCount_),
    priority_ (0),
    sleep_    (0),
    status_   (NEW){    
    setConstruct( construct(this) );  
  }
  
  /** 
   * Constructor.
   *
   * @param target an task interface whose main method is invoked when this thread is started.
   */
  Thread::Thread(::api::Task& target) : Parent(),
    target_   (NULL),
    block_    (NULL),
    register_ (NULL),
    stack_    (NULL),
    id_       (++idCount_),
    priority_ (0),
    sleep_    (0),
    status_   (NEW){
    setConstruct( construct(&target) );  
  }
  
  /** 
   * Destructor.
   */
  Thread::~Thread()
  {
    if(!isConstructed()) return;
    scheduler_->remove(*this);
    delete stack_;    
    stack_ = NULL;
    delete register_;
    register_ = NULL;
  }
  
  /**
   * Tests if this object has been constructed.
   *
   * @return true if object has been constructed successfully.
   */    
  bool Thread::isConstructed() const
  {
    return this->Parent::isConstructed();
  }
  
  /**
   * Causes this thread to begin execution.
   */
  void Thread::start()
  {
    if(!isConstructed()) return;
    scheduler_->start(*this);
  }
  
  /**
   * Waits for this thread to die.
   */  
  void Thread::join()
  {
    if(!isConstructed()) return;
    scheduler_->join(*this);
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
    scheduler_->sleep(millis, nanos);
  }
  
  /**
   * Blocks current thread on given resource and yields the task.
   *
   * @param res pointer to resource.
   */  
  void Thread::block(::api::Resource& res)
  {
    if(scheduler_ == NULL) return;
    scheduler_->block(res);
  }

  /**
   * Returns a pointer to the currently executing thread.
   *
   * @return the executable thread.
   */
  Thread& Thread::currentThread()
  {
    if(scheduler_ == NULL) Core::fail();
    Thread* thread = scheduler_->currentTask();
    if(thread == NULL) Core::fail();
    return *thread;
  }

  /**
   * Yields to next thread.
   */
  void Thread::yield()
  {
    if(scheduler_ == NULL) return;
    scheduler_->jump();
  }
  
  /**
   * Returns this thread priority.
   *
   * @return priority value.
   */  
  int32 Thread::getPriority() const
  {
    return priority_;
  }  
  
  /**
   * Sets this thread priority.
   *
   * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY].
   */  
  void Thread::setPriority(int32 priority)
  {
    if(!isConstructed()) return;
    if(priority > MAX_PRIORITY) priority = MAX_PRIORITY;
    else if(priority < MIN_PRIORITY) priority = MIN_PRIORITY;
    else priority_ = priority;
  }
  
  /**
   * Returns the identifier of this thread.
   *
   * @return the thread identifier.
   */
  int64 Thread::getId()
  {
    return id_;
  }
  
  /** 
   * Returns the toggle interface for controlling global thread switch.
   *
   * @return toggle interface.
   */ 
  ::api::Toggle& Thread::global()
  {
    if(scheduler_ == NULL) Core::fail();
    return *scheduler_;
  }
  
  /**
   * The method with self context which will be executed by default.
   */  
  void Thread::main()
  {
  }  

  /**
   * Initiates an execution of threads.
   */  
  void Thread::execute()
  {
    if(scheduler_ == NULL) return;
    scheduler_->execute();
  }
  
  /**
   * Constructor.
   *
   * @param target an interface whose run method is invoked when this thread is started.   
   */
  bool Thread::construct(::api::Task* target)
  {
    if(!isConstructed()) return false;  
    if(scheduler_ == NULL || !scheduler_->isConstructed()) return false;
    if(idCount_ < 0) return false;
    if(!target->isConstructed()) return false;    
    const Thread* thread = scheduler_->currentTask();
    priority_ = thread != NULL ? thread->getPriority() : NORM_PRIORITY;
    // Set this thread CPU registers context 
    register_ = target::Register::create();
    if(register_ == NULL || !register_->isConstructed()) return false;
    // Set this thread stack context 
    stack_ = new ::util::Stack<int64>(::util::Stack<int64>::ED, target->stackSize() >> 3);
    if(stack_ == NULL || !stack_->isConstructed()) return false;
    target_ = target;
    return true;
  }
  
  /**
   * Initialization.
   *
   * @return true if no errors.
   */
  bool Thread::init()
  {
    int32 stage = 0;
    scheduler_ = NULL;
    idCount_ = 0;
    do{
      // Stage 1
      stage++;
      scheduler_ = new Scheduler();
      if(scheduler_ == NULL || !scheduler_->isConstructed()) break;
      // Stage complete
      stage = 0;
    }while(false);
    switch(stage)
    {
      default: return false;
      case  0: return true;
      case  1: delete scheduler_;
               scheduler_ = NULL;
               return false;
    }
  }
  
  /**
   * Deinitialization.
   */
  void Thread::deinit()
  {
    if(scheduler_ != NULL)
    {
      delete scheduler_;
      scheduler_ = NULL;    
    }
  }  
  
  /**
   * Thread scheduler (no boot).
   */
  Scheduler* Thread::scheduler_;
  
  /**
   * Counter of thread identifiers (no boot).
   */    
  int64 Thread::idCount_;  
}
