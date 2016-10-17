/** 
 * TI TMS320c64x environment.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_AM18X_ENVIRONMENT_HPP_
#define BOOS_CORE_AM18X_ENVIRONMENT_HPP_

#include "boos.core.Object.hpp"
#include "boos.util.Buffer.hpp"

namespace core
{
  class Environment;
  
  namespace am18x
  {
    class Environment : public ::core::Object<>
    {
      friend class ::core::Environment;
      typedef ::util::Buffer< ::api::Object*, 1 > Buffer;
 
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
      
      /**
       * Initialized controller objects (no boot).
       */
      static Buffer* controller_;
    
    };
  }
}
#endif // BOOS_CORE_AM18X_ENVIRONMENT_HPP_
