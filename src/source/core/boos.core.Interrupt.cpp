/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Core.hpp"
#include "boos.core.Register.hpp"
#include "boos.core.Stack.hpp"
#include "boos.core.Interrupt.hpp"
#include "boos.util.Memory.hpp"
#include "boos.util.Buffer.hpp"

extern cregister volatile unsigned int CSR;

namespace core
{
  Interrupt::Context     Interrupt::context_[NUMBER_VECTORS];  
  Interrupt::ContextLow  Interrupt::contextLow_[NUMBER_VECTORS];    
  Interrupt::Reg*        Interrupt::reg_ = NULL;
  Stack*                 Interrupt::stack_ = NULL;
  Register*              Interrupt::register_ = NULL;
  Interrupt::Global*     Interrupt::global_ = NULL;
  
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
   * @param source  available interrupt source.
   * @param handler pointer to user class which implements an interrupt handler interface.
   */
  Interrupt::Interrupt(api::InterruptHandler& handler, Source source) : 
    ctx_ (NULL){
    setConstruct( setHandler(source, handler) );
  }

  /**
   * Destructor.
   */
  Interrupt::~Interrupt()
  {
    bool is = global().disable();
    edge(RISING);    
    removeHandler();
    global().enable(is);
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
  api::Switchable& Interrupt::global()
  {
    if(global_ == NULL) Core::fail();
    return *global_;
  }
  
  /** 
   * Configures an external interrupt polarity register.
   *
   * As a rule this configuration is used as configuration of external interrupt pins.
   * By default those pins are configured as low-to-high transition.   
   *
   * @param edge transition on an interrupt source is recognized as an interrupt.
   */    
  void Interrupt::edge(EdgeDriven edge)
  {
    if(!isAllocated()) return;
    int32 bit = 0;
    switch(ctx_->source)
    {
      case GPINT4: bit = 1; break;
      case GPINT5: bit = 2; break;
      case GPINT6: bit = 4; break;
      case GPINT7: bit = 8; break;
      default: return;
    }
    switch(edge)
    {    
      case RISING: reg_->extpol &= ~bit; break;
      case FALLING: reg_->extpol |= bit; break;
    }
  }  
  
  /**
   * Sets interrupt source handler.
   *
   * @param source  available interrupt source.
   * @param handler pointer to user class which implements an interrupt handler interface..
   * @return true if handler is set successfully.
   */      
  bool Interrupt::setHandler(Source source, api::InterruptHandler& handler)
  {
    bool is = global().disable();
    if(ctx_ != NULL){ global().enable(is); return false; }
    //Checking is interrupt source alloced:
    for(int32 i=0; i<NUMBER_VECTORS; i++)
    {
      if(context_[i].source == source) 
      { 
        global().enable(is); 
        return false;
      }
    }
    for(int32 i=0; i<NUMBER_VECTORS; i++)
    {
      if(context_[i].handler != NULL) continue;
      if(setMux(source, i, &context_[i].mux) == false)
      { 
        global().enable(is); 
        return false; 
      }
      ctx_ = &context_[i];
      ctx_->source = source;
      ctx_->handler = &handler;
      ctx_->number = i+4;
      // TODO: Registers and Stack should be a local for nested interrupts
      ctx_->reg = register_;
      ctx_->stack = stack_;      
      contextLow_[i].reg = ctx_->reg->regs();
      contextLow_[i].tos = ctx_->stack->tos();      
      break;
    }  
    global().enable(is);    
    return true;
  }
  
  /**
   * Removes this interrupt source.
   */
  void Interrupt::removeHandler()
  {
    if(!isAllocated()) return;  
    bool is = global().disable();
    disableLow(ctx_->number);
    clearLow(ctx_->number);    
    *ctx_->mux.reg &= ctx_->mux.mask;
    util::Memory::memset(ctx_, 0x0, sizeof(Context));
    ctx_ = NULL;
    global().enable(is);  
  }
  
  /**
   * Sets new registers context for store.
   * 
   * @param reg pointer to new registers context.
   */        
  void Interrupt::setRegister(Register* reg)
  {
    if(reg != NULL) contextLow_[ctx_->number - 4].reg = reg->regs();  
  }
  
  /**
   * Initialization.
   *
   * @return true if no errors.
   */
  bool Interrupt::init()
  {
    int32 stage = 0;
    CSR |= 0x2;
    reg_ = new (REG_MUX_BASE) Reg();
    util::Memory::memset(context_, 0x0, sizeof(context_));
    util::Memory::memset(contextLow_, 0x0, sizeof(contextLow_));    
    while(true)
    {
      // Stage 1
      stage++;
      global_ = new Global();
      if( !isConstructed(global_) ) break;    
      // Stage 2
      stage++;
      register_ = new Register();
      if( !isConstructed(register_) ) break;    
      // Stage 3
      stage++;
      stack_ = new Stack(Core::config().interruptStackSize);
      if( !isConstructed(stack_) ) break;          
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
    reg_->reset();
    reg_ = NULL;
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
   * Current object is have HW interrupt.
   *
   * @return true if object is have interrupt source.
   */

  bool Interrupt::isAllocated()
  {
    if(!isConstructed()) return false;
    return ctx_ == NULL ? false : true;
  }     

  /**
   * Set MUX register.
   *
   * @return true if no error.
   */  
  bool Interrupt::setMux(int32 source, uint32 vi, Mux* mux)
  {
    uint32 shift;
    switch( vi )
    {
      case  0: mux->reg = &reg_->muxl; mux->mask = 0xffffffe0; shift = 0;  break;    
      case  1: mux->reg = &reg_->muxl; mux->mask = 0xfffffc1f; shift = 5;  break;
      case  2: mux->reg = &reg_->muxl; mux->mask = 0xffff83ff; shift = 10; break;
      case  3: mux->reg = &reg_->muxl; mux->mask = 0xffe0ffff; shift = 16; break;
      case  4: mux->reg = &reg_->muxl; mux->mask = 0xfc1fffff; shift = 21; break;
      case  5: mux->reg = &reg_->muxl; mux->mask = 0x83ffffff; shift = 26; break;
      case  6: mux->reg = &reg_->muxh; mux->mask = 0xffffffe0; shift = 0;  break;
      case  7: mux->reg = &reg_->muxh; mux->mask = 0xfffffc1f; shift = 5;  break;
      case  8: mux->reg = &reg_->muxh; mux->mask = 0xffff83ff; shift = 10; break;
      case  9: mux->reg = &reg_->muxh; mux->mask = 0xffe0ffff; shift = 16; break;
      case 10: mux->reg = &reg_->muxh; mux->mask = 0xfc1fffff; shift = 21; break;
      case 11: mux->reg = &reg_->muxh; mux->mask = 0x83ffffff; shift = 26; break;      
      default: return false;
    }
    *mux->reg = ( *mux->reg & mux->mask ) | ( source << shift );
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
    register api::InterruptHandler* handler = ctx->handler;
    handler->handler();
  }
}

