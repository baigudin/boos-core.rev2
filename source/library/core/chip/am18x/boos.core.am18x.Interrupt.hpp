/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_AM18X_INTERRUPT_HPP_
#define BOOS_CORE_AM18X_INTERRUPT_HPP_

#include "boos.core.Object.hpp"
#include "boos.api.Stack.hpp"
#include "boos.core.epi.Interrupt.hpp"

namespace core
{
  class Interrupt;

  namespace am18x
  {
    namespace registers
    {  
      struct AINTC;  
    }
    class Register;
  
    class Interrupt : public ::core::Object<>, public ::core::epi::Interrupt
    {
      friend class ::core::Interrupt;
      typedef ::core::Object<> Parent;

    public:
    
      /**
       * Available interrupt sources for all AM18x family.
       *
       * NOTE: Some sources for some microprocessors can not be used,
       * because those peripherial might be absented on chips.
       */
      enum Source
      {
        COMMTX             = 0,
        COMMRX             = 1,
        NINT               = 2,
        PRU_EVTOUT0        = 3,
        PRU_EVTOUT1        = 4,
        PRU_EVTOUT2        = 5,
        PRU_EVTOUT3        = 6,
        PRU_EVTOUT4        = 7,
        PRU_EVTOUT5        = 8,
        PRU_EVTOUT6        = 9,
        PRU_EVTOUT7        = 10,
        EDMA3_0_CC0_INT0   = 11,
        EDMA3_0_CC0_ERRINT = 12,
        EDMA3_0_TC0_ERRINT = 13,
        EMIFA_INT          = 14,
        IIC0_INT           = 15,
        MMCSD0_INT0        = 16,
        MMCSD0_INT1        = 17,
        PSC0_ALLINT        = 18,
        RTC_IRQS           = 19,
        SPI0_INT           = 20,
        T64P0_TINT12       = 21,
        T64P0_TINT34       = 22,
        T64P1_TINT12       = 23,
        T64P1_TINT34       = 24,
        UART0_INT          = 25,
        PROTERR            = 27,
        SYSCFG_CHIPINT0    = 28,
        SYSCFG_CHIPINT1    = 29,
        SYSCFG_CHIPINT2    = 30,
        SYSCFG_CHIPINT3    = 31,
        EDMA3_0_TC1_ERRINT = 32,
        EMAC_C0RXTHRESH    = 33,
        EMAC_C0RX          = 34,
        EMAC_C0TX          = 35,
        EMAC_C0MISC        = 36,
        EMAC_C1RXTHRESH    = 37,
        EMAC_C1RX          = 38,
        EMAC_C1TX          = 39,
        EMAC_C1MISC        = 40,
        DDR2_MEMERR        = 41,
        GPIO_B0INT         = 42,
        GPIO_B1INT         = 43,
        GPIO_B2INT         = 44,
        GPIO_B3INT         = 45,
        GPIO_B4INT         = 46,
        GPIO_B5INT         = 47,
        GPIO_B6INT         = 48,
        GPIO_B7INT         = 49,
        GPIO_B8INT         = 50,
        IIC1_INT           = 51,
        LCDC_INT           = 52,
        UART_INT1          = 53,
        MCASP_INT          = 54,
        PSC1_ALLINT        = 55,
        SPI1_INT           = 56,
        UHPI_ARMINT        = 57,
        USB0_INT           = 58,
        USB1_HCINT         = 59,
        USB1_R_WAKEUP      = 60,
        UART2_INT          = 61,
        EHRPWM0            = 63,
        EHRPWM0TZ          = 64,
        EHRPWM1            = 65,
        EHRPWM1TZ          = 66,
        SATA_INT           = 67,
        T64P2_ALL          = 68,
        ECAP0              = 69,
        ECAP1              = 70,
        ECAP2              = 71,
        MMCSD1_INT0        = 72,
        MMCSD1_INT1        = 73,
        T64P2_CMPINT0      = 74,
        T64P2_CMPINT1      = 75,
        T64P2_CMPINT2      = 76,
        T64P2_CMPINT3      = 77,
        T64P2_CMPINT4      = 78,
        T64P2_CMPINT5      = 79,
        T64P2_CMPINT6      = 80,
        T64P2_CMPINT7      = 81,
        T64P3_CMPINT0      = 82,
        T64P3_CMPINT1      = 83,
        T64P3_CMPINT2      = 84,
        T64P3_CMPINT3      = 85,
        T64P3_CMPINT4      = 86,
        T64P3_CMPINT5      = 87,
        T64P3_CMPINT6      = 88,
        T64P3_CMPINT7      = 89,
        ARMCLKSTOPREQ      = 90,
        UPP_ALLINT         = 91,
        VPIF_ALLINT        = 92,
        EDMA3_1_CC0_INT0   = 93,
        EDMA3_1_CC0_ERRINT = 94,
        EDMA3_1_TC0_ERRINT = 95,
        T64P3_ALL          = 96,
        MCBSP0_RINT        = 97,
        MCBSP0_XINT        = 98,
        MCBSP1_RINT        = 99,
        MCBSP1_XINT        = 100,
        UNDEF              = -1
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
       * Tests if this object has been constructed.
       *
       * @return true if object has been constructed successfully.
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
       * Method sets a new register context for store the CPU registers to it.
       * This method may be called in an user interrupt hander, it means
       * given conxet will be restored until the hander restore procedure.
       *
       * @param reg pointer to new registers context.
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
       * TI ARM AM18x ARM Interrupt Controller initialization.
       *
       * @return true if no errors.
       */
      static bool initAINTC();
      
