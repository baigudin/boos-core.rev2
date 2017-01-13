/**
 * TI TMS320c64x 32-Bit Timer registers.
 *
 * TMS320C6000 DSP 32-Bit Timer Reference Guide
 * Literature Number: SPRU582A
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_REGISTER_TIMER_HPP_
#define BOOS_TARGET_REGISTER_TIMER_HPP_

#include "boos.Types.hpp"

namespace target
{
  namespace registers
  {
    struct Timer
    {
    
    public:
    
      /** 
       * Constructor.
       */  
      Timer() :
        ctl (0),
        prd (0),
        cnt (0){
      }
      
      /** 
       * Copy constructor.
       *
       * @param obj reference to source object.
       */  
      Timer(const Timer& obj) :
        ctl (obj.ctl),
        prd (obj.prd),
        cnt (obj.cnt){
      }
      
      /** 
       * Destructor.
       */    
     ~Timer(){}
     
      /**
       * Assignment operator.
       *
       * @param obj reference to source object.
       */    
      Timer& operator =(const Timer& obj)
      {
        ctl = obj.ctl;
        prd = obj.prd;
        cnt = obj.cnt;
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
       * Memory mapped addresses.
       */    
      static const uint32 TIMER0 = 0x01940000;
      static const uint32 TIMER1 = 0x01980000;
      static const uint32 TIMER2 = 0x01ac0000;            
    
      /**
       * Timer Control Register (CTL).
       */
      union CTL{
      
        CTL() : 
          value (0){
        }
        
        CTL(uint32 def) : 
          value (def){
        }
    
        CTL(const CTL& reg) : 
          value (reg.value){
        }        
        
       ~CTL()
        {
          value = 0;
        }
        
        CTL& operator =(const CTL& reg)
        {
          value = reg.value;
          return *this;
        }
    
        uint32 value;
        // Read only structure for overlaying the memory mapped register
        struct 
        {
          uint32 func   : 1;
          uint32 invout : 1;
          uint32 datout : 1;
          uint32 datin  : 1;
          uint32 pwid   : 1;
          uint32        : 1;
          uint32 go     : 1;
          uint32 hld    : 1;
          uint32 cp     : 1;
          uint32 clksrc : 1;
          uint32 invinp : 1;
          uint32 tstat  : 1;
          uint32        : 3;
          uint32 spnd   : 1;
          uint32        : 16;
        } bit;
      } ctl;
      
      /**
       * Timer Period Register (PRD).
       */      
      union PRD{
      
        PRD() : 
          value (0){
        }
        
        PRD(uint32 def) : 
          value (def){
        }
        
        PRD(const PRD& reg) : 
          value (reg.value){
        }        
        
       ~PRD()
        {
          value = 0;
        }
        
        PRD& operator =(const PRD& reg)
        {
          value = reg.value;
          return *this;
        }         
    
        uint32 value;
        // Read only structure for overlaying the memory mapped register
        struct 
        {
          uint32 prd   : 32;
        } bit;
      } prd;
      
      /**
       * Timer Count Register (CNT).
       */
      union CNT{
      
        CNT() : 
          value (0){
        }
        
        CNT(uint32 def) : 
          value (def){
        }
        
        CNT(const CNT& reg) : 
          value (reg.value){
        }        
        
       ~CNT()
        {
          value = 0;
        }
        
        CNT& operator =(const CNT& reg)
        {
          value = reg.value;
          return *this;
        }         
    
        uint32 value;
        // Read only structure for overlaying the memory mapped register
        struct 
        {
          uint32 cnt   : 32;
        } bit;
      } cnt;
    
    };    
  }
}
#endif // BOOS_TARGET_REGISTER_TIMER_HPP_
