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
#include "boos.api.Interrupt.hpp"
#include "boos.api.InterruptHandler.hpp"

namespace core
{
  namespace epi { class Interrupt; }

  class Interrupt : public Object<>, public ::api::Interrupt
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
     * @param handler pointer to user class which implements an interrupt handler interface.
     * @param source  available interrupt source.
     */     
    Interrupt(::api::InterruptHandler& handler, int32 source);
    
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
     * Returns the switchable interface for global interrupt controlling.
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
    epi::Interrupt& extension();

  private:
    
    /**
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.   
     * @param source  available interrupt source.     
     * @return true if object has been constructed successfully.     
     */    
    bool construct(::api::InterruptHandler* handler, int32 source);
    
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    static bool init();

    /**
     * Deinitialization.
     */
    static void deinit();

    /**
     * Extended interrupt controller interface.
     */    
    epi::Interrupt* chip_;

  };
}
#endif // BOOS_CORE_INTERRUPT_HPP_
