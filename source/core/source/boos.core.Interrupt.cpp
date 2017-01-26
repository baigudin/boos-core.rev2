/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Core.hpp"
#include "boos.core.Interrupt.hpp"
#include "boos.target.Interrupt.hpp"
 
namespace core
{
  /**
   * Constructor.
   */
  Interrupt::Interrupt() : Parent(),
    isConstructed_ (getConstruct()),  
    target_        (NULL){
    setConstruct( construct(NULL, 0) );
  }  
  
  /**
   * Constructor.
   *
   * @param handler pointer to user class which implements an interrupt handler interface.   
   * @param source  available interrupt source.
   */
  Interrupt::Interrupt(::api::Task& handler, int32 source) : Parent(),
    isConstructed_ (getConstruct()),
    target_        (NULL){
    setConstruct( construct(&handler, source) );
  }
  
  /**
   * Destructor.
   */
  Interrupt::~Interrupt()
  {
    delete target_;
  }
  
  /**
   * Constructor.
   *
   * @param handler pointer to user class which implements an interrupt handler interface.   
   * @param source  available interrupt source.
   * @return true if object has been constructed successfully.
   */
  bool Interrupt::construct(::api::Task* handler, int32 source)
  {
    if(!isConstructed_) return false;
    if(handler != NULL) 
      target_ = target::Interrupt::create(*handler, source);
    else 
      target_ = target::Interrupt::create();
    return target_ != NULL ? target_->isConstructed() : false;
  }

  /**
   * Tests if this object has been constructed.
   *
   * @return true if object has been constructed successfully.
   */    
  bool Interrupt::isConstructed() const
  {
    return isConstructed_;
  }
  
  /**
   * Jumps to interrupt HW vector.
   */  
  void Interrupt::jump()
  {
    if(!isConstructed_) return;
    target_->jump();
  }
  
  /**
   * Clears an interrupt status of this source.
   */  
  void Interrupt::clear()
  {
    if(!isConstructed_) return;
    target_->clear();  
  }
  
  /**
   * Sets an interrupt status of this source.
   */  
  void Interrupt::set()
  {
    if(!isConstructed_) return;
    target_->set();  
  }  
  
  /**
   * Locks this interrupt source.
   *
   * @return an interrupt enable source bit value before method was called.
   */    
  bool Interrupt::disable()
  {
    if(!isConstructed_) return false;  
    return target_->disable();
  }
  
  /**
   * Unlocks this interrupt source.
   *
   * @param status returned status by disable method.
   */
  void Interrupt::enable(bool status)
  {
    if(!isConstructed_) return;
    target_->enable(status);  
  }
  


  /**
   * Initialization.
   *
   * @return true if no errors.
   */
  bool Interrupt::init()
  {
    int32 stage = 0;
    while(true)
    {
      // Stage 1 creates global interrupt class switching
      stage++;
      global_ = new Global();
      if( global_ == NULL || !global_->isConstructed() ) break;
      // Stage complete
      stage = 0;
      break;
    }
    switch(stage)
    {
      case 1: delete global_; global_ = NULL;      
      default: return false;
      case 0: return true;
    }  
  }

  /**
   * Deinitialization.
   */
  void Interrupt::deinit()
  {
    if(global_ != NULL)
    {
      delete global_; 
      global_ = NULL;
    }
  }

  /** 
   * Returns the toggle interface for controlling global interrupts.
   *
   * @return toggle interface.
   */ 
  ::api::Toggle& Interrupt::global()
  {
    if(global_ == NULL) Core::fail();
    return *global_;
  }
  
  /** 
   * Returns interrupt developing interface.
   *
   * @return interrupt kernel developing interface.
   */  
  ::target::Interrupt& Interrupt::extension()
  {
    if(!isConstructed_) Core::fail();
    return *target_;
  }
  
  
  /** 
   * Disables all maskable interrupts.
   *
   * @return global interrupt enable bit value before method was called.
   */ 
  bool Interrupt::Global::disable()
  {
    return ::target::Interrupt::globalDisable();
  }
  
  /** 
   * Enables all maskable interrupts.
   *
   * @param status returned status by disable method.
   */    
  void Interrupt::Global::enable(bool status)
  {
    ::target::Interrupt::globalEnable(status);  
  }
  
  /**    
   * Hardware global interrupt controller (no boot).
   */
  Interrupt::Global* Interrupt::global_;
}

