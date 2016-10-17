/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.tms320c64x.Timer.hpp"
#include "boos.core.tms320c64x.Interrupt.hpp"
#include "boos.core.tms320c64x.registers.TIMER.hpp"
#include "boos.core.Core.hpp" 
#include "boos.core.Interrupt.hpp"

namespace core
{
  namespace tms320c64x
  {
    typedef Interrupt Switch;

    /**
     * Locked by some object flag of each HW timer (no boot).  
     */
    bool Timer::lock_[NUMBER_TIMERS];
    
    /** 
     * Constructor.
     *
     * Construct Timer object and alloc first free HW timer.
     */
    Timer::Timer() :
      switch_ (Switch::global()),
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
    Timer::Timer(int32 number) : 
      switch_ (Switch::global()),  
      number_ (-1),
      reg_    (NULL){
      setConstruct( construct(number) );
    }
    
    /** 
     * Destructor.
     */
    Timer::~Timer()
    {
      if(!isConstructed()) return;
      bool is = switch_.disable();
      lock_[number_] = false;
      stop();
      reg_ = NULL;
      number_ = -1;      
      switch_.enable(is);
    }
    
    /**
     * Tests if this object is constructed.
     *
     * @return true if object is constructed successfully.
     */    
    bool Timer::isConstructed() const
    {
      return this->Parent::isConstructed();
    } 
    
    /**
     * Gets this timer period.
     *
     * @return timer period register value.
     */      
    int64 Timer::getPeriod() const
    {
      return isConstructed() ? reg_->prd.value : 0;
    }  
    
    /**
     * Sets this timer period.
     *
     * @param us timer period in microseconds, zero is set period to maxinum value.
     */      
    void Timer::setPeriod(int64 us)
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
     * Gets this timer counter.
     *
     * @return timer counter register value.   
     */      
    int64 Timer::getCount() const
    {
      return isConstructed() ? reg_->cnt.value : 0;
    }
    
    /**
     * Sets this timer counter.
     *
     * @param count timer counter register value.
     */      
    void Timer::setCount(int64 count)
    {
      if(!isConstructed()) return;  
      uint32 reg = count & 0xffffffff;
      if(reg > reg_->prd.value) return;
      reg_->cnt.value = reg;
    }      
    
    /**
     * Starts this timer count.
     */        
    void Timer::start()
    {
      if(!isConstructed()) return;
      registers::TIMER::CTL ctl = 0;
      ctl.bit.hld = 1;      
      ctl.bit.clksrc = 1;
      ctl.bit.spnd = 1;     
      ctl.bit.go = 1;
      reg_->ctl = ctl;
    }
        
    /**
     * Stops this timer count.
     */      
    void Timer::stop()
    {
      if(!isConstructed()) return;
      reg_->ctl.value = 0;      
    }
    
    /**
     * Returns this timer number.
     *
     * @return number of this timer.
     */      
    int32 Timer::number() const
    {
      return number_;      
    }
    
    /**
     * Returns number of timer digits.
     *
     * @return timer digits.
     */  
    int32 Timer::digits() const
    {
      return 32;
    }
    
    /**
     * Returns this timer internal clock in Hz.
     *
     * @return timer internal clock.
     */  
    int64 Timer::internalClock() const
    {
      return ::core::Core::configuration().cpuClock / 8;
    }
    
    /**
     * Tests if this timer can interrupt a CPU.
     *
     * @return true if this source is polarizing.
     */  
    bool Timer::isInterrupting() const
    {
      return true;
    }
    
    /**
     * Returns an available interrupt source for this timer.
     *
     * @return available interrupt source.
     */  
    int32 Timer::interrupSource() const
    {
      switch(number_)
      {
        case 0: return Interrupt::TINT0;
        case 1: return Interrupt::TINT1;
        case 2: return Interrupt::TINT2;
      }
      return -1;
    }
    
    
    /** 
     * Constructor.
     *
     * @param number available timer number.
     * @return boolean result.
     */
    bool Timer::construct(int32 number)
    {
      uint32 addr;
      bool is = switch_.disable();
      switch(number)
      {
        case  0: addr = Regs::TIMER0; break;
        case  1: addr = Regs::TIMER1; break;
        case  2: addr = Regs::TIMER2; break;
        default: return switch_.enable(is, false);
      }    
      if(lock_[number] == true) return switch_.enable(is, false); 
      reg_ = new (addr) Regs();
      lock_[number] = true;
      number_ = number;
      return switch_.enable(is, true);
    }
    
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    bool Timer::init()
    {
      return resetRegs();
    }
    
    /**
     * Deinitialization.
     */
    void Timer::deinit()
    {
      resetRegs();
    } 
  
    /**
     * Reset all HW registers.
     *
     * @return true if no errors.   
     */
    bool Timer::resetRegs()
    {
      for(int32 i=0; i<NUMBER_TIMERS; i++) 
      {
        switch(i)
        {
          case  0: new (Regs::TIMER0) Regs(); break;
          case  1: new (Regs::TIMER1) Regs(); break;
          case  2: new (Regs::TIMER2) Regs(); break;
          default: return false;
        }
        lock_[i] = false;      
      } 
      return true;
    }
  }
}
