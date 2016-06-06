/** 
 * Hardware interrupt interface.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2015-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_INTERRUPT_HPP_
#define BOOS_API_INTERRUPT_HPP_

#include "boos.api.Switchable.hpp"

namespace api
{
  class Interrupt : public api::Switchable
  {

  public:
    
    /** 
     * Destructor.
     */                               
    virtual ~Interrupt(){}
    
    /**
     * Jumps to interrupt hardware vector.
     */      
    virtual void jump() = 0;
    
    /**
     * Clears an interrupt status of this source.
     */     
    virtual void clear() = 0;
    
    /**
     * Sets an interrupt status of this source.
     */    
    virtual void set() = 0;
    
    /**
     * Locks this interrupt source.
     *
     * @return an interrupt enable source bit value before method was called.
     */    
    virtual bool disable() = 0;
    
    /**
     * Unlocks this interrupt source.
     *
     * @param status returned status by lock method.
     */
    virtual void enable(bool status) = 0;
    
  };
}
#endif // BOOS_CORE_INTERRUPT_HPP_
