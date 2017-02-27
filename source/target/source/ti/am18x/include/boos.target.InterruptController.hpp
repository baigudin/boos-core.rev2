/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_INTERRUPT_CONTROLLER_HPP_
#define BOOS_TARGET_INTERRUPT_CONTROLLER_HPP_

#include "boos.target.Object.hpp"
#include "boos.target.Interrupt.hpp"
#include "boos.target.registers.Cpu.hpp"
#include "boos.target.registers.Aintc.hpp"
#include "boos.target.Configuration.hpp"
#include "boos.util.Stack.hpp"

namespace target
{
  class Main;

  class InterruptController : public ::target::Object<>, public ::target::Interrupt
  {
    friend class Main;
    typedef ::target::Object<>              Parent;
    typedef ::util::Stack<int64,Allocator>  Stack;

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
    InterruptController() : Parent(),
      ctx_ (NULL){
      setConstruct( true );      
    }

    /** 
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.
     * @param source  available interrupt source.
     */     
    InterruptController(::api::Task& handler, int32 source) : Parent(),
      ctx_ (NULL){
      setConstruct( setHandler(handler, source) );
    }  
    
    /** 
     * Destructor.
     */
    virtual ~InterruptController()
    {
      removeHandler();
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
      if(isAllocated()) jumpLow(ctx_->source);
    }
    
    /**
     * Clears an interrupt status of this source.
     */     
    virtual void clear()
    {
      if(!isAllocated()) return;
      aintc_->sicr.bit.index = ctx_->source & 0x7f;
    }
    
    /**
     * Sets an interrupt status of this source.
     */    
    virtual void set()
    {
      if(!isAllocated()) return;
      aintc_->sisr.bit.index = ctx_->source & 0x7f;
    }  
    
    /**
     * Locks this interrupt source.
     *
     * @return an interrupt enable source bit value before method was called.
     */    
    virtual bool disable()
    {
      if(!isAllocated()) return false;
      bool is = Interrupt::globalDisable();
      uint32 n = ctx_->source >> 5;
      uint32 m = 0x00000001 << (ctx_->source & 0x1f);
      uint32 v = aintc_->esr[n].value;
      bool r = v & m ? true : false;
      aintc_->eicr.bit.index = ctx_->source & 0x7f;
      return Interrupt::globalEnable(is, r);
    }
    
    /**
     * Unlocks this interrupt source.
     *
     * @param status returned status by lock method.
     */
    virtual void enable(bool status)
    {
      if(!isAllocated()) return;
      if(status == false) return;
      aintc_->eisr.bit.index = ctx_->source & 0x7f;
    }
    
    /**
     * Sets interrupt source handler.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.
     * @param source  available interrupt source.
     * @return true if handler is set successfully.
     */      
    virtual bool setHandler(::api::Task& handler, int32 source)
    {
      bool is = Interrupt::globalDisable();      
      if(isAllocated()) return Interrupt::globalEnable(is, false);
      if(!isSource(source)) return Interrupt::globalEnable(is, false);
      Source src = static_cast<Source>(source);      
      // Test if interrupt source is alloced
      for(int32 i=0; i<NUMBER_CHANNELS; i++)
        if(context_[i].source == src)
          return Interrupt::globalEnable(is, false);
      // Looking for free IRQ channel and alloc that if it is found
      int32 channel = -1;      
      for(int32 i=2; i<NUMBER_CHANNELS; i++)
      {
        if(context_[i].source != UNDEF) continue;
        channel = i;
        break;
      }
      if(channel < 0) return Interrupt::globalEnable(is, false);
      setChannelForSource(channel, src);
      ctx_ = &context_[channel];      
      int32 stage = 0;      
      // Create dinamicle resources
      while(true)
      {
        // Stage 1 creates register contex
        stage++;
        ctx_->reg = new registers::Cpu();
        if(ctx_->reg == NULL || !ctx_->reg->isConstructed() ) break;
        // Stage 2 creates stack
        stage++;
        int32 count = handler.stackSize() >> 3;
        Stack* stack = new Stack(Stack::FD, count);
        ctx_->stack = stack;
        if(stack == NULL || !stack->isConstructed()) break;                    
        // Stage complete
        stage = 0;
        break;
      }
      switch(stage)
      {
        case  2: delete ctx_->stack; 
                 ctx_->stack = NULL;
        case  1: delete ctx_->reg; 
                 ctx_->reg = NULL;
                 ctx_ = NULL;
        default: return Interrupt::globalEnable(is, false);
        case  0: break;
      }      
      ctx_->channel = channel;
      ctx_->handler = &handler;
      ctx_->source = src;
      ctx_->low = &contextLow_[ctx_->source];
      ctx_->low->arg = channel;        
      ctx_->low->reg = ctx_->reg->registers();
      ctx_->low->tos = ctx_->stack->tos();
      return Interrupt::globalEnable(is, true);
    }

