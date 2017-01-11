/** 
 * Escalator class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Escalator.hpp"
#include "boos.core.Thread.hpp"
#include "boos.core.Interrupt.hpp"

namespace core
{
  /** 
   * Constructor.
   *
   * In this case the escalator will be constructed as unfair.
   *
   * @param permits the initial number of permits available.
   */      
  Escalator::Escalator(int32 permits) : Parent(),
    toggle_  (Interrupt::global()),
    permits_ (permits),
    isFair_  (false),
    list_    (){
    setConstruct( construct() );  
  }    
  
  /** 
   * Constructor.
   *
   * @param permits the initial number of permits available.      
   * @param fair true if this escalator will guarantee FIFO granting of permits under contention.
   */      
  Escalator::Escalator(int32 permits, bool fair) : Parent(),
    toggle_  (Interrupt::global()),    
    permits_ (permits),
    isFair_  (fair),
    list_    (){
    setConstruct( construct() );  
  }

  /** 
   * Destructor.
   */
  Escalator::~Escalator()
  {
  }
  
  /**
   * Tests if this object has been constructed.
   *
   * @return true if object has been constructed successfully.
   */    
  bool Escalator::isConstructed() const
  {
    return this->Parent::isConstructed();
  }

  /**
   * Acquires one permit from this escalator.
   *
   * @return true if the escalator is acquired successfully.
   */
  bool Escalator::acquire()
  {
    return acquire(1);
  }    

  /**
   * Acquires the given number of permits from this escalator.
   *
   * @param permits the number of permits to acquire.
   * @return true if the escalator is acquired successfully.
   */   
  bool Escalator::acquire(int32 permits)
  {
    bool res, is;  
    if(!isConstructed()) return false;
    is = toggle_.disable();
    Node node(Thread::currentThread(), permits);
    // Check about available space in the semaphoring critical section
    if( permits_ - permits >= 0 && list_.lock.isEmpty() )
    {
      // Add current thread to the executing queue
      res = isFair_ ? list_.exec.add(node) : true;
      // Decrement the number of available permits
      if(res == true) permits_ -= permits;
      // Go through the escalator to critical section
      return toggle_.enable(is, res);      
    }
    // Add current thread to the locking queue
    res = list_.lock.add(node);
    if(res == true)
    {
      // Block current thread on the escalator and switch to another thread
      Thread::block(*this);
      // This thread is unblocked by the scheduler called isBlocked method 
      res = removeNode(list_.lock, node);
    }
    // Go through the escalator to critical section
    return toggle_.enable(is, res);      
  }    

  /**
   * Releases one permit.
   *
   * @return true if the escalator is released successfully.
   */
  bool Escalator::release()
  {
    return release(1);
  }    

  /**
   * Releases the given number of permits.
   *
   * @param permits the number of permits to release.
   * @return true if the escalator is released successfully.
   */  
  bool Escalator::release(int32 permits)
  {
    bool res, is;
    if(!isConstructed()) return false;
    is = toggle_.disable();
    Node node(Thread::currentThread(), permits);
    // Remove current thread from executing list    
    res = isFair_ ? removeNode(list_.exec, node) : true;
    // Increment the number of available permits    
    if(res == true) permits_ += permits;
    // Signal the escalator has released permits
    return toggle_.enable(is, res);
  }  
  
  /** 
   * Tests if this resource is blocked.
   *
   * @return true if this resource is blocked.
   */ 
  bool Escalator::isBlocked()
  {
    if(!isConstructed()) return false;
    bool is = toggle_.disable();
    Node cur(Thread::currentThread(), 0);
    Node res = list_.lock.element();
    // Test if current thread is the first in FIFO
    if(cur != res) return toggle_.enable(is, true);
    // Check about free permits of escalator
    if(permits_ - res.permits < 0) return toggle_.enable(is, true);
    // Unblock thread
    permits_ -= res.permits;
    if(isFair_ == true) list_.exec.add( Node(Thread::currentThread(), res.permits) );
    return toggle_.enable(is, false);    
  }
  
  /**
   * Tests if this escalator is fair.
   *
   * @return true if this escalator has fairness set true.
   */  
  bool Escalator::isFair() const
  {
    return isFair_;
  }
  
  /**
   * Removes last element from list.
   *
   * @param list reference to SemaphoreList class.
   * @param node reference to node.     
   */  
  bool Escalator::removeNode(::api::Queue<Node>& list, Node& node)
  {
    while(true)
    {
      // Remove the head thread if it given thread of the node
      if(list.element() == node) return list.remove();
      Thread::yield();
    }      
  }      
  
  /**
   * Constructor.
   *
   * @return true if object has been constructed successfully.   
   */
  bool Escalator::construct()
  {
    if(!isConstructed()) return false;      
    if(!list_.isConstructed()) return false;      
    return true;
  }
}
