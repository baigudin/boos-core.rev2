/** 
 * Target board initialization.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_BOARD_HPP_
#define BOOS_TARGET_BOARD_HPP_

#include "boos.Types.hpp"
#include "boos.target.Configuration.hpp"

namespace target
{
  class Board
  {

  public:
  
    /**
     * Initialization.
     *
     * @param config the kernel configuration.
     * @return true if no errors.
     */
    static bool init(const Configuration& config);

    /**
     * Deinitialization.
     */
    static void deinit();
    
  private:
    
    /**
     * The kernel configuration (no boot).
     */
    static const Configuration* config_;    

  };
}
#endif // BOOS_TARGET_BOARD_HPP_
