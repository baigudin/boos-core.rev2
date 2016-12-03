/** 
 * Core chip timers definitions.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_CHIP_TIMER_HPP_
#define BOOS_CORE_CHIP_TIMER_HPP_

/**
 * Texas Instruments TMS320C64x Digital Signal Processors family.
 */
#ifdef  BS_TMS320C64X
#ifndef BS_CHIP_TIMER
#define BS_CHIP_TIMER
#include "../chip/tms320c64x/boos.core.tms320c64x.Timer.hpp"
namespace core { namespace chip = tms320c64x; }
#endif
#endif

/**
 * Texas Instruments AM18X ARM Microprocessors family.
 */
#ifdef  BS_AM18X
#ifndef BS_CHIP_TIMER
#define BS_CHIP_TIMER
#include "../chip/am18x/boos.core.am18x.Timer.hpp"
namespace core { namespace chip = am18x; }
#endif
#endif

/**
 * Abstract chip timer.
 */
#ifndef BS_CHIP_TIMER
#include "boos.core.Object.hpp" 
#include "boos.core.epi.Timer.hpp" 
namespace core
{
  class Timer;
  
  namespace chip
  {
    class Timer : public ::core::Object<>, public ::core::epi::Timer
    {
      friend class ::core::Timer;
      typedef ::core::Object<> Parent;

    public:

      /** 
       * Constructor.
       *
       * Constructs this object and allocs a first free hardware timer.
       */      
      Timer(){
        setConstruct( construct() );      
      }
      
      /** 
       * Constructor.
       *
       * @param number available timer number.
       */
      Timer(int32 number){
        setConstruct( construct() );      
      }

      /** 
       * Destructor.
       */    
      virtual ~Timer()
      {
      }
      
      /**
       * Tests if this object has been constructed.
       *
       * @return true if object has been constructed successfully.
       */    
      virtual bool isConstructed() const
      {
        return this->Parent::isConstructed();
      }
      
      /**
       * Gets this timer counter.
       *
       * @return timer counter register value.   
       */      
      virtual int64 getCount() const
      {
        return 0;
      }
      
      /**
       * Gets this timer period.
       *
       * @return timer period register value.
       */      
      virtual int64 getPeriod() const
      {
        return 0;
      }
      
      /**
       * Sets this timer counter.
       *
       * @param count timer counter register value.
       */      
      virtual void setCount(int64 count)
      {
      }
      
      /**
       * Sets this timer period.
       *
       * @param us timer period in microseconds, zero sets the period to maxinum value.
       */      
      virtual void setPeriod(int64 us=0)
      {
      }
      
      /**
       * Starts this timer count.
       */      
      virtual void start()
      {
      }
      
      /**
       * Stops this timer count.
       */      
      virtual void stop()
      {
      }

      /**
       * Returns this timer number.
       *
       * @return number of this timer, or -1 if error is occured.
       */      
      virtual int32 number() const
      {
        return -1;
      }
      
      /**
       * Returns number of timer digits.
       *
       * @return timer digits.
       */  
      virtual int32 digits() const
      {
        return 0;
      }
      
      /**
       * Tests if this timer can interrupt a CPU.
       *
       * @return true if this source is polarizing.
       */  
      virtual bool isInterrupting() const
      {
        return false;
      }
      
      /**
       * Returns this timer internal clock in Hz.
       *
       * @return timer internal clock.
       */  
      virtual int64 internalClock() const
      {
        return 0;
      }
      
      /**
       * Returns an available interrupt source for this timer.
       *
       * @return available interrupt source.
       */  
      virtual int32 interrupSource() const
      {
        return -1;
      }

    private:
      
      /** 
       * Constructor.
       *
       * @return boolean result.
       */  
      bool construct()
      {
        return false;
      }
      
      /**
       * Initialization.
       *
       * @return true if no errors.
       */
      static bool init()
      {
        return false;
      }

      /**
       * Deinitialization.
       */
      static void deinit()
      {
      }      

    };
  }
}
#endif // BS_CHIP_TIMER
#endif // BOOS_CORE_CHIP_TIMER_HPP_
