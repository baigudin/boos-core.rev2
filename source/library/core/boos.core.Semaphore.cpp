/** 
 * Semaphore class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Semaphore.hpp"
#include "boos.core.Thread.hpp"
#include "boos.core.Interrupt.hpp"
#include "boos.core.Core.hpp"

namespace core
{
  typedef Interrupt Switch;

  /** 
   * Constructor.
   *
   * In this case the semaphore will be constructed as unfair.
   *
   * @param permits the initial number of permits available.
   */      
  Semaphore::Semaphore(int32 permits) :
    switch_  (Switch::global()),
    permits_ (permits),
    isFair_  (false){
    setConstruct( construct() );  
  }    
  
  /** 
   * Constructor.
   *
   * @param permits the initial number of permits available.      
   * @param fair true if this semaphore will guarantee FIFO granting of permits under contention.
   */      
  Semaphore::Semaphore(int32 permits, bool fair) :
    switch_  (Switch::global()),    
    permits_ (permits),
    isFair_  (fair){
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
   * Acquires a permit, blocking until one is available.
   *
   * @return true if the semaphore is acquired successfully.
   */  
  bool Semaphore::acquire()
  {
    return acquire(1);
  }    

  /**
   * Acquires the given number of permits.
   *
   * @param permits the number of permits to acquire.
   * @return true if the semaphore is acquired successfully.
   */  
  bool Semaphore::acquire(int32 permits)
  {
    if(!isConstructed()) return false;
    bool is = switch_.disable();
    Node node = Node(Thread::currentThread(), permits);
    // Check about free space in semaphore zone
    int32 count = permits_ - permits;
    // If count is available and no locked threads
    if(count >= 0 && list_.lock().length() == 0)
    {
      permits_ -= permits;
      if( isFair() ) list_.exec().add(node);
      // Go through sem to locked zone
      return switch_.enable(is, true);
    }
    // Block current thread on this semaphore
    list_.lock().add(node);
    Thread::block(*this);
    // This thread is unblock
    removeNode(list_.lock(), node);
    return switch_.enable(is, true);
  }    

  /**
   * Releases a permit.
   *
   * @return true if the semaphore is release successfully.
   */
  bool Semaphore::release()
  {
    return release(1);
  }    

  /**
   * Releases the given number of permits.
   *
   * @param permits the number of permits to release.
   * @return true if the semaphore is release successfully.
   */  
  bool Semaphore::release(int32 permits)
  {
    if(!isConstructed()) return false;
    bool is = switch_.disable();
    Node node = Node(Thread::currentThread(), permits);      
    bool res = isFair() ? removeNode(list_.exec(), node) : true;
    permits_ += permits;
    return switch_.enable(is, res);
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
   * Tests if this resource is blocked.
   *
   * @return true if this resource is blocked.
   */ 
  bool Semaphore::isBlocked()
  {
    if(!isConstructed()) return false;
    int32 permits, count;
    bool is = switch_.disable();
    Node cur = Node(Thread::currentThread(), 0);
    Node res = list_.lock().element();
    // Current thread is first in fifo
    if(cur != res) return switch_.enable(is, true); 
    // Check about free space in semaphore zone
    permits = res.permits();
    count = permits_ - permits;
    if(count < 0) return switch_.enable(is, true); 
    // Unblock thread
    permits_ -= permits;
    if(isFair_ == true) list_.exec().add( Node(Thread::currentThread(), permits) );
    return switch_.enable(is, false); 
  }
  
  /**
   * Removes last element from list.
   *
   * @param list reference to SemaphoreList class.
   * @param node reference to node.     
   */  
  bool Semaphore::removeNode(::api::Queue<Node>& list, Node& node)
  {
    while(true)
    {
      if(list.element() == node) return list.remove();
      Thread::yield();
    }      
  }      
  
  /**
   * Constructor.
   *
   * @return true if object has been constructed successfully.   
   */
  bool Semaphore::construct()
  {
    if(!isConstructed()) return false;      
    if(!list_.isConstructed()) return false;      
    return true;
  }
}
