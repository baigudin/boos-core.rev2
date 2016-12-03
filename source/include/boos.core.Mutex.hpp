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
  class Mutex : public Object<>, public ::api::Mutex
  {
    typedef core::Object<> Parent;    

  public:

    /** 
     * Constructor.
     */    
    Mutex() :
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
     *
     * @return true if the semaphore is unlock successfully.
     */      
    virtual bool unlock()
    {
      return sem_.release();         
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

    Semaphore                 sem_;

  };
}
#endif // BOOS_CORE_MUTEX_HPP_
