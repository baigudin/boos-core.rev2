/** 
 * Target kernel of system.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.Core.hpp"
#include "boos.target.Interrupt.hpp"

namespace target
{
  /**
   * Fails the target kernel.
   */
  void Core::fail()
  {
    Interrupt::globalDisable();
    while(true);
  }
}

