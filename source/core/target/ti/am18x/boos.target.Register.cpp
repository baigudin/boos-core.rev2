/** 
 * Target processor registers factory.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.Register.hpp"
#include "boos.target.registers.Cpu.hpp"

namespace target
{
  /**
   * Returns the register interface of a target processor.
   *
   * @return target processor register interface.
   */
  ::target::Register* Register::create()
  {
    return new registers::Cpu();
  }
}
