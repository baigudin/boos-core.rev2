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

#include "boos.target.Object.hpp" 
#include "boos.target.Timer.hpp" 

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
     */      
    TimerController() 
    {
    }  
    
    /** 
     * Constructor.
     *
     * @param number available timer number.
     */
    TimerController(int32 number)
    {
    }

    /** 
     * Destructor.
     */    
    virtual ~TimerController()
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
     * @return number of this timer, or -1 if error has been occurred.
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
     * Returns this timer internal clock in Hz.
     *
     * @return timer internal clock.
     */  
    virtual int64 internalClock() const
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
      return true;
    }
    
    /**
     * Returns an available interrupt source for this timer.
     *
     * @return available interrupt source, or -1 if error has been occurred.
     */  
    virtual int32 interrupSource() const
    {
      return -1;
    }
    
  private:
    
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    static bool init()
    {
      return true;
    }
    
    /**
     * Deinitialization.
     */
    static void deinit()
    {
    }    
  
  };
}
#endif // BOOS_TARGET_TIMER_CONTROLLER_HPP_
