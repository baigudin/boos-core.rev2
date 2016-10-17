/** 
 * Core chip environment definitions.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_CHIP_ENVIRONMENT_HPP_
#define BOOS_CORE_CHIP_ENVIRONMENT_HPP_

/**
 * Texas Instruments TMS320C64x Digital Signal Processors family.
 */
#ifdef BS_TMS320C64X
#ifndef BS_CHIP_ENVIRONMENT
#define BS_CHIP_ENVIRONMENT
#include "../chip/tms320c64x/boos.core.tms320c64x.Environment.hpp"
namespace core { namespace chip = tms320c64x; }
#endif
#endif

/**
 * Texas Instruments AM18X ARM Microprocessors family.
 */
#ifdef BS_AM18X
#ifndef BS_CHIP_ENVIRONMENT
#define BS_CHIP_ENVIRONMENT
#include "../chip/am18x/boos.core.am18x.Environment.hpp"
namespace core { namespace chip = am18x; }
#endif
#endif

/**
 * Abstract chip interrupt.
 */
#ifndef BS_CHIP_ENVIRONMENT
#include "boos.Types.hpp"

namespace core
{
  namespace chip
  {
    class Environment
    {
  
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
#endif // BS_CHIP_ENVIRONMENT
#endif // BOOS_CORE_CHIP_ENVIRONMENT_HPP_
