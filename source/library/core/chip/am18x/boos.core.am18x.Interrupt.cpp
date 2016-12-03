/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.am18x.Interrupt.hpp" 
#include "boos.core.am18x.Register.hpp"
#include "boos.core.am18x.registers.AINTC.hpp"
#include "boos.core.Core.hpp"
#include "boos.util.Stack.hpp"

namespace core
{
  namespace am18x
  {
    /**
     * ARM Interrupt Controller (no boot).
     */
    registers::AINTC* Interrupt::aintc_;  
    
    /**    
     * Hardware global interrupt controller (no boot).
     */
    Interrupt::Global* Interrupt::global_;
    
    /**
     * Hi level interrupt channels (no boot).
     */        
    Interrupt::Context Interrupt::context_[Interrupt::NUMBER_CHANNELS];      
    
    /**
     * Low level interrupts context table (no boot).
     */    
    Interrupt::ContextLow* Interrupt::contextLow_;
    
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
      if(isAllocated()) jumpLow(ctx_->source);
    }
    
    /**
     * Clears an interrupt status of this source.
     */  
    void Interrupt::clear()
    {
      if(isAllocated()) aintc_->sicr.bit.index = ctx_->source;
    }
    
    /**
     * Sets an interrupt status of this source.
     */  
    void Interrupt::set()
    {
      if(isAllocated()) aintc_->sisr.bit.index = ctx_->source;
    }  
    
    /**
     * Locks this interrupt source.
     *
     * @return an interrupt enable source bit value before method was called.
     */    
    bool Interrupt::disable()
    {
      if(!isAllocated()) return false;
      bool is = global().disable();
      uint32 n = ctx_->source >> 5;
      uint32 m = 0x00000001 << (ctx_->source & 0x1f);
      uint32 v = aintc_->esr[n].value;
      bool r = v & m ? true : false;
      aintc_->eicr.bit.index = ctx_->source;
      global().enable(is);      
      return r;
    }
    
    /**
     * Unlocks this interrupt source.
     *
     * @param status returned status by disable method.
     */
    void Interrupt::enable(bool status)
    {
      if(!isAllocated()) return;
      if(status == false) return;
      aintc_->eisr.bit.index = ctx_->source;
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
      return false;
    }
    
    /**
     * Sets a low-to-high transition on an interrupt source.
     */
    void Interrupt::risingPolarization()
    {
    }
    
    /**
     * Sets a high-to-low transition on an interrupt source.
     */
    void Interrupt::fallingPolarization()
    {
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
      if(isAllocated()) return false;
      if(!isSource(source)) return false;
      if(ctx_ != NULL) return false;      
      bool is = global().disable();      
      Source src = *reinterpret_cast<Source*>(&source);      
      // Test if interrupt source is alloced
      for(int32 i=0; i<NUMBER_CHANNELS; i++)
        if(context_[i].source == src) 
          return global().enable(is, false);
      // Looking for free IRQ channel and alloc that if it is found
      int32 channel = -1;      
      for(int32 i=2; i<NUMBER_CHANNELS; i++)
      {
        if(context_[i].source != UNDEF) continue;
        channel = i;
        break;
      }
      if(channel < 0) return global().enable(is, false);      
      setChannelForSource(channel, src);
      ctx_ = &context_[channel];      
      int32 stage = 0;      
      // Create dinamicle resources
      while(true)
      {
        // Stage 1 creates register contex
        stage++;
        ctx_->reg = new Register();
        if( !isObject<Register>(ctx_->reg) ) break;        
        // Stage 2 creates stack
        stage++;
        int32 count = ::core::Core::configuration().interruptStackSize >> 3;
        ::util::Stack<int64>* stack = new ::util::Stack<int64>(::util::Stack<int64>::FD, count);
        ctx_->stack = stack;
        if( !isObject< ::util::Stack<int64> >(stack) ) break;                    
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
        default: return global().enable(is, false);
        case  0: break;
      }      
      ctx_->channel = channel;
      ctx_->context = ctx_->reg;
      ctx_->handler = &handler;
      ctx_->source = src;
      ctx_->low = &contextLow_[ctx_->source];
      ctx_->low->arg = channel;        
      ctx_->low->reg = ctx_->context->registers();
      ctx_->low->tos = ctx_->stack->tos();
      risingPolarization();
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
      ctx_->context = NULL;
      ctx_ = NULL;
      global().enable(is);  
    }
    
