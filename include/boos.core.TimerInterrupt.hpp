/** 
 * Hardware timer interrupt resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_TIMER_INTERRUPT_HPP_
#define BOOS_CORE_TIMER_INTERRUPT_HPP_

#include "boos.core.Interrupt.hpp"
#include "boos.core.Timer.hpp"

namespace core
{
  class TimerInterrupt : public Interrupt, public Timer
  {
    typedef ::core::Interrupt Parent;
    typedef ::core::Interrupt ResInt;    
    typedef ::core::Timer     ResTim;
    
  public:

    /** 
     * Constructor.
     *
     * @param handler user class which implements an interrupt handler interface.
     */     
    TimerInterrupt(::api::Task& handler);

    /**
     * Constructor.
     *
     * @param handler user class which implements an interrupt handler interface.
     * @param number  available timer number for interrupting.
     */     
    TimerInterrupt(::api::Task& handler, int32 number);

    /** 
     * Destructor.
     */
    virtual ~TimerInterrupt();

    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const;
    
  protected:
  
    /** 
     * Constructor.
     */     
    TimerInterrupt();   
  
    /**
     * Sets the object constructed flag.
     *
     * @param flag constructed flag.
     */      
    virtual void setConstruct(bool flag);
    
  private:

    /**
     * Constructor.
     *
     * @param handler user class which implements an interrupt handler interface.
     * @return true if object has been constructed successfully.     
     */     
    bool construct(::api::Task* handler);    
    
    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    TimerInterrupt(const TimerInterrupt& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     * @return reference to this object.     
     */
    TimerInterrupt& operator =(const TimerInterrupt& obj);      

  };
}
#endif // BOOS_CORE_TIMER_INTERRUPT_HPP_
