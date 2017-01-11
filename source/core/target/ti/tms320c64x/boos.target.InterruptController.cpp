/** 
 * Target processor interrupts factory.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.InterruptController.hpp"

namespace target
{
  /**
   * HW interrupt handle routing.
   *
   * @param index index of HW interrupt vector number in context table
   */  
  void InterruptController::handler(register int32 index)
  {
    register Context* ctx = &context_[index];
    register ::api::Task* handler = ctx->handler;
    handler->main();
  }    
  
  /**
   * HW interrupt registers (no boot).
   */
  registers::Intc* InterruptController::intc_;
  
  /**    
   * Hardware global interrupt controller (no boot).
   */
  InterruptController::Global* InterruptController::global_;

  /**
   * Hi level interrupts context table (no boot).
   */        
  InterruptController::Context InterruptController::context_[NUMBER_VECTORS];  

  /**
   * Low level interrupts context table (no boot).
   */    
  InterruptController::ContextLow InterruptController::contextLow_[NUMBER_VECTORS];
}