    /**
     * Sets new registers context for store.
     * 
     * @param reg pointer to new registers context.
     */        
    void Interrupt::setRegister(::core::epi::Register& reg)
    {
      if(isAllocated()) ctx_->low->reg = reg.registers();
    }
    
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    bool Interrupt::init()
    {
      int32 stage = 0;
      aintc_ = new (registers::AINTC::ADDRESS) registers::AINTC();
      global_ = NULL;      
      while(true)
      {
        // Stage 1 creates global interrupt class switching
        stage++;
        if( initAINTC() == false) break;
        // Stage 2 creates global interrupt class switching
        stage++;
        global_ = new Global();
        if( !isObject<Global>(global_) ) break;
        // Stage complete
        stage = 0;
        break;
      }
      switch(stage)
      {
        case 2: delete global_; global_ = NULL;      
        case 1: deinitAINTC();
        default: return false;
        case 0: return true;
      }
    }
    
    /**
     * Deinitialization.
     */
    void Interrupt::deinit()
    {
      delete global_;
      global_ = NULL;    
      deinitAINTC();      
    }
    
    /**
     * TI ARM AM18x ARM Interrupt Controller initialization.
     *
     * @return true if no errors.
     */
    bool Interrupt::initAINTC()
    {
      registers::AINTC& reg = *aintc_;
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
        context_[i].context = NULL;
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
    void Interrupt::deinitAINTC()
    {
      registers::AINTC& reg = *aintc_;    
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
    bool Interrupt::setChannelForSource(int32 channel, Source source)
    {
      registers::AINTC& reg = *aintc_;
      if(source == UNDEF) return false;
      if(!isChannel(channel)) return false;
      int32 i = source >> 2;
      switch(source & 0x3)
      {
        case  0: reg.cmr[i].bit.channel0 = channel; break;
        case  1: reg.cmr[i].bit.channel1 = channel; break;
        case  2: reg.cmr[i].bit.channel2 = channel; break;
        case  3: reg.cmr[i].bit.channel3 = channel; break;                        
        default: return false;
      }
      return true;
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
     * Tests if given source is available.
     *
     * @param source  interrupt source.
     * @return true if the source is available.
     */      
    bool Interrupt::isSource(int32 source)
    {
      if(source < 0 || source > 100 ) return false;
      if(source == 26) return false;      
      if(28 <= source && source <= 31) return false;
      if(source == 62) return false;
      #ifdef BS_AM1806
      if(33 <= source && source <= 40) return false;
      if(59 <= source && source <= 60) return false;
      if(source == 67) return false;      
      #elif BS_AM1802
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
    bool Interrupt::isChannel(int32 channel)
    {
      return (0 <= channel && channel < NUMBER_CHANNELS) ? true : false;
    }
    
    /**
     * HW interrupt handle routing.
     *
     * @param channel interrupt channel.
     */
    void Interrupt::handler(register int32 channel)
    {
      register Context* ctx = &context_[channel];
      register ::api::InterruptHandler* handler = ctx->handler;
      handler->handler();
    }
    
    /**
     * Supervisor exception.
     *
     * @param source interrupt source.
     * @return branch address.
     */
    int32 Interrupt::supervisor(int32 source)
    {
      register int32 size = 4 * (0x1 << aintc_->vsr.bit.size);
      return aintc_->vbr.bit.base + source * size;
    }

  }
}