    /**
     * Removes this interrupt source.
     */        
    virtual void removeHandler()
    {
      if(!isAllocated()) return;
      bool is = Interrupt::globalDisable();
      disable();
      clear();
      delete ctx_->stack;
      delete ctx_->reg;
      ctx_->low->arg = -1;
      ctx_->low->reg = NULL;
      ctx_->low->tos = NULL;
      ctx_->channel = -1;
      ctx_->source = UNDEF;
      ctx_->handler = NULL;
      ctx_->stack = NULL;
      ctx_->reg = NULL;
      ctx_ = NULL;
      Interrupt::globalEnable(is);  
    }
    
    /**
     * Resets registers context for storing to the default.
     */
    virtual void resetRegister()
    {
      if(isAllocated()) ctx_->low->reg = ctx_->reg->registers();
    }
    
    /**
     * Sets new registers context for store.
     *
     * @param reg pointer to new registers context.
     */
    virtual void setRegister(::target::Register& reg)
    {
      if(isAllocated()) ctx_->low->reg = reg.registers();
    }
    
    /**
     * Disables all maskable interrupts.
     *
     * @return global interrupts enable bit value before method was called.
     */
    static bool globalDisable();
    
    /**
     * Enables all maskable interrupts.
     *
     * @param status the returned status by disable method.
     */
    static void globalEnable(bool status);    
    
  private:    

    /**
     * Initialization.
     *
     * @param config the kernel configuration.
     * @return true if no errors.
     */
    static bool init(const Configuration& config)
    {
      config_ = &config;
      int32 stage = 0;
      aintc_ = new (registers::Aintc::ADDRESS) registers::Aintc();
      do{
        // Stage 1 creates global interrupts class switching
        stage++;
        if( initAintc() == false) break;
        // Stage complete
        stage = 0;
        break;
      }while(false);
      switch(stage)
      {
        case 1: deinitAintc();
        default: return false;
        case 0: return true;
      }
    }
    
    /**
     * Deinitialization.
     */
    static void deinit()
    {
      deinitAintc();      
      aintc_ = NULL;      
    }
    
    /**
     * Current object has HW interrupt.
     *
     * @return true if object has interrupt source.
     */    
    bool isAllocated()
    {
      if(!isConstructed()) return false;
      return ctx_ == NULL ? false : true;
    }
    
    /**
     * TI ARM AM18x ARM Interrupt Controller initialization.
     *
     * @return true if no errors.
     */
    static bool initAintc()
    {
      registers::Aintc& reg = *aintc_;
      // Disable AINTC 
      reg.ger.bit.enable = 0;
      // Reset channels map  
      for(int32 i=0; i<26; i++) reg.cmr[i].value = 0x00000000;
      // Clear system interrupt statuses
      for(int32 i=0; i<4; i++) reg.secr[i].value = 0xffffffff;
      // Disable all system interrupts
      for(int32 i=0; i<4; i++) reg.ecr[i].value = 0xffffffff;
      // Set ISR vector addresses
      reg.vbr.value = reinterpret_cast<uint32>(&handlerBaseLow);
      // Set the individual ISR routines sizes which equal to 32 bytes
      reg.vsr.bit.size = 3;
      // Set the Null ISR vector
      reg.vnr.value = reinterpret_cast<uint32>(&handlerNullLow);
      // Fill internal class structures
      for(int32 i=0; i<NUMBER_CHANNELS; i++)
      {
        context_[i].channel = -1;
        context_[i].source = UNDEF;
        context_[i].handler = NULL;
        context_[i].stack = NULL;
        context_[i].reg = NULL;
      }
      // Here we are trying to do not shoot a leg by mapping
      // the low context structure to individual ISR routines
      contextLow_ = reinterpret_cast<ContextLow*>(reg.vbr.value);
      for(int32 i=0; i<NUMBER_SOURCES; i++)
      {
        contextLow_[i].arg = -1;      
        contextLow_[i].reg = NULL;
        contextLow_[i].tos = NULL;        
      }
      // Enable IRQ and FIQ host interrupts
      reg.hier.bit.fiq = 1;
      reg.hier.bit.irq = 1;
      // Enable AINTC 
      reg.ger.bit.enable = 1;
      return true;
    }
    
