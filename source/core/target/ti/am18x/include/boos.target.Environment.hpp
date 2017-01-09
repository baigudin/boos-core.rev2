/** 
 * Core target environment definitions.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_ENVIRONMENT_HPP_
#define BOOS_TARGET_ENVIRONMENT_HPP_

#include "boos.target.Configuration.hpp"

namespace target
{
  class Core;

  class Environment
  {
    friend class Core;

  private:
    
    /**
     * Initialization.
     *
     * @param cfg the core configuration.
     * @return true if no errors.
     */
    static bool init(const Configuration& cfg);    

    /**
     * Deinitialization.
     */
    static void deinit();

  };
}
#endif // BOOS_TARGET_ENVIRONMENT_HPP_
