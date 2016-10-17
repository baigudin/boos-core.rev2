/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_TMS320C64X_INTERRUPT_HPP_
#define BOOS_CORE_TMS320C64X_INTERRUPT_HPP_

#include "boos.core.Object.hpp"
#include "boos.api.Stack.hpp"
#include "boos.core.epi.Interrupt.hpp"

namespace core
{
  class Interrupt;

  namespace tms320c64x
  {
    namespace registers
    {  
      struct INTC;  
    }
    class Register;
    
    class Interrupt : public ::core::Object<>, public ::core::epi::Interrupt
    {
      friend class ::core::Interrupt;
      typedef ::core::Object<> Parent;

    public:
    
      /**
       * Available interrupt sources.
       */
      enum Source 
      {
        DSPINT     = 0x00, //Host port host to DSP interrupt
        TINT0      = 0x01, //Timer 0 interrupt
        TINT1      = 0x02, //Timer 1 interrupt
        SD_INTA    = 0x03, //EMIFA SDRAM timer interrupt
        GPINT4     = 0x04, //GPIO interrupt 4/External interrupt 4
        GPINT5     = 0x05, //GPIO interrupt 5/External interrupt 5
        GPINT6     = 0x06, //GPIO interrupt 6/External interrupt 6
        GPINT7     = 0x07, //GPIO interrupt 7/External interrupt 7
        EDMA_INT   = 0x08, //EDMA channel (0 through 63) interrupt
        XINT0      = 0x0c, //McBSP 0 transmit interrupt
        RINT0      = 0x0d, //McBSP 0 receive interrupt
        XINT1      = 0x0e, //McBSP 1 transmit interrupt
        RINT1      = 0x0f, //McBSP 1 receive interrupt
        GPINT0     = 0x10, //GPIO interrupt 0
        XINT2      = 0x11, //McBSP 2 transmit interrupt
        RINT2      = 0x12, //McBSP 2 receive interrupt
        TINT2      = 0x13, //Timer 2 interrupt
        SD_INTB    = 0x14, //EMIFB SDRAM timer interrupt
        PCI_WAKEUP = 0x15, //PCI wakeup interrupt
        UINT       = 0x17  //UTOPIA interupt
      };
    
      /** 
       * Constructor.
       */    
      Interrupt();

      /** 
       * Constructor.
       *
       * @param handler pointer to user class which implements an interrupt handler interface.
       * @param source  available interrupt source.
       */     
      Interrupt(::api::InterruptHandler& handler, int32 source);
      
      /** 
       * Destructor.
       */
      virtual ~Interrupt();
      
      /**
       * Tests if this object is constructed.
       *
       * @return true if object is constructed successfully.
       */    
      virtual bool isConstructed() const;
      
      /**
       * Jumps to interrupt hardware vector.
       */      
      virtual void jump();
      
      /**
       * Clears an interrupt status of this source.
       */     
      virtual void clear();
      
      /**
       * Sets an interrupt status of this source.
       */    
      virtual void set();
      
      /**
       * Locks this interrupt source.
       *
       * @return an interrupt enable source bit value before method was called.
       */    
      virtual bool disable();
      
      /**
       * Unlocks this interrupt source.
       *
       * @param status returned status by lock method.
       */
      virtual void enable(bool status);

      /** 
       * Returns the switchable interface for global interrupt controlling.
       *
       * @return switchable interface.
       */ 
      static ::api::Switchable& global();
      
      /**
       * Sets interrupt source handler.
       *
       * @param handler pointer to user class which implements an interrupt handler interface.
       * @param source  available interrupt source.
       * @return true if handler is set successfully.
       */      
      virtual bool setHandler(::api::InterruptHandler& handler, int32 source);

      /**
       * Removes this interrupt source.
       */        
      virtual void removeHandler();
      
      /**
       * Sets new registers context for store.
       * 
       * Method sets a new register context for storing the CPU registers to it.
       * This method may be called in an user interrupt hander, it means
       * given conxet will be restored until the hander restore procedure.
       * Also, heed that given interface of some registers is the interface of 
       * current executing CPU, because interrupt service routine can not check
       * a child class of the interface and simply saves a context to it.
       *
       * @param reg new registers context.
       */
      virtual void setRegister(::core::epi::Register& reg);
      
      /**
       * Tests if this interrupt source can be polarized.
       *
       * @return true if this source is polarizing.
       */  
      virtual bool isPolarizing();
      
      /**
       * Sets a low-to-high transition on an interrupt source.
       */
      virtual void risingPolarization();
      
      /**
       * Sets a high-to-low transition on an interrupt source.
       */
      virtual void fallingPolarization();
      
