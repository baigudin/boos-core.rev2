/** 
 * Target processor interrupts factory.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_INTERRUPT_HPP_
#define BOOS_TARGET_INTERRUPT_HPP_

#include "boos.api.Interrupt.hpp"
#include "boos.api.Task.hpp"
#include "boos.target.Register.hpp"

namespace target
{
  class Interrupt : public ::api::Interrupt
  {

  public:
  
    /** 
     * Destructor.
     */                               
    virtual ~Interrupt(){}
    
    /**
     * Sets interrupt source handler.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.
     * @param source  available interrupt source.
     * @return true if handler is set successfully.
     */      
    virtual bool setHandler(::api::Task& handler, int32 source) = 0;
    
    /**
     * Removes this interrupt source.
     */        
    virtual void removeHandler() = 0;
    
    /**
     * Resets registers context for storing to the default.
     * 
     * Method restores default registers for storing the CPU registers to it.
     * This method may be called in an user interrupt handler, it means
     * the default conxet will be restored by the context restore procedure.
     */
    virtual void resetRegister() = 0;
    
    /**
     * Sets new registers context for storing.
     * 
     * Method sets a new register context for storing the CPU registers to it.
     * This method may be called in an user interrupt handler, it means
     * given conxet will be restored by the context restore procedure.
     *
     * @param reg new registers context.
     */
    virtual void setRegister(::target::Register& reg) = 0;
  
    /**
     * Returns the interrupt interface of a target processor.
     *
     * @return target processor interrupt interface.
     */
    static ::target::Interrupt* create();
  
    /**
     * Returns the interrupt interface of a target processor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.
     * @param source  available interrupt source.     
     * @return target processor interrupt interface.
     */
    static ::target::Interrupt* create(::api::Task& handler, int32 source);
    
    /**
     * Disables all maskable interrupts.
     *
     * @return global interrupts enable bit value before method was called.
     */
    static bool globalDisable();
    
    /**
     * Enables all maskable interrupts.
     *
     * @param status the returned status by disable method.
     */
    static void globalEnable(bool status);
    
    /**
     * Enables all maskable interrupts.
     *
     * @param status the returned status by disable method.
     * @param ret    value which will be returned.     
     * @return given value.     
     */
    template<class Type>
    static inline bool globalEnable(bool status, Type ret)
    {
      globalEnable(status);
      return ret;   
    }    
    
  };
}
#endif // BOOS_TARGET_INTERRUPT_HPP_
