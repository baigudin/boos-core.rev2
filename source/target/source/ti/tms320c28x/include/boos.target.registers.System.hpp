/**
 * TI TMS320F2833x/F2823x DSC System Control Registers.
 *
 * System Control Registers include PLL, Clocking, 
 * Watchdog, and Low-Power Mode Registers.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_REGISRES_SYSTEM_HPP_
#define BOOS_TARGET_REGISRES_SYSTEM_HPP_

#include "boos.Types.hpp"

namespace target
{
  namespace registers
  {
    struct System
    {
    
    public:
    
      /**
       * Memory mapped addresses.
       */    
      static const uint32 ADDRESS = 0x00007010;
      
      /** 
       * Constructor.
       */  
      System() :
        pllsts  (),
        hispcp  (),
        lospcp  (),
        pclkcr0 (),
        pclkcr1 (),
        lpmcr0  (),
        pclkcr3 (),
        pllcr   (),
        scsr    (),
        wdcntr  (),
        wdkey   (),
        wdcr    (),
        mapcnf  (){
      }
    
      /** 
       * Destructor.
       */    
     ~System(){}    
      
      /**
       * Operator new.
       *
       * @param size unused.
       * @param ptr  address of memory.
       * @return address of memory.
       */     
      void* operator new(size_t, uint32 ptr)
      {
        return reinterpret_cast<void*>(ptr);
      }
      
    private:        
    
      uint16 space0_[1];
      
    public:  
    
      // EALLOW PROTECTED
      
      /**
       * PLL Status Register.
       */
      union Pllsts
      {
        Pllsts(){}
        Pllsts(uint16 v){val = v;}          
       ~Pllsts(){}    
    
        volatile uint16 val;
        struct Val
        {
          volatile uint16 plllocks : 1;
          volatile uint16          : 1;
          volatile uint16 plloff   : 1;
          volatile uint16 mclksts  : 1;
          volatile uint16 mclkclr  : 1;
          volatile uint16 oscoff   : 1;
          volatile uint16 mclkoff  : 1;
          volatile uint16 divsel   : 2;
          volatile uint16          : 7;
        } bit;
      } pllsts; 
    
    private:        
    
      uint16 space1_[8];
      
    public:
    
      /**
       * High-Speed Peripheral Clock Prescaler Register.
       */
      union Hispcp
      {
        Hispcp(){}
        Hispcp(uint16 v){val = v;}          
       ~Hispcp(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 hspclk : 2;
          uint16        : 14;
        } bit;
      } hispcp; 
      
      /**
       * Low-Speed Peripheral Clock Prescaler Register.
       */
      union Lospcp
      {
        Lospcp(){}
        Lospcp(uint16 v){val = v;}          
       ~Lospcp(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 lspclk : 2;
          uint16        : 14;
        } bit;
      } lospcp; 
      
      /**
       * Peripheral Clock Control Register 0.
       */
      union Pclkcr0
      {
        Pclkcr0(){}
        Pclkcr0(uint16 v){val = v;}          
       ~Pclkcr0(){}    
    
        uint16 val;
        struct Val 
        {
          uint16             : 2;
          uint16 tbclksync   : 1;
          uint16 adcenclk    : 1;
          uint16 i2caenclk   : 1;
          uint16 scicenclk   : 1;
          uint16             : 2;
          uint16 spiaenclk   : 1;
          uint16             : 1;
          uint16 sciaenclk   : 1;
          uint16 scibenclk   : 1;
          uint16 mcbspaenclk : 1;
          uint16 mcbspbenclk : 1;
          uint16 ecanaenclk  : 1;
          uint16 ecanbenclk  : 1;
        } bit;
      } pclkcr0; 
      
      /**
       * Peripheral Clock Control Register 1.
       */
      union Pclkcr1
      {
        Pclkcr1(){}
        Pclkcr1(uint16 v){val = v;}          
       ~Pclkcr1(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 epwm1enclk : 1;
          uint16 epwm2enclk : 1; 
          uint16 epwm3enclk : 1; 
          uint16 epwm4enclk : 1; 
          uint16 epwm5enclk : 1; 
          uint16 epwm6enclk : 1; 
          uint16            : 2;
          uint16 ecap1enclk : 1; 
          uint16 ecap2enclk : 1; 
          uint16 ecap3enclk : 1; 
          uint16 ecap4enclk : 1; 
          uint16 ecap5enclk : 1; 
          uint16 ecap6enclk : 1; 
          uint16 eqep1enclk : 1; 
          uint16 eqep2enclk : 1; 
        } bit;
      } pclkcr1; 
      
      /**
       * Low-Power Mode Control Register 0.
       */
      union Lpmcr0
      {
        Lpmcr0(){}
        Lpmcr0(uint16 v){val = v;}          
       ~Lpmcr0(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 lpm       : 2;
          uint16 qualstdby : 6;
          uint16           : 7;
          uint16 wdinte    : 1;
        } bit;
      } lpmcr0; 
      
    private:        
    
      uint16 space2_[1];
      
    public:
      
      /**
       * Peripheral Clock Control Register 3.
       */
      union Pclkcr3
      {
        Pclkcr3(){}
        Pclkcr3(uint16 v){val = v;}          
       ~Pclkcr3(){}    
    
        uint16 val;
        struct Val 
        {
          uint16                : 8;
          uint16 cputimer0enclk : 1;
          uint16 cputimer1enclk : 1;
          uint16 cputimer2enclk : 1;
          uint16 dmaenclk       : 1;
          uint16 xintfenclk     : 1;
          uint16 gpioinenclk    : 1;
          uint16                : 2;
        } bit;
      } pclkcr3; 
      
      /**
       * PLL Control Register.
       */
      union Pllcr
      {
        Pllcr(){}
        Pllcr(uint16 v){val = v;}          
       ~Pllcr(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 div : 4;
          uint16     : 12;      
        } bit;
      } pllcr; 
      
      /**
       * System Control and Status Register.
       */
      union Scsr
      {
        Scsr(){}
        Scsr(uint16 v){val = v;}          
       ~Scsr(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 wdoverride : 1;
          uint16 wdenint    : 1;
          uint16 wdints     : 1;
          uint16            : 13;
        } bit;
      } scsr; 
      
      /**
       * Watchdog Counter Register.
       */
      union Wdcntr
      {
        Wdcntr(){}
        Wdcntr(uint16 v){val = v;}          
       ~Wdcntr(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 wdcntr : 8;
          uint16        : 8;  
        } bit;
      } wdcntr; 
      
    private:        
    
      uint16 space3_[1];
      
    public:
    
      /**
       * Watchdog Reset Key Register.
       */
      union Wdkey
      {
        Wdkey(){}
        Wdkey(uint16 v){val = v;}          
       ~Wdkey(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 wdkey : 8;
          uint16       : 8;  
        } bit;
      } wdkey; 
    
    private:        
    
      uint16 space4_[3];
      
    public:
    
      /**
       * Watchdog Control Register.
       */
      static const uint16 WDCR_V_WDDIS = 0x0040;
      static const uint16 WDCR_M_WDDIS = 0x0040;    
      static const uint16 WDCR_V_WDCHK = 0x0028;    
      static const uint16 WDCR_M_WDCHK = 0x0038;
       
      union Wdcr
      {
        Wdcr(){}
        Wdcr(uint16 v){val = v;}          
       ~Wdcr(){}    
       
    
        uint16 val;
        struct Val 
        {
          uint16 wdps     : 3;
          uint16 wdchk    : 3;
          uint16 wddis    : 1;
          uint16 wdflag   : 1;
          uint16          : 8;
        } bit;
      } wdcr; 
    
    private:        
    
      uint16 space5_[4];
      
    public:
    
      /**
       * ePWM/HRPWM Re-map Register.
       */
      union Mapcnf
      {
        Mapcnf(){}
        Mapcnf(uint16 v){val = v;}          
       ~Mapcnf(){}    
    
        uint32 val;
        struct Val 
        {
          uint32 mapepwm : 1;
          uint32         : 31;
        } bit;
      } mapcnf; 
    
    };
  }
}  
#endif // BOOS_TARGET_REGISRES_SYSTEM_HPP_