    /**
     * TI ARM AM18x ARM Interrupt Controller deinitialization.
     */
    static void deinitAintc()
    {
      registers::Aintc& reg = *aintc_;    
      // Disable AINTC 
      reg.ger.bit.enable = 0;
      // Disable IRQ and FIQ host interrupts
      reg.hier.bit.fiq = 0;
      reg.hier.bit.irq = 0;     
    }
    
    /**
     * Sets the channel for the source.
     *
     * @param channel available channel.
     * @param source  available source.
     * @return true if the channel is set for the source.     
     */
    static bool setChannelForSource(int32 channel, Source source)
    {
      registers::Aintc& reg = *aintc_;
      if(source == UNDEF) return false;
      if(!isChannel(channel)) return false;
      int32 i = source >> 2;
      switch(source & 0x3)
      {
        case  0: reg.cmr[i].bit.channel0 = channel & 0xff; break;
        case  1: reg.cmr[i].bit.channel1 = channel & 0xff; break;
        case  2: reg.cmr[i].bit.channel2 = channel & 0xff; break;
        case  3: reg.cmr[i].bit.channel3 = channel & 0xff; break;
        default: return false;
      }
      return true;
    }    
    
    /**
     * Tests if given source is available.
     *
     * @param source interrupt source.
     * @return true if the source is available.
     */      
    static bool isSource(int32 source)
    {
      if(source < 0 || source > 100 ) return false;
      if(source == 26) return false;      
      if(28 <= source && source <= 31) return false;
      if(source == 62) return false;
      #ifdef BOOS_AM1806
      if(33 <= source && source <= 40) return false;
      if(59 <= source && source <= 60) return false;
      if(source == 67) return false;      
      #elif BOOS_AM1802
      if(3 <= source && source <= 10) return false;
      if(51 <= source && source <= 52) return false;      
      if(source == 57) return false;      
      if(59 <= source && source <= 60) return false;
      if(62 <= source && source <= 67) return false;
      if(69 <= source && source <= 73) return false;
      if(91 <= source && source <= 92) return false;
      if(97 <= source && source <= 100) return false;      
      #endif
      return true;      
    }
    
    /**
     * Tests if given channel is available.
     *
     * @param channel interrupt channel.
     * @return true if the channel is available.
     */      
    static bool isChannel(int32 channel)
    {
      return (0 <= channel && channel < NUMBER_CHANNELS) ? true : false;
    }

    /**
     * HW interrupt handle routing.
     *
     * @param channel interrupt channel.
     */
    static void handler(int32 channel);
    
    /**
     * Supervisor exception.
     *
     * @param source interrupt source.
     * @return branch address.
     */
    static int32 supervisor(int32 source);
    
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
     * Jumps to interrupt HW vector.
     *
     * @param source interrupt source.
     */    
    static void jumpLow(int32 source);

    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    InterruptController(const InterruptController& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     */
    InterruptController& operator =(const InterruptController& obj);

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
       * Constructor.
       */
      Context() :
        channel (0),
        source  (UNDEF),
        handler (NULL),
        stack   (NULL),
        reg     (NULL),
        low     (NULL){
      }

      /**
       * Destructor.
       */
      ~Context(){}

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
      ::api::Task* handler;
      
      /**
       * Stack of interrupt source handler.
       */    
      ::api::Stack<int64>* stack;
      
      /**
       * CPU register state of interrupt source handler.
       */
      ::target::Register* reg;

      /**
       * Low level interrupt context.
       */        
      ContextLow* low;

    private:

      /**
       * Copy constructor.
       *
       * @param obj reference to source object.
       */
      Context(const Context& obj);

      /**
       * Assignment operator.
       *
       * @param obj reference to source object.
       */
      Context& operator=(const Context& obj);

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
    static registers::Aintc* aintc_;
    
    /**
     * Hi level interrupt channels (no boot).
     */        
    static Context context_[NUMBER_CHANNELS];
    
    /**
     * Low level interrupts context table (no boot).
     */    
    static ContextLow* contextLow_;
    
    /**
     * The kernel configuration (no boot).
     */
    static const Configuration* config_;     
    
    /**
     * This interrupt channel.
     */
    Context* ctx_;

  };
}
#endif // BOOS_TARGET_INTERRUPT_CONTROLLER_HPP_
