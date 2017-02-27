/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_INTERRUPT_CONTROLLER_HPP_
#define BOOS_TARGET_INTERRUPT_CONTROLLER_HPP_

#include "boos.target.Object.hpp"
#include "boos.target.Interrupt.hpp"
#include "boos.target.Configuration.hpp"
#include "boos.util.Stack.hpp"

namespace target
{
  class Main;
  
  class InterruptController : public ::target::Object<>, public ::target::Interrupt
  {
    friend class Main;
    typedef ::target::Object<> Parent;

  public:
  
    /** 
     * Constructor.
     */    
    InterruptController() : Parent(),
      handler_ (NULL),
      source_  (-1),
      reg_     (NULL),
      ie_      (false){
    }

    /** 
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.
     * @param source  available interrupt source.
     */     
    InterruptController(::api::Task& handler, int32 source) : Parent(),
      handler_ (&handler),
      source_  (source),
      reg_     (NULL),
      ie_      (false){
    }

    /** 
     * Destructor.
     */
    virtual ~InterruptController()
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
     * Jumps to interrupt hardware vector.
     */      
    virtual void jump()
    {
    }
    
    /**
     * Clears an interrupt status of this source.
     */     
    virtual void clear()
    {
    }
    
    /**
     * Sets an interrupt status of this source.
     */    
    virtual void set()
    {
    }  
    
    /**
     * Locks this interrupt source.
     *
     * @return an interrupt enable source bit value before method was called.
     */    
    virtual bool disable()
    {
      return false;
    }
    
    /**
     * Unlocks this interrupt source.
     *
     * @param status returned status by lock method.
     */
    virtual void enable(bool status)
    {
      ie_ = status;
    }
    
    /**
     * Sets interrupt source handler.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.
     * @param source  available interrupt source.
     * @return true if handler is set successfully.
     */      
    virtual bool setHandler(::api::Task& handler, int32 source)
    {
      handler_ = &handler;
      source_ = source;
      return false;
    }

    /**
     * Removes this interrupt source.
     */        
    virtual void removeHandler()
    {
    }
    
    /**
     * Resets registers context for storing to the default.
     */
    virtual void resetRegister()
    {
    }
    
    /**
     * Sets new registers context for storing.
     *
     * @param reg new registers context.
     */
    virtual void setRegister(::target::Register& reg)
    {
      reg_ = &reg;
    }
    
    /**
     * Disables all maskable interrupts.
     *
     * @return global interrupts enable bit value before method was called.
     */
    static bool globalDisable();

    /**
     * Enables all maskable interrupts.
     *
     * @param status the returned status by disable method.
     */
    static void globalEnable(bool status);
    
  private:    
    
    /**
     * Initialization.
     *
     * @param config the kernel configuration.
     * @return true if no errors.
     */
    static bool init(const Configuration& config)
    {
      config_ = &config;
      return true;
    }
    
    /**
     * Deinitialization.
     */
    static void deinit()
    {
    }

    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    InterruptController(const InterruptController& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     */
    InterruptController& operator =(const InterruptController& obj);

    /**
     * The kernel configuration (no boot).
     */
    static const Configuration* config_;

    /**
     * Handler of user class which implements an interrupt handler interface.
     */
    ::api::Task* handler_;

    /**
     * This interrupt source.
     */
    int32 source_;

    /**
     * Target CPU register context.
     */
    Register* reg_;

    /**
     * Source interrupts enable flag (no boot).
     */
    bool ie_;
  
  };
}
#endif // BOOS_TARGET_INTERRUPT_CONTROLLER_HPP_
