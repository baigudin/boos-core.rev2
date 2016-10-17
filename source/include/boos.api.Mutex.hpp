/**
 * Mutex semaphore interface.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2015-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_MUTEX_HPP_
#define BOOS_API_MUTEX_HPP_

#include "boos.api.Resource.hpp"

namespace api
{  
  class Mutex : public Resource
  {

  public:
  
    /** 
     * Destructor.
     */
    virtual ~Mutex(){}

    /**
     * Locks this mutex.
     *
     * @return true if this mutex is locked successfully.
     */
    virtual bool lock() = 0;

    /**
     * Unlocks this mutex.
     *
     * @return true if this mutex is unlocked successfully.       
     */
    virtual bool unlock() = 0;   

    /**
     * Unlocks this mutex.       
     *
     * @param value a value which will be returned.
     * @return given argument value.
     */
    template<typename Type> 
    Type unlock(Type value)
    {
      unlock();
      return value;
    }

  };
}
#endif // BOOS_API_MUTEX_HPP_
