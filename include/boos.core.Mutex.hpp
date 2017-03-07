/**
 * Mutex semaphore class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2015-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_MUTEX_HPP_
#define BOOS_CORE_MUTEX_HPP_

#include "boos.core.Semaphore.hpp"
#include "boos.api.Mutex.hpp"

namespace core
{  
  class Mutex : public ::core::Object<>, public ::api::Mutex
  {
    typedef ::core::Object<> Parent;    

  public:

    /** 
     * Constructor.
     */    
    Mutex() : Parent(),
      sem_(1){
      setConstruct( sem_.isConstructed() );
    }

    
    /** 
     * Destructor.
     */      
    virtual ~Mutex()
    {
    }
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const
    {
      return this->Parent::isConstructed();
    }    
    
    /**
     * Lock mutex.
     *
     * @return true if the semaphore is lock successfully.
     */      
    virtual bool lock()
    {
      return sem_.acquire();
    }
    
    /**
     * Unlock mutex.
     */      
    virtual void unlock()
    {
      sem_.release();         
    }

    /** 
     * Tests if this resource is blocked.
     *
     * @return true if this resource is blocked.
     */ 
    virtual bool isBlocked()
    {
      return sem_.isBlocked();
    }

  private:
    
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
     */
    Mutex& operator =(const Mutex& obj);      
  
    /**
     * Semaphore resource.
     */
    Semaphore sem_;

  };
}
#endif // BOOS_CORE_MUTEX_HPP_
