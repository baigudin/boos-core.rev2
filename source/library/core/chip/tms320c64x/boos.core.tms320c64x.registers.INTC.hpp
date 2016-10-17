/**
 * TI TMS320c64x Interrupt selector registers.
 *
 * TMS320C6000 DSP Interrupt Selector Reference Guide
 * Literature Number: SPRU646A
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_TMS320C64X_REGISTER_INTC_HPP_
#define BOOS_CORE_TMS320C64X_REGISTER_INTC_HPP_

#include "boos.core.tms320c64x.registers.Mapped.hpp"

namespace core
{
  namespace tms320c64x
  {
    namespace registers
    {
      struct INTC : public Mapped
      {
      
      public:
      
        /** 
         * Constructor.
         */  
        INTC() :
          muxh   (0),
          muxl   (0),
          extpol (0){
        }
        
        /** 
         * Copy constructor.
         *
         * @param reg reference to source object. 
         */  
        INTC(const INTC& reg) :
          muxh   (reg.muxh),
          muxl   (reg.muxl),
          extpol (reg.extpol){
        }
        
        /** 
         * Destructor.
         */    
       ~INTC(){}    
       
        /**
         * Assignment operator.
         *
         * @param reg reference to source object. 
         */    
        void operator =(const INTC& reg)
        {
          muxh = reg.muxh;
          muxl = reg.muxl;
          extpol = reg.extpol;
        }
      
        /**
         * Memory mapped address.
         */    
        static const uint32 ADDRESS = 0x019c0000;      
      
        /**
         * Interrupt Multiplexer High Register (MUXH).
         */
        union MUXH{
        
          MUXH() : 
            value (0){
          }
          
          MUXH(uint32 def) : 
            value (def){
          }
          
          MUXH(const MUXH& reg) : 
            value (reg.value){
          }        
          
         ~MUXH()
          {
            value = 0;
          }    
         
          void operator =(const MUXH& reg)
          {
            value = reg.value;
          }
      
          uint32 value;
          // Read only structure for overlaying the memory mapped register
          struct 
          {
            uint32 intsel10 : 5;
            uint32 intsel11 : 5;
            uint32 intsel12 : 5;
            uint32          : 1;
            uint32 intsel13 : 5;
            uint32 intsel14 : 5;
            uint32 intsel15 : 5;
            uint32          : 1;
          } bit;
        } muxh;
        
        /**
         * Interrupt Multiplexer Low Register (MUXL).
         */
        union MUXL{
        
          MUXL() : 
            value (0){
          }
          
          MUXL(uint32 def) : 
            value (def){
          }
          
          MUXL(const MUXL& reg) : 
            value (reg.value){
          }        
          
         ~MUXL()
          {
            value = 0;
          }
          
          void operator =(const MUXL& reg)
          {
            value = reg.value;
          }       
      
          uint32 value;
          // Read only structure for overlaying the memory mapped register
          struct 
          {
            uint32 intsel4 : 5;
            uint32 intsel5 : 5;
            uint32 intsel6 : 5;
            uint32         : 1;
            uint32 intsel7 : 5;
            uint32 intsel8 : 5;
            uint32 intsel9 : 5;
            uint32         : 1;
          } bit;
        } muxl;
        
        /**
         * External Interrupt Polarity Register (EXTPOL).
         */
        union EXTPOL{
        
          EXTPOL() : 
            value (0){
          }
          
          EXTPOL(uint32 def) : 
            value (def){
          }
          
          EXTPOL(const EXTPOL& reg) : 
            value (reg.value){
          }        
          
         ~EXTPOL()
          {
            value = 0;
          }  
          
          void operator =(const EXTPOL& reg)
          {
            value = reg.value;
          }         
      
          uint32 value;
          // Read only structure for overlaying the memory mapped register
          struct 
          {
            uint32 xip4 : 1;
            uint32 xip5 : 1;
            uint32 xip6 : 1;
            uint32 xip7 : 1;          
            uint32      : 28;
          } bit;
        } extpol;            
      
      };
    }
  }
}
#endif // BOOS_CORE_TMS320C64X_REGISTER_INTC_HPP_

