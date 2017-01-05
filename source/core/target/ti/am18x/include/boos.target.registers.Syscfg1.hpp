/** 
 * TI ARM AM18x System Configuration (SYSCFG) Module.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_REGISRES_SYSCFG1_HPP_
#define BOOS_TARGET_REGISRES_SYSCFG1_HPP_

#include "boos.Types.hpp"

namespace target
{
  namespace registers
  {
    struct Syscfg1
    {
    
    public:

      static const uint32 ADDRESS = 0x01E2C000;
      
      /** 
       * Constructor.
       */  
      Syscfg1() :
        vtpioCtl(),
        ddrSlew(),
        deepsleep(),
        pupdEna(),
        pupdSel(),
        rxactive(),
        pwrdn(){
      }
      
      /** 
       * Destructor.
       */  
     ~Syscfg1(){}
     
      /**
       * Operator new.
       *
       * @param size unused.
       * @param ptr  address of memory.
       * @return address of memory.
       */
      void* operator new(uint32, uint32 ptr)
      {
        return reinterpret_cast<void*>(ptr);
      } 
          
      /**
       * VTP I/O Control Register.
       */
      union VTPIO_CTL
      {
        VTPIO_CTL(){}
        VTPIO_CTL(uint32 v){value = v;}         
       ~VTPIO_CTL(){}    
 
        uint32 value;
        struct 
        {
          uint32 f       : 3;
          uint32 d       : 3;
          uint32 powerdn : 1;
          uint32 lock    : 1;
          uint32 pwrsave : 1;
          uint32         : 4;
          uint32 clkrz   : 1;
          uint32 iopwrdn : 1;
          uint32 ready   : 1;
          uint32 vreftap : 2;
          uint32 vrefen  : 1;
          uint32         : 13;
        } bit;
      } vtpioCtl;
      
      /**
       * DDR Slew Register.
       */
      union DDR_SLEW
      {
        DDR_SLEW(){}
        DDR_SLEW(uint32 v){value = v;}         
       ~DDR_SLEW(){}    
       
        uint32 value;
        struct 
        {
          uint32 ddrCmdslew  : 2;
          uint32 ddrDataslew : 2;
          uint32 cmosen      : 1;
          uint32 ddrPdena    : 1;
          uint32             : 2;
          uint32 odtTermoff  : 2;
          uint32 odtTermon   : 2;
          uint32             : 20;
        } bit;
      } ddrSlew;
      
      /**
       * Deep Sleep Register.
       */
      union DEEPSLEEP
      {
        DEEPSLEEP(){}
        DEEPSLEEP(uint32 v){value = v;}          
       ~DEEPSLEEP(){}    
       
        uint32 value;
        struct 
        {
          uint32 sleepcount    : 16;
          uint32               : 14;
          uint32 sleepcomplete : 1;
          uint32 sleepenable   : 1;
        } bit;
      } deepsleep;
      
      /**
       * Pullup/Pulldown Enable Register.
       */
      union PUPD_ENA
      {
        PUPD_ENA(){}
        PUPD_ENA(uint32 v){value = v;}          
       ~PUPD_ENA(){}    
       
        uint32 value;
        struct 
        {
          uint32 pupdena : 32;
        } bit;
      } pupdEna;
      
      /**
       * Pullup/Pulldown Select Register.
       */
      union PUPD_SEL
      {
        PUPD_SEL(){}
        PUPD_SEL(uint32 v){value = v;}          
       ~PUPD_SEL(){}    
       
        uint32 value;
        struct 
        {
          uint32 pupdsel : 32;
        } bit;
      } pupdSel;
      
      /**
       * RXACTIVE Control Register.
       */
      union RXACTIVE
      {
        RXACTIVE(){}
        RXACTIVE(uint32 v){value = v;}          
       ~RXACTIVE(){}    
       
        uint32 value;
        struct
        {
          uint32 rxactive : 32;
        } bit;
      } rxactive;
      
      /**
       * Power Down Control Register.
       */
      union PWRDN
      {
        PWRDN(){}
        PWRDN(uint32 v){value = v;}          
       ~PWRDN(){}    
       
        uint32 value;
        struct 
        {
          uint32 sataclkPwrdn : 1;
          uint32              : 31;            
        } bit;
      } pwrdn;        
      
    };
  }
}
#endif // BOOS_TARGET_REGISRES_SYSCFG1_HPP_
