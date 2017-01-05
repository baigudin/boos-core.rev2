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
    target_ (NULL){
    setConstruct( construct(NULL, 0) );
  }  
  
  /**
   * Constructor.
   *
   * @param handler pointer to user class which implements an interrupt handler interface.   
   * @param source  available interrupt source.
   */
  Interrupt::Interrupt(::api::Task& handler, int32 source) : Parent(),
    target_ (NULL){
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
    if(!isConstructed()) return false;
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
    return this->Parent::isConstructed();
  }
  
  /**
   * Jumps to interrupt HW vector.
   */  
  void Interrupt::jump()
  {
    if(!isConstructed()) return;
    target_->jump();
  }
  
  /**
   * Clears an interrupt status of this source.
   */  
  void Interrupt::clear()
  {
    if(!isConstructed()) return;
    target_->clear();  
  }
  
  /**
   * Sets an interrupt status of this source.
   */  
  void Interrupt::set()
  {
    if(!isConstructed()) return;
    target_->set();  
  }  
  
  /**
   * Locks this interrupt source.
   *
   * @return an interrupt enable source bit value before method was called.
   */    
  bool Interrupt::disable()
  {
    if(!isConstructed()) return false;  
    return target_->disable();
  }
  
  /**
   * Unlocks this interrupt source.
   *
   * @param status returned status by disable method.
   */
  void Interrupt::enable(bool status)
  {
    if(!isConstructed()) return;
    target_->enable(status);  
  }
  
  /** 
   * Returns the switchable interface for controlling global interrupts.
   *
   * @return switchable interface.
   */ 
  ::api::Switchable& Interrupt::global()
  {
    return target::Interrupt::global();
  }
  
  /** 
   * Returns interrupt developing interface.
   *
   * @return interrupt core developing interface.
   */  
  ::target::Interrupt& Interrupt::extension()
  {
    if(!isConstructed()) Core::fail();
    return *target_;
  }
}

