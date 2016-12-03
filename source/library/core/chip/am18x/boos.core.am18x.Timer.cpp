/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.am18x.Timer.hpp"
#include "boos.core.am18x.Interrupt.hpp"
#include "boos.core.am18x.registers.TIMER.hpp"
#include "boos.core.am18x.registers.SYSCFG0.hpp"
#include "boos.core.am18x.registers.PLLC0.hpp"
#include "boos.core.am18x.registers.PLLC1.hpp"
#include "boos.core.Core.hpp" 
#include "boos.core.Interrupt.hpp"

namespace core
{
  namespace am18x
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
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
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
      if(!isConstructed()) return 0;
      uint64 prd;
      prd = reg_->prd34.value;
      prd = prd << 32;      
      prd = prd bitor reg_->prd12.value;
      return prd;
    }  
    
    /**
     * Sets this timer period.
     *
     * @param us timer period in microseconds, zero is set period to maxinum value.
     */      
    void Timer::setPeriod(int64 us)
    {
      if(!isConstructed()) return; 
      uint64 prd = us != 0 ? (us * internalClock()) / 1000000 : 0xffffffffffffffff;
      bool is = isStarted();
      if(is) stop();
      reg_->prd12.value = prd bitand 0xffffffff;
      prd = prd >> 32;       
      reg_->prd34.value = prd bitand 0xffffffff;
      if(is) start();
    }
    
    /**
     * Gets this timer counter.
     *
     * @return timer counter register value.   
     */      
    int64 Timer::getCount() const
    {
      if(!isConstructed()) return 0;
      uint64 cnt;
      cnt = reg_->tim34.value;
      cnt = cnt << 32;      
      cnt = cnt bitor reg_->tim12.value;
      return cnt;
    }
    
    /**
     * Sets this timer counter.
     *
     * @param count timer counter register value.
     */      
    void Timer::setCount(int64 count)
    {
      if(!isConstructed()) return;
      uint64 cnt = count;
      uint64 prd = getPeriod();
      if(cnt > prd) return;
      bool is = isStarted();
      if(is) stop();
      reg_->tim12.value = cnt bitand 0xffffffff;
      cnt = cnt >> 32;       
      reg_->tim34.value = cnt bitand 0xffffffff;
      if(is) start();
    }      
    
    /**
     * Starts this timer count.
     */        
    void Timer::start()
    {
      if(!isConstructed()) return;
      // The timer is enabled continuously
      reg_->tcr.bit.enamode12 = 2;
    }
        
    /**
     * Stops this timer count.
     */      
    void Timer::stop()
    {
      if(!isConstructed()) return;
      // The timer is disabled
      reg_->tcr.bit.enamode12 = 0;
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
      return 64;
    }
    
    /**
     * Returns this timer internal clock in Hz.
     *
     * @return timer internal clock.
     */  
    int64 Timer::internalClock() const
    {
      if(!isConstructed()) return 0;
      int64 oscin = ::core::Core::configuration().sourceClock;
      switch(number_)
      {
        case 0:
        case 1:        
        {
          // Internal clock for this timers is AUXCLK, which is OSCIN
          return oscin;
        }
        case 2:
        case 3:        
        {
          int64 prediv, pllm, postdiv, plldiv2;
          registers::SYSCFG0* syscfg0 = new (registers::SYSCFG0::ADDRESS) registers::SYSCFG0();
          // Get clocks from PLL0 SYSCLK2
          if(syscfg0->cfgchip3.bit.async3Clksrc == 0)
          {
            registers::PLLC0* pllc0 = new (registers::PLLC0::ADDRESS) registers::PLLC0();
            // PLL0 in normal mode
            if(pllc0->pllctl.bit.pllen == 1)
            {
              prediv = pllc0->prediv.bit.ratio + 1;
              pllm = pllc0->pllm.bit.pllm + 1;
              postdiv = pllc0->postdiv.bit.ratio + 1;
            }
            // PLL0 in bypassed mode
            else
            {
              prediv = 1;
              pllm = 1;
              postdiv = 1;
            }
            plldiv2 = pllc0->plldiv2.bit.ratio + 1;            
          }
          // Get clocks from PLL1 SYSCLK2
          else
          {
            registers::PLLC1* pllc1 = new (registers::PLLC1::ADDRESS) registers::PLLC1();
            // PLL1 in normal mode
            if(pllc1->pllctl.bit.pllen == 1)            
            {
              pllm = pllc1->pllm.bit.pllm + 1;
              postdiv = pllc1->postdiv.bit.ratio + 1;
            }
            // PLL1 in bypassed mode
            else
            {
              pllm = 1;
              postdiv = 1;
            }
            prediv = 1;
            plldiv2 = pllc1->plldiv2.bit.ratio + 1;
          }
          // Calculation
          int64 clock = oscin;
          clock = clock / prediv;
          clock = clock * pllm;
          clock = clock / postdiv;
          clock = clock / plldiv2;
          return clock;
        }
        default: return 0;        
      }
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
        case 0: return Interrupt::T64P0_TINT12;
        case 1: return Interrupt::T64P1_TINT12;
        case 2: return Interrupt::T64P2_ALL;
        case 3: return Interrupt::T64P3_ALL;        
      }
      return -1;
    }
    
    /**
     * Tests if this timer is counting.
     *
     * @return true if this timer is counting.
     */        
    bool Timer::isStarted()
    {
      return reg_->tcr.bit.enamode12 == 0 ? false : true;
    }    
    
    /** 
     * Constructor.
     *
     * @param number available timer number.
     * @return boolean result.
     */
    bool Timer::construct(int32 number)
    {
      uint32 addr = address(number);
      if(addr == 0) return false;
      bool is = switch_.disable();
      if(lock_[number] == true) return switch_.enable(is, false); 
      reg_ = new (addr) Regs();
      lock_[number] = true;
      number_ = number;
      reset(*reg_);
      // Set an internal clock as the selected clock source for the timer
      reg_->tcr.bit.clksrc12 = 0;
      // Enable the 64-Bit mode
      reg_->tgcr.bit.timmode = 0;
      reg_->tgcr.bit.tim12rs = 1;
      reg_->tgcr.bit.tim34rs = 1;
      return switch_.enable(is, true);
    }
    
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    bool Timer::init()
    {
      Regs* timer;    
      registers::SYSCFG0* syscfg0 = new (registers::SYSCFG0::ADDRESS) registers::SYSCFG0();
      // Unlock the SYSCFG module
      syscfg0->kick0r.bit.kick0 = 0x83E70B13;
      syscfg0->kick1r.bit.kick1 = 0x95A4F1E0;
      // Set emulation suspend sources for all timers
      syscfg0->suspsrc.bit.timer64p3src = 0;
      syscfg0->suspsrc.bit.timer64p2src = 0;
      syscfg0->suspsrc.bit.timer64p1src = 0;
      syscfg0->suspsrc.bit.timer64p0src = 0;
      for(int32 i=0; i<NUMBER_TIMERS; i++) 
      {
        lock_[i] = false;      
        timer = new ( address(i) ) Regs(); 
        reset(*timer);
      }
      // Lock the SYSCFG module
      syscfg0->kick0r.bit.kick0 = 0x00000000;
      syscfg0->kick1r.bit.kick1 = 0x00000000;        
      return true;
    }
    
    /**
     * Deinitialization.
     */
    void Timer::deinit()
    {
      for(int32 i=0; i<NUMBER_TIMERS; i++) 
      {
        Regs* reg = new ( address(i) ) Regs(); 
        reg->tcr.bit.enamode12 = 0;        
      }
    }
    
    /**
     * Resets timer registers.
     *
     * @param reg timer registers.
     */
    void Timer::reset(Regs& reg)
    {
      reg.emumgt.value = 0x00000000;
      reg.tcr.value = 0x00000000;        
      reg.tgcr.value = 0x00000000;            
      reg.prd12.value = 0x00000000;    
      reg.prd34.value = 0x00000000;        
      reg.tim12.value = 0x00000000;    
      reg.tim34.value = 0x00000000; 
    } 
    
    /**
     * Resets timer registers.
     *
     * @param number timer number.
     * @return memory address of given timer number.
     */
    int32 Timer::address(int32 number)
    {
      switch(number)
      {
        case 0: return registers::TIMER::ADDRESS0;
        case 1: return registers::TIMER::ADDRESS1;
        case 2: return registers::TIMER::ADDRESS2;
        case 3: return registers::TIMER::ADDRESS3;
        default: return 0;
      }
    }       
  }
}
