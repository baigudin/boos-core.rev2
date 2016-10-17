/** 
 * TI TMS320c64x environment.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_TMS320C64X_ENVIRONMENT_HPP_
#define BOOS_CORE_TMS320C64X_ENVIRONMENT_HPP_

#include "boos.Types.hpp"

namespace core
{
  class Environment;
  
  namespace tms320c64x
  {
    class Environment
    {
      friend class ::core::Environment;
 
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
}
#endif // BOOS_CORE_TMS320C64X_ENVIRONMENT_HPP_
