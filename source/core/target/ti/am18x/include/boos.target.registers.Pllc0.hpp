/** 
 * TI ARM AM18x Phase-Locked Loop Controller (PLLC).
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_REGISRES_PLLC0_HPP_
#define BOOS_TARGET_REGISRES_PLLC0_HPP_

#include "boos.Types.hpp"

namespace target
{
  namespace registers
  {
    struct Pllc0
    {

    public:
    
      static const uint32 ADDRESS = 0x01C11000;    

      /** 
       * Constructor.
       */  
      Pllc0() :
        revid(),
        rstype(),
        rsctrl(),
        pllctl(),      
        ocsel(),      
        pllm(),
        prediv(),      
        plldiv1(),
        plldiv2(),
        plldiv3(),
        oscdiv(),      
        postdiv(),      
        pllcmd(),      
        pllstat(),      
        alnctl(),      
        dchange(),      
        cken(),      
        ckstat(),
        systat(),      
        plldiv4(),
        plldiv5(),
        plldiv6(),
        plldiv7(),
        emucnt0(),      
        emucnt1(){
      }
      
      /** 
       * Destructor.
       */  
     ~Pllc0(){}
     
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
       * PLLC0 Divider Register base.
       */
      union PLLDIV
      {
        PLLDIV(){}
        PLLDIV(uint32 v){value = v;}          
       ~PLLDIV(){}    

        uint32 value;
        struct 
        {
          uint32 ratio : 5;
          uint32       : 10;
          uint32 dNen  : 1;
          uint32       : 16;
        } bit;
      };
      
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
    
      uint32 space0_[56];
      
    public:
    
      /**
       * Reset Type Status Register.
       */
      union RSTYPE
      {
        RSTYPE(){}
        RSTYPE(uint32 v){value = v;}
       ~RSTYPE(){}    

        uint32 value;
        struct 
        {
          uint32 por      : 1;
          uint32 xwrst    : 1;
          uint32 pllswrst : 1;
          uint32          : 29;            
        } bit;
      } rstype;
    
      /**
       * PLLC0 Reset Control Register.
       */
      union RSCTRL
      {
        RSCTRL(){}
        RSCTRL(uint32 v){value = v;}          
       ~RSCTRL(){}    

        uint32 value;
        struct 
        {
          uint32 key   : 16;
          uint32 swrst : 1;
          uint32       : 15;            
        } bit;
      } rsctrl;
      
    private:        
    
      uint32 space1_[5];
      
    public:
    
      /**
       * PLLC0 Control Register.
       */
      union PLLCTL
      {
        PLLCTL(){}
        PLLCTL(uint32 v){value = v;}          
       ~PLLCTL(){}    

        uint32 value;
        struct 
        {
          uint32 pllen     : 1;
          uint32 pllpwrdn  : 1;
          uint32           : 1;
          uint32 pllrst    : 1;
          uint32           : 1;
          uint32 pllensrc  : 1;            
          uint32           : 2;
          uint32 clkmode   : 1;
          uint32 extclksrc : 1;            
          uint32           : 22;
        } bit;
      } pllctl;      
     
      
      /**
       * PLLC0 OBSCLK Select Register.
       */
      union OCSEL
      {
        OCSEL(){}
        OCSEL(uint32 v){value = v;}          
       ~OCSEL(){}    

        uint32 value;
        struct 
        {
          uint32 ocsrc : 5;
          uint32       : 27;
        } bit;
      } ocsel;      
      
    private:        
    
      uint32 space3_[2];
      
    public:
                        
      /**
       * PLL Multiplier Control Register.
       */
      union PLLM
      {
        PLLM(){}
        PLLM(uint32 v){value = v;}          
       ~PLLM(){}    

        uint32 value;
        struct
        {
          uint32 pllm : 5;
          uint32      : 27;
        } bit;
      } pllm;

      /**
       * PLLC0 Pre-Divider Control Register.
       */
      union PREDIV
      {
        PREDIV(){}
        PREDIV(uint32 v){value = v;}          
       ~PREDIV(){}    

        uint32 value;
        struct 
        {
          uint32 ratio  : 5;
          uint32        : 10;
          uint32 preden : 1;
          uint32        : 16;
        } bit;
      } prediv;      

      /**
       * PLLC0 Divider 1 Register.
       */
      PLLDIV plldiv1;

      /**
       * PLLC0 Divider 2 Register.
       */
      PLLDIV plldiv2;

      /**
       * PLLC0 Divider 3 Register.
       */
      PLLDIV plldiv3;

      /**
       * PLLC0 Oscillator Divider 1 Register.
       */
      union OSCDIV
      {
        OSCDIV(){}
        OSCDIV(uint32 v){value = v;}          
       ~OSCDIV(){}    

        uint32 value;
        struct 
        {
          uint32 ratio : 5;
          uint32       : 10;
          uint32 od1en : 1;
          uint32       : 16;
        } bit;
      } oscdiv;      

      /**
       * PLL Post-Divider Control Register.
       */
      union POSTDIV
      {
        POSTDIV(){}
        POSTDIV(uint32 v){value = v;}          
       ~POSTDIV(){}    

        uint32 value;
        struct 
        {
          uint32 ratio   : 5;
          uint32         : 10;
          uint32 postden : 1;
          uint32         : 16;
        } bit;
      } postdiv;      

    private:        
    
      uint32 space4_[3];
      
    public:
                        
      /**
       * PLL Controller Command Register.
       */
      union PLLCMD
      {
        PLLCMD(){}
        PLLCMD(uint32 v){value = v;}          
       ~PLLCMD(){}    

        uint32 value;
        struct 
        {
          uint32 goset : 1;
          uint32       : 15;
        } bit;
      } pllcmd;      

      /**
       * PLL Controller Status Register.
       */
      union PLLSTAT
      {
        PLLSTAT(){}
        PLLSTAT(uint32 v){value = v;}          
       ~PLLSTAT(){}    

        uint32 value;
        struct 
        {
          uint32 gostat : 1;
          uint32        : 1;
          uint32 stable : 1;
          uint32        : 29;
        } bit;
      } pllstat;      

      /**
       * PLLC0 Clock Align Control Register.
       */
      union ALNCTL
      {
        ALNCTL(){}
        ALNCTL(uint32 v){value = v;}          
       ~ALNCTL(){}    

        uint32 value;
        struct 
        {
          uint32 aln1 : 1;
          uint32 aln2 : 1;
          uint32 aln3 : 1;
          uint32 aln4 : 1;
          uint32 aln5 : 1;
          uint32 aln6 : 1;
          uint32 aln7 : 1;
          uint32      : 25;
        } bit;
      } alnctl;      

      /**
       * PLLC0 PLLDIV Ratio Change Status Register.
       */
      union DCHANGE
      {
        DCHANGE(){}
        DCHANGE(uint32 v){value = v;}          
       ~DCHANGE(){}    
             
        uint32 value;
        struct 
        {
          uint32 sys1 : 1;
          uint32 sys2 : 1;
          uint32 sys3 : 1;
          uint32 sys4 : 1;
          uint32 sys5 : 1;
          uint32 sys6 : 1;
          uint32 sys7 : 1;
          uint32      : 25;
        } bit;
      } dchange;      

      /**
       * PLLC0 Clock Enable Control Register.
       */
      union CKEN
      {
        CKEN(){}
        CKEN(uint32 v){value = v;}          
       ~CKEN(){}    

        uint32 value;
        struct 
        {
          uint32 auxen : 1;
          uint32 obsen : 1;
          uint32       : 30;
        } bit;
      } cken;

      /**
       * PLLC0 Clock Status Register.
       */
      union CKSTAT
      {
        CKSTAT(){}
        CKSTAT(uint32 v){value = v;}          
       ~CKSTAT(){}    

        uint32 value;
        struct 
        {
          uint32 auxen : 1;
          uint32 obsen : 1;
          uint32       : 30;
        } bit;
      } ckstat;

      /**
       * PLLC0 SYSCLK Status Register.
       */
      union SYSTAT
      {
        SYSTAT(){}
        SYSTAT(uint32 v){value = v;}          
       ~SYSTAT(){}    

        uint32 value;
        struct 
        {
          uint32 sys1on : 1;
          uint32 sys2on : 1;
          uint32 sys3on : 1;
          uint32 sys4on : 1;
          uint32 sys5on : 1;
          uint32 sys6on : 1;
          uint32 sys7on : 1;
          uint32        : 25;
        } bit;
      } systat;      

    private:        
    
      uint32 space5_[3];
      
    public:
                        
      /**
       * PLLC0 Divider 4 Register.
       */
      PLLDIV plldiv4;

      /**
       * PLLC0 Divider 5 Register.
       */
      PLLDIV plldiv5;

      /**
       * PLLC0 Divider 6 Register.
       */
      PLLDIV plldiv6;

      /**
       * PLLC0 Divider 7 Register.
       */
      PLLDIV plldiv7;


    private:        
    
      uint32 space6_[32];
      
    public:
                        
      /**
       * Emulation Performance Counter 0 Register.
       */
      union EMUCNT0
      {
        EMUCNT0(){}
        EMUCNT0(uint32 v){value = v;}          
       ~EMUCNT0(){}    

        uint32 value;
        struct 
        {
          uint32 count : 32;
        } bit;
      } emucnt0;      

      /**
       * Emulation Performance Counter 1 Register.
       */
      union EMUCNT1
      {
        EMUCNT1(){}
        EMUCNT1(uint32 v){value = v;}          
       ~EMUCNT1(){}    

        uint32 value;
        struct 
        {
          uint32 count : 32;
        } bit;
      } emucnt1;      

    };
  }
} 
#endif // BOOS_TARGET_REGISRES_PLLC0_HPP_
