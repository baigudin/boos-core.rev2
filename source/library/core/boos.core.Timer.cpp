/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Core.hpp" 
#include "boos.core.Timer.hpp"
#include "boos.core.chip.Timer.hpp"

namespace core
{
  /** 
   * Constructor.
   *
   * Construct Timer object and alloc first free HW timer.
   */
  Timer::Timer() :
    chip_ (NULL){
    setConstruct( construct(NULL) );    
  }

  /** 
   * Constructor.
   *
   * @param available timer number.
   */
  Timer::Timer(int32 number) : 
    chip_ (NULL){
    setConstruct( construct(&number) );
  }
  
  /** 
   * Destructor.
   */
  Timer::~Timer()
  {
    delete chip_;
  }
  
  /**
   * Constructor.
   *
   * @param number available timer number.
   * @return true if object has been constructed successfully.
   */
  bool Timer::construct(int32* number)
  {
    if(!isConstructed()) return false;
    chip::Timer* chip = number != NULL ? new chip::Timer(*number) : new chip::Timer();
    chip_ = chip;
    return isObject<chip::Timer>(chip);
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
    return isConstructed() ? chip_->getPeriod() : 0;
  }  
  
  /**
   * Sets this timer period.
   *
   * @param us timer period in microseconds, zero is set period to maxinum value.
   */      
  void Timer::setPeriod(int64 us)
  {
    if( isConstructed() ) chip_->setPeriod(us);  
  }
  
  /**
   * Gets this timer counter.
   *
   * @return timer counter register value.   
   */      
  int64 Timer::getCount() const
  {
    return isConstructed() ? chip_->getCount() : 0;
  }
  
  /**
   * Sets this timer counter.
   *
   * @param count timer counter register value.
   */      
  void Timer::setCount(int64 count)
  {
    if( isConstructed() ) chip_->setCount(count);  
  }      
  
  /**
   * Starts this timer count.
   */        
  void Timer::start()
  {
    if( isConstructed() ) chip_->start();  
  }
      
  /**
   * Stops this timer count.
   */      
  void Timer::stop()
  {
    if( isConstructed() ) chip_->stop();  
  }
  
  /**
   * Returns this timer number.
   *
   * @return number of this timer, or -1 if error is occured.
   */
  int32 Timer::number() const
  {
    return isConstructed() ? chip_->number() : -1;
  }
  
  /** 
   * Returns timer developing interface.
   *
   * @return timer core developing interface.
   */  
  epi::Timer& Timer::extension()
  {
    if(!isConstructed()) Core::fail();
    return *chip_;
  }
  
  /**
   * Initialization.
   *
   * @return true if no errors.
   */
  bool Timer::init()
  {
    return chip::Timer::init();
  }
  
  /**
   * Deinitialization.
   */
  void Timer::deinit()
  {
    chip::Timer::deinit();
  } 
 
}
