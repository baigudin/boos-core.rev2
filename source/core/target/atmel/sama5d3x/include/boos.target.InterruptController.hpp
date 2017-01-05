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

#include "boos.target.Core.hpp"
#include "boos.target.Object.hpp"
#include "boos.target.Interrupt.hpp"
#include "boos.util.Switcher.hpp"

namespace target
{
  class Core;
  
  class InterruptController : public ::target::Object<>, public ::target::Interrupt
  {
    friend class Core;
    typedef ::target::Object<> Parent;

  public:
  
    /** 
     * Constructor.
     */    
    InterruptController() :
      handler_ (NULL),
      source_  (-1),
      reg_     (NULL){
    }

    /** 
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.
     * @param source  available interrupt source.
     */     
    InterruptController(::api::Task& handler, int32 source) :
      handler_ (&handler),
      source_  (source),
      reg_     (NULL){
    }

    /**
     * Copy constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.
     * @param source  available interrupt source.
     */
    InterruptController(::target::InterruptController& obj) :
      handler_ (NULL),
      source_  (-1),
      reg_     (NULL){
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
      handler_ = handler;
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
     * Tests if this interrupt source can be polarized.
     *
     * @return true if this source is polarizing.
     */  
    virtual bool isPolarizing()
    {
      return false;
    }
    
    /**
     * Sets a low-to-high transition on an interrupt source.
     */
    virtual void risingPolarization()
    {
    }
    
    /**
     * Sets a high-to-low transition on an interrupt source.
     */
    virtual void fallingPolarization()
    {
    }
    
    /** 
     * Returns the switchable interface for controlling global interrupts.
     *
     * @return switchable interface.
     */ 
    static ::api::Switchable& global()
    {
      if(global_ == NULL) Core::fail();
      return *global_;
    }
    
  private:    
    
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    static bool init()
    {
      global_ = new ::util::Switcher<Allocator>();
      return global_ != NULL ? global_->isConstructed() : false;
    }
    
    /**
     * Deinitialization.
     */
    static void deinit()
    {
      delete global_;
      global_ = NULL;      
    }

    /**
     * A switcher.
     */    
    static ::util::Switcher<Allocator>* global_;

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
  
  };
}
#endif // BOOS_TARGET_INTERRUPT_CONTROLLER_HPP_
