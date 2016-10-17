/** 
 * TI ARM AM18x ARM Interrupt Controller (AINTC).
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_AM18X_REGISRES_AINTC_HPP_
#define BOOS_CORE_AM18X_REGISRES_AINTC_HPP_

#include "boos.core.am18x.registers.Mapped.hpp"

namespace core
{
  namespace am18x
  {
    namespace registers
    {
      struct AINTC : public Mapped
      {

      public:

        AINTC(){}
       ~AINTC(){}

        static const uint32 ADDRESS = 0xfffee000;
        
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
         * Control Register.
         */
        union CR
        {
          CR(){}
          CR(uint32 v){value = v;}          
         ~CR(){}    

          uint32 value;
          struct 
          {
            uint32            : 2;
            uint32 nestmode   : 2;
            uint32 prholdmode : 1;
            uint32            : 27;                                    
          } bit;
        } cr;

      private:        
      
        uint32 space0_[2];
        
      public:
                          
        /**
         * Global Enable Register.
         */
        union GER
        {
          GER(){}
          GER(uint32 v){value = v;}          
         ~GER(){}    

          uint32 value;
          struct 
          {
            uint32 enable : 1;
            uint32        : 31;
          } bit;
        } ger;

      private:        
      
        uint32 space1_[2];
        
      public:

        /**
         * Global Nesting Level Register.
         */
        union GNLR
        {
          GNLR(){}
          GNLR(uint32 v){value = v;}          
         ~GNLR(){}    

          uint32 value;
          struct 
          {
            uint32 nestlv   : 9;
            uint32          : 22;
            uint32 override : 1;
          } bit;
        } gnlr;

        /**
         * System Interrupt Status Indexed Set Register.
         */
        union SISR
        {
          SISR(){}
          SISR(uint32 v){value = v;}          
         ~SISR(){}    

          uint32 value;
          struct 
          {
            uint32 index : 7;
            uint32       : 25;
          } bit;
        } sisr;

        /**
         * System Interrupt Status Indexed Clear Register.
         */
        union SICR
        {
          SICR(){}
          SICR(uint32 v){value = v;}          
         ~SICR(){}    

          uint32 value;
          struct 
          {
            uint32 index : 7;
            uint32       : 25;
          } bit;
        } sicr;

        /**
         * System Interrupt Enable Indexed Set Register.
         */
        union EISR
        {
          EISR(){}
          EISR(uint32 v){value = v;}          
         ~EISR(){}    

          uint32 value;
          struct 
          {
            uint32 index : 7;
            uint32       : 25;
          } bit;
        } eisr;

        /**
         * System Interrupt Enable Indexed Clear Register.
         */
        union EICR
        {
          EICR(){}
          EICR(uint32 v){value = v;}          
         ~EICR(){}    

          uint32 value;
          struct 
          {
            uint32 index : 7;
            uint32       : 25;
          } bit;
        } eicr;

      private:        
      
        uint32 space2_[1];
        
      public:

        /**
         * Host Interrupt Enable Indexed Set Register.
         */
        union HIEISR
        {
          HIEISR(){}
          HIEISR(uint32 v){value = v;}          
         ~HIEISR(){}    

          uint32 value;
          struct 
          {
            uint32 index : 1;
            uint32       : 31;
          } bit;
        } hieisr;

        /**
         * Host Interrupt Enable Indexed Clear Register.
         */
        union HIEICR
        {
          HIEICR(){}
          HIEICR(uint32 v){value = v;}          
         ~HIEICR(){}    

          uint32 value;
          struct 
          {
            uint32 index : 1;
            uint32       : 31;
          } bit;
        } hieicr;

      private:        

        uint32 space3_[5];

      public:
                          
        /**
         * Vector Base Register.
         */
        union VBR
        {
          VBR(){}
          VBR(uint32 v){value = v;}          
         ~VBR(){}    

          uint32 value;
          struct 
          {
            uint32 base : 32;
          } bit;
        } vbr;

        /**
         * Vector Size Register.
         */
        union VSR
        {
          VSR(){}
          VSR(uint32 v){value = v;}          
         ~VSR(){}    

          uint32 value;
          struct 
          {
            uint32 size : 8;
            uint32      : 24;
          } bit;
        } vsr;

        /**
         * Vector Null Register.
         */
        union VNR
        {
          VNR(){}
          VNR(uint32 v){value = v;}          
         ~VNR(){}    

          uint32 value;
          struct 
          {
            uint32 null : 32;
          } bit;
        } vnr;

      private:        

        uint32 space4_[9];

      public:
                          
        /**
         * Global Prioritized Index Register.
         */
        union GPIR 
        {
          GPIR (){}
          GPIR (uint32 v){value = v;}          
         ~GPIR (){}    

          uint32 value;
          struct 
          {
            uint32 priIndx : 10;
            uint32          : 21;
            uint32 none     : 1;
          } bit;
        } gpir ;

        /**
         * Global Prioritized Vector Register.
         */
        union GPVR
        {
          GPVR(){}
          GPVR(uint32 v){value = v;}          
         ~GPVR(){}    

          uint32 value;
          struct 
          {
            uint32 addr : 32;
          } bit;
        } gpvr;

      private:        

        uint32 space5_[94];

      public:
                          
        /**
         * System Interrupt Status Raw/Set Register.
         */
        union SRSR
        {
          SRSR(){}
          SRSR(uint32 v){value = v;}          
         ~SRSR(){}    

          uint32 value;
          struct 
          {
            uint32 rawStatus : 32;
          } bit;
        } srsr[4];

      private:        

        uint32 space6_[28];

      public:
                          
        /**
         * System Interrupt Status Enabled/Clear Register.
         */
        union SECR
        {
          SECR(){}
          SECR(uint32 v){value = v;}          
         ~SECR(){}    

          uint32 value;
          struct 
          {
            uint32 enblStatus : 32;
          } bit;
        } secr[4];

      private:        

        uint32 space7_[28];

      public:
                          
        /**
         * System Interrupt Enable Set Register.
         */
        union ESR
        {
          ESR(){}
          ESR(uint32 v){value = v;}          
         ~ESR(){}    

          uint32 value;
          struct 
          {
            uint32 enable : 32;
          } bit;
        } esr[4];

      private:        

        uint32 space8_[28];

      public:

        /**
         * System Interrupt Enable Clear Register.
         */
        union ECR
        {
          ECR(){}
          ECR(uint32 v){value = v;}          
         ~ECR(){}    

          uint32 value;
          struct 
          {
            uint32 disable : 32;
          } bit;
        } ecr[4];

      private:        

        uint32 space9_[28];

      public:
      
        /**
         * Channel Map Registers.
         */
        union CMR
        {
          CMR(){}
          CMR(uint32 v){value = v;}          
         ~CMR(){}    

          uint32 value;
          struct 
          {
            uint32 channel0 : 8;
            uint32 channel1 : 8;
            uint32 channel2 : 8;
            uint32 channel3 : 8;                                    
          } bit;
        } cmr[26];
          
      private:        

        uint32 space10_[294];

      public:
                          
        /**
         * Host Interrupt Prioritized Index Register.
         */
        union HIPIR
        {
          HIPIR(){}
          HIPIR(uint32 v){value = v;}          
         ~HIPIR(){}    

          uint32 value;
          struct 
          {
            uint32 priIndx : 10;
            uint32         : 21;
            uint32 none    : 1;
          } bit;
        } hipir[2];

      private:        

        uint32 space11_[510];

      public:
                          
        /**
         * Host Interrupt Nesting Level Register.
         */
        union HINLR
        {
          HINLR(){}
          HINLR(uint32 v){value = v;}          
         ~HINLR(){}    

          uint32 value;
          struct 
          {
            uint32 nestLvl  : 9;
            uint32          : 22;
            uint32 override : 1;
          } bit;
        } hinlr[2];

      private:        

        uint32 space12_[254];

      public:
                          
        /**
         * Host Interrupt Enable Register.
         */
        union HIER
        {
          HIER(){}
          HIER(uint32 v){value = v;}          
         ~HIER(){}    

          uint32 value;
          struct 
          {
            uint32 fiq : 1;
            uint32 irq : 1;
            uint32     : 30;
          } bit;
        } hier;

      private:        

        uint32 space13_[63];

      public:
                          
        /**
         * Host Interrupt Prioritized Vector Register.
         */
        union HIPVR
        {
          HIPVR(){}
          HIPVR(uint32 v){value = v;}          
         ~HIPVR(){}    

          uint32 value;
          struct 
          {
            uint32 addr : 32;
          } bit;
        } hipvr[2];

      private:        

        uint32 space14_[1];
                          
      };
    }
  }
} 
#endif // BOOS_CORE_AM18X_REGISRES_AINTC_HPP_
