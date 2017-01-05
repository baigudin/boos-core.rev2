/** 
 * Target processor timers factory.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.TimerController.hpp"

namespace target
{
  /**
   * The core configuration (no boot).
   */
  const Configuration* TimerController::config_;
  
  /**
   * Locked by some object flag of each HW timer (no boot).  
   */
  bool TimerController::lock_[NUMBER_TIMERS];
}
