/** 
 * Hardware timer interrupt resource of core.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
namespace core
{
  class CoreTimerInterrupt : public TimerInterrupt, public api::InterruptHandler
  {

  public:

    /** 
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.
     */     
    CoreTimerInterrupt() : TimerInterrupt( reinterpret(this) ),
      timer_ (getTimer()),
      core_  (Core::config()),
      cnt_   (0),
      acc_   (0),
      time_  (0){
      setConstruct( construct() );
    }

    /** 
     * Destructor.
     */
    virtual ~CoreTimerInterrupt()
    {
    }
    
    /** 
     * Hardware interrupt handler.
     */      
    virtual void handler()
    {
      updateTime(timer_.getPeriod());
    }

    /**
     * Current value of the running system.
     *
     * @return time in nanoseconds.
     */  
    int64 nanoTime()
    {
      return isConstructed() ? updateTime(timer_.getCount()) : 0;
    }

  private:

    /**
     * Update system time.
     *
     * @param cnt CPU counter value.
     * @return updated current time in nanoseconds.
     */    
    int64 updateTime(uint32 cnt)
    {
      register int64 time, dc, dt;
      bool is = global().disable();
      // Set delta count it the value in timer clocks
      // which equals a time from previous updating.
      // This time in nanoseconds is a multiplying of
      // the value in timer clocks and system timer period.
      dc = cnt - cnt_;
      // Use a multiplying  on 1E+9 for getting a time in nsec
      // from timer frequency in hz
      acc_ = dc * 1000000000 + acc_;
      // The nanoseconds left time after previous updating
      dt = acc_ / core_.timerFrequency;
      // Increment core working time in nsec
      time = time_ += dt;
      // Store the remainder for next updating
      acc_ = acc_ - dt * core_.timerFrequency;
      // Store the timer counter value
      cnt_ = cnt;
      global().enable(is);               
      return time;
    } 

    /** 
     * Constructor.
     *
     * @return boolean result.
     */
    bool construct()
    {
      if(!isConstructed()) return false;
      timer_.setPeriod();
      if(timer_.getPeriod() != MAX_PERIOD) return false;
      timer_.setCount(0);
      timer_.start();
      enable(true);
      return true;
    }

    /**
     * Fixs a collision to call a TimerInterrupt constructor.
     *
     * Method gives to compiler an understanding about what should be called.
     * The parent constructor will called, just not a copy constructor.
     *
     * @param cls pointer to this class.
     * @return the reference to InterruptHandler interface of given class.
     */
    static api::InterruptHandler& reinterpret(CoreTimerInterrupt* cls)
    {
      return *cls;
    }

    static const int64        MAX_PERIOD = 0x00000000ffffffff;

    api::Timer&               timer_;
    CoreConfig                core_;
    uint32                    cnt_;
    uint64                    acc_;
    uint64                    time_;

  };
}
