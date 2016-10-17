/** 
 * CPU registers definitions.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_CHIP_REGISTER_HPP_
#define BOOS_CORE_CHIP_REGISTER_HPP_

/**
 * Texas Instruments TMS320C64x Digital Signal Processors family.
 */
#ifdef  BS_TMS320C64X
#ifndef BS_CHIP_REGISTER
#define BS_CHIP_REGISTER
#include "../chip/tms320c64x/boos.core.tms320c64x.Register.hpp"
namespace core { namespace chip = tms320c64x; }
#endif
#endif

/**
 * Texas Instruments AM18X ARM Microprocessors family.
 */
#ifdef  BS_AM18X
#ifndef BS_CHIP_REGISTER
#define BS_CHIP_REGISTER
#include "../chip/am18x/boos.core.am18x.Register.hpp"
namespace core { namespace chip = am18x; }
#endif
#endif

/**
 * Abstract chip timer.
 */
#ifndef BS_CHIP_REGISTER
#include "boos.core.Object.hpp" 
#include "boos.core.epi.Register.hpp" 
namespace core
{
  namespace chip
  {
    class Register : public ::core::Object<>, public ::core::epi::Register
    {
      typedef ::core::Object<> Parent;

    public:

      /** 
       * Constructor.
       *
       * Constructs this object and allocs a first free hardware timer.
       */      
      Register(){
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
       * Tests if this object is constructed.
       *
       * @return true if object is constructed successfully.
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
      }
    
      /** 
       * Returns a pointer to a first register of registers.
       *
       * @return memory address of registers order.
       */    
      virtual void* registers()
      {
        return NULL;
      }
      
    private:
      
      /** 
       * Constructor.
       *
       * @return boolean result.
       */  
      bool construct()
      {
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
        return reg.isConstructed();
      }      
      
    };
  }
}
#endif // BS_CHIP_REGISTER
#endif // BOOS_CORE_CHIP_REGISTER_HPP_
