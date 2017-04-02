/**
 * Mutex class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2015-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_MUTEX_HPP_
#define BOOS_CORE_MUTEX_HPP_

#include "boos.core.Object.hpp"
#include "boos.api.Mutex.hpp"
#include "boos.util.LinkedList.hpp"

namespace core
{  
  class Thread;
  
  class Mutex : public ::core::Object<>, public ::api::Mutex
  {
    typedef ::core::Object<> Parent;    

  public:

    /** 
     * Constructor.
     */    
    Mutex();

    /** 
     * Destructor.
     */      
    virtual ~Mutex();
        
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const;  
    
    /**
     * Locks the mutex.
     *
     * @return true if the mutex is lock successfully.
     */      
    virtual bool lock();
    
    /**
     * Unlocks the mutex.
     */      
    virtual void unlock();

    /** 
     * Tests if this resource is blocked.
     *
     * @return true if this resource is blocked.
     */ 
    virtual bool isBlocked();

  private:

    /**
     * Constructor.
     *
     * @return true if object has been constructed successfully.     
     */    
    bool construct();  
    
    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    Mutex(const Mutex& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     * @return reference to this object.     
     */
    Mutex& operator =(const Mutex& obj);      

    /**
     * The unlocked id.
     */
    static const int64 UNLOCKED_ID = -1;    

    /** 
     * Reference the root object constructed flag.
     */  
    const bool& isConstructed_; 
  
    /**
     * The identifier of locked thread.
     */
    int64 id_;
    
    /**
     * The mutex counter.
     */
    int32 count_;
    
    /** 
     * Queue of locked threads.
     */     
    ::util::LinkedList<Thread*> fifo_;    

  };
}
#endif // BOOS_CORE_MUTEX_HPP_
