/** 
 * Target processor timers factory.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.Timer.hpp"
#include "boos.target.TimerController.hpp"

namespace target
{
  /**
   * Returns the timer interface of a target processor.
   *
   * Constructs this object and allocs a first free hardware timer.
   *       
   * @return target processor interrupt interface, or NULL if error has been occurred.
   */
  ::target::Timer* Timer::create()
  {
    return new TimerController();
  }
      
  /**
   * Returns the timer interface of a target processor.
   *
   * @param number available timer number.
   * @return target processor timer interface, or NULL if error has been occurred.
   */
  ::target::Timer* Timer::create(int32 number)
  {
    return new TimerController(number);
  }
}