      /**
       * TI ARM AM18x ARM Interrupt Controller deinitialization.
       */
      static void deinitAINTC();
      
      /**
       * HW interrupt handle routing.
       *
       * @param channel interrupt channel.
       */
      static void handler(int32 channel);

      /**
       * HW interrupt handle base routing address.
       *
       * IMPORTANT: This is not a normal C++ method and MUST NOT be called 
       * from any other code places!
       */        
      static void handlerBaseLow();
      
      /**
       * HW interrupt handle null routing.
       */        
      static void handlerNullLow();
      
      /**
       * Sets the channel for the source.
       *
       * @param channel available channel.
       * @param source  available source.
       * @return true if the channel is set for the source.     
       */
      static bool setChannelForSource(int32 channel, Source source);      
      
      /**
       * Tests if given source is available.
       *
       * @param source interrupt source.
       * @return true if the source is available.
       */      
      static bool isSource(int32 source);
      
      /**
       * Tests if given channel is available.
       *
       * @param channel interrupt channel.
       * @return true if the channel is available.
       */      
      static bool isChannel(int32 channel);
      
      /**
       * Jumps to interrupt HW vector.
       *
       * @param source interrupt source.
       */    
      static void jumpLow(int32 source);
      
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
       * Supervisor exception.
       *
       * @param source interrupt source.
       * @return branch address.
       */
      static int32 supervisor(int32 source);
      
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
        Global(){}  
        
        /** 
         * Destructor.
         */                               
        virtual ~Global(){}
        
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
       *       It maps on assembly source code of an intrrupt routine and
       *       has to be equal the size which set in AINTC Vector Size Register.
       *       The order of structure data is important and must not be changed,
       *       because it is used by low level interrupt routine.
       */
      struct ContextLow
      {
      
      public:
            
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
        
      private:

        /**
         * Assembly source code of an intrrupt routine.
         *
         * NOTE: never modify it!
         */
        int32 asm_[5];
      
      public:
        
        /**
         * Number of channel for this source.
         */      
        int32 arg;

        /**
         * Registers for storing and restoring intrrupted program.
         */
        void* reg;
        
        /**
         * Top of stack will be loaded to SP for routing an intrrupt.
         */        
        const int64* tos;
         
      };
      
      /**
       * Hi level interrupt context.
       */
      struct Context
      {

        /**
         * Number of this channel.
         */      
        int32 channel;      

        /**
         * Interrupt source.
         */
        Source source;
        
        /**
         * This user interrupt handler.
         */
        ::api::InterruptHandler* handler;
        
        /**
         * Stack of interrupt source handler.
         */    
        ::api::Stack<int64>* stack;
        
        /**
         * CPU register state of interrupt source handler.
         */
        Register* reg;
        
        /**
         * Context CPU registers for storing interrupted programme state.
         */
        ::core::epi::Register* context;

        /**
         * Low level interrupt context.
         */        
        ContextLow* low;

      };      

      /**
       * Number of interrupt channals.
       */
      static const int32 NUMBER_CHANNELS = 32;
      
      /**
       * Number of interrupt sources.
       */
      static const int32 NUMBER_SOURCES = 101;
      
      /**
       * ARM Interrupt Controller (no boot).
       */
      static registers::AINTC* aintc_;
      
      /**    
       * Hardware global interrupt controller (no boot).
       */
      static Global* global_;
      
      /**
       * Hi level interrupt channels (no boot).
       */        
      static Context context_[NUMBER_CHANNELS];
      
      /**
       * Low level interrupts context table (no boot).
       */    
      static ContextLow* contextLow_;
      
      /**
       * This interrupt channel.
       */
      Context* ctx_;
      
    };
  }
}
#endif // BOOS_CORE_AM18X_INTERRUPT_HPP_
