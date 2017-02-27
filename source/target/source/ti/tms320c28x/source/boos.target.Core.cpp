/** 
 * Target core initialization.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.Core.hpp"
#include "boos.target.registers.System.hpp"

namespace target
{

  /**
   * Initialization.
   *
   * @param config the kernel configuration.
   * @return true if no errors.
   */
  bool Core::init()
  {
    registers::System* sysReg = new (registers::System::ADDRESS) registers::System();
    registerPublic();
    // Disable watchdog
    uint16 val = sysReg->wdcr.val;
    val &= ~(registers::System::WDCR_M_WDDIS|registers::System::WDCR_M_WDCHK);
    val |=   registers::System::WDCR_V_WDDIS|registers::System::WDCR_V_WDCHK;
    sysReg->wdcr.val = val;
    registerProtected();    
    return true;
  }
  
  /**
   * Deinitialization.
   */
  void Core::deinit()
  {
  }
}
