/** 
 * TI ARM AM18x 64-Bit Timer.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_REGISRES_TIMER_HPP_
#define BOOS_TARGET_REGISRES_TIMER_HPP_

#include "boos.Types.hpp"

namespace target
{
  namespace registers
  {
    struct Timer
    {

    public:

      static const uint32 ADDRESS0 = 0x01c20000;
      static const uint32 ADDRESS1 = 0x01c21000;
      static const uint32 ADDRESS2 = 0x01f0c000;
      static const uint32 ADDRESS3 = 0x01f0d000;
      
      /** 
       * Constructor.
       */  
      Timer() :
        revid(),
        emumgt(),
        gpintgpen(),
        gpdatgpdir(),
        tim12(),
        tim34(),
        prd12(),
        prd34(),
        tcr(),
        tgcr(),
        wdtcr(),
        rel12(),
        rel34(),
        cap12(),
        cap34(),
        ntctlstat(){
      }
      
      /** 
       * Destructor.
       */  
     ~Timer(){}
     
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
       * Revision ID Register.
       */
      union REVID
      {
        REVID(){}
        REVID(uint32 v){value = v;}          
       ~REVID(){}    

        uint32 value;
        struct 
        {
          uint32 rev: 32;
        } bit;
      } revid;

      /**
       * Emulation Management Register.
       */
      union EMUMGT
      {
        EMUMGT(){}
        EMUMGT(uint32 v){value = v;}          
       ~EMUMGT(){}    

        uint32 value;
        struct 
        {
          uint32 free: 1;
          uint32 soft: 1;
          uint32     : 30;
        } bit;
      } emumgt;

      /**
       * GPIO Interrupt Control and Enable Register.
       */
      union GPINTGPEN
      {
        GPINTGPEN(){}
        GPINTGPEN(uint32 v){value = v;}          
       ~GPINTGPEN(){}    

        uint32 value;
        struct 
        {
          uint32 gpint12eni  : 1;
          uint32 gpint12eno  : 1;
          uint32             : 2;
          uint32 gpint12invi : 1;
          uint32 gpint12invo : 1;
          uint32             : 10;
          uint32 gpeni12     : 1;
          uint32 gpeno12     : 1;
          uint32             : 14;
        } bit;
      } gpintgpen;

      /**
       * GPIO Data and Direction Register.
       */
      union GPDATGPDIR
      {
        GPDATGPDIR(){}
        GPDATGPDIR(uint32 v){value = v;}          
       ~GPDATGPDIR(){}    

        uint32 value;
        struct 
        {
          uint32 gpdati12 : 1;
          uint32 gpdato12 : 1;
          uint32          : 14;
          uint32 gpdiri12 : 1;
          uint32 gpdiro12 : 1;
          uint32          : 14;                        
        } bit;
      } gpdatgpdir;

      /**
       * Timer Counter Register 12.
       */
      union TIM12
      {
        TIM12(){}
        TIM12(uint32 v){value = v;}          
       ~TIM12(){}    

        uint32 value;
        struct 
        {
          uint32 tim12 : 32;
        } bit;
      } tim12;

      /**
       * Timer Counter Register 34.
       */
      union TIM34
      {
        TIM34(){}
        TIM34(uint32 v){value = v;}          
       ~TIM34(){}    

        uint32 value;
        struct 
        {
          uint32 tim34 : 32;
        } bit;
      } tim34;

      /**
       * Timer Period Register 12.
       */
      union PRD12
      {
        PRD12(){}
        PRD12(uint32 v){value = v;}
       ~PRD12(){}    

        uint32 value;
        struct
        {
          uint32 prd12 : 32;
        } bit;
      } prd12;

      /**
       * Timer Period Register 34.
       */
      union PRD34
      {
        PRD34(){}
        PRD34(uint32 v){value = v;}          
       ~PRD34(){}    

        uint32 value;
        struct 
        {
          uint32 prd34 : 32;
        } bit;
      } prd34;

      /**
       * Timer Control Register.
       */
      union TCR
      {
        TCR(){}
        TCR(uint32 v){value = v;}          
       ~TCR(){}    

        uint32 value;
        struct 
        {
          uint32 tstat12       : 1;
          uint32 invoutp12     : 1;
          uint32 invinp12      : 1;
          uint32 cp12          : 1;
          uint32 pwid12        : 2;
          uint32 enamode12     : 2;
          uint32 clksrc12      : 1;
          uint32 tien12        : 1;
          uint32 readrstmode12 : 1;
          uint32 capmode12     : 1;
          uint32 capvtmode12   : 2;
          uint32               : 8;
          uint32 enamode34     : 2;
          uint32               : 2;
          uint32 readrstmode34 : 1;
          uint32               : 5;
        } bit;
      } tcr;

      /**
       * Timer Global Control Register.
       */
      union TGCR
      {
        TGCR(){}
        TGCR(uint32 v){value = v;}          
       ~TGCR(){}    

        uint32 value;
        struct 
        {
          uint32 tim12rs : 1;
          uint32 tim34rs : 1;
          uint32 timmode : 2;
          uint32 plusen  : 1;
          uint32         : 3;
          uint32 psc34   : 4;
          uint32 tddr34  : 4;
          uint32         : 16;
        } bit;
      } tgcr;

      /**
       * Watchdog Timer Control Register.
       */
      union WDTCR
      {
        WDTCR(){}
        WDTCR(uint32 v){value = v;}          
       ~WDTCR(){}    

        uint32 value;
        struct 
        {
          uint32        : 14;
          uint32 wden   : 1;
          uint32 wdflag : 1;
          uint32 wdkey  : 16;
        } bit;
      } wdtcr;

    private:        
    
      uint32 space0_[2];
      
    public:
                        
      /**
       * Timer Reload Register 12.
       */
      union REL12
      {
        REL12(){}
        REL12(uint32 v){value = v;}          
       ~REL12(){}    

        uint32 value;
        struct 
        {
          uint32 rel12 : 32;
        } bit;
      } rel12;

      /**
       * Timer Reload Register 34.
       */
      union REL34
      {
        REL34(){}
        REL34(uint32 v){value = v;}          
       ~REL34(){}    

        uint32 value;
        struct 
        {
          uint32 rel34 : 32;
        } bit;
      } rel34;

      /**
       * Timer Capture Register 12.
       */
      union CAP12
      {
        CAP12(){}
        CAP12(uint32 v){value = v;}          
       ~CAP12(){}    

        uint32 value;
        struct 
        {
          uint32 cap12 : 32;
        } bit;
      } cap12;

      /**
       * Timer Capture Register 34.
       */
      union CAP34
      {
        CAP34(){}
        CAP34(uint32 v){value = v;}          
       ~CAP34(){}    

        uint32 value;
        struct 
        {
          uint32 cap34 : 32;
        } bit;
      } cap34;

      /**
       * Timer Interrupt Control and Status Register.
       */
      union NTCTLSTAT
      {
        NTCTLSTAT(){}
        NTCTLSTAT(uint32 v){value = v;}          
       ~NTCTLSTAT(){}    

        uint32 value;
        struct 
        {
          uint32 prdinten12   : 1;
          uint32 prdintstat12 : 1;
          uint32 evtinten12   : 1;
          uint32 evtintstat12 : 1;
          uint32              : 12;
          uint32 prdinten34   : 1;
          uint32 prdintstat34 : 1;
          uint32 evtinten34   : 1;
          uint32 evtintstat34 : 1;
          uint32              : 12;
        } bit;
      } ntctlstat;

    private:        
    
      uint32 space1_[6];
      
    public:
           
      /**
       * Timer Compare Registers.
       */
      union CMP
      {
        CMP(){}
        CMP(uint32 v){value = v;}          
       ~CMP(){}    

        uint32 value;
        struct 
        {
          uint32 cmp : 32;
        } bit;
      } cmp[8];

    };
  }
} 
#endif // BOOS_TARGET_REGISRES_TIMER_HPP_