    private:
    
      /**
       * Current object has HW interrupt.
       *
       * @return true if object has interrupt source.
       */    
      bool isAllocated();
      
      /**
       * Set MUX register.
       *
       * @param source available interrupt source.
       * @param vn hardware interrupt vector number.
       * @return true if no error.
       */    
      static bool setMux(Source source, int32 vn);
            
      /**
       * Initialization.
       *
       * @return true if no errors.
       */
      static bool init();
      
      /**
       * Deinitialization.
       */
      static void deinit();
      
      /**
       * HW interrupt handle routing.
       *
       * @param index index of HW interrupt vector number in context table
       */  
      static void handler(int32 index);     
      
      /**
       * Locks maskable interrupt source.
       *
       * @param vn hardware interrupt vector number.
       * @return an interrupt enable source bit in low bit before method was called.
       */
      static bool disableLow(uint32 vn);
      
      /**
       * Unlocks maskable interrupt source.
       *
       * @param vn hardware interrupt vector number.
       * @param is the returned status by disable method.
       */
      static void enableLow(uint32 vn, bool is);
      
      /**
       * Sets a maskable interrupt status.
       *
       * @param vn hardware interrupt vector number.
       */    
      static void setLow(uint32 vn);
      
      /**
       * Clears a maskable interrupt status.
       *
       * @param vn hardware interrupt vector number.
       */    
      static void clearLow(uint32 vn);
      
      /**
       * Jumps to interrupt HW vector.
       *
       * @param vn hardware interrupt vector number.
       */    
      static void jumpLow(uint32 vn);
      
      /**
       * Disables all maskable interrupts.
       *
       * @return global interrupt enable bit value before method was called.
       */
      static bool globalDisableLow();
      
      /**
       * Enables all maskable interrupts.
       *
       * @param is the returned status by disable method.
       */
      static void globalEnableLow(bool is);    

      /** 
       * Hardware global interrupt controller.
       */
      class Global : public ::core::Object<>, public ::api::Switchable
      {
        typedef ::core::Object<> Parent;

      public:
      
        /** 
         * Constructor.
         */
        Global()
        {
        }  
        
        /** 
         * Destructor.
         */                               
        virtual ~Global()
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
         * Disables all maskable interrupts.
         *
         * @return global interrupt enable bit value before method was called.
         */ 
        virtual bool disable()
        {
          return Interrupt::globalDisableLow();
        }
        
        /** 
         * Enables all maskable interrupts.
         *
         * @param status returned status by disable method.
         */    
        virtual void enable(bool status)
        {
          Interrupt::globalEnableLow(status);
        }
       
      };

      /**
       * Low level interrupt context.
       *
       * NOTE: This struct data is used by low level interrupt routine.
       *       It has to contain two fields and total size has to be eight bytes.
       *       The address of it has to be aligned to eight.
       */
      struct ContextLow
      {
        /**
         * DSP A0 for storing and restoring intrrupted program.
         */
        void* reg;
        
        /**
         * Top of stack will be loaded to DSP SP for routing an intrrupt.
         */        
        const int64* tos;
      };
      
      /**
       * Hi level interrupt context.
       */
      struct Context
      {
        /**
         * CPU register state of interrupt source handler.
         */
        Register* reg;
        
        /**
         * Stack of interrupt source handler.
         */         
        ::api::Stack<int64>* stack;
        
        /**
         * This user interrupt handler.
         */
        ::api::InterruptHandler* handler;
        
        /**
         * Number of interrupt vector.
         */
        int32 number;
        
        /**
         * Interrupt source.
         */
        Source source;
        
      };

      /**
       * Number of HW interrupt vectors.
       */
      static const uint32 NUMBER_VECTORS = 12;

      /**
       * HW interrupt registers (no boot).
       */
      static registers::INTC* intc_;

      /**
       * All interrupt handlers stack (no boot).
       */    
      static ::api::Stack<int64>* stack_;

      /**
       * All no overrided interrupt handlers CPU register state (no boot).
       */    
      static Register* register_;
      
      /**    
       * Hardware global interrupt controller (no boot).
       */
      static Global* global_;

      /**
       * Hi level interrupts context table (no boot).
       */        
      static Context context_[NUMBER_VECTORS];

      /**
       * Low level interrupts context table (no boot).
       */    
      static ContextLow contextLow_[NUMBER_VECTORS];
      
      /**
       * Pointer to the hi level interrupt context.
       */    
      Context* ctx_;    

    };
  }
}
#endif // BOOS_CORE_TMS320C64X_INTERRUPT_HPP_
