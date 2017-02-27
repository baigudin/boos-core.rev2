/**
 * TI TMS320F2833x/F2823x DSC Pulse Width Modulator registers, including High Resolution and Enhanced PWM.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_REGISRES_PWM_HPP_
#define BOOS_TARGET_REGISRES_PWM_HPP_

#include "boos.Types.hpp"

namespace target
{
  namespace registers
  {
    struct Pwm
    {
    
    public:
    
      /**
       * Default configuration addresses in PF1.
       */
      static const uint32 ADDRESS0 = 0x00006800;
      static const uint32 ADDRESS1 = 0x00006840;
      static const uint32 ADDRESS2 = 0x00006880;
      static const uint32 ADDRESS3 = 0x000068C0;
      static const uint32 ADDRESS4 = 0x00006900;
      static const uint32 ADDRESS5 = 0x00006940;
      
      /**
       * Remapped configuration addresses in PF3 - DMA-Accessible.
       */
      static const uint32 REMAP_ADDRESS0 = 0x00005800;
      static const uint32 REMAP_ADDRESS1 = 0x00005840;
      static const uint32 REMAP_ADDRESS2 = 0x00005880;
      static const uint32 REMAP_ADDRESS3 = 0x000058C0;
      static const uint32 REMAP_ADDRESS4 = 0x00005900;
      static const uint32 REMAP_ADDRESS5 = 0x00005940;  
    
      /** 
       * Constructor.
       */  
      Pwm() :
        tbctl   (), // ALLOWED
        tbsts   (), // ALLOWED
        tbphshr (), // ALLOWED
        tbphs   (), // ALLOWED
        tbctr   (), // ALLOWED
        tbprd   (), // ALLOWED
        cmpctl  (), // ALLOWED
        cmpahr  (), // ALLOWED
        aqsfrc  (), // ALLOWED
        aqcsfrc (), // ALLOWED
        dbctl   (), // ALLOWED
        dbred   (), // ALLOWED
        dbfed   (), // ALLOWED
        tzsel   (), // PROTECTED  
        tzctl   (), // PROTECTED  
        tzeint  (), // PROTECTED  
        tzflg   (), // ALLOWED
        tzclr   (), // PROTECTED  
        tzfrc   (), // PROTECTED  
        etsel   (), // ALLOWED  
        etps    (), // ALLOWED  
        etflg   (), // ALLOWED  
        etclr   (), // ALLOWED  
        etfrc   (), // ALLOWED  
        pcctl   (), // ALLOWED  
        hrcnfg  (){ // PROTECTED
      }
      
      /** 
       * Destructor.
       */    
     ~Pwm(){}    
      
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
      
      // NOT EALLOW PROTECTED  
    
      /**
       * Time Base Control Register.
       */
      union Tbctl
      {
        Tbctl(){}
        Tbctl(uint16 v){val = v;}          
       ~Tbctl(){}    
       
        uint16 val;
        struct Val
        {
          // CLKDIV bits
          static const uint16 CLKDIV_1   = 0x0000;  // default on reset 
          static const uint16 CLKDIV_2   = 0x0001;
          static const uint16 CLKDIV_4   = 0x0002;
          static const uint16 CLKDIV_8   = 0x0003;
          static const uint16 CLKDIV_16  = 0x0004;
          static const uint16 CLKDIV_32  = 0x0005;
          static const uint16 CLKDIV_64  = 0x0006;            
          static const uint16 CLKDIV_128 = 0x0007;  
          // HSPCLKDIV bits
          static const uint16 HSPCLKDIV_1  = 0x0000;
          static const uint16 HSPCLKDIV_2  = 0x0001; // default on reset 
          static const uint16 HSPCLKDIV_4  = 0x0002;
          static const uint16 HSPCLKDIV_6  = 0x0003;
          static const uint16 HSPCLKDIV_8  = 0x0004;
          static const uint16 HSPCLKDIV_10 = 0x0005;
          static const uint16 HSPCLKDIV_12 = 0x0006;            
          static const uint16 HSPCLKDIV_14 = 0x0007;        
          // CTRMODE bits
          static const uint16 COUNT_UP     = 0x0;
          static const uint16 COUNT_DOWN   = 0x1;
          static const uint16 COUNT_UPDOWN = 0x2;
          static const uint16 COUNT_FREEZE = 0x3; // default on reset 
          // PHSEN bits
          static const uint16 DISABLE = 0x0;
          static const uint16 ENABLE  = 0x1;
          // PRDLD bits
          static const uint16 SHADOW    = 0x0;
          static const uint16 IMMEDIATE = 0x1;     
          // SYNCOSEL bits
          static const uint16 SYNC_IN      = 0x0;
          static const uint16 CTR_ZERO     = 0x1;
          static const uint16 CTR_CMPB     = 0x2;
          static const uint16 SYNC_DISABLE = 0x3;
          
          uint16 ctrmode   : 2;
          uint16 phsen     : 1;
          uint16 prdld     : 1;
          uint16 syncosel  : 2;
          uint16 swfsync   : 1;
          uint16 hspclkdiv : 3;
          uint16 clkdiv    : 3;
          uint16 phsdir    : 1;
          uint16 freesoft  : 2;
        } bit;
      } tbctl;  
    
      /**
       * Time Base Status Register.
       */
      union Tbsts
      {
        Tbsts(){}
        Tbsts(uint16 v){val = v;}          
       ~Tbsts(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 ctrdir : 1;
          uint16 synci  : 1; 
          uint16 ctrmax : 1;
          uint16        : 13;
        } bit;
      } tbsts;
      
      /**
       * Time Base Phase HRPWM Register.
       */
      union Tbphshr
      {
        Tbphshr(){}
        Tbphshr(uint16 v){val = v;}          
       ~Tbphshr(){}    
    
        uint16 val;
        struct Val 
        {
          uint16        : 8;    
          uint16 tbphsh : 8;
        } bit;
      } tbphshr;
      
      /**
       * Time Base Phase Register.
       */
      union Tbphs
      {
        Tbphs(){}
        Tbphs(uint16 v){val = v;}          
       ~Tbphs(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 tbphs : 16;
        } bit;
      } tbphs;
      
      /**
       * Time Base Counter Register.
       */
      union Tbctr
      {
        Tbctr(){}
        Tbctr(uint16 v){val = v;}          
       ~Tbctr(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 tbctr : 16;
        } bit;
      } tbctr;
      
      /**
       * Time Base Period Register Set.
       */
      union Tbprd
      {
        Tbprd(){}
        Tbprd(uint16 v){val = v;}          
       ~Tbprd(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 tbprd: 16;
        } bit;
      } tbprd;
    
    private:        
    
      uint16 space0_[1];
      
    public:
    
      /**
       * Counter Compare Control Register.
       */
      union Cmpctl
      {
        Cmpctl(){}
        Cmpctl(uint16 v){val = v;}          
       ~Cmpctl(){}    
    
        uint16 val;
        struct Val 
        {
          // LOADAMODE and LOADBMODE bits
          static const uint16 LOAD_CTR_EQ_ZERO         = 0x0000;
          static const uint16 LOAD_CTR_EQ_PRD          = 0x0001;
          static const uint16 LOAD_CTR_EQ_ZERO_AND_PRD = 0x0002;
          static const uint16 LOAD_FREEZE              = 0x0003;      
          // SHDWBMODE bits
          static const uint16 SHADOW    = 0x0;
          static const uint16 IMMEDIATE = 0x1;        
         
          uint16 loadamode : 2;
          uint16 loadbmode : 2;
          uint16 shdwamode : 1;
          uint16           : 1;
          uint16 shdwbmode : 1;
          uint16           : 1;
          uint16 shdwafull : 1;
          uint16 shdwbfull : 1;
          uint16           : 6;
        } bit;
      } cmpctl;
      
      /**
       * Time Base Compare A HRPWM Register.
       */
      union Cmpahr
      {
        Cmpahr(){}
        Cmpahr(uint16 v){val = v;}          
       ~Cmpahr(){}    
    
        uint16 val;
        struct Val 
        {
          uint16        : 8;
          uint16 cmpahr : 8;      
        } bit;
      } cmpahr;
      
      /**
       * Counter Compare A and B Registers Set.
       */
      union Cmp
      {
        Cmp(){}
        Cmp(uint16 v){val = v;}          
       ~Cmp(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 cmp : 16;
        } bit;
      } cmp[2];
      
      /**
       * Action Qualifier Control Register For Output A and B.
       */
      union Aqctl
      {
        Aqctl(){}
        Aqctl(uint16 v){val = v;}          
       ~Aqctl(){}    
    
        uint16 val;
        struct Val 
        {
          // ZRO, PRD, CAU, CAD, CBU, and CBD bits
          static const uint16 DISABLE = 0x0;
          static const uint16 CLEAR   = 0x1;
          static const uint16 SET     = 0x2;
          static const uint16 TOGGLE  = 0x3;      
          
          uint16 zro : 2; 
          uint16 prd : 2;
          uint16 cau : 2;
          uint16 cad : 2;
          uint16 cbu : 2;
          uint16 cbd : 2;
          uint16     : 4;
        } bit;
      } aqctl[2];
      
      /**
       * Action Qualifier Software Force Register.
       */
      union Aqsfrc
      {
        Aqsfrc(){}
        Aqsfrc(uint16 v){val = v;}          
       ~Aqsfrc(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 actsfa : 2;  
          uint16 otsfa  : 1;
          uint16 actsfb : 2;
          uint16 otsfb  : 1;
          uint16 rldcsf : 2;
          uint16        : 8;
        } bit;
      } aqsfrc;
      
      /**
       * Action Qualifier Continuous S/W Force Register Set.
       */
      union Aqcsfrc
      {
        Aqcsfrc(){}
        Aqcsfrc(uint16 v){val = v;}          
       ~Aqcsfrc(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 csfa : 2;
          uint16 csfb : 2;
          uint16      : 12;
        } bit;
      } aqcsfrc;
      
      /**
       * Dead-Band Generator Control Register.
       */
      union Dbctl
      {
        Dbctl(){}
        Dbctl(uint16 v){val = v;}          
       ~Dbctl(){}    
    
        uint16 val;
        struct Val 
        {
          // OUT MODE bits
          static const uint16 DISABLE     = 0x0;
          static const uint16 A_ENABLE    = 0x1;
          static const uint16 B_ENABLE    = 0x2;
          static const uint16 FULL_ENABLE = 0x3;
          // POLSEL bits
          static const uint16 ACTV_HI  = 0x0;
          static const uint16 ACTV_LOC = 0x1;
          static const uint16 ACTV_HIC = 0x2;
          static const uint16 ACTV_LO  = 0x3;
          // IN MODE;
          static const uint16 A_ALL       = 0x0;
          static const uint16 B_RED_A_FED = 0x1;
          static const uint16 A_RED_B_FED = 0x2;
          static const uint16 B_ALL       = 0x3;
          
          uint16 outMode : 2;
          uint16 polsel  : 2;
          uint16 inMode  : 2;
          uint16         : 10;
        } bit;
      } dbctl;
      
      /**
       * Dead-Band Generator Rising Edge Delay Count Register.
       */
      union Dbred
      {
        Dbred(){}
        Dbred(uint16 v){val = v;}          
       ~Dbred(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 del : 10;    
          uint16     : 6;
        } bit;
      } dbred;
      
      /**
       * Dead-Band Generator Falling Edge Delay Count Register.
       */
      union Dbfed
      {
        Dbfed(){}
        Dbfed(uint16 v){val = v;}          
       ~Dbfed(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 del : 10;    
          uint16     : 6;
        } bit;
      } dbfed;
      
      // EALLOW PROTECTED  
      
      /**
       * Trip Zone Select Register(1).
       */
      union Tzsel
      {
        Tzsel(){}
        Tzsel(uint16 v){val = v;}          
       ~Tzsel(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 cbc1  : 1;
          uint16 cbc2  : 1;
          uint16 cbc3  : 1;
          uint16 cbc4  : 1;
          uint16 cbc5  : 1;
          uint16 cbc6  : 1;
          uint16       : 2;
          uint16 osht1 : 1;
          uint16 osht2 : 1;
          uint16 osht3 : 1;
          uint16 osht4 : 1;
          uint16 osht5 : 1;
          uint16 osht6 : 1;
          uint16       : 2;
          
        } bit;
      } tzsel;
    
    private:        
    
      uint16 space1_[1];
      
    public:
    
      /**
       * Trip Zone Control Register(1).
       */
      union Tzctl
      {
        Tzctl(){}
        Tzctl(uint16 v){val = v;}          
       ~Tzctl(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 tza : 2;
          uint16 tzb : 2;      
          uint16     : 12;      
        } bit;
      } tzctl;
      
      /**
       * Trip Zone Enable Interrupt Register(1).
       */
      union Tzeint
      {
        Tzeint(){}
        Tzeint(uint16 v){val = v;}          
       ~Tzeint(){}    
    
        uint16 val;
        struct Val 
        {
          uint16     : 1;
          uint16 cbc : 1;
          uint16 ost : 1;      
          uint16     : 13;
        } bit;
      } tzeint;
      
      // NOT EALLOW PROTECTED
      
      /**
       * Trip Zone Flag Register.
       */
      union Tzflg
      {
        Tzflg(){}
        Tzflg(uint16 v){val = v;}          
       ~Tzflg(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 intb : 1;
          uint16 cbc  : 1;
          uint16 ost  : 1;      
          uint16      : 13;
        } bit;
      } tzflg;
      
      // EALLOW PROTECTED  
      
      /**
       * Trip Zone Clear Register(1).
       */
      union Tzclr
      {
        Tzclr(){}
        Tzclr(uint16 v){val = v;}          
       ~Tzclr(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 intb : 1;
          uint16 cbc  : 1;
          uint16 ost  : 1;      
          uint16      : 13;
        } bit;
      } tzclr;
      
      /**
       * Trip Zone Force Register(1).
       */
      union Tzfrc
      {
        Tzfrc(){}
        Tzfrc(uint16 v){val = v;}          
       ~Tzfrc(){}    
    
        uint16 val;
        struct Val 
        {
          uint16     : 1;
          uint16 cbc : 1;
          uint16 ost : 1;      
          uint16     : 13;
        } bit;
      } tzfrc;
      
      // NOT EALLOW PROTECTED  
    
      /**
       * Event Trigger Selection Register.
       */
      union Etsel
      {
        Etsel(){}
        Etsel(uint16 v){val = v;}          
       ~Etsel(){}    
    
        uint16 val;
        struct Val 
        {
          // OUT MODE bits
          static const uint16 CTR_ZERO  = 0x1;
          static const uint16 CTR_PRD   = 0x2;
          static const uint16 CTRU_CMPA = 0x4;
          static const uint16 CTRD_CMPA = 0x5;
          static const uint16 CTRU_CMPB = 0x6;
          static const uint16 CTRD_CMPB = 0x7;
          
          uint16 intsel  : 3;
          uint16 inten   : 1;
          uint16         : 4;
          uint16 socasel : 3;
          uint16 socaen  : 1;
          uint16 socbsel : 3;
          uint16 socben  : 1;
        } bit;
      } etsel;
      
      /**
       * Event Trigger Prescale Register.
       */
      union Etps
      {
        Etps(){}
        Etps(uint16 v){val = v;}          
       ~Etps(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 intprd  : 2;
          uint16 intcnt  : 2;
          uint16         : 4;
          uint16 socaprd : 2;
          uint16 socacnt : 2;
          uint16 socbprd : 2;
          uint16 socbcnt : 2;
        } bit;
      } etps;
    
      /**
       * Event Trigger Flag Register.
       */
      union Etflg
      {
        Etflg(){}
        Etflg(uint16 v){val = v;}          
       ~Etflg(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 intb : 1;
          uint16      : 1;
          uint16 soca : 1;
          uint16 socb : 1;
          uint16      : 12;
        } bit;
      } etflg;
      
      /**
       * Event Trigger Clear Register.
       */
      union Etclr
      {
        Etclr(){}
        Etclr(uint16 v){val = v;}          
       ~Etclr(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 intb : 1;
          uint16      : 1;
          uint16 soca : 1;
          uint16 socb : 1;
          uint16      : 12;
        } bit;
      } etclr;
      
      /**
       * Event Trigger Force Register.
       */
      union Etfrc
      {
        Etfrc(){}
        Etfrc(uint16 v){val = v;}          
       ~Etfrc(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 intb : 1;
          uint16      : 1;
          uint16 soca : 1;
          uint16 socb : 1;
          uint16      : 12;
        } bit;
      } etfrc;
      
      /**
       * PWM Chopper Control Register.
       */
      union Pcctl
      {
        Pcctl(){}
        Pcctl(uint16 v){val = v;}          
       ~Pcctl(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 chpen   : 1;
          uint16 oshtwth : 4;
          uint16 chpfreq : 3;
          uint16 chpduty : 3;
          uint16         : 5;
        } bit;
      } pcctl;
    
    private:        
    
      uint16 space2_[1];
      
    public:
    
      // EALLOW PROTECTED
    
      /**
       * HRPWM Configuration Register.
       */
      union Hrcnfg
      {
        Hrcnfg(){}
        Hrcnfg(uint16 v){val = v;}          
       ~Hrcnfg(){}    
    
        uint16 val;
        struct Val 
        {
          uint16 edgmode : 2;
          uint16 ctlmode : 1;
          uint16 hrload  : 1;
          uint16         : 12;
        } bit;
      } hrcnfg;
    
    };
  }
}
#endif // BOOS_TARGET_REGISRES_PWM_HPP_
