/** 
 * TI TMS320c64x environment.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.am18x.Environment.hpp"
#include "boos.core.am18x.PLLC.hpp"

namespace core
{
  namespace am18x
  {
    /**
     * Initialized controller objects (no boot).
     */
    Environment::Buffer* Environment::controller_;          
    
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    bool Environment::init()
    {
      controller_ = new Buffer(NULL);
      if(!isObject<Buffer>(controller_)) return false;
      Buffer& controller = *controller_;
      controller.fill(NULL);
      // Phase-Locked Loop Controller
      PLLC* pllc = new PLLC();
      controller[0] = pllc;      
      if(!isObject<PLLC>(pllc)) return false;      
      // Complete
      return true;
    }
    
    /**
     * Deinitialization.
     */
    void Environment::deinit()
    {
      if(!isObject<Buffer>(controller_)) return;
      Buffer& controller = *controller_;
      int32 count = controller.length();
      for(int32 i=0; i<count; i++)
        if(!controller.isIllegal(controller[i])) 
          delete controller[i];
    }
  }
}
