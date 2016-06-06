/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2015 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Core.hpp" 
#include "boos.core.Interrupt.hpp"
#include "boos.core.Timer.hpp"

namespace core
{
  typedef Interrupt Switch;
  
  bool  Timer::lock_[NUMBER_TIMERS] = {false, false, false};
  
  /** 
   * Constructor.
   *
   * Construct Timer object and alloc first free HW timer.
   */
  Timer::Timer() :
    switch_ (Switch::global()),
    number_ (TIM0),
    reg_    (NULL){
    for(int32 i=0; i<NUMBER_TIMERS; i++) 
    {
      Number number;
      switch(i)
      {
        case  0: number = TIM0; break;
        case  1: number = TIM1; break;
        case  2: number = TIM2; break;
        default: setConstruct(false); return;
      }
      if( construct(number) == false ) continue;
      setConstruct(true);
      return;
    }
    setConstruct(false);
  }  

  /** 
   * Constructor.
   *
     * @param available timer number.
   */
  Timer::Timer(Number number) : 
    switch_ (Switch::global()),  
    number_ (TIM0),
    reg_    (NULL){
    setConstruct( construct(number) );
  }
  
  /** 
   * Constructor.
   *
   * @param number available timer number.
   * @return boolean result.
   */
  bool Timer::construct(Number number)
  {
    int32 num;
    bool is = switch_.disable();
    switch(number)
    {
      case  TIM0: num = 0; break;
      case  TIM1: num = 1; break;
      case  TIM2: num = 2; break;
      default: return switch_.enable(is, true);
    }    
    if(lock_[num] == true) return switch_.enable(is, false); 
    reg_ = new (number) Reg();
    lock_[num] = true;
    number_ = number;
    return switch_.enable(is, true);
  }  

  /** 
   * Destructor.
   */
  Timer::~Timer()
  {
    if(!isConstructed()) return;
    bool is = switch_.disable();
    int32 num;
    switch(number_)
    {
      case  TIM0: num = 0; break;
      case  TIM1: num = 1; break;
      case  TIM2: num = 2; break;
      default: switch_.enable(is); return;
    }
    lock_[num] = false;
    reg_->reset();    
    reg_ = NULL;
    switch_.enable(is);
  }
  
  /**
   * Gets this timer period.
   *
   * @return timer period register value.
   */      
  int64 Timer::getPeriod() const
  {
    return isConstructed() ? reg_->prd : 0;
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
      reg_->prd = 0xffffffff;
    }
    else
    {
      int64 prd = (us * Core::config().timerFrequency) / 1000000;
      if( (prd & 0xffffffff00000000) == 0) reg_->prd = prd & 0xffffffff;
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
    return isConstructed() ? reg_->cnt : 0;
  }
  
  /**
   * Sets this timer counter.
   *
   * @param count timer counter rerister value.
   */      
  void Timer::setCount(int64 count)
  {
    if(!isConstructed()) return;  
    uint32 reg = count & 0xffffffff;
    if(reg > reg_->prd) return;
    reg_->cnt = reg;
  }      
  
  /**
   * Starts this timer count.
   */        
  void Timer::start()
  {
    if(isConstructed()) reg_->ctl = TCTL_SPND | TCTL_CLKSRC | TCTL_HLD | TCTL_GO;
  }
      
  /**
   * Stops this timer count.
   */      
  void Timer::stop()
  {
    if(isConstructed()) reg_->ctl = TCTL_SPND | TCTL_CLKSRC;
  }
  
  /**
   * Returns this timer number.
   *
   * @return number of this timer.
   */      
  Timer::Number Timer::number() const
  {
    return number_;
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
        case  0: new (TIM0) Reg(); break;
        case  1: new (TIM1) Reg(); break;
        case  2: new (TIM2) Reg(); break;
        default: return false;
      }
    } 
    return true;
  }
}
