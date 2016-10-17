/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_TMS320C64X_TIMER_HPP_
#define BOOS_CORE_TMS320C64X_TIMER_HPP_

#include "boos.core.Object.hpp" 
#include "boos.core.epi.Timer.hpp" 
#include "boos.api.Switchable.hpp" 

namespace core
{
  class Timer;

  namespace tms320c64x
  {
    namespace registers
    {
      struct TIMER;
    }
    
    class Timer : public ::core::Object<>, public ::core::epi::Timer
    {
      friend class ::core::Timer;
      typedef ::core::Object<> Parent;
      typedef registers::TIMER Regs;

    public:

      /** 
       * Constructor.
       *
       * Constructs this object and allocs a first free hardware timer.
       */      
      Timer();
      
      /** 
       * Constructor.
       *
       * @param number available timer number.
       */
      Timer(int32 number);

      /** 
       * Destructor.
       */    
      virtual ~Timer();
      
      /**
       * Tests if this object is constructed.
       *
       * @return true if object is constructed successfully.
       */    
      virtual bool isConstructed() const;    
      
      /**
       * Gets this timer counter.
       *
       * @return timer counter register value.   
       */      
      virtual int64 getCount() const;
      
      /**
       * Gets this timer period.
       *
       * @return timer period register value.
       */      
      virtual int64 getPeriod() const;
      
      /**
       * Sets this timer counter.
       *
       * @param count timer counter register value.
       */      
      virtual void setCount(int64 count);
      
      /**
       * Sets this timer period.
       *
       * @param us timer period in microseconds, zero sets the period to maxinum value.
       */      
      virtual void setPeriod(int64 us=0);
      
      /**
       * Starts this timer count.
       */      
      virtual void start();
      
      /**
       * Stops this timer count.
       */      
      virtual void stop();

      /**
       * Returns this timer number.
       *
       * @return number of this timer.
       */      
      virtual int32 number() const;
      
      /**
       * Returns number of timer digits.
       *
       * @return timer digits.
       */  
      virtual int32 digits() const;
      
      /**
       * Returns this timer internal clock in Hz.
       *
       * @return timer internal clock.
       */  
      virtual int64 internalClock() const;
      
      /**
       * Tests if this timer can interrupt a CPU.
       *
       * @return true if this source is polarizing.
       */  
      virtual bool isInterrupting() const;
      
      /**
       * Returns an available interrupt source for this timer.
       *
       * @return available interrupt source.
       */  
      virtual int32 interrupSource() const;

    private:

      /** 
       * Constructor.
       *
       * @param number available timer number.
       * @return boolean result.
       */  
      bool construct(int32 number);
      
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
       * Reset all HW registers.
       *
       * @return true if no errors.   
       */
      static bool resetRegs();

      /**
       * Number of HW timers.
       */
      static const int32 NUMBER_TIMERS = 3;
      
      /**
       * Locked by some object flag of each HW timer (no boot).
       */    
      static bool lock_[NUMBER_TIMERS];

      /**
       * Switchable interface for global interrupts.
       */
      ::api::Switchable& switch_;
      
      /**
       * Number of hardware timer
       */
      int32 number_;
      
      /**
       * HW timet registers (no boot).
       */
      Regs* reg_;
      
    };
  }
}
#endif // BOOS_CORE_TMS320C64X_TIMER_HPP_
