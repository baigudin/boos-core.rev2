/** 
 * Core of system.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.CoreTimerInterrupt.hpp"
#include "boos.core.Core.hpp"
#include "boos.target.Core.hpp"

namespace core
{
  /** 
   * Returns a current value of the running core.
   *
   * @return time in nanoseconds.
   */      
  int64 Core::nanoTime()
  {
    return interrupt_ != NULL ? interrupt_->nanoTime() : 0;
  }
  
  /** 
   * Terminates the core.
   */      
  void Core::fail()
  {
    ::target::Core::fail();
  }

  /**
   * Initialization.
   *
   * @return true if no errors.
   */
  bool Core::init()
  {
    // Create kernel system tick timer
    interrupt_ = new CoreTimerInterrupt();
    if(interrupt_ == NULL || !interrupt_->isConstructed()) return false;
    // Set heap interrupt controller
    global_ = NULL;
    ::api::Heap* heap = ::Allocator::getHeap();
    if(heap == NULL || !heap->isConstructed()) return false;
    global_ = &interrupt_->global();
    heap->toggle(global_);
    return true;
  }
  
  /**
   * Deinitialization.
   *
   * @param heap a target core heap interface.   
   */
  void Core::deinit()
  {
    global_ = NULL;
    if(interrupt_ != NULL)
    {
      delete interrupt_;
      interrupt_ = NULL;
    }
  }
  
  /**
   * Hardware timer interrupt resource of core (no boot).
   */
  CoreTimerInterrupt* Core::interrupt_;  

  /**
   * Global interrupt resource (no boot).
   */
  ::api::Toggle* Core::global_;
}
