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
#include "boos.core.chip.Interrupt.hpp"
 
namespace core
{
  /**
   * Constructor.
   */
  Interrupt::Interrupt() :
    chip_ (NULL){
    setConstruct( construct(NULL, 0) );
  }  
  
  /**
   * Constructor.
   *
   * @param handler pointer to user class which implements an interrupt handler interface.   
   * @param source  available interrupt source.
   */
  Interrupt::Interrupt(::api::InterruptHandler& handler, int32 source) : 
    chip_ (NULL){
    setConstruct( construct(&handler, source) );
  }
  
  /**
   * Destructor.
   */
  Interrupt::~Interrupt()
  {
    delete chip_;
  }
  
  /**
   * Constructor.
   *
   * @param handler pointer to user class which implements an interrupt handler interface.   
   * @param source  available interrupt source.
   * @return true if object is constructed successfully.
   */
  bool Interrupt::construct(::api::InterruptHandler* handler, int32 source)
  {
    if(!isConstructed()) return false;
    chip::Interrupt* chip = handler != NULL ? new chip::Interrupt(*handler, source) : new chip::Interrupt();
    chip_ = chip;
    return isObject<chip::Interrupt>(chip);
  }

  /**
   * Tests if this object is constructed.
   *
   * @return true if object is constructed successfully.
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
    if( isConstructed() ) chip_->jump();
  }
  
  /**
   * Clears an interrupt status of this source.
   */  
  void Interrupt::clear()
  {
    if( isConstructed() ) chip_->clear();  
  }
  
  /**
   * Sets an interrupt status of this source.
   */  
  void Interrupt::set()
  {
    if( isConstructed() ) chip_->set();  
  }  
  
  /**
   * Locks this interrupt source.
   *
   * @return an interrupt enable source bit value before method was called.
   */    
  bool Interrupt::disable()
  {
    return isConstructed() ? chip_->disable() : false;
  }
  
  /**
   * Unlocks this interrupt source.
   *
   * @param status returned status by disable method.
   */
  void Interrupt::enable(bool status)
  {
    if( isConstructed() ) chip_->enable(status);  
  }
  
  /** 
   * Returns the switchable interface for global interrupt controlling.
   *
   * @return switchable interface.
   */ 
  ::api::Switchable& Interrupt::global()
  {
    return chip::Interrupt::global();
  }
  
  /** 
   * Returns interrupt developing interface.
   *
   * @return interrupt core developing interface.
   */  
  epi::Interrupt& Interrupt::extension()
  {
    if(!isConstructed()) Core::fail();
    return *chip_;
  }
  
  /**
   * Initialization.
   *
   * @return true if no errors.
   */
  bool Interrupt::init()
  {
    return chip::Interrupt::init();
  }    
  
  /**
   * Deinitialization.
   */
  void Interrupt::deinit()
  {
    chip::Interrupt::deinit();  
  }
}

