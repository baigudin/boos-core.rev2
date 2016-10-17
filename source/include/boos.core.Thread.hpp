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

#include "boos.core.Object.hpp"
#include "boos.api.Runnable.hpp"
#include "boos.api.Resource.hpp"
#include "boos.api.Switchable.hpp"

namespace core
{
  class Scheduler;
  class SchedulerTask;  

  class Thread : public Object<>, public ::api::Runnable
  {
    friend class Core;
    typedef core::Object<> Parent;
    
  public:

    /** 
     * Thead priority constants.
     */
    static const int32  MAX_PRIORITY  = 10;
    static const int32  MIN_PRIORITY  = 1;
    static const int32  NORM_PRIORITY = 5;
   
    /** 
     * Constructor.
     */
    Thread();

    /** 
     * Constructor.
     *
     * @param target an interface whose run method is invoked when this thread is started.
     */
    Thread(::api::Runnable& target);
    
    /** 
     * Destructor.
     */
    virtual ~Thread();
    
    /**
     * Tests if this object is constructed.
     *
     * @return true if object is constructed successfully.
     */    
    virtual bool isConstructed() const;

    /**
     * Running default method.
     */  
    virtual void run();

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
    virtual int32 getPriority();
  
    /**
     * Sets this thread priority.
     *
     * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY].
     */  
    virtual void setPriority(int32 priority);

    /**
     * Returns the identifier of currently executing thread.
     *
     * @return thread identifier.
     */  
    static int32 getCurrentThreadId();

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
     * Returns a pointer to the currently executing thread.
     *
     * @return the executable thread.
     */
    static ::core::Thread* currentThread();

    /** 
     * Returns the switchable interface for global thread switch controlling.
     *
     * @return switchable interface.
     */ 
    static ::api::Switchable& global();
          
  private:
  
    /**
     * Constructor.
     *
     * @param target an interface whose run method is invoked when this thread is started.       
     */
    bool construct(::api::Runnable* target);  

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
    static int32 idCount_;      

    /**
     * Thread scheduler (no boot).
     */
    static Scheduler* scheduler_;

    /**
     * Current thread task.
     */    
    SchedulerTask* task_;

  };
}
#endif // BOOS_CORE_THREAD_HPP_
