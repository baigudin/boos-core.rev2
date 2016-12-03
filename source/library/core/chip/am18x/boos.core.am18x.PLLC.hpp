/** 
 * TI ARM AM18x Phase-Locked Loop Controller (PLLC).
 *
 * This is an example configuration file for configuring 
 * the PLL Controller of TI AM18x chips. As an example, 
 * we will base on 25 MHz rate of input crystal clock, 
 * which will be given as argument to this object constructor, 
 * and desire 375 MHz, which will be gotten from 
 * the BOOS Core configuration, for ARM core.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_AM18X_PLLC_HPP_
#define BOOS_CORE_AM18X_PLLC_HPP_

#include "boos.core.am18x.registers.SYSCFG0.hpp"
#include "boos.core.am18x.registers.SYSCFG1.hpp"
#include "boos.core.am18x.registers.PLLC0.hpp"
#include "boos.core.am18x.registers.PLLC1.hpp"
#include "boos.core.Configuration.hpp"
#include "boos.core.Core.hpp"
#include "boos.core.Object.hpp"

namespace core
{
  namespace am18x
  {
    class PLLC : public ::core::Object<>
    {
      typedef ::core::Object<> Parent;
      
    public:

      /** 
       * Constructor.
       *
       * @param oscin reference clock rate in Hz.
       */    
      PLLC() : 
        syscfg0_ (NULL),
        syscfg1_ (NULL),
        pllc0_   (NULL),
        pllc1_   (),
        cpuClock_(::core::Core::configuration().cpuClock),
        oscin_   (::core::Core::configuration().sourceClock){
        setConstruct( construct() );
      }     

      /** 
       * Destructor.
       */    
      virtual ~PLLC()
      {
      } 
      
      /**
       * Tests if this object has been constructed.
       *
       * @return true if object has been constructed successfully.
       */
      virtual bool isConstructed() const
      {
        return this->Parent::isConstructed();
      }
 
    private:
    
      /** 
       * Constructor.
       *
       * @return boolean result.
       */
      bool construct()
      {
        if(!isConstructed()) return false;
        bool res = true;        
        syscfg0_ = new (registers::SYSCFG0::ADDRESS) registers::SYSCFG0();
        syscfg1_ = new (registers::SYSCFG1::ADDRESS) registers::SYSCFG1();
        pllc0_ = new (registers::PLLC0::ADDRESS) registers::PLLC0();
        pllc1_ = new (registers::PLLC1::ADDRESS) registers::PLLC1();        
        // Unlock the SYSCFG module
        syscfg0_->kick0r.bit.kick0 = 0x83E70B13;
        syscfg0_->kick1r.bit.kick1 = 0x95A4F1E0;
        // Unlock the PLLC0 and PLLC1 modules
        syscfg0_->cfgchip0.bit.pllMasterLock = 0;
        syscfg0_->cfgchip3.bit.pll1MasterLock = 0;  
        // Configure the PLLC0 and PLLC1 modules
        res |= pll0();
        res |= pll1();  
        // Unlock the PLLC0 and PLLC1 modules
        syscfg0_->cfgchip0.bit.pllMasterLock = 1;
        syscfg0_->cfgchip3.bit.pll1MasterLock = 1;  
        // Lock the SYSCFG module
        syscfg0_->kick0r.bit.kick0 = 0x00000000;
        syscfg0_->kick1r.bit.kick1 = 0x00000000;        
        return res;
      }
      
      /** 
       * PLL0 configuration.
       */
      bool pll0()
      {
        // Test the power-down state
        bool isPowerDown = pllc0_->pllctl.bit.pllpwrdn;
        // Set an internal oscillator (crystal) way
        if(isPowerDown) pllc0_->pllctl.bit.clkmode = 0;      
        // Calculate the values for multiplier and dividers
        registers::PLLC0::PLLM reg = 0xffffffff;
        int32 cpllm = cpuClock_ / oscin_ - 1;
        int32 mpllm = reg.bit.pllm;
        if(cpllm & ~mpllm) return false;              
        // Switch the PLL to bypass mode
        pllc0_->pllctl.bit.pllensrc = 0;
        pllc0_->pllctl.bit.extclksrc = 0;  
        pllc0_->pllctl.bit.pllen = 0;
        for(uint32 i=0; i<4; i++);
        // Set reset is asserted
        pllc0_->pllctl.bit.pllrst = 0;
        // Up the power
        if(isPowerDown) pllc0_->pllctl.bit.pllpwrdn = 0;
        // Set pre-divider value to 1: before 25 MHz, after 25 MHz
        pllc0_->prediv.bit.ratio = 0;  
        pllc0_->prediv.bit.preden = 1;
        // Set calculated multiplier value to 15: before 25 MHz, after 375 MHz
        pllc0_->pllm.bit.pllm = cpllm;
        // Set post-divider value to 1: before 375 MHz, after 375 MHz
        pllc0_->postdiv.bit.ratio = 0;  
        pllc0_->postdiv.bit.postden = 1;
        // Set EMIFA clocking to 93.75 MHz
        syscfg0_->cfgchip3.bit.emaClksrc = 0;
        plldiv0(pllc0_->plldiv3, 4);
        // Set ARM clocking to 375 MHz
        plldiv0(pllc0_->plldiv6, 1);
        // TODO: SUPPLEMENT SOME DIVIDER SETS WHEN THOSE ARE NEEDED
        // Set reset is not asserted
        pllc0_->pllctl.bit.pllrst = 1;
        // Wait for the PLL to lock
        for(uint32 i=0; i<200; i++);
        // Switch the PLL to normal mode, not bypassed
        pllc0_->pllctl.bit.pllen = 1;
        // Set, for an example, ARM clocking for test and debug purposes
        pllc0_->ocsel.bit.ocsrc = 0x1c;
        pllc0_->oscdiv.bit.ratio = 0;
        pllc0_->oscdiv.bit.od1en = 1;
        return true;
      } 
      
      /** 
       * PLL1 configuration.
       */
      bool pll1()
      {
        // Test the power-down state
        bool isPowerDown = pllc1_->pllctl.bit.pllpwrdn;
        // Switch the PLL to bypass mode
        pllc1_->pllctl.bit.pllensrc = 0;
        pllc1_->pllctl.bit.pllen = 0;
        for(uint32 i=0; i<4; i++);
        // Set reset is asserted
        pllc1_->pllctl.bit.pllrst = 0;
        // Up the power
        if(isPowerDown) pllc1_->pllctl.bit.pllpwrdn = 0;
        // Set calculated multiplier value to 12: before 25 MHz, after 300 MHz
        pllc1_->pllm.bit.pllm = 11;
        // Set post-divider value to 1: before 300 MHz, after 300 MHz
        pllc1_->postdiv.bit.ratio = 0;  
        pllc1_->postdiv.bit.postden = 1;
        // Set DDR clocking to 300 MHz
        plldiv1(pllc1_->plldiv1, 1);
        // Set TIMER2/3, UART1/2, McBSP, and etc clocking to 100 MHz
        syscfg0_->cfgchip3.bit.async3Clksrc = 1;
        plldiv1(pllc1_->plldiv2, 3);
        // TODO: SUPPLEMENT SOME DIVIDER SETS WHEN THOSE ARE NEEDED
        // Set reset is not asserted
        pllc1_->pllctl.bit.pllrst = 1;
        // Wait for the PLL to lock
        for(uint32 i=0; i<200; i++);
        // Switch the PLL to normal mode, not bypassed
        pllc1_->pllctl.bit.pllen = 1;        
        // Set, for an example, DDR clocking for test and debug purposes
        pllc1_->ocsel.bit.ocsrc = 0x17;
        pllc1_->oscdiv.bit.ratio = 0;
        pllc1_->oscdiv.bit.od1en = 1;
        return true;
      } 
      
      /** 
       * Configures a PLLDIV of PLL0.
       *
       * @param plldiv reference to register.
       * @param div    divider value.
       */
      void plldiv0(registers::PLLC0::PLLDIV& plldiv, int32 div)
      {
        while(pllc0_->pllstat.bit.gostat);
        plldiv.bit.ratio = div - 1;
        plldiv.bit.dNen = 1;
        pllc0_->pllcmd.bit.goset = 1;
        while(pllc0_->pllstat.bit.gostat);
      }       
      
      /** 
       * Configures a PLLDIV of PLL1.
       *
       * @param plldiv reference to register.
       * @param div    divider value.
       */
      void plldiv1(registers::PLLC1::PLLDIV& plldiv, int32 div)
      {
        while(pllc1_->pllstat.bit.gostat);
        plldiv.bit.ratio = div-1;
        plldiv.bit.dNen = 1;
        pllc1_->pllcmd.bit.goset = 1;
        while(pllc1_->pllstat.bit.gostat);
      }       
      
      /**
       * System Configuration Module 0 registers.
       */ 
      registers::SYSCFG0* syscfg0_;      
      
      /**
       * System Configuration Module 1 registers.
       */ 
      registers::SYSCFG1* syscfg1_;
      
      /**
       * Phase-Locked Loop Controller 0 registers.
       */ 
      registers::PLLC0* pllc0_;
      
      /**
       * Phase-Locked Loop Controller 1 registers.
       */             
      registers::PLLC1* pllc1_;
      
      /**
       * Reference clock rate in Hz.
       */      
      int64 oscin_;
      
      /**
       * ARM clock rate in Hz.
       */      
      int64 cpuClock_;
      
    };
  }
}
#endif // BOOS_CORE_AM18X_PLLC_HPP_
