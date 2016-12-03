/**
 * TI AM18x registers.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_AM18X_REGISTER_HPP_
#define BOOS_CORE_AM18X_REGISTER_HPP_

#include "boos.core.Object.hpp"
#include "boos.core.epi.Register.hpp"

namespace core
{
  namespace am18x
  {  
    class Register : public ::core::Object<>, public ::core::epi::Register
    { 
      typedef ::core::Object<> Parent;
    
    public:

      /** 
       * Constructor.
       */  
      Register() {
        setConstruct( construct() );
      }
      
      /** 
       * Copy constructor.
       *
       * @param reg reference to source registers.
       */ 
      Register(const Register& reg){
        setConstruct( copy(reg) );
      }
      
      /** 
       * Destructor.
       */    
      virtual ~Register()
      {
      }
      
      /**
       * Tests if this object has been constructed.
       *
       * @return true if object has been constructed successfully.
       */    
      virtual bool isConstructed() const
      {
        return this->Parent::isConstructed();
      }      
      
      /** 
       * Initializes the registers.
       *
       * @param stack a stack.
       * @param entry router entry point.
       * @param arg1  first router argument.
       * @param arg2  second router argument.     
       */  
      virtual void initialize(::api::Stack<int64>& stack, int32 entry, int32 arg1, int32 arg2)
      {
        r0_ = arg1;
        r1_ = arg2;
        sp_ = reinterpret_cast<int32>(stack.tos());        
        pc_ = entry;
        // Set start status for this context
        PSR psr = 0;
        psr.bit.m = PSR::SYS;
        psr.bit.f = 1;
        psr_ = psr.value;
      }     

      /** 
       * Returns a pointer to a first register of registers.
       *
       * @return memory address of registers order.
       */    
      virtual void* registers()
      {
        return isConstructed() ? &r3_ : NULL;
      }
      
    private:

      /**
       * Constructor.
       *
       * @return true if object has been constructed successfully.     
       */    
      bool construct()
      {
        align8_ = 0xb00cffffffffb00c;
        #ifndef BS_DEBUG
        r0_  = r1_  = r2_  = r3_  = 
        r4_  = r5_  = r6_  = r7_  = 
        r8_  = r9_  = r10_ = r11_ =
        r12_ = sp_  = lr_  = pc_  = 
        psr_ = 0x00000000;
        #else //!BS_DEBUG
        int32 id = 0x0B00C;
        r0_  = 0xa00<<20|id; r1_  = 0xa01<<20|id;
        r2_  = 0xa02<<20|id; r3_  = 0xa03<<20|id;
        r4_  = 0xa04<<20|id; r5_  = 0xa05<<20|id;
        r6_  = 0xa06<<20|id; r7_  = 0xa07<<20|id;
        r8_  = 0xa08<<20|id; r9_  = 0xa09<<20|id;
        r10_ = 0xa10<<20|id; r11_ = 0xa11<<20|id;
        r12_ = 0xa12<<20|id; sp_  = 0xa13<<20|id;
        lr_  = 0xa14<<20|id; pc_  = 0xa15<<20|id;
        psr_ = 0x00000000;
        #endif // BS_DEBUG
        return true;
      }

      /** 
       * Copy constructor.
       *
       * @param reg reference to source registers.
       * @return boolean result.
       */
      bool copy(const Register& reg)
      {
        align8_ = reg.align8_;
        r0_  = reg.r0_ ; r1_  = reg.r1_ ;
        r2_  = reg.r2_ ; r3_  = reg.r3_ ;
        r4_  = reg.r4_ ; r5_  = reg.r5_ ;
        r6_  = reg.r6_ ; r7_  = reg.r7_ ;
        r8_  = reg.r8_ ; r9_  = reg.r9_ ;
        r10_ = reg.r10_; r11_ = reg.r11_;
        r12_ = reg.r12_; sp_  = reg.sp_ ;
        lr_  = reg.lr_ ; pc_  = reg.pc_ ;
        psr_ = reg.psr_;
        return reg.isConstructed();
      }
      
      /**
       * Program Status Register.
       */
      union PSR
      {
        
        PSR(){}
        PSR(uint32 v){value = v;}          
       ~PSR(){}    
       
        /**
         * Modes.
         */
        enum Mode
        {
          USR = 0x10,
          FIQ = 0x11,
          IRQ = 0x12,
          SVC = 0x13,
          ABT = 0x17,
          UND = 0x1b,
          SYS = 0x1f
        };

        int32 value;
        struct 
        {
          uint32 m  : 5;
          uint32 t  : 1;
          uint32 f  : 1;
          uint32 i  : 1;
          uint32 a  : 1;
          uint32 e  : 1;
          uint32    : 6;
          uint32 ge : 4;
          uint32    : 4;
          uint32 j  : 1;
          uint32    : 2;
          uint32 q  : 1;
          uint32 v  : 1;
          uint32 c  : 1;
          uint32 z  : 1;
          uint32 n  : 1;                              
        } bit;
      };

      /**
       * For alignment to eight on stack
       */
      int64 align8_;

      /**
       * Core registers.
       *
       * IMPORTANT: The order of CPU registers must not be changed,
       * because these are used by low level interrupt routine.
       */
      int32 r3_;
      int32 r5_;
      int32 r6_;
      int32 r7_;
      int32 r8_;
      int32 r9_;
      int32 r10_;
      int32 r11_;
      int32 r12_;
      int32 r0_;
      int32 r1_;
      int32 r2_;
      int32 r4_;
      int32 pc_;
      int32 psr_;
      int32 sp_;
      int32 lr_;

    };
  }
}
#endif // BOOS_CORE_AM18X_REGISTER_HPP_

