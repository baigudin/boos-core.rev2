/**
 * Memory mapped registers.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_TMS320C64X_MAPPED_REGISTER_HPP_
#define BOOS_CORE_TMS320C64X_MAPPED_REGISTER_HPP_

#include "boos.Types.hpp"

namespace core
{
  namespace tms320c64x
  {  
    /**
     * Base structure for memory mapped registers description.
     */
    struct MappedRegisters
    { 
    
    public:

      /** 
       * Constructor.
       */  
      MappedRegisters(){}
      
      /** 
       * Destructor.
       */    
     ~MappedRegisters(){}
     
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

    };
    
    /**
     * Interrupt selector registers.
     *
     * TMS320C6000 DSP Interrupt Selector Reference Guide
     * Literature Number: SPRU646A
     */
    struct InterruptSelectorRegisters : public MappedRegisters
    {
    
    public:

      /** 
       * Constructor.
       */  
      InterruptSelectorRegisters() :
        muxh   (0),
        muxl   (0),
        extpol (0){
      }
      
      /** 
       * Copy constructor.
       *
       * @param reg reference to source object. 
       */  
      InterruptSelectorRegisters(const InterruptSelectorRegisters& reg) :
        muxh   (reg.muxh),
        muxl   (reg.muxl),
        extpol (reg.extpol){
      }
      
      /** 
       * Destructor.
       */    
     ~InterruptSelectorRegisters(){}    
     
      /**
       * Assignment operator.
       *
       * @param reg reference to source object. 
       */    
      void operator =(const InterruptSelectorRegisters& reg)
      {
        muxh = reg.muxh;
        muxl = reg.muxl;
        extpol = reg.extpol;
      }

      /**
       * Memory mapped address.
       */    
      static const uint32 BASE_ADDR = 0x019c0000;      

      /**
       * Interrupt Multiplexer High Register (MUXH).
       */
      union MultiplexerHigh{
      
        MultiplexerHigh() : 
          value (0){
        }
        
        MultiplexerHigh(uint32 def) : 
          value (def){
        }
        
        MultiplexerHigh(const MultiplexerHigh& reg) : 
          value (reg.value){
        }        
        
       ~MultiplexerHigh(){
         value = 0;
        }    
       
        void operator =(const MultiplexerHigh& reg)
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
      union MultiplexerLow{
      
        MultiplexerLow() : 
          value (0){
        }
        
        MultiplexerLow(uint32 def) : 
          value (def){
        }
        
        MultiplexerLow(const MultiplexerLow& reg) : 
          value (reg.value){
        }        
        
       ~MultiplexerLow()
        {
          value = 0;
        }
        
        void operator =(const MultiplexerLow& reg)
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
      union Polarity{
      
        Polarity() : 
          value (0){
        }
        
        Polarity(uint32 def) : 
          value (def){
        }
        
        Polarity(const Polarity& reg) : 
          value (reg.value){
        }        
        
       ~Polarity()
        {
          value = 0;
        }  
        
        void operator =(const Polarity& reg)
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
    
    
    /**
     * 32-Bit Timer registers.
     *
     * TMS320C6000 DSP 32-Bit Timer Reference Guide
     * Literature Number: SPRU582A
     */
    struct TimerRegisters : public MappedRegisters
    {
    
    public:

      /** 
       * Constructor.
       */  
      TimerRegisters() :
        ctl (0),
        prd (0),
        cnt (0){
      }
      
      /** 
       * Copy constructor.
       *
       * @param reg reference to source object. 
       */  
      TimerRegisters(const TimerRegisters& reg) :
        ctl (reg.ctl),
        prd (reg.prd),
        cnt (reg.cnt){
      }
      
      /** 
       * Destructor.
       */    
     ~TimerRegisters(){}
     
      /**
       * Assignment operator.
       *
       * @param reg reference to source object. 
       */    
      void operator =(const TimerRegisters& reg)
      {
        ctl = reg.ctl;
        prd = reg.prd;
        cnt = reg.cnt;
      }
        

      /**
       * Memory mapped addresses.
       */    
      static const uint32 BASE_TIM0_ADDR = 0x01940000;
      static const uint32 BASE_TIM1_ADDR = 0x01980000;
      static const uint32 BASE_TIM2_ADDR = 0x01ac0000;            

      /**
       * Timer Control Register.
       */
      union Control{
      
        Control() : 
          value (0){
        }
        
        Control(uint32 def) : 
          value (def){
        }

        Control(const Control& reg) : 
          value (reg.value){
        }        
        
       ~Control()
        {
          value = 0;
        }
        
        void operator =(const Control& reg)
        {
          value = reg.value;
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
       * Timer Period Register.
       */      
      union Period{
      
        Period() : 
          value (0){
        }
        
        Period(uint32 def) : 
          value (def){
        }
        
        Period(const Period& reg) : 
          value (reg.value){
        }        
        
       ~Period()
        {
          value = 0;
        }
        
        void operator =(const Period& reg)
        {
          value = reg.value;
        }         

        uint32 value;
        // Read only structure for overlaying the memory mapped register
        struct 
        {
          uint32 prd   : 32;
        } bit;
      } prd;
      
      /**
       * Timer Count Register.
       */
      union Count{
      
        Count() : 
          value (0){
        }
        
        Count(uint32 def) : 
          value (def){
        }
        
        Count(const Count& reg) : 
          value (reg.value){
        }        
        
       ~Count()
        {
          value = 0;
        }
        
        void operator =(const Count& reg)
        {
          value = reg.value;
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
#endif // BOOS_CORE_TMS320C64X_MAPPED_REGISTER_HPP_

