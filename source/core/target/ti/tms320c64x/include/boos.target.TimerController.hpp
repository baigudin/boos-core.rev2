/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_TIMER_CONTROLLER_HPP_
#define BOOS_TARGET_TIMER_CONTROLLER_HPP_

#include "boos.target.Core.hpp"
#include "boos.target.Object.hpp" 
#include "boos.target.Timer.hpp"
#include "boos.target.Configuration.hpp"
#include "boos.target.InterruptController.hpp"
#include "boos.target.registers.Timer.hpp"

namespace target
{
  class Core;
  
  class TimerController : public ::target::Object<>, public ::target::Timer
  {
    friend class Core;
    typedef ::target::Object<>  Parent;
    typedef InterruptController Controller;

  public:

    /** 
     * Constructor.
     */      
    TimerController() :
      toggle_ (Controller::global()),
      number_ (-1),
      reg_    (NULL){
      for(int32 i=0; i<NUMBER_TIMERS; i++) 
      {
        if( construct(i) == true )
        {
          setConstruct(true);
          return;
        }
      }
      setConstruct(false);
    }    
    
    /** 
     * Constructor.
     *
     * @param number available timer number.
     */
    TimerController(int32 number) : 
      toggle_ (Controller::global()),  
      number_ (-1),
      reg_    (NULL){
      setConstruct( construct(number) );
    }

    /** 
     * Destructor.
     */    
    virtual ~TimerController()
    {
      if(!isConstructed()) return;
      bool is = toggle_.disable();
      lock_[number_] = false;
      stop();
      reg_ = NULL;
      number_ = -1;      
      toggle_.enable(is);    
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
      return isConstructed() ? reg_->cnt.value : 0;
    }
    
    /**
     * Gets this timer period.
     *
     * @return timer period register value.
     */      
    virtual int64 getPeriod() const
    {
      return isConstructed() ? reg_->prd.value : 0;
    }  
    
    /**
     * Sets this timer counter.
     *
     * @param count timer counter register value.
     */      
    virtual void setCount(int64 count)
    {
      if(!isConstructed()) return;  
      uint32 reg = count & 0xffffffff;
      if(reg > reg_->prd.value) return;
      reg_->cnt.value = reg;    
    }      
    
    /**
     * Sets this timer period.
     *
     * @param us timer period in microseconds, zero sets the period to maxinum value.
     */      
    virtual void setPeriod(int64 us=0)
    {
      if(!isConstructed()) return;
      if(us == 0) 
      {
        reg_->prd.value = 0xffffffff;
      }
      else
      {
        int64 prd = (us * internalClock()) / 1000000;
        if( (prd & 0xffffffff00000000) == 0) reg_->prd.value = prd & 0xffffffff;
        else return setPeriod();
      }    
    }
    
    /**
     * Starts this timer count.
     */      
    virtual void start()
    {
      if(!isConstructed()) return;
      registers::Timer::CTL ctl = 0;
      ctl.bit.hld = 1;      
      ctl.bit.clksrc = 1;
      ctl.bit.spnd = 1;     
      ctl.bit.go = 1;
      reg_->ctl = ctl;    
    }
    
    /**
     * Stops this timer count.
     */      
    virtual void stop()
    {
      if(!isConstructed()) return;
      reg_->ctl.value = 0;     
    }

    /**
     * Returns this timer number.
     *
     * @return number of this timer, or -1 if error has been occurred.
     */      
    virtual int32 number() const
    {
      return number_; 
    }
    
    /**
     * Returns number of timer digits.
     *
     * @return timer digits.
     */  
    virtual int32 digits() const
    {
      return 32;
    }
    
    /**
     * Returns this timer internal clock in Hz.
     *
     * @return timer internal clock.
     */  
    virtual int64 internalClock() const
    {
      return config_->cpuClock / 8;    
    }    
    
    /**
     * Tests if this timer can interrupt a CPU.
     *
     * @return true if this source is polarizing.
     */  
    virtual bool isInterrupting() const
    {
      return true;
    }
    
    /**
     * Returns an available interrupt source for this timer.
     *
     * @return available interrupt source, or -1 if error has been occurred.
     */  
    virtual int32 interrupSource() const
    {
      switch(number_)
      {
        case 0: return InterruptController::TINT0;
        case 1: return InterruptController::TINT1;
        case 2: return InterruptController::TINT2;
      }
      return -1;
    }
    
  private:
  
    /** 
     * Constructor.
     *
     * @param number available timer number.
     * @return boolean result.
     */  
    bool construct(int32 number)
    {
      uint32 addr;
      bool is = toggle_.disable();
      switch(number)
      {
        case  0: addr = registers::Timer::TIMER0; break;
        case  1: addr = registers::Timer::TIMER1; break;
        case  2: addr = registers::Timer::TIMER2; break;
        default: return toggle_.enable(is, false);
      }    
      if(lock_[number] == true) return toggle_.enable(is, false); 
      reg_ = new (addr) registers::Timer();
      lock_[number] = true;
      number_ = number;
      return toggle_.enable(is, true);    
    }
    
    /**
     * Initialization.
     *
     * @param cfg the core configuration.
     * @return true if no errors.
     */
    static bool init(const Configuration& cfg)
    {
      config_ = &cfg;
      return resetRegs();
    }
    
    /**
     * Deinitialization.
     */
    static void deinit()
    {
      resetRegs();    
    }
    
    /**
     * Reset all HW registers.
     *
     * @return true if no errors.   
     */
    static bool resetRegs()
    {
      for(int32 i=0; i<NUMBER_TIMERS; i++) 
      {
        switch(i)
        {
          case  0: new (registers::Timer::TIMER0) registers::Timer(); break;
          case  1: new (registers::Timer::TIMER1) registers::Timer(); break;
          case  2: new (registers::Timer::TIMER2) registers::Timer(); break;
          default: return false;
        }
        lock_[i] = false;      
      } 
      return true;
    }    

    /**
     * Number of HW timers.
     */
    static const int32 NUMBER_TIMERS = 3;
    
    /**
     * The core configuration (no boot).
     */
    static const Configuration* config_;     
    
    /**
     * Locked by some object flag of each HW timer (no boot).
     */    
    static bool lock_[NUMBER_TIMERS];

    /**
     * Toggle interface for global interrupts.
     */
    ::api::Toggle& toggle_;
    
    /**
     * Number of hardware timer
     */
    int32 number_;
    
    /**
     * HW timet registers (no boot).
     */
    registers::Timer* reg_;        
  
  };
}
#endif // BOOS_TARGET_TIMER_CONTROLLER_HPP_
