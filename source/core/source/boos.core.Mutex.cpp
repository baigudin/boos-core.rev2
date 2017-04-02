/** 
 * Mutex class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Mutex.hpp"
#include "boos.core.Thread.hpp"
#include "boos.target.Interrupt.hpp"

namespace core
{
  typedef ::target::Interrupt Int;

  /** 
   * Constructor.
   */    
  Mutex::Mutex() : Parent(),
    isConstructed_ (getConstruct()),
    id_            (UNLOCKED_ID),
    count_         (1),
    fifo_          (NULL){    
    setConstruct( construct() );    
  }

  /** 
   * Destructor.
   */      
  Mutex::~Mutex()
  {
  }
      
  /**
   * Tests if this object has been constructed.
   *
   * @return true if object has been constructed successfully.
   */    
  bool Mutex::isConstructed() const
  {
    return isConstructed_;  
  }
  
  /**
   * Locks the mutex.
   *
   * @return true if the mutex is lock successfully.
   */      
  bool Mutex::lock()
  {
    if(!isConstructed_) return false;
    bool is = Int::globalDisable();
    // The first checking for acquiring available permits of the mutex
    if( count_ - 1 >= 0 && fifo_.isEmpty() )
    {
      // Decrement the number of available permits
      count_ -= 1;
      // Go through the mutex to critical section
      return Int::globalEnable(is, true);      
    }
    Thread* thread = &Thread::currentThread();
    // Add current thread to the queue tail
    if( fifo_.add(thread) == false ) return Int::globalEnable(is, false);
    while(true)
    {
      // Block current thread on the mutex and switch to another thread
      Thread::block(*this);
      // Test if head thread is current thread
      if(fifo_.element() != thread) continue;
      // Test available permits for no breaking the fifo queue by removing
      if(count_ - 1 < 0) continue;
      // Decrement the number of available permits
      count_ -= 1;        
      // Remove head thread
      return Int::globalEnable( is, fifo_.remove() );
    }    
  }
  
  /**
   * Unlocks the mutex.
   */      
  void Mutex::unlock()
  {
    if(!isConstructed_) return;
    bool is = Int::globalDisable();
    count_ += 1;
    Int::globalEnable(is);  
  }

  /** 
   * Tests if this resource is blocked.
   *
   * @return true if this resource is blocked.
   */ 
  bool Mutex::isBlocked()
  {
    if(!isConstructed_) return false;
    bool is = Int::globalDisable();
    bool res = count_ > 0 ? false : true;
    return Int::globalEnable(is, res);  
  }
  
  /**
   * Constructor.
   *
   * @return true if object has been constructed successfully.   
   */
  bool Mutex::construct()
  {
    if(!isConstructed_) return false;
    return true;
  }
}
