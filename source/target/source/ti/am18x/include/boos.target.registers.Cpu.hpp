/**
 * TI AM18x registers.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_REGISTERS_CPU_HPP_
#define BOOS_TARGET_REGISTERS_CPU_HPP_

#include "boos.target.Object.hpp"
#include "boos.target.Register.hpp"

namespace target
{  
  namespace registers
  {  
    class Cpu : public ::target::Object<>, public ::target::Register
    { 
      typedef ::target::Object<> Parent;
    
    public:
    
      /** 
       * Constructor.
       */  
      Cpu() : Parent(),
        align8_ (0xb00cffffffffb00c),
        r3_  (0), r5_  (0), r6_  (0),
        r7_  (0), r8_  (0), r9_  (0),
        r10_ (0), r11_ (0), r12_ (0),
        r0_  (0), r1_  (0), r2_  (0),
        r4_  (0), pc_  (0), psr_ (0),
        sp_  (0), lr_  (0){
        setConstruct( construct() );
      }
      
      /** 
       * Copy constructor.
       *
       * @param obj reference to source object.
       */ 
      Cpu(const Cpu& obj) : Parent(obj),
        align8_ (obj.align8_),
        r3_  (obj.r3_) , r5_  (obj.r5_ ), r6_  (obj.r6_ ),
        r7_  (obj.r7_ ), r8_  (obj.r8_ ), r9_  (obj.r9_ ),
        r10_ (obj.r10_), r11_ (obj.r11_), r12_ (obj.r12_),
        r0_  (obj.r0_) , r1_  (obj.r1_ ), r2_  (obj.r2_ ),
        r4_  (obj.r4_) , pc_  (obj.pc_ ), psr_ (obj.psr_),
        sp_  (obj.sp_) , lr_  (obj.lr_ ){
      }
      
      /** 
       * Destructor.
       */    
      virtual ~Cpu()
      {
      }
      
      /** 
       * Assignment operator.
       *
       * @param obj reference to source object.
       */  
      Cpu& operator =(const Cpu& obj)
      {
        Parent::operator=(obj);
        copy(obj);
        return *this;
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
        #ifndef BOOS_DEBUG
        r0_  = r1_  = r2_  = r3_  = 
        r4_  = r5_  = r6_  = r7_  = 
        r8_  = r9_  = r10_ = r11_ =
        r12_ = sp_  = lr_  = pc_  = 
        psr_ = 0x00000000;
        #else //!BOOS_DEBUG
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
        #endif // BOOS_DEBUG
        return true;
      }
    
      /** 
       * Copies context.
       *
       * @param reg reference to source object.
       * @return boolean result.
       */
      bool copy(const Cpu& reg)
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
#endif // BOOS_TARGET_REGISTERS_CPU_HPP_
