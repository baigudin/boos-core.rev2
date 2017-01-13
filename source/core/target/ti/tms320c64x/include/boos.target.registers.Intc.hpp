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
#ifndef BOOS_TARGET_REGISTER_INTC_HPP_
#define BOOS_TARGET_REGISTER_INTC_HPP_

#include "boos.Types.hpp"

namespace target
{
  namespace registers
  {
    struct Intc
    {
    
    public:
    
      /** 
       * Constructor.
       */  
      Intc() :
        muxh   (0),
        muxl   (0),
        extpol (0){
      }
      
      /** 
       * Copy constructor.
       *
       * @param obj reference to source object.
       */  
      Intc(const Intc& obj) :
        muxh   (obj.muxh),
        muxl   (obj.muxl),
        extpol (obj.extpol){
      }
      
      /** 
       * Destructor.
       */    
     ~Intc(){}    
     
      /**
       * Assignment operator.
       *
       * @param obj reference to source object.
       */    
      Intc& operator =(const Intc& obj)
      {
        muxh = obj.muxh;
        muxl = obj.muxl;
        extpol = obj.extpol;
        return *this;        
      }
      
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
       
        MUXH& operator =(const MUXH& reg)
        {
          value = reg.value;
          return *this;        
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
        
        MUXL& operator =(const MUXL& reg)
        {
          value = reg.value;
          return *this;          
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
        
        EXTPOL& operator =(const EXTPOL& reg)
        {
          value = reg.value;
          return *this;                  
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
#endif // BOOS_TARGET_REGISTER_INTC_HPP_

