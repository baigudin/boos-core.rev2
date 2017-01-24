/** 
 * Core boot routine.
 *
 * The module performs the tasks to initialize C/C++ run-time environment.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.Boot.hpp"

namespace target
{
  /**
   * Initialization.
   *
   * @return true if no errors.
   */
  bool Boot::init()
  {
    return true;    
  }
  
  /**
   * Deinitialization.
   */
  void Boot::deinit()
  {
  }
}
