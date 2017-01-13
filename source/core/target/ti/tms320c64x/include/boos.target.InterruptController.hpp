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

#include "boos.target.Core.hpp"
#include "boos.target.Object.hpp"
#include "boos.target.Interrupt.hpp"
#include "boos.target.Configuration.hpp"
#include "boos.target.registers.Cpu.hpp"
#include "boos.target.registers.Intc.hpp"
#include "boos.util.Stack.hpp"
#include "boos.util.Memory.hpp"

namespace target
{
  class Core;
  
  class InterruptController : public ::target::Object<>, public ::target::Interrupt
  {
    friend class Core;
    typedef ::target::Object<>              Parent;
    typedef ::util::Stack<int64,Allocator>  Stack;

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
    InterruptController() :
      ctx_ (NULL){
      setConstruct( true );
    } 

    /** 
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.
     * @param source  available interrupt source.
     */     
    InterruptController(::api::Task& handler, int32 source) :
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
      if(!isAllocated()) return;
      jumpLow(ctx_->number);    
    }
    
    /**
     * Clears an interrupt status of this source.
     */     
    virtual void clear()
    {
      if(!isAllocated()) return;    
      clearLow(ctx_->number);    
    }
    
    /**
     * Sets an interrupt status of this source.
     */    
    virtual void set()
    {
      if(!isAllocated()) return;
      setLow(ctx_->number);    
    }  
    
    /**
     * Locks this interrupt source.
     *
     * @return an interrupt enable source bit value before method was called.
     */    
    virtual bool disable()
    {
      if(!isAllocated()) return false;
      return disableLow(ctx_->number);
    }
    
    /**
     * Unlocks this interrupt source.
     *
     * @param status returned status by lock method.
     */
    virtual void enable(bool status)
    {
      if(!isAllocated()) return;    
      enableLow(ctx_->number, status);    
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
      Source src;
      switch(source)
      {
        case DSPINT     : src = DSPINT;     break;
        case TINT0      : src = TINT0;      break;
        case TINT1      : src = TINT1;      break;
        case SD_INTA    : src = SD_INTA;    break;
        case GPINT4     : src = GPINT4;     break;
        case GPINT5     : src = GPINT5;     break;
        case GPINT6     : src = GPINT6;     break;
        case GPINT7     : src = GPINT7;     break;
        case EDMA_INT   : src = EDMA_INT;   break;
        case XINT0      : src = XINT0;      break;
        case RINT0      : src = RINT0;      break;
        case XINT1      : src = XINT1;      break;
        case RINT1      : src = RINT1;      break;
        case GPINT0     : src = GPINT0;     break;
        case XINT2      : src = XINT2;      break;
        case RINT2      : src = RINT2;      break;
        case TINT2      : src = TINT2;      break;
        case SD_INTB    : src = SD_INTB;    break;
        case PCI_WAKEUP : src = PCI_WAKEUP; break;
        case UINT       : src = UINT;       break;
        default         : return false;
      }
      bool is = global().disable();
      if(isAllocated()) return global().enable(is, false);
      // Test if interrupt source is alloced
      for(int32 i=0; i<NUMBER_VECTORS; i++)
        if(context_[i].source == src) 
          return global().enable(is, false); 
      // Looking for free vector and alloc that if it is found          
      int32 index = -1;
      for(int32 i=0; i<NUMBER_VECTORS; i++)
      {
        if(context_[i].handler != NULL) continue;
        index = i;
        break;
      }
      if(index < 0) return global().enable(is, false);      
      ctx_ = &context_[index];
      ctx_->low = &contextLow_[index];
      ctx_->number = index + 4;      
      ctx_->source = src;
      ctx_->handler = &handler;      
      ctx_->reg = new registers::Cpu();;
      if(ctx_->reg == NULL || !ctx_->reg->isConstructed() ) return global().enable(is, false);            
      ctx_->stack = new Stack(Stack::ED, handler.stackSize() >> 3);
      if(ctx_->stack == NULL || !ctx_->stack->isConstructed()) return global().enable(is, false);;        
      ctx_->low->reg = ctx_->reg->registers();
      ctx_->low->tos = ctx_->stack->tos();      
      if(setMux(src, ctx_->number) == false) return global().enable(is, false);        
      risingPolarization();
      return global().enable(is, true);
    }

    /**
     * Removes this interrupt source.
     */        
    virtual void removeHandler()
    {
      if(!isAllocated()) return;  
      bool is = global().disable();
      disable();
      clear();
      setMux(DSPINT, ctx_->number);
      ctx_->low->reg = NULL;
      ctx_->low->tos = NULL;
      delete ctx_->stack;      
      ctx_->stack = NULL;
      delete ctx_->reg;
      ctx_->reg = NULL;      
      ctx_->handler = NULL;
      ctx_->source = DSPINT;      
      ctx_->number = 0;      
      ctx_->low = NULL;
      ctx_ = NULL;
      global().enable(is);      
    }
    
    /**
     * Resets registers context for storing to the default.
     */
    virtual void resetRegister()
    {
      if(!isAllocated()) return;
      ctx_->low->reg = ctx_->reg->registers();
    }
    
    /**
     * Sets new registers context for store.
     *
     * @param reg pointer to new registers context.
     */
    virtual void setRegister(::target::Register& reg)
    {
      if(!isAllocated()) return;
      ctx_->low->reg = reg.registers();
    }

