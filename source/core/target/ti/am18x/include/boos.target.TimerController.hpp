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

#include "boos.target.Configuration.hpp"
#include "boos.target.Object.hpp" 
#include "boos.target.Timer.hpp" 
#include "boos.target.InterruptController.hpp"
#include "boos.target.registers.Timer.hpp"
#include "boos.target.registers.Syscfg0.hpp"
#include "boos.target.registers.Pllc0.hpp"
#include "boos.target.registers.Pllc1.hpp"

namespace target
{
  class Core;
  
  class TimerController : public ::target::Object<>, public ::target::Timer
  {
    friend class Core;
    typedef ::target::Object<> Parent;

  public:

    /** 
     * Constructor.
     *
     * Constructs this object and allocs a first free hardware timer.
     */      
    TimerController() : Parent(),
      switch_ (Interrupt::global()),
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
    TimerController(int32 number) : Parent(),
      switch_ (Interrupt::global()),  
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
      if(!isConstructed()) return 0;
      uint64 cnt;
      cnt = reg_->tim34.value;
      cnt = cnt << 32;      
      cnt = cnt bitor reg_->tim12.value;
      return cnt;
    }
    
    /**
     * Gets this timer period.
     *
     * @return timer period register value.
     */      
    virtual int64 getPeriod() const
    {
      if(!isConstructed()) return 0;
      uint64 prd;
      prd = reg_->prd34.value;
      prd = prd << 32;      
      prd = prd bitor reg_->prd12.value;
      return prd;
    }  
    
    /**
     * Sets this timer counter.
     *
     * @param count timer counter register value.
     */      
    virtual void setCount(int64 count)
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
     * Sets this timer period.
     *
     * @param us timer period in microseconds, zero sets the period to maxinum value.
     */      
    virtual void setPeriod(int64 us=0)
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
     * Starts this timer count.
     */      
    virtual void start()
    {
      if(!isConstructed()) return;
      // The timer is enabled continuously
      reg_->tcr.bit.enamode12 = 2;
    }
    
    /**
     * Stops this timer count.
     */      
    virtual void stop()
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
      return 64;
    }
    
    /**
     * Returns this timer internal clock in Hz.
     *
     * @return timer internal clock.
     */  
    virtual int64 internalClock() const
    {
      if(!isConstructed()) return 0;
      int64 oscin = config_->sourceClock;
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
          registers::Syscfg0* syscfg0 = new (registers::Syscfg0::ADDRESS) registers::Syscfg0();
          // Get clocks from PLL0 SYSCLK2
          if(syscfg0->cfgchip3.bit.async3Clksrc == 0)
          {
            registers::Pllc0* pllc0 = new (registers::Pllc0::ADDRESS) registers::Pllc0();
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
            registers::Pllc1* pllc1 = new (registers::Pllc1::ADDRESS) registers::Pllc1();
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
    virtual bool isInterrupting() const
    {
      return true;
    }
    
    /**
     * Returns an available interrupt source for this timer.
     *
     * @return available interrupt source.
     */  
    virtual int32 interrupSource() const
    {
      switch(number_)
      {
        case 0: return InterruptController::T64P0_TINT12;
        case 1: return InterruptController::T64P1_TINT12;
        case 2: return InterruptController::T64P2_ALL;
        case 3: return InterruptController::T64P3_ALL;        
      }
      return -1;
    }
    
  private:
    
    /**
     * Initialization.
     *
     * @param cfg the core configuration.
     * @return true if no errors.
     */
    static bool init(const Configuration& cfg)
    {
      config_ = &cfg;    
      registers::Timer* timer;    
      registers::Syscfg0* syscfg0 = new (registers::Syscfg0::ADDRESS) registers::Syscfg0();
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
        timer = new ( address(i) ) registers::Timer(); 
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
    static void deinit()
    {
      for(int32 i=0; i<NUMBER_TIMERS; i++) 
      {
        registers::Timer* reg = new ( address(i) ) registers::Timer(); 
        reg->tcr.bit.enamode12 = 0;        
      }
    }
  
    /** 
     * Constructor.
     *
     * @param number available timer number.
     * @return boolean result.
     */  
    bool construct(int32 number)
    {
      if(!isConstructed()) return false;
      uint32 addr = address(number);
      if(addr == 0) return false;
      bool is = switch_.disable();
      if(lock_[number] == true) return switch_.enable(is, false); 
      reg_ = new (addr) registers::Timer();
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
     * Tests if this timer is counting.
     *
     * @return true if this timer is counting.
     */        
    bool isStarted()
    {
      return reg_->tcr.bit.enamode12 == 0 ? false : true;
    }    
    
    /**
     * Resets timer registers.
     *
     * @param reg timer registers.
     */
    static void reset(registers::Timer& reg)
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
    static int32 address(int32 number)
    {
      switch(number)
      {
        case 0: return registers::Timer::ADDRESS0;
        case 1: return registers::Timer::ADDRESS1;
        case 2: return registers::Timer::ADDRESS2;
        case 3: return registers::Timer::ADDRESS3;
        default: return 0;
      }
    }
    
    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    TimerController(const TimerController& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     */
    TimerController& operator =(const TimerController& obj);

    /**
     * Timers number.
     */
    static const int32 NUMBER_TIMERS = 4;
    
    /**
     * The core configuration (no boot).
     */
    static const Configuration* config_;    
    
    /**
     * Locked by some object flag of each HW timer (no boot).
     */    
    static bool lock_[NUMBER_TIMERS];
    
    /**
     * Switchable interface of global interrupts.
     */
    ::api::Switchable& switch_;
    
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
