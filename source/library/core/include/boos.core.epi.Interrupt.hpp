/** 
 * Hardware interrupt interface.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_EPI_INTERRUPT_HPP_
#define BOOS_CORE_EPI_INTERRUPT_HPP_

#include "boos.api.Interrupt.hpp"
#include "boos.api.InterruptHandler.hpp"
#include "boos.core.epi.Register.hpp"

namespace core
{
  namespace epi
  {
    class Interrupt : public ::api::Interrupt
    {

    public:

      /** 
       * Destructor.
       */                               
      virtual ~Interrupt(){}
      
      /**
       * Sets interrupt source handler.
       *
       * @param handler pointer to user class which implements an interrupt handler interface.
       * @param source  available interrupt source.
       * @return true if handler is set successfully.
       */      
      virtual bool setHandler(::api::InterruptHandler& handler, int32 source) = 0;
      
      /**
       * Removes this interrupt source.
       */        
      virtual void removeHandler() = 0;
      
      /**
       * Sets new registers context for store.
       * 
       * Method sets a new register context for store the CPU registers to it.
       * This method may be called in an user interrupt hander, it means
       * given conxet will be restored in the context restore procedure.
       *
       * @param reg new registers context.
       */
      virtual void setRegister(Register& reg) = 0;

      /**
       * Tests if this interrupt source can be polarized.
       *
       * @return true if this source is polarizing.
       */  
      virtual bool isPolarizing() = 0;
      
      /**
       * Sets a low-to-high transition on an interrupt source.
       */
      virtual void risingPolarization() = 0;
      
      /**
       * Sets a high-to-low transition on an interrupt source.
       */
      virtual void fallingPolarization() = 0;      

    };
  }
}
#endif // BOOS_CORE_EPI_INTERRUPT_HPP_
