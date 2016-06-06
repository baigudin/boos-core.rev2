/** 
 * Hardware timer interrupt resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2015 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.TimerInterrupt.hpp"

namespace core
{
  /** 
   * Constructor.
   *
   * @param handler pointer to user class which implements an interrupt handler interface.
   */     
  TimerInterrupt::TimerInterrupt(api::InterruptHandler& handler) : Interrupt(),
    timer_    (){
    setConstruct( construct(handler) );
  }

  /**
   * Constructor.
   *
   * @param handler pointer to user class which implements an interrupt handler interface.   
   * @param source  available timer interrupt source.
   */
  TimerInterrupt::TimerInterrupt(api::InterruptHandler& handler, Source source) : Interrupt (),
    timer_    ( toTimerNumber(source) ){
    setConstruct( construct(handler) );
  }

  /**
   * Destructor.
   */
  TimerInterrupt::~TimerInterrupt()
  {
  }
  
  /**
   * Constructor of this class.
   */
  bool TimerInterrupt::construct(api::InterruptHandler& handler)
  {
    if(!isConstructed()) return false;  
    if(!timer_.isConstructed()) return false;
	return setHandler( toInterruptSource( timer_.number() ), handler );
  }
  
  /**
   * Returns used hardware timer resource.
   *
   * @return hardware timer resource.
   */
  api::Timer& TimerInterrupt::getTimer()
  {
    return timer_;
  }
  
  /**
   * Returns available interrupt source.
   *
   * @param source available timer number.
   * @return available interrupt source.
   */
  Interrupt::Source TimerInterrupt::toInterruptSource(Timer::Number number)
  {
    switch(number)
    {
      default:
      case Timer::TIM0: return Interrupt::TINT0;
      case Timer::TIM1: return Interrupt::TINT1;
      case Timer::TIM2: return Interrupt::TINT2;
    }
  }
  
  /**
   * Returns available timer number.
   *
   * @param source available timer interrupt source.
   * @return available timer number.
   */
  Timer::Number TimerInterrupt::toTimerNumber(Source source)
  {
    switch(source)
    {
      default:
      case TINT0: return Timer::TIM0;
      case TINT1: return Timer::TIM1;
      case TINT2: return Timer::TIM2;
    }  
  }
}
