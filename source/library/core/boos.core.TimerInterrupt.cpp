/** 
 * Hardware timer interrupt resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2015 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.TimerInterrupt.hpp"
#include "boos.core.epi.Interrupt.hpp" 
#include "boos.core.epi.Timer.hpp"

namespace core
{
  /** 
   * Constructor.
   *
   * @param handler user class which implements an interrupt handler interface.
   */     
  TimerInterrupt::TimerInterrupt(::api::InterruptHandler& handler) : 
    Interrupt (),
    Timer     (){
    setConstruct( construct(handler) );
  }

  /**
   * Constructor.
   *
   * @param handler user class which implements an interrupt handler interface.
   * @param number  available timer number for interrupting.
   */     
  TimerInterrupt::TimerInterrupt(::api::InterruptHandler& handler, int32 number) : 
    Interrupt (),
    Timer     (number){
    setConstruct( construct(handler) );    
  }

  /**
   * Destructor.
   */
  TimerInterrupt::~TimerInterrupt()
  {
  }
  
  /**
   * Constructor.
   *
   * @param handler user class which implements an interrupt handler interface.
   * @return true if object has been constructed successfully.     
   */     
  bool TimerInterrupt::construct(::api::InterruptHandler& handler)
  {
    if(!isConstructed()) return false;
    if(!ResTim::extension().isInterrupting()) return false;
    return ResInt::extension().setHandler(handler, ResTim::extension().interrupSource());
  }
  
  /**
   * Tests if this object has been constructed.
   *
   * @return true if object has been constructed successfully.
   */    
  bool TimerInterrupt::isConstructed() const  
  {
    if(!ResInt::isConstructed()) return false;
    if(!ResTim::isConstructed()) return false;    
    return true;
  }
  
  /**
   * Sets the object constructed flag.
   *
   * @param flag constructed flag.
   */      
  void TimerInterrupt::setConstruct(bool flag)
  {
    ResInt::setConstruct(flag);
    ResTim::setConstruct(flag);    
  }  
}
