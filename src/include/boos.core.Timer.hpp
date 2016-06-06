/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_TIMER_HPP_
#define BOOS_CORE_TIMER_HPP_

#include "boos.core.Object.hpp" 
#include "boos.api.Timer.hpp" 
#include "boos.api.Switchable.hpp" 

namespace core
{
  class Timer : public Object<>, public api::Timer
  {

  public:
  
    /**
     * Available timer numders.
     */
    enum Number
    {
      TIM0  = 0x01940000,
      TIM1  = 0x01980000,
      TIM2  = 0x01ac0000
    };

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
    Timer(Number number);

    /** 
     * Destructor.
     */    
    virtual ~Timer();
    
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
     * @param count timer counter rerister value.
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
    virtual Number number() const;

  private:
  
    bool                      construct(Number number);
    static bool               init();
    static void               deinit();
    static bool               resetRegs();    

    struct Reg
    {
      Reg(){
        reset();
      }

      void reset()
      {
        ctl = 0;
        prd = 0;
        cnt = 0;
      }

      void* operator new(uint32, Number ptr)
      {
        return reinterpret_cast<void*>(ptr);
      }

      uint32                  ctl;
      uint32                  prd;
      uint32                  cnt;
    };                        

    static const uint32       NUMBER_TIMERS = 3;

    static const uint32       TCTL_FUNC   = 0x00000001;
    static const uint32       TCTL_INVOUT = 0x00000002;
    static const uint32       TCTL_DATOUT = 0x00000004;
    static const uint32       TCTL_DATIN  = 0x00000008;
    static const uint32       TCTL_PWID   = 0x00000010;
    static const uint32       TCTL_GO     = 0x00000040;
    static const uint32       TCTL_HLD    = 0x00000080;
    static const uint32       TCTL_CP     = 0x00000100;
    static const uint32       TCTL_CLKSRC = 0x00000200;
    static const uint32       TCTL_INVINP = 0x00000400;
    static const uint32       TCTL_TSTAT  = 0x00000800;
    static const uint32       TCTL_SPND   = 0x00008000;

    api::Switchable&          switch_;
    Number                    number_;              // Hardware number of timer
    Reg*                      reg_;                 // HW register addresses
    static bool               lock_[NUMBER_TIMERS]; // Timer is locked by some object

    friend class              Core;
  };
}
#endif // BOOS_CORE_TIMER_HPP_
