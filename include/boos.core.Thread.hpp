/**
 * Thread class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_THREAD_HPP_
#define BOOS_CORE_THREAD_HPP_

#include "boos.core.ThreadTask.hpp"
#include "boos.api.Stack.hpp"
#include "boos.api.Resource.hpp"
#include "boos.api.Switchable.hpp"

namespace target { class Register; }

namespace core
{
  class Core;
  class Scheduler;

  class Thread : public ::core::ThreadTask
  {
    friend class ::core::Core;
    friend class ::core::Scheduler;
    typedef ::core::ThreadTask Parent;
    
  public:

    /** 
     * Thead priority constants.
     */
    static const int32 MAX_PRIORITY  = 10;
    static const int32 MIN_PRIORITY  = 1;
    static const int32 NORM_PRIORITY = 5;
    
    /** 
     * Constructor.
     *
     * Constructs this thread as the task for executing.
     */
    Thread();

    /** 
     * Constructor.
     *
     * @param target an task interface whose main method is invoked when this thread is started.
     */
    Thread(::api::Task& target);
    
    /** 
     * Destructor.
     */
    virtual ~Thread();
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const;

    /**
     * Waits for this thread to die.
     */  
    virtual void join();

    /**
     * Causes this thread to begin execution.
     */
    virtual void start();

    /**
     * Returns this thread priority.
     *
     * @return priority value.
     */  
    virtual int32 getPriority() const;
  
    /**
     * Sets this thread priority.
     *
     * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY].
     */  
    virtual void setPriority(int32 priority);
    
    /**
     * Returns the identifier of this thread.
     *
     * @return the thread identifier.
     */
    virtual int64 getId();
    
    /**
     * The method with self context which will be executed by default.
     */  
    virtual void main();

    /**
     * Causes the currently executing thread to sleep.
     *
     * @param millis a time to sleep in milliseconds.
     * @param nanos  an additional nanoseconds to sleep.
     */  
    static void sleep(int64 millis, int32 nanos=0);

    /**
     * Yields to next thread.
     */
    static void yield();

    /**
     * Blocks current thread on given resource and yields the task.
     *
     * @param res reference to resource.
     */  
    static void block(::api::Resource& res);

    /**
     * Returns the currently executing thread.
     *
     * @return the executable thread.
     */
    static ::core::Thread& currentThread();

    /** 
     * Returns the switchable interface for controlling global thread switch.
     *
     * @return switchable interface.
     */ 
    static ::api::Switchable& global();
          
  private:
  
    /** 
     * Thread available statuses.
     */
    enum Status
    {
      NEW      = 0,
      RUNNABLE = 1,
      RUNNING  = 2,
      WAITING  = 3,
      BLOCKED  = 4,
      SLEEPING = 5,
      DEAD     = 6
    };
  
    /**
     * Constructor.
     *
     * @param target an interface whose run method is invoked when this thread is started.       
     */
    bool construct(::api::Task* target);

    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    static bool init();

    /**
     * Deinitialization.
     */
    static void deinit();

    /**
     * Initiates an execution of threads.
     */
    static void execute();
    
    /**
     * Counter of thread identifiers (no boot).
     */    
    static int64 idCount_;

    /**
     * Thread scheduler (no boot).
     */
    static Scheduler* scheduler_;
    
    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    Thread(const Thread& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     */
    Thread& operator =(const Thread& obj);

    /**
     * User executing runnable interface.
     */        
    ::api::Task* target_;
    
    /**
     * Given blocked resource.
     */        
    ::api::Resource* block_;
    
    /**
     * CPU state registers.
     */        
    ::target::Register* register_;
    
    /**
     * Thread stack.
     */        
    ::api::Stack<int64>* stack_;
    
    /**
     * Current identifier.
     */        
    int64 id_;
    
    /**
     * Current priority.
     */        
    int32 priority_;
    
    /**
     * Wake up time in nanoseconds.
     */        
    int64 sleep_;    
    
    /**
     * Current status.
     */        
    Status status_;

  };
}
#endif // BOOS_CORE_THREAD_HPP_