    /**
     * Tests if this interrupt source can be polarized.
     *
     * @return true if this source is polarizing.
     */  
    virtual bool isPolarizing()
    {
      if(!isAllocated()) return false;
      switch(ctx_->source)
      {
        default    : return false;
        case GPINT4:
        case GPINT5:
        case GPINT6:
        case GPINT7: return true;
      }
    }
    
    /**
     * Sets a low-to-high transition on an interrupt source.
     */
    virtual void risingPolarization()
    {
      if(!isAllocated()) return;
      switch(ctx_->source)
      {
        case GPINT4: intc_->extpol.bit.xip4 = 0; break;
        case GPINT5: intc_->extpol.bit.xip5 = 0; break;
        case GPINT6: intc_->extpol.bit.xip6 = 0; break;
        case GPINT7: intc_->extpol.bit.xip7 = 0; break;
        default: break;
      }    
    }
    
    /**
     * Sets a high-to-low transition on an interrupt source.
     */
    virtual void fallingPolarization()
    {
      if(!isAllocated()) return;
      switch(ctx_->source)
      {
        case GPINT4: intc_->extpol.bit.xip4 = 1; break;
        case GPINT5: intc_->extpol.bit.xip5 = 1; break;
        case GPINT6: intc_->extpol.bit.xip6 = 1; break;
        case GPINT7: intc_->extpol.bit.xip7 = 1; break;
        default: break;
      }    
    }
    
    /** 
     * Returns the toggle interface for controlling global interrupts.
     *
     * @return toggle interface.
     */ 
    static ::api::Toggle& global()
    {
      if(global_ == NULL) Core::fail();
      return *global_;
    }
    
  private:
  
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
     * Initialization.
     *
     * @param cfg the core configuration.
     * @return true if no errors.
     */
    static bool init(const Configuration& cfg)
    {
      config_ = &cfg;
      int32 stage = 0;
      global_ = NULL;
      intc_ = new (registers::Intc::ADDRESS) registers::Intc();      
      util::Memory::memset(context_, 0x0, sizeof(context_));
      util::Memory::memset(contextLow_, 0x0, sizeof(contextLow_));    
      while(true)
      {
        // Stage 1 creates global interrupt class switching
        stage++;
        global_ = new Global();
        if( global_ == NULL || !global_->isConstructed() ) break;
        // Stage complete
        stage = 0;
        break;
      }
      switch(stage)
      {
        case 1: delete global_; global_ = NULL;      
        default: return false;
        case 0: return true;
      }
    }
    
    /**
     * Deinitialization.
     */
    static void deinit()
    {
      intc_ = NULL;
      delete global_;
      global_ = NULL;         
      util::Memory::memset(context_, 0x0, sizeof(context_));
      util::Memory::memset(contextLow_, 0x0, sizeof(contextLow_));         
    }
    
    /**
     * Set MUX register.
     *
     * @param source available interrupt source.
     * @param vn hardware interrupt vector number.
     * @return true if no error.
     */    
    static bool setMux(Source source, int32 vn)
    {
      registers::Intc intc = *intc_;
      switch(vn)
      {
        case  4: intc.muxl.bit.intsel4  = source & 0x1f; break;
        case  5: intc.muxl.bit.intsel5  = source & 0x1f; break;
        case  6: intc.muxl.bit.intsel6  = source & 0x1f; break;
        case  7: intc.muxl.bit.intsel7  = source & 0x1f; break;
        case  8: intc.muxl.bit.intsel8  = source & 0x1f; break;
        case  9: intc.muxl.bit.intsel9  = source & 0x1f; break;
        case 10: intc.muxh.bit.intsel10 = source & 0x1f; break;
        case 11: intc.muxh.bit.intsel11 = source & 0x1f; break;
        case 12: intc.muxh.bit.intsel12 = source & 0x1f; break;
        case 13: intc.muxh.bit.intsel13 = source & 0x1f; break;
        case 14: intc.muxh.bit.intsel14 = source & 0x1f; break;
        case 15: intc.muxh.bit.intsel15 = source & 0x1f; break;
        default: return false;
      }
      *intc_ = intc;
      return true;
    }    
    
    /**
     * HW interrupt handle routing.
     *
     * @param index index of HW interrupt vector number in context table
     */  
    static void handler(register int32 index);   

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
     * Hardware global interrupts controller.
     */
    class Global : public ::target::Object<>, public ::api::Toggle
    {
      typedef ::target::Object<> Parent;

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
          return InterruptController::globalDisableLow();
        }
        
        /** 
         * Enables all maskable interrupts.
         *
         * @param status returned status by disable method.
         */    
        virtual void enable(bool status)
        {
          InterruptController::globalEnableLow(status);
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
         * Number of interrupt vector.
         */
        int32 number;
      
        /**
         * Interrupt source.
         */
        Source source;

        /**
         * This user interrupt handler.
         */
        ::api::Task* handler;
      
        /**
         * CPU register state of interrupt source handler.
         */
        Register* reg;
        
        /**
         * Stack of interrupt source handler.
         */         
        ::api::Stack<int64>* stack;
        
        /**
         * Low level interrupt context.
         */        
        ContextLow* low;        

      };

      /**
       * Number of HW interrupt vectors.
       */
      static const int32 NUMBER_VECTORS = 12;

      /**
       * HW interrupt registers (no boot).
       */
      static registers::Intc* intc_;
      
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
       * The core configuration (no boot).
       */
      static const Configuration* config_;

      /**
       * Pointer to the hi level interrupt context.
       */    
      Context* ctx_;
  
  };
}
#endif // BOOS_TARGET_INTERRUPT_CONTROLLER_HPP_
