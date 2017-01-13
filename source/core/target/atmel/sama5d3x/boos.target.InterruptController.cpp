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
   * Hardware global interrupts controller (no boot).
   */
  ::util::Toggle<Allocator>* InterruptController::global_;
}
