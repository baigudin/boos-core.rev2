/** 
 * Core chip interrupts definitions.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_CHIP_INTERRUPT_HPP_
#define BOOS_CORE_CHIP_INTERRUPT_HPP_

/**
 * Texas Instruments TMS320C64x Digital Signal Processors family.
 */
#ifdef BS_TMS320C64X
#ifndef BS_CHIP_INTERRUPT
#define BS_CHIP_INTERRUPT
#include "../chip/tms320c64x/boos.core.tms320c64x.Interrupt.hpp"
namespace core { namespace chip = tms320c64x; }
#endif
#endif

/**
 * Texas Instruments AM18X ARM Microprocessors family.
 */
#ifdef BS_AM18X
#ifndef BS_CHIP_INTERRUPT
#define BS_CHIP_INTERRUPT
#include "../chip/am18x/boos.core.am18x.Interrupt.hpp"
namespace core { namespace chip = am18x; }
#endif
#endif

/**
 * Abstract chip interrupt.
 */
#ifndef BS_CHIP_INTERRUPT
#include "boos.core.Object.hpp"
#include "boos.core.epi.Interrupt.hpp"
#include "boos.api.Switchable.hpp"

namespace core
{
  class Interrupt;

  namespace chip
  {
    class Register;
    
    class Interrupt : public ::core::Object<>, public ::core::epi::Interrupt
    {
      friend class ::core::Interrupt;
      typedef ::core::Object<> Parent;

    public:
    
      /** 
       * Constructor.
       */    
      Interrupt(){
        setConstruct( construct() );      
      }

      /** 
       * Constructor.
       *
       * @param handler pointer to user class which implements an interrupt handler interface.
       * @param source  available interrupt source.
       */     
      Interrupt(::api::InterruptHandler& handler, int32 source){      
        setConstruct( construct() );      
      }
      
      /** 
       * Destructor.
       */
      virtual ~Interrupt()
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
       * Jumps to interrupt hardware vector.
       */      
      virtual void jump()
      {
      }
      
      /**
       * Clears an interrupt status of this source.
       */     
      virtual void clear()
      {
      }
      
      /**
       * Sets an interrupt status of this source.
       */    
      virtual void set()
      {
      }
      
      /**
       * Locks this interrupt source.
       *
       * @return an interrupt enable source bit value before method was called.
       */    
      virtual bool disable()
      {
        return false;
      }
      
      /**
       * Unlocks this interrupt source.
       *
       * @param status returned status by lock method.
       */
      virtual void enable(bool status)
      {
      }

      /** 
       * Returns the switchable interface for global interrupt controlling.
       *
       * @return switchable interface.
       */ 
      static ::api::Switchable& global()
      {
      }
      
      /**
       * Sets interrupt source handler.
       *
       * @param handler pointer to user class which implements an interrupt handler interface.
       * @param source  available interrupt source.
       * @return true if handler is set successfully.
       */      
      virtual bool setHandler(::api::InterruptHandler& handler, int32 source)
      {
        return false;
      }

      /**
       * Removes this interrupt source.
       */        
      virtual void removeHandler()
      {
      }
      
      /**
       * Sets new registers context for store.
       * 
       * Method sets a new register context for store the CPU registers to it.
       * This method may be called in an user interrupt hander, it means
       * given conxet will be restored until the hander restore procedure.
       *
       * @param reg pointer to new registers context.
       */
      virtual void setRegister(::core::epi::Register* reg)
      {
      }
      
      /**
       * Tests if this interrupt source can be polarized.
       *
       * @return true if this source is polarizing.
       */  
      virtual bool isPolarizing()
      {
        return false;
      }      
      
      /**
       * Sets a low-to-high transition on an interrupt source.
       */
      virtual void risingPolarization()
      {
      }
      
      /**
       * Sets a high-to-low transition on an interrupt source.
       */
      virtual void fallingPolarization()
      {
      }
      
    private:
    
      /** 
       * Constructor.
       *
       * @return boolean result.
       */  
      bool construct()
      {
        if(!Parent::isConstructed()) return false;
        return true;
      }
            
      /**
       * Initialization.
       *
       * @return true if no errors.
       */
      static bool init()
      {
        return true;
      }
      
      /**
       * Deinitialization.
       */
      static void deinit()
      {
      }

    };
  }
}
#endif // BS_CHIP_INTERRUPT
#endif // BOOS_CORE_CHIP_INTERRUPT_HPP_
