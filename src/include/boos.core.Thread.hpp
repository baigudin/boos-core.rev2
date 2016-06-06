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
  class ThreadTask;
  class ThreadScheduler;

  class Thread : public Object<>, public api::Runnable
  {
    
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
    Thread(api::Runnable& target);
    
    /** 
     * Destructor.
     */
    virtual ~Thread();

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
    static void block(api::Resource& res);

    /**
     * Returns a pointer to the currently executing thread.
     *
     * @return the executable thread.
     */
    static Thread* currentThread();

    /** 
     * Returns the switchable interface for global thread switch controlling.
     *
     * @return switchable interface.
     */ 
    static api::Switchable& global();
          
  private:

    bool                      construct(api::Runnable* target);
    static bool               init();
    static void               deinit();
    static void               execute();

    static ThreadScheduler*   scheduler_;
    ThreadTask*               task_;

    friend class              Core;
  };
}
#endif // BOOS_CORE_THREAD_HPP_
