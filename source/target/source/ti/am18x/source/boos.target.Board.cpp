/** 
 * Target board initialization.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.Board.hpp"
#include "boos.target.PllController.hpp"

namespace target
{

  /**
   * Initialization.
   *
   * @param config the core configuration.
   * @return true if no errors.
   */
  bool Board::init(const Configuration& config)
  {
    config_ = &config;
    bool res = true;
    res = res && PllController::init(config.sourceClock, config.cpuClock);
    return res;
  }
  
  /**
   * Deinitialization.
   */
  void Board::deinit()
  {
  }
  
  /**
   * The core configuration (no boot).
   */
  const Configuration* Board::config_;  
}
