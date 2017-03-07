/** 
 * Boot routine.
 *
 * The module performs the tasks to initialize C/C++ run-time environment.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_BOOT_HPP_
#define BOOS_TARGET_BOOT_HPP_

#include "boos.Types.hpp"

namespace target
{
  class Main;
  
  class Boot
  {
    friend class Main;

  private:
    
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
 
  };
}
#endif // BOOS_TARGET_BOOT_HPP_
