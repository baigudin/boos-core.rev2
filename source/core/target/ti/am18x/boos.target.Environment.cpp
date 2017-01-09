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
   * @param cfg the core configuration.
   * @return true if no errors.
   */
  bool Environment::init(const Configuration& cfg)
  {
    bool res = true;
    res = res && PllController::init(cfg.sourceClock, cfg.cpuClock);
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
