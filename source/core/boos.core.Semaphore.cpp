/** 
 * Semaphore class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Semaphore.hpp"
#include "boos.core.Thread.hpp"
#include "boos.core.Interrupt.hpp"

namespace core
{
  /** 
   * Constructor.
   *
   * In this case the semaphore will be constructed as unfair.
   *
   * @param permits the initial number of permits available.
   */      
  Semaphore::Semaphore(int32 permits) : Parent(),
    toggle_  (Interrupt::global()),
    permits_ (permits),
    isFair_  (false),    
    fifo_    (NULL){
    setConstruct( construct() );  
  }    
  
  /** 
   * Constructor.
   *
   * @param permits the initial number of permits available.      
   * @param fair true if this semaphore will guarantee FIFO granting of permits under contention.
   */      
  Semaphore::Semaphore(int32 permits, bool fair) : Parent(),
    toggle_  (Interrupt::global()),    
    permits_ (permits),
    isFair_  (fair),
    fifo_    (NULL){
    setConstruct( construct() );  
  }

  /** 
   * Destructor.
   */
  Semaphore::~Semaphore()
  {
  }
  
  /**
   * Tests if this object has been constructed.
   *
   * @return true if object has been constructed successfully.
   */    
  bool Semaphore::isConstructed() const
  {
    return this->Parent::isConstructed();
  }

  /**
   * Acquires one permit from this semaphore.
   *
   * @return true if the semaphore is acquired successfully.
   */
  bool Semaphore::acquire()
  {
    return acquire(1);
  }

  /**
   * Acquires the given number of permits from this semaphore.
   *
   * @param permits the number of permits to acquire.
   * @return true if the semaphore is acquired successfully.
   */   
  bool Semaphore::acquire(int32 permits)
  {
    bool res, is;  
    if(!isConstructed()) return false;
    is = toggle_.disable();
    switch(isFair_)
    {
      case  true: res = acquireFair(permits); break;
      case false: res = acquireUnfair(permits); break;
    }
    return toggle_.enable(is, res);
  }
  
  /**
   * Fairly acquires the given number of permits from this semaphore.
   *
   * @param permits the number of permits to acquire.
   * @return true if the semaphore is acquired successfully.
   */  
  bool Semaphore::acquireFair(int32 permits)
  {
    // The first checking for acquiring available permits of the semaphore
    if( permits_ - permits >= 0 && fifo_.isEmpty() )
    {
      // Decrement the number of available permits
      permits_ -= permits;
      // Go through the semaphore to critical section
      return true;      
    }
    Thread* thread = &Thread::currentThread();
    // Add current thread to the queue tail
    if( fifo_.add(thread) == false ) return false;      
    while(true)
    {
      // Block current thread on the semaphore and switch to another thread
      Thread::block(*this);
      // Test if head thread is current thread
      if(fifo_.element() != thread) continue;
      // Test available permits for no breaking the fifo queue by removing
      if(permits_ - permits < 0) continue;
      // Decrement the number of available permits
      permits_ -= permits;        
      // Remove head thread
      return fifo_.remove();
    }
  }    
  
  /**
   * Unfairly acquires the given number of permits from this semaphore.
   *
   * @param permits the number of permits to acquire.
   * @return true if the semaphore is acquired successfully.
   */  
  bool Semaphore::acquireUnfair(int32 permits)
  {
    while(true)
    {
      // Check about available permits in the semaphoring critical section
      if( permits_ - permits >= 0 )
      {
        // Decrement the number of available permits
        permits_ -= permits;
        // Go through the semaphore to critical section
        return true;
      }
      // Block current thread on the semaphore and switch to another thread
      Thread::block(*this);      
    }  
  }    

  /**
   * Releases one permit.
   *
   * @return true if the semaphore is released successfully.
   */
  bool Semaphore::release()
  {
    return release(1);
  }    

  /**
   * Releases the given number of permits.
   *
   * @param permits the number of permits to release.
   * @return true if the semaphore is released successfully.
   */  
  bool Semaphore::release(int32 permits)
  {
    if(!isConstructed()) return false;
    bool is = toggle_.disable();
    // Increment the number of available permits    
    permits_ += permits;
    // Signal the semaphore has released permits
    return toggle_.enable(is, true);
  }  
  
  /** 
   * Tests if this resource is blocked.
   *
   * @return true if this resource is blocked.
   */ 
  bool Semaphore::isBlocked()
  {
    if(!isConstructed()) return false;
    bool is = toggle_.disable();
    bool res = permits_ > 0 ? false : true;
    return toggle_.enable(is, res);
  }
  
  /**
   * Tests if this semaphore is fair.
   *
   * @return true if this semaphore has fairness set true.
   */  
  bool Semaphore::isFair() const
  {
    return isFair_;
  }
  
  /**
   * Constructor.
   *
   * @return true if object has been constructed successfully.   
   */
  bool Semaphore::construct()
  {
    if(!isConstructed()) return false;      
    if(!fifo_.isConstructed()) return false;      
    return true;
  }
}
