/** 
 * TI ARM AM18x Phase-Locked Loop Controller (PLLC).
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_AM18X_REGISRES_PLLC1_HPP_
#define BOOS_CORE_AM18X_REGISRES_PLLC1_HPP_

#include "boos.core.am18x.registers.Mapped.hpp"

namespace core
{
  namespace am18x
  {
    namespace registers
    {
      struct PLLC1 : public Mapped
      {

      public:

        PLLC1(){}
       ~PLLC1(){}

        static const uint32 ADDRESS = 0x01E1A000;
        
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
         * PLLC1 Revision Identification Register.
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
      
        uint32 space0_[0x3f];
        
      public:
                          
        /**
         * PLLC1 Control Register.
         */
        union PLLCTL
        {
          PLLCTL(){}
          PLLCTL(uint32 v){value = v;}          
         ~PLLCTL(){}    

          uint32 value;
          struct 
          {
            uint32 pllen    : 1;
            uint32 pllpwrdn : 1;
            uint32          : 1;
            uint32 pllrst   : 1;                                    
            uint32          : 1;
            uint32 pllensrc : 1;
            uint32          : 26;
          } bit;
        } pllctl;

        /**
         * PLLC1 OBSCLK Select Register.
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
      
        uint32 space1_[2];
        
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

      private:        
      
        uint32 space2_[1];
        
      public:
                          
        /**
         * PLLC1 Divider 1 Register.
         */
        PLLDIV plldiv1;

        /**
         * PLLC1 Divider 2 Register.
         */
        PLLDIV plldiv2;

        /**
         * PLLC1 Divider 3 Register.
         */
        PLLDIV plldiv3;

        /**
         * PLLC1 Oscillator Divider 1 Register.
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
      
        uint32 space3_[3];
        
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
         * PLLC1 Clock Align Control Register.
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
            uint32      : 29;
          } bit;
        } alnctl;      

        /**
         * PLLC1 PLLDIV Ratio Change Status Register.
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
            uint32      : 29;
          } bit;
        } dchange;      

        /**
         * PLLC1 Clock Enable Control Register.
         */
        union CKEN
        {
          CKEN(){}
          CKEN(uint32 v){value = v;}          
         ~CKEN(){}    

          uint32 value;
          struct 
          {
            uint32       : 1;
            uint32 obsen : 1;
            uint32       : 30;
          } bit;
        } cken;      


        /**
         * PLLC1 Clock Status Register.
         */
        union CKSTAT
        {
          CKSTAT(){}
          CKSTAT(uint32 v){value = v;}          
         ~CKSTAT(){}    

          uint32 value;
          struct 
          {
            uint32       : 1;
            uint32 obsen : 1;
            uint32       : 30;
          } bit;
        } ckstat;

        /**
         * PLLC1 SYSCLK Status Register.
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
            uint32        : 29;
          } bit;
        } systat;      

      private:        
      
        uint32 space4_[0x27];
        
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
} 
#endif // BOOS_CORE_AM18X_REGISRES_PLLC1_HPP_
