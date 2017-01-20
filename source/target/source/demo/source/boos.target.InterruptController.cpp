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
   * The core configuration (no boot).
   */
  const Configuration* InterruptController::config_;

  /**
   * Global interrupts enable flag (no boot).
   */
  bool InterruptController::gie_;
}
