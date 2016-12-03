/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.tms320c64x.Interrupt.hpp" 
#include "boos.core.tms320c64x.Register.hpp"
#include "boos.core.tms320c64x.registers.INTC.hpp"
#include "boos.core.Core.hpp"
#include "boos.util.Stack.hpp"
#include "boos.util.Memory.hpp"

namespace core
{
  namespace tms320c64x
  {
    /**
     * HW interrupt registers (no boot).
     */
    registers::INTC* Interrupt::intc_;

    /**
     * All interrupt handlers stack (no boot).
     */    
    ::api::Stack<int64>* Interrupt::stack_;

    /**
     * All no overrided interrupt handlers CPU register state (no boot).
     */    
    Register* Interrupt::register_;
    
    /**    
     * Hardware global interrupt controller (no boot).
     */
    Interrupt::Global* Interrupt::global_;

    /**
     * Hi level interrupts context table (no boot).
     */        
    Interrupt::Context Interrupt::context_[NUMBER_VECTORS];  

    /**
     * Low level interrupts context table (no boot).
     */    
    Interrupt::ContextLow Interrupt::contextLow_[NUMBER_VECTORS];    
    
    /**
     * Constructor.
     */
    Interrupt::Interrupt() :
      ctx_ (NULL){
      setConstruct( true );
    }  
    
    /**
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.
     * @param source  available interrupt source.     
     */
    Interrupt::Interrupt(::api::InterruptHandler& handler, int32 source) : 
      ctx_ (NULL){
      setConstruct( setHandler(handler, source) );
    }

    /**
     * Destructor.
     */
    Interrupt::~Interrupt()
    {
      removeHandler();
    }
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    bool Interrupt::isConstructed() const
    {
      return this->Parent::isConstructed();
    }
    
    /**
     * Jumps to interrupt HW vector.
     */  
    void Interrupt::jump()
    {
      if(isAllocated()) jumpLow(ctx_->number);
    }
    
    /**
     * Clears an interrupt status of this source.
     */  
    void Interrupt::clear()
    {
      if(isAllocated()) clearLow(ctx_->number);
    }
    
    /**
     * Sets an interrupt status of this source.
     */  
    void Interrupt::set()
    {
      if(isAllocated()) setLow(ctx_->number);
    }  
    
    /**
     * Locks this interrupt source.
     *
     * @return an interrupt enable source bit value before method was called.
     */    
    bool Interrupt::disable()
    {
      return isAllocated() ? disableLow(ctx_->number) : false;
    }
    
    /**
     * Unlocks this interrupt source.
     *
     * @param status returned status by disable method.
     */
    void Interrupt::enable(bool status)
    {
      if(isAllocated()) enableLow(ctx_->number, status);
    }
    
    /** 
     * Returns the switchable interface for global interrupt controlling.
     *
     * @return switchable interface.
     */ 
    ::api::Switchable& Interrupt::global()
    {
      if(global_ == NULL) ::core::Core::fail();
      return *global_;
    }
    
    /**
     * Tests if this interrupt source can be polarized.
     *
     * @return true if this source is polarizing.
     */  
    bool Interrupt::isPolarizing()
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
    void Interrupt::risingPolarization()
    {
      if(!isAllocated()) return;
      switch(ctx_->source)
      {
        case GPINT4: intc_->extpol.bit.xip4 = 0; break;
        case GPINT5: intc_->extpol.bit.xip5 = 0; break;
        case GPINT6: intc_->extpol.bit.xip6 = 0; break;
        case GPINT7: intc_->extpol.bit.xip7 = 0; break;
      }
    }
    
    /**
     * Sets a high-to-low transition on an interrupt source.
     */
    void Interrupt::fallingPolarization()
    {
      if(!isAllocated()) return;
      switch(ctx_->source)
      {
        case GPINT4: intc_->extpol.bit.xip4 = 1; break;
        case GPINT5: intc_->extpol.bit.xip5 = 1; break;
        case GPINT6: intc_->extpol.bit.xip6 = 1; break;
        case GPINT7: intc_->extpol.bit.xip7 = 1; break;
      }
    }
    
