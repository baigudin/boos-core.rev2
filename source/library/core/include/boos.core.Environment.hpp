/** 
 * Core environment.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_ENVIRONMENT_HPP_
#define BOOS_CORE_ENVIRONMENT_HPP_

#include "boos.core.Types.hpp"

namespace core
{
  class Environment
  {
    friend class Core;

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
#endif // BOOS_CORE_ENVIRONMENT_HPP_
