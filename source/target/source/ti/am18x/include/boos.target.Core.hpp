/** 
 * Target core initialization.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_CORE_HPP_
#define BOOS_TARGET_CORE_HPP_

#include "boos.Types.hpp"

namespace target
{
  class Core
  {

  public:
  
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    static bool init();

    /**
     * Deinitialization.
     */
    static void deinit();
    
  private:

  };
}
#endif // BOOS_TARGET_CORE_HPP_
