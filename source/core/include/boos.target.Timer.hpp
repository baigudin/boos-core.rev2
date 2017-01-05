/** 
 * Target processor timers factory. 
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_TIMER_HPP_
#define BOOS_TARGET_TIMER_HPP_

#include "boos.api.Timer.hpp"

namespace target
{
  class Timer : public ::api::Timer
  {
  
  public:
  
    /** 
     * Destructor.
     */                               
    virtual ~Timer(){}
    
    /**
     * Returns number of timer digits.
     *
     * @return timer digits.
     */  
    virtual int32 digits() const = 0;
    
    /**
     * Returns this timer internal clock in Hz.
     *
     * @return timer internal clock.
     */  
    virtual int64 internalClock() const = 0;      
    
    /**
     * Tests if this timer can interrupt a CPU.
     *
     * @return true if this source is polarizing.
     */  
    virtual bool isInterrupting() const = 0;
    
    /**
     * Returns an available interrupt source for this timer.
     *
     * @return available interrupt source, or -1 if error has been occurred.
     */  
    virtual int32 interrupSource() const = 0;

    /**
     * Returns the timer interface of a target processor.
     *
     * Constructs this object and allocs a first free hardware timer.
     *       
     * @return target processor timer interface, or NULL if error has been occurred.
     */
    static ::target::Timer* create();
        
    /**
     * Returns the timer interface of a target processor.
     *
     * @param number available timer number.
     * @return target processor timer interface, or NULL if error has been occurred.
     */
    static ::target::Timer* create(int32 number);
    
  };
}
#endif // BOOS_TARGET_TIMER_HPP_
