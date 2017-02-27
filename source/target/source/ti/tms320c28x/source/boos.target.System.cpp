/** 
 * Target kernel system.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.System.hpp"
#include "boos.target.Interrupt.hpp"

namespace target
{
  /**
   * Fails the target kernel.
   */
  void System::fail()
  {
    Interrupt::globalDisable();
    while(true);
  }
}

