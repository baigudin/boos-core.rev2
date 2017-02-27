/** 
 * TI TMS320F2833x/F2823x DSC Phase-Locked Loop Controller.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_PLL_CONTROLLER_HPP_
#define BOOS_TARGET_PLL_CONTROLLER_HPP_

#include "boos.Types.hpp"
#include "boos.target.Core.hpp"
#include "boos.target.registers.System.hpp"

namespace target
{
  class PllController
  {
  
  public:
  
    /**
     * Initializes the driver.
     *
     * @param sourceClock source clock in Hz.    
     * @param cpuClock    requesting CPU clock in Hz.
     * @return true if no errors are occurred.
     */
    static bool init(int64 sourceClock, int64 cpuClock)
    {
      registers::System* sysReg = new (registers::System::ADDRESS) registers::System();
      int32 sel = 0x2;
      int32 mul = ( cpuClock * 2 / sourceClock ) & 0xffffffff;
      // Output frequency of the PLL (VCOCLK) does not exceed 300 MHz
      if(sourceClock * mul > 300000000) return false;
      // Multipliers more than 10 are reserved
      if(mul > 10) return false;
      // Test the oscillator is not off
      if(sysReg->pllsts.bit.oscoff == 1) return false;
      // Test the PLL is set correctly
      if(sysReg->pllsts.bit.plloff == 1 && sysReg->pllcr.bit.div > 0) return false;
      // Start changing procedure
      if(sysReg->pllsts.bit.mclksts == 1) return false;    
      Core::registerPublic();
      // Set division to four
      if(sysReg->pllsts.bit.divsel != 0) sysReg->pllsts.bit.divsel = 0;
      // Disable failed oscillator detect logic
      sysReg->pllsts.bit.mclkoff = 1;
      // Set new PLL
      sysReg->pllcr.bit.div = mul;
      // Test PLL is locked
      while(sysReg->pllsts.bit.plllocks != 1);
      // Enable failed oscillator detect logic
      sysReg->pllsts.bit.mclkoff = 0;
      // Set divider
      sysReg->pllsts.bit.divsel = sel;
      Core::registerProtected();
      return true;    
    }    
    
    /**
     * Deinitializes the driver.
     */
    static void deinit()
    {
    }

  };
}
#endif // BOOS_TARGET_PLL_CONTROLLER_HPP_
