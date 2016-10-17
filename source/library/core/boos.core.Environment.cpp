/** 
 * TI TMS320c64x environment.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Environment.hpp" 
#include "boos.core.chip.Environment.hpp"

namespace core
{
  /**
   * Initialization.
   *
   * @return true if no errors.
   */
  bool Environment::init()
  {
    return chip::Environment::init();
  }
  
  /**
   * Deinitialization.
   */
  void Environment::deinit()
  {
    chip::Environment::deinit();      
  }
}

