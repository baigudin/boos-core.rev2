/**
 * Core registers.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_REGISTER_HPP_
#define BOOS_CORE_REGISTER_HPP_

#include "boos.core.Object.hpp"

namespace core
{
  class Register : public Object<>
  { 
  
  public:

    /** 
     * Default register initialization.
     */  
    struct Init
    {

      /** 
       * Constructor.
       */  
      Init() :
        link  (0),
        stack (0),
        page  (0),
        start (0){
        arg[0] = 0; 
        arg[1] = 0;
      }

      /** 
       * Destructor.
       */    
     ~Init(){}

      /** 
       * Return address.
       */  
      int32 link;

      /** 
       * Top of stack.
       */ 
      int32 stack;

      /** 
       * Data page pointer or number.
       */ 
      int32 page;

      /** 
       * Entry point.
       */ 
      int32 start;

      /** 
       * Entry point arguments.
       */ 
      int64 arg[2];

    };

    /** 
     * Constructor.
     */  
    Register() {
      Init init = Init();
      setConstruct( construct(init) );
    }
    
    /** 
     * Constructor.
     *
     * @param init reference to initializing data structure.
     */  
    Register(const Init& init) {
      setConstruct( construct(init) );
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
     * Initialize the registers.  .
     *
     * @param init reference to initializing data structure.
     */  
    void initialize(const Init& init) 
    {
      irp_ = init.start;
      b3_  = init.link;
      b14_ = init.page;
      b15_ = init.stack;
      a4_  = (init.arg[0] >>  0) & 0xffffffff;
      a5_  = (init.arg[0] >> 32) & 0xffffffff;
      b4_  = (init.arg[1] >>  0) & 0xffffffff;
      b5_  = (init.arg[1] >> 32) & 0xffffffff;
    }     

    /** 
     * Returns a pointer to first register of registers.
     *
     * @return pointer to TOS.
     */    
    void* regs()
    {
      return isConstructed() ? &a0_ : NULL;
    }
    
  private:

    /** 
     * Constructor.
     *
     * @param init reference to initializing data structure.
     * @return boolean result.
     */
    bool construct(const Init& init)
    {
      temp_ = 0xb00cffffffffb00c;
      #ifndef BOOS_DEBUG
      a0_  = a1_  = b0_  = b1_,
      a2_  = a3_  = b2_  = b3_,
      a4_  = a5_  = b4_  = b5_,
      a6_  = a7_  = b6_  = b7_,
      a8_  = a9_  = b8_  = b9_,
      a10_ = a11_ = b10_ = b11_,
      a12_ = a13_ = b12_ = b13_,
      a14_ = a15_ = b14_ = b15_,
      a16_ = a17_ = b16_ = b17_,
      a18_ = a19_ = b18_ = b19_,
      a20_ = a21_ = b20_ = b21_,
      a22_ = a23_ = b22_ = b23_,
      a24_ = a25_ = b24_ = b25_,
      a26_ = a27_ = b26_ = b27_,
      a28_ = a29_ = b28_ = b29_,
      a30_ = a31_ = b30_ = b31_,
      amr_ = irp_ = csp_ = ier_ = 0x00000000; 
      #else
      int32 id = 0x0B00C;
      a0_  = 0xa00<<20|id;  b0_  = 0xb00<<20|id;
      a1_  = 0xa01<<20|id;  b1_  = 0xb01<<20|id;
      a2_  = 0xa02<<20|id;  b2_  = 0xb02<<20|id;
      a3_  = 0xa03<<20|id;  b3_  = 0x00000000;
      a4_  = 0xa04<<20|id;  b4_  = 0xb04<<20|id;
      a5_  = 0xa05<<20|id;  b5_  = 0xb05<<20|id;
      a6_  = 0xa06<<20|id;  b6_  = 0xb06<<20|id;
      a7_  = 0xa07<<20|id;  b7_  = 0xb07<<20|id;
      a8_  = 0xa08<<20|id;  b8_  = 0xb08<<20|id;
      a9_  = 0xa09<<20|id;  b9_  = 0xb09<<20|id;
      a10_ = 0xa10<<20|id;  b10_ = 0xb10<<20|id;
      a11_ = 0xa11<<20|id;  b11_ = 0xb11<<20|id;
      a12_ = 0xa12<<20|id;  b12_ = 0xb12<<20|id;
      a13_ = 0xa13<<20|id;  b13_ = 0xb13<<20|id;
      a14_ = 0xa14<<20|id;  b14_ = 0x00000000;
      a15_ = 0x00000000;    b15_ = 0x00000000;             
      a16_ = 0xa16<<20|id;  b16_ = 0xb16<<20|id;
      a17_ = 0xa17<<20|id;  b17_ = 0xb17<<20|id;
      a18_ = 0xa18<<20|id;  b18_ = 0xb18<<20|id;
      a19_ = 0xa19<<20|id;  b19_ = 0xb19<<20|id;
      a20_ = 0xa20<<20|id;  b20_ = 0xb20<<20|id;
      a21_ = 0xa21<<20|id;  b21_ = 0xb21<<20|id;
      a22_ = 0xa22<<20|id;  b22_ = 0xb22<<20|id;
      a23_ = 0xa23<<20|id;  b23_ = 0xb23<<20|id;
      a24_ = 0xa24<<20|id;  b24_ = 0xb24<<20|id;
      a25_ = 0xa25<<20|id;  b25_ = 0xb25<<20|id;
      a26_ = 0xa26<<20|id;  b26_ = 0xb26<<20|id;
      a27_ = 0xa27<<20|id;  b27_ = 0xb27<<20|id;
      a28_ = 0xa28<<20|id;  b28_ = 0xb28<<20|id;
      a29_ = 0xa29<<20|id;  b29_ = 0xb29<<20|id;
      a30_ = 0xa30<<20|id;  b30_ = 0xb30<<20|id;
      a31_ = 0xa31<<20|id;  b31_ = 0xb31<<20|id;
      amr_ = irp_ = csp_ = ier_ = 0x00000000;
      #endif // BOOS_DEBUG
      a15_ = 0x00000000;
      initialize(init);
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
      temp_ = reg.temp_;
      a0_  = reg.a0_;   b0_  = reg.a0_;
      a1_  = reg.a1_;   b1_  = reg.a1_;
      a2_  = reg.a2_;   b2_  = reg.a2_;
      a3_  = reg.a3_;   b3_  = reg.a3_;
      a4_  = reg.a4_;   b4_  = reg.a4_;
      a5_  = reg.a5_;   b5_  = reg.a5_;
      a6_  = reg.a6_;   b6_  = reg.a6_;
      a7_  = reg.a7_;   b7_  = reg.a7_;
      a8_  = reg.a8_;   b8_  = reg.a8_;
      a9_  = reg.a9_;   b9_  = reg.a9_;
      a10_ = reg.a10_;  b10_ = reg.a10_;
      a11_ = reg.a11_;  b11_ = reg.a11_;
      a12_ = reg.a12_;  b12_ = reg.a12_;
      a13_ = reg.a13_;  b13_ = reg.a13_;
      a14_ = reg.a14_;  b14_ = reg.a14_;
      a15_ = reg.a15_;  b15_ = reg.a15_;            
      a16_ = reg.a16_;  b16_ = reg.a16_;
      a17_ = reg.a17_;  b17_ = reg.a17_;
      a18_ = reg.a18_;  b18_ = reg.a18_;
      a19_ = reg.a19_;  b19_ = reg.a19_;
      a20_ = reg.a20_;  b20_ = reg.a20_;
      a21_ = reg.a21_;  b21_ = reg.a21_;
      a22_ = reg.a22_;  b22_ = reg.a22_;
      a23_ = reg.a23_;  b23_ = reg.a23_;
      a24_ = reg.a24_;  b24_ = reg.a24_;
      a25_ = reg.a25_;  b25_ = reg.a25_;
      a26_ = reg.a26_;  b26_ = reg.a26_;
      a27_ = reg.a27_;  b27_ = reg.a27_;
      a28_ = reg.a28_;  b28_ = reg.a28_;
      a29_ = reg.a29_;  b29_ = reg.a29_;
      a30_ = reg.a30_;  b30_ = reg.a30_;
      a31_ = reg.a31_;  b31_ = reg.a31_;
      amr_ = reg.amr_;
      irp_ = reg.irp_;
      csp_ = reg.csp_;
      ier_ = reg.ier_;
      return reg.isConstructed();
    }

    int64 temp_; // For alignment to eight on stack;

    /**
     * Core registers.    
     */
    int32 a0_,  a1_,  b0_,  b1_,
          a2_,  a3_,  b2_,  b3_,
          a4_,  a5_,  b4_,  b5_,
          a6_,  a7_,  b6_,  b7_,
          a8_,  a9_,  b8_,  b9_,
          a10_, a11_, b10_, b11_,
          a12_, a13_, b12_, b13_,
          a14_, a15_, b14_, b15_,
          a16_, a17_, b16_, b17_,
          a18_, a19_, b18_, b19_,
          a20_, a21_, b20_, b21_,
          a22_, a23_, b22_, b23_,
          a24_, a25_, b24_, b25_,
          a26_, a27_, b26_, b27_,
          a28_, a29_, b28_, b29_,
          a30_, a31_, b30_, b31_,
          amr_, irp_, csp_, ier_; 

  };
}
#endif // BOOS_CORE_REGISTER_HPP_

