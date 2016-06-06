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

#include "boos.core.Timer.hpp"
#include "boos.core.Interrupt.hpp"

namespace core
{
  class TimerInterrupt : public Interrupt
  {

  public:

    /**
     * Available timer interrupt sources.
     */
    enum Source 
    {
      TINT0 = Interrupt::TINT0,
      TINT1 = Interrupt::TINT1,
      TINT2 = Interrupt::TINT2
    };

    /** 
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.
     */     
    TimerInterrupt(api::InterruptHandler& handler);

    /** 
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.
     * @param source  available timer interrupt source.
     */     
    TimerInterrupt(api::InterruptHandler& handler, Source source);

    /** 
     * Destructor.
     */
    virtual ~TimerInterrupt();

    /** 
     * Returns used hardware timer resource.
     *
     * @return hardware timer resource.
     */
    virtual api::Timer& getTimer();
    
  private:
      
    bool                      construct(api::InterruptHandler& handler);
    static Interrupt::Source  toInterruptSource(Timer::Number number);
    static Timer::Number      toTimerNumber(Source source);

    Timer                     timer_;

  };
}
#endif // BOOS_CORE_TIMER_INTERRUPT_HPP_
