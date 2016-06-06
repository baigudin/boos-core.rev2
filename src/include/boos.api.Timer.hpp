/** 
 * Hardware timer resource interface.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_TIMER_HPP_
#define BOOS_API_TIMER_HPP_

#include "boos.Types.hpp" 

namespace api
{
  class Timer
  {
    
  public:
  
    /** 
     * Destructor.
     */    
    virtual ~Timer(){}
    
    /**
     * Gets this timer counter.
     *
     * @return timer counter register value.   
     */      
    virtual int64 getCount() const = 0;
    
    /**
     * Gets this timer period.
     *
     * @return timer period register value.
     */      
    virtual int64 getPeriod() const = 0;
    
    /**
     * Sets this timer counter.
     *
     * @param count timer counter rerister value.
     */      
    virtual void setCount(int64 count) = 0;
    
    /**
     * Sets this timer period.
     *
     * @param us timer period in microseconds, zero value sets a period to maximum value.
     */      
    virtual void setPeriod(int64 us=0) = 0;
    
    /**
     * Starts this timer count.
     */      
    virtual void start() = 0;
    
    /**
     * Stops this timer count.
     */      
    virtual void stop() = 0;
    
  };
}
#endif // BOOS_API_TIMER_HPP_
