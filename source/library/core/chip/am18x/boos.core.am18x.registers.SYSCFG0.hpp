/** 
 * TI ARM AM18x System Configuration (SYSCFG) Module.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_AM18X_REGISRES_SYSCFG0_HPP_
#define BOOS_CORE_AM18X_REGISRES_SYSCFG0_HPP_

#include "boos.core.am18x.registers.Mapped.hpp"

namespace core
{
  namespace am18x
  {
    namespace registers
    {
      struct SYSCFG0 : public Mapped
      {
      
      public:
   
        SYSCFG0(){}
       ~SYSCFG0(){}
       
        static const uint32 ADDRESS = 0x01C14000;       
        
        /**
         * Revision Identification Register.
         */
        union REVID
        {
          REVID(){}
          REVID(uint32 v){value = v;}         
         ~REVID(){}    

          uint32 value;
          struct 
          {
            uint32 rev : 32;
          } bit;
        } revid;
        
      private:        
      
        uint32 space0_[5];
        
      public:                
        
        /**
         * Device Identification Register 0.
         */
        union DEVIDR0
        {
          DEVIDR0(){}
          DEVIDR0(uint32 v){value = v;}          
         ~DEVIDR0(){}    

          uint32 value;
          struct 
          {
            uint32 devid0 : 32;
          } bit;
        } devid0;
        
      private:        
      
        uint32 space1_[1];
        
      public:                
        
        /**
         * Boot Configuration Register.
         */
        union BOOTCFG
        {
          BOOTCFG(){}
          BOOTCFG(uint32 v){value = v;}          
         ~BOOTCFG(){}    

          uint32 value;
          struct 
          {
            uint32 bootmode : 16;
            uint32          : 16;
          } bit;
        } bootcfg;
        
      private:        
      
        uint32 space2_[5];
        
      public:                
        
        /**
         * Kick 0 Register.
         */
        union KICK0R
        {
          KICK0R(){}
          KICK0R(uint32 v){value = v;}          
         ~KICK0R(){}
         
          uint32 value;
          struct 
          {
            uint32 kick0 : 32;
          } bit;
        } kick0r;               
        
        /**
         * Kick 1 Register.
         */
        union KICK1R
        {
          KICK1R(){}
          KICK1R(uint32 v){value = v;}          
         ~KICK1R(){}    

          uint32 value;
          struct 
          {
            uint32 kick1 : 32;
          } bit;
        } kick1r;
        
        /**
         * Host 0 Configuration Register.
         */
        union HOST0CFG
        {
          HOST0CFG(){}
          HOST0CFG(uint32 v){value = v;}          
         ~HOST0CFG(){}    

          uint32 value;
          struct 
          {
            uint32 bootrdy : 1;
            uint32         : 31;            
          } bit;
        } host0cfg;
        
      private:        
      
        uint32 space3_[39];
        
      public:                
        
        /**
         * Interrupt Raw Status/Set Register.
         */
        union IRAWSTAT
        {
          IRAWSTAT(){}
          IRAWSTAT(uint32 v){value = v;}          
         ~IRAWSTAT(){}    

          uint32 value;
          struct 
          {
            uint32 proterr : 1;
            uint32 addrerr : 1;
            uint32         : 30;            
          } bit;
        } irawstat;
        
        /**
         * Interrupt Enable Status/Clear Register.
         */
        union IENSTAT
        {
          IENSTAT(){}
          IENSTAT(uint32 v){value = v;}          
         ~IENSTAT(){}    

          uint32 value;
          struct 
          {
            uint32 proterr : 1;
            uint32 addrerr : 1;
            uint32         : 30;            
          } bit;
        } ienstat;
        
        /**
         * Interrupt Enable Register.
         */
        union IENSET
        {
          IENSET(){}
          IENSET(uint32 v){value = v;}          
         ~IENSET(){}    

          uint32 value;
          struct 
          {
            uint32 proterrEn : 1;
            uint32 addrerrEn : 1;
            uint32           : 30;            
          } bit;
        } ienset;  
        
        /**
         * Interrupt Enable Clear Register.
         */
        union IENCLR
        {
          IENCLR(){}
          IENCLR(uint32 v){value = v;}          
         ~IENCLR(){}    

          uint32 value;
          struct 
          {
            uint32 proterrClr : 1;
            uint32 addrerrClr : 1;
            uint32            : 30;            
          } bit;
        } ienclr; 
        
        /**
         * End of Interrupt Register.
         */
        union EOI
        {
          EOI(){}
          EOI(uint32 v){value = v;}          
         ~EOI(){}    

          uint32 value;
          struct 
          {
            uint32 eoivect : 8;
            uint32         : 24;
          } bit;
        } eoi;
        
        /**
         * Fault Address Register.
         */
        union FLTADDRR
        {
          FLTADDRR(){}
          FLTADDRR(uint32 v){value = v;}          
         ~FLTADDRR(){}    

          uint32 value;
          struct 
          {
            uint32 fltaddrr : 32;
          } bit;
        } fltaddrr;
        
        /**
         * Fault Status Register.
         */
        union FLTSTAT
        {
          FLTSTAT(){}
          FLTSTAT(uint32 v){value = v;}          
         ~FLTSTAT(){}    

          uint32 value;
          struct 
          {
            uint32 type   : 6;
            uint32        : 3;
            uint32 privid : 4;
            uint32        : 3;
            uint32 mstid  : 8;
            uint32 id     : 8;                                                            
          } bit;
        } fltstat;
        
      private:        
      
        uint32 space4_[5];
        
      public:                
        
        /**
         * Master Priority 0 Register.
         */
        union MSTPRI0
        {
          MSTPRI0(){}
          MSTPRI0(uint32 v){value = v;}          
         ~MSTPRI0(){}    

          uint32 value;
          struct 
          {
            uint32 armI : 3;
            uint32      : 1;
            uint32 armD : 3;
            uint32      : 1;                                    
            uint32      : 3;
            uint32      : 1;
            uint32      : 3;
            uint32      : 1;            
            uint32 upp  : 3;
            uint32      : 1;
            uint32 sata : 3;
            uint32      : 1;                                    
            uint32      : 3;
            uint32      : 1;
            uint32      : 3;
            uint32      : 1;            
          } bit;
        } mstpri0; 
        
        /**
         * Master Priority 1 Register.
         */
        union MSTPRI1
        {
          MSTPRI1(){}
          MSTPRI1(uint32 v){value = v;}          
         ~MSTPRI1(){}    

          uint32 value;
          struct 
          {
            uint32 pru0      : 3;
            uint32           : 1;
            uint32 pru1      : 3;
            uint32           : 1;                                    
            uint32 edms30tc0 : 3;
            uint32           : 1;
            uint32 edma30tc1 : 3;
            uint32           : 1;            
            uint32 edma31tc0 : 3;
            uint32           : 1;
            uint32           : 3;
            uint32           : 1;                                    
            uint32 vpifDma0  : 3;
            uint32           : 1;
            uint32 vpifDma1  : 3;
            uint32           : 1;            
          } bit;
        } mstpri1;
        
        /**
         * Master Priority 2 Register.
         */
        union MSTPRI2
        {
          MSTPRI2(){}
          MSTPRI2(uint32 v){value = v;}          
         ~MSTPRI2(){}    

          uint32 value;
          struct 
          {
            uint32 emac     : 3;
            uint32          : 1;
            uint32          : 3;
            uint32          : 1;                                    
            uint32 usb0cfg  : 3;
            uint32          : 1;
            uint32 usb0cdma : 3;
            uint32          : 1;            
            uint32          : 3;
            uint32          : 1;
            uint32 uhpi     : 3;
            uint32          : 1;                                    
            uint32 usb1     : 3;
            uint32          : 1;
            uint32 lcdc     : 3;
            uint32          : 1;            
          } bit;
        } mstpri2;
        
      private:        
      
        uint32 space5_[1];
        
      public:                
        
        /**
         * Pin Multiplexing Control 0-19 Registers
         */
        union PINMUX
        {
          PINMUX(){}
          PINMUX(uint32 v){value = v;}          
         ~PINMUX(){}    

          uint32 value;
          struct 
          {
            uint32 pinmux3to0   : 4;
            uint32 pinmux7to4   : 4;
            uint32 pinmux11to8  : 4;                                    
            uint32 pinmux15to12 : 4;
            uint32 pinmux19to16 : 4;            
            uint32 pinmux23to20 : 4;
            uint32 pinmux27to24 : 4;
            uint32 pinmux31to28 : 4;                                    
          } bit;
        };
        PINMUX pinmux0;
        PINMUX pinmux1;
        PINMUX pinmux2;
        PINMUX pinmux3;
        PINMUX pinmux4;
        PINMUX pinmux5;
        PINMUX pinmux6;
        PINMUX pinmux7;
        PINMUX pinmux8;
        PINMUX pinmux9;
        PINMUX pinmux10;
        PINMUX pinmux11;
        PINMUX pinmux12;
        PINMUX pinmux13;
        PINMUX pinmux14;
        PINMUX pinmux15;
        PINMUX pinmux16;
        PINMUX pinmux17;
        PINMUX pinmux18;
        PINMUX pinmux19;
        
        /**
         * Suspend Source Register.
         */
        union SUSPSRC
        {
          SUSPSRC(){}
          SUSPSRC(uint32 v){value = v;}          
         ~SUSPSRC(){}    

          uint32 value;
          struct 
          {
            uint32 ecap0src     : 1;
            uint32 ecap1src     : 1;
            uint32 ecap2src     : 1;
            uint32 timer64p3src : 1;
            uint32 uppsrc       : 1;
            uint32 emacsrc      : 1;
            uint32 prusrc       : 1;
            uint32 mcbsp0src    : 1;
            uint32 mcbsp1src    : 1;
            uint32 usb0src      : 1;
            uint32              : 1;
            uint32              : 1;
            uint32 hpisrc       : 1;
            uint32 satasrc      : 1;
            uint32 vpifsrc      : 1;
            uint32              : 1;
            uint32 i2c0src      : 1;
            uint32 i2c1src      : 1;
            uint32 uart0src     : 1;
            uint32 uart1src     : 1;
            uint32 uart2src     : 1;
            uint32 spi0src      : 1;
            uint32 spi1src      : 1;
            uint32 epwm0src     : 1;
            uint32 epwm1src     : 1;
            uint32              : 1;
            uint32              : 1;
            uint32 timer64p0src : 1;
            uint32 timer64p1src : 1;
            uint32 timer64p2src : 1;
            uint32              : 1;
            uint32              : 1;
          } bit;
        } suspsrc;
        
        /**
         * Chip Signal Register.
         */
        union CHIPSIG
        {
          CHIPSIG(){}
          CHIPSIG(uint32 v){value = v;}          
         ~CHIPSIG(){}    

          uint32 value;
          struct 
          {
            uint32 chipsig0 : 1;
            uint32 chipsig1 : 1;
            uint32 chipsig2 : 1;
            uint32 chipsig3 : 1;
            uint32          : 1;
            uint32          : 27;
          } bit;
        } chipsig;
        
        /**
         * Chip Signal Clear Register.
         */
        union CHIPSIG_CLR
        {
          CHIPSIG_CLR(){}
          CHIPSIG_CLR(uint32 v){value = v;}          
         ~CHIPSIG_CLR(){}    

          uint32 value;
          struct 
          {
            uint32 chipsig0 : 1;
            uint32 chipsig1 : 1;
            uint32 chipsig2 : 1;
            uint32 chipsig3 : 1;
            uint32          : 1;
            uint32          : 27;
          } bit;
        } chipsigClr; 
        
        /**
         * Chip Configuration 0 Register.
         */
        union CFGCHIP0
        {
          CFGCHIP0(){}
          CFGCHIP0(uint32 v){value = v;}          
         ~CFGCHIP0(){}    

          uint32 value;
          struct 
          {
            uint32 edma30tc0dbs  : 2;
            uint32 edma30tc1dbs  : 2;
            uint32 pllMasterLock : 1;
            uint32               : 27;
          } bit;
        } cfgchip0;
                                  
        /**
         * Chip Configuration 1 Register.
         */
        union CFGCHIP1
        {
          CFGCHIP1(){}
          CFGCHIP1(uint32 v){value = v;}          
         ~CFGCHIP1(){}    

          uint32 value;
          struct 
          {
            uint32 amutesel0    : 4;
            uint32              : 8;
            uint32 tbclksync    : 1;            
            uint32 edma31tc0dbs : 2;
            uint32 hpiena       : 1;
            uint32 hpibytead    : 1;
            uint32 cap0src      : 5;                        
            uint32 cap1src      : 5;
            uint32 cap2src      : 5;                                    
          } bit;
        } cfgchip1; 
        
        /**
         * Chip Configuration 2 Register.
         */
        union CFGCHIP2
        {
          CFGCHIP2(){}
          CFGCHIP2(uint32 v){value = v;}          
         ~CFGCHIP2(){}    

          uint32 value;
          struct 
          {
            uint32 usb0refFreq   : 4;
            uint32 usb0vbdtcten  : 1;
            uint32 usb0sesnden   : 1;            
            uint32 usb0phyPllon  : 1;
            uint32 usb1suspendm  : 1;
            uint32 usb0datpol    : 1;
            uint32 usb0otgpwrdn  : 1;                        
            uint32 usb0phypwdn   : 1;
            uint32 usb0phyclkmux : 1;                                    
            uint32 usb1phyclkmux : 1;                                    
            uint32 usb0otgmode   : 2;                                    
            uint32 reset         : 1;                                    
            uint32 usb0vbussense : 1;                                    
            uint32 usb0phyclkgd  : 1;                                    
            uint32               : 14;                                                                                                            
          } bit;
        } cfgchip2;
        
        /**
         * Chip Configuration 3 Register.
         */
        union CFGCHIP3
        {
          CFGCHIP3(){}
          CFGCHIP3(uint32 v){value = v;}          
         ~CFGCHIP3(){}    

          uint32 value;
          struct 
          {
            uint32                : 1;
            uint32 emaClksrc      : 1;
            uint32 div45pena      : 1;            
            uint32 pruevtsel      : 1;
            uint32 async3Clksrc   : 1;
            uint32 pll1MasterLock : 1;
            uint32 uppTxClksrc    : 1;                        
            uint32                : 1;
            uint32 rmii_sel       : 1;                                    
            uint32                : 23;                                    
          } bit;
        } cfgchip3;    
        
        /**
         * Chip Configuration 4 Register.
         */
        union CFGCHIP4
        {
          CFGCHIP4(){}
          CFGCHIP4(uint32 v){value = v;}          
         ~CFGCHIP4(){}    

          uint32 value;
          struct 
          {
            uint32 amuteclr0 : 1;
            uint32           : 7;
            uint32           : 24;            
          } bit;
        } cfgchip4;                                   
                                
      };
    }
  }
}
#endif // BOOS_CORE_AM18X_REGISRES_SYSCFG0_HPP_