    /**
     * Sets interrupt source handler.
     *
     * @param source  available interrupt source.
     * @param handler pointer to user class which implements an interrupt handler interface..
     * @return true if handler is set successfully.
     */      
    bool Interrupt::setHandler(::api::InterruptHandler& handler, int32 source)
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
      if(ctx_ != NULL) return global().enable(is, false);
      // Test if interrupt source is alloced
      for(int32 i=0; i<NUMBER_VECTORS; i++)
        if(context_[i].source == src) 
          return global().enable(is, false); 
      // Looking for free vector and alloc that if it is found          
      for(int32 i=0; i<NUMBER_VECTORS; i++)
      {
        if(context_[i].handler != NULL) continue;
        if(setMux(src, i+4) == false) return global().enable(is, false);        
        ctx_ = &context_[i];
        ctx_->source = src;
        ctx_->handler = &handler;
        ctx_->number = i+4;
        // TODO: Registers and Stack should be a local for nested interrupts
        ctx_->reg = register_;
        ctx_->stack = stack_;      
        contextLow_[i].reg = ctx_->reg->registers();
        contextLow_[i].tos = ctx_->stack->tos();      
        risingPolarization();
        break;
      }  
      return global().enable(is, true);
    }
    
    /**
     * Removes this interrupt source.
     */
    void Interrupt::removeHandler()
    {
      if(!isAllocated()) return;  
      bool is = global().disable();
      disable();
      clear();
      setMux(Interrupt::DSPINT, ctx_->number);
      ctx_->reg = NULL;
      ctx_->stack = NULL;
      ctx_->handler = NULL;
      ctx_->number = 0;
      ctx_->source = Interrupt::DSPINT;      
      ctx_ = NULL;
      global().enable(is);  
    }
    
    /**
     * Sets new registers context for store.
     * 
     * @param reg new registers context.
     */        
    void Interrupt::setRegister(::core::epi::Register& reg)
    {
      if(isAllocated()) contextLow_[ctx_->number - 4].reg = reg.registers();
    }
    
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    bool Interrupt::init()
    {
      int32 stage = 0;
      intc_ = new (registers::INTC::ADDRESS) registers::INTC();
      stack_ = NULL;
      register_ = NULL;
      global_ = NULL;
      util::Memory::memset(context_, 0x0, sizeof(context_));
      util::Memory::memset(contextLow_, 0x0, sizeof(contextLow_));    
      while(true)
      {
        // Stage 1 creates global interrupt class switching
        stage++;
        global_ = new Global();
        if( !isObject<Global>(global_) ) break;
        // Stage 2 creates register contex for all router
        stage++;
        register_ = new Register();
        if( !isObject<Register>(register_) ) break;        
        // Stage 3 creates stack for all router
        stage++;
        int32 count = ::core::Core::configuration().interruptStackSize >> 3;
        ::util::Stack<int64>* stack = new ::util::Stack<int64>(::util::Stack<int64>::ED, count);
        stack_ = stack;
        if( !isObject< ::util::Stack<int64> >(stack) ) break;                    
        // Stage complete
        stage = 0;
        break;
      }
      switch(stage)
      {
        case 3: delete stack_; stack_ = NULL;
        case 2: delete register_; register_ = NULL;
        case 1: delete global_; global_ = NULL;      
        default: return false;
        case 0: return true;
      }
    }    
    
    /**
     * Deinitialization.
     */
    void Interrupt::deinit()
    {
      intc_ = NULL;
      delete stack_; 
      stack_ = NULL;
      delete register_; 
      register_ = NULL; 
      delete global_;
      global_ = NULL;         
      util::Memory::memset(context_, 0x0, sizeof(context_));
      util::Memory::memset(contextLow_, 0x0, sizeof(contextLow_));    
    }
    
    /**
     * Current object has HW interrupt.
     *
     * @return true if object has interrupt source.
     */
    bool Interrupt::isAllocated()
    {
      if(!isConstructed()) return false;
      return ctx_ == NULL ? false : true;
    }     
    
    /**
     * Set MUX register.
     *
     * @param source available interrupt source.
     * @param vn hardware interrupt vector number.
     * @return true if no error.
     */    
    bool Interrupt::setMux(Source source, int32 vn)
    {
      registers::INTC intc = *intc_;
      switch(vn)
      {
        case  4: intc.muxl.bit.intsel4  = source; break;
        case  5: intc.muxl.bit.intsel5  = source; break;
        case  6: intc.muxl.bit.intsel6  = source; break;
        case  7: intc.muxl.bit.intsel7  = source; break;
        case  8: intc.muxl.bit.intsel8  = source; break;
        case  9: intc.muxl.bit.intsel9  = source; break;
        case 10: intc.muxh.bit.intsel10 = source; break;
        case 11: intc.muxh.bit.intsel11 = source; break;
        case 12: intc.muxh.bit.intsel12 = source; break;
        case 13: intc.muxh.bit.intsel13 = source; break;
        case 14: intc.muxh.bit.intsel14 = source; break;
        case 15: intc.muxh.bit.intsel15 = source; break;
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
    void Interrupt::handler(register int32 index)
    {
      register Context* ctx = &context_[index];
      register ::api::InterruptHandler* handler = ctx->handler;
      handler->handler();
    }
  }
}

