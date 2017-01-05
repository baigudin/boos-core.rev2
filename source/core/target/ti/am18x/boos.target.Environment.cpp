/** 
 * Target processor environment factory. 
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.Environment.hpp"
#include "boos.target.PllController.hpp"

namespace target
{

  /**
   * Initialization.
   *
   * @return true if no errors.
   */
  bool Environment::init()
  {
    bool res = true;
    res = res && PllController::init(25000000, 375000000);
    return res;
  }
  
  /**
   * Deinitialization.
   */
  void Environment::deinit()
  {
    PllController::deinit();
  }
}
