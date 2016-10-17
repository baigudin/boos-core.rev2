/** 
 * Hardware timer interface.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_EPI_TIMER_HPP_
#define BOOS_CORE_EPI_TIMER_HPP_

#include "boos.api.Timer.hpp"

namespace core
{
  namespace epi
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
       * @return available interrupt source.
       */  
      virtual int32 interrupSource() const = 0;

    };
  }
}
#endif // BOOS_CORE_EPI_TIMER_HPP_
