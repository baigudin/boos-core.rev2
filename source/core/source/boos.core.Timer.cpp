/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Timer.hpp"
#include "boos.target.Timer.hpp"
#include "boos.target.System.hpp" 

namespace core
{
  /** 
   * Constructor.
   *
   * Construct Timer object and alloc first free HW timer.
   */
  Timer::Timer() : Parent(),
    target_ (NULL){
    setConstruct( construct(NULL) );    
  }

  /** 
   * Constructor.
   *
   * @param available timer number.
   */
  Timer::Timer(int32 number) : Parent(),
    target_ (NULL){
    setConstruct( construct(&number) );
  }
  
  /** 
   * Destructor.
   */
  Timer::~Timer()
  {
    delete target_;
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
    if(number != NULL) 
      target_ = ::target::Timer::create(*number);
    else 
      target_ = ::target::Timer::create();
    return target_ != NULL ? target_->isConstructed() : false;
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
    return isConstructed() ? target_->getPeriod() : 0;
  }  
  
  /**
   * Sets this timer period.
   *
   * @param us timer period in microseconds, zero is set period to maxinum value.
   */      
  void Timer::setPeriod(int64 us)
  {
    if( isConstructed() ) target_->setPeriod(us);  
  }
  
  /**
   * Gets this timer counter.
   *
   * @return timer counter register value.   
   */      
  int64 Timer::getCount() const
  {
    return isConstructed() ? target_->getCount() : 0;
  }
  
  /**
   * Sets this timer counter.
   *
   * @param count timer counter register value.
   */      
  void Timer::setCount(int64 count)
  {
    if( isConstructed() ) target_->setCount(count);  
  }      
  
  /**
   * Starts this timer count.
   */        
  void Timer::start()
  {
    if( isConstructed() ) target_->start();  
  }
      
  /**
   * Stops this timer count.
   */      
  void Timer::stop()
  {
    if( isConstructed() ) target_->stop();  
  }
  
  /**
   * Returns this timer number.
   *
   * @return number of this timer, or -1 if error has been occurred.
   */
  int32 Timer::number() const
  {
    return isConstructed() ? target_->number() : -1;
  }
  
  /** 
   * Returns timer developing interface.
   *
   * @return timer kernel developing interface.
   */  
  ::target::Timer& Timer::extension()
  {
    if(!isConstructed()) ::target::System::fail();
    return *target_;
  }
}
