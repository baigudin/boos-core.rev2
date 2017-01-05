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

namespace target { class Timer; }

namespace core
{
  class Timer : public ::core::Object<>, public ::api::Timer
  {
    typedef ::core::Object<> Parent;

  public:

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
    Timer(int32 number);

    /** 
     * Destructor.
     */    
    virtual ~Timer();
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const;    
    
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
     * @param count timer counter register value.
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
     * @return number of this timer, or -1 if error has been occurred.
     */
    virtual int32 number() const;
    
  protected:

    /** 
     * Returns extended core interface of interrupt.
     *
     * @return extended interface.
     */  
    ::target::Timer& extension();

  private:
  
    /**
     * Constructor.
     *
     * @param number available timer number.
     * @return true if object has been constructed successfully.
     */
    bool construct(int32* number);
    
    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    Timer(const Timer& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     */
    Timer& operator =(const Timer& obj);

    /**
     * Extended timer controller interface.
     */    
    ::target::Timer* target_;
    
  };
}
#endif // BOOS_CORE_TIMER_HPP_
