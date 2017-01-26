/** 
 * Target board initialization.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.Board.hpp"

namespace target
{

  /**
   * Initialization.
   *
   * @param config the kernel configuration.
   * @return true if no errors.
   */
  bool Board::init(const Configuration& config)
  {
    config_ = &config;
    return true;
  }
  
  /**
   * Deinitialization.
   */
  void Board::deinit()
  {
  }
  
  /**
   * The kernel configuration (no boot).
   */
  const Configuration* Board::config_;  
}
