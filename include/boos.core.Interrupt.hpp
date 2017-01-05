/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_INTERRUPT_HPP_
#define BOOS_CORE_INTERRUPT_HPP_

#include "boos.core.Object.hpp"
#include "boos.core.InterruptTask.hpp"
#include "boos.api.Interrupt.hpp"

namespace target { class Interrupt; }

namespace core
{
  class Core;

  class Interrupt : public ::core::Object<>, public ::api::Interrupt
  {
    friend class Core;
    typedef ::core::Object<> Parent;

  public:
    
    /** 
     * Constructor.
     */    
    Interrupt();
    
    /** 
     * Constructor.
     *
     * @param handler user class which implements an interrupt handler interface.
     * @param source  available interrupt source.
     */     
    Interrupt(::api::Task& handler, int32 source);
    
    /** 
     * Destructor.
     */
    virtual ~Interrupt();
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const;
    
    /**
     * Jumps to interrupt hardware vector.
     */      
    virtual void jump();    
    
    /**
     * Clears an interrupt status of this source.
     */     
    virtual void clear();
    
    /**
     * Sets an interrupt status of this source.
     */    
    virtual void set();
    
    /**
     * Locks this interrupt source.
     *
     * @return an interrupt enable source bit value before method was called.
     */    
    virtual bool disable();
    
    /**
     * Unlocks this interrupt source.
     *
     * @param status returned status by lock method.
     */
    virtual void enable(bool status);

    /** 
     * Returns the switchable interface for controlling global interrupts.
     *
     * @return switchable interface.
     */
    static ::api::Switchable& global();
    
  protected:

    /** 
     * Returns extended core interface of interrupt.
     *
     * @return extended interface.
     */  
    ::target::Interrupt& extension();

  private:
    
    /**
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.   
     * @param source  available interrupt source.     
     * @return true if object has been constructed successfully.     
     */    
    bool construct(::api::Task* handler, int32 source);

    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    Interrupt(const Interrupt& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     */
    Interrupt& operator =(const Interrupt& obj);

    /**
     * Extended interrupt controller interface.
     */    
    ::target::Interrupt* target_;

  };
}
#endif // BOOS_CORE_INTERRUPT_HPP_
