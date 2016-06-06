/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_INTERRUPT_HPP_
#define BOOS_CORE_INTERRUPT_HPP_

#include "boos.core.Object.hpp"
#include "boos.api.Interrupt.hpp"
#include "boos.api.InterruptHandler.hpp"

namespace core
{
  class Register;
  class Stack;

  class Interrupt : public Object<>, public api::Interrupt
  {

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
     * External interrupt polarity register configuration
     */
    enum EdgeDriven
    {
      RISING  = 0,
      FALLING = 1
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
    Interrupt(api::InterruptHandler& handler, Source source);
    
    /** 
     * Destructor.
     */
    virtual ~Interrupt();
    
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
    static api::Switchable& global();
    
    /** 
     * Configures an external interrupt polarity register.
     *
     * As a rule this configuration is used as configuration of external interrupt pins.
     * By default those pins are configured as low-to-high transition.
     *
     * @param edge transition on an interrupt source is recognized as an interrupt.
     */    
    void edge(EdgeDriven edge);

  protected:

    /**
     * Sets interrupt source handler.
     *
     * @param source  available interrupt source.
     * @param handler pointer to user class which implements an interrupt handler interface.
     * @return true if handler is set successfully.
     */      
    virtual bool setHandler(Source source, api::InterruptHandler& handler);

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
    virtual void setRegister(Register* reg);

  private:

    /** 
     * Hardware global interrupt controller.
     */
    class Global : public Object<>, public api::Switchable
    {

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
      void*                   reg;
      void*                   tos;
    };

    struct Mux
    {
      volatile uint32*        reg;
      uint32                  mask;
    };
    
    struct Context
    {
      Register*               reg;
      Stack*                  stack;
      api::InterruptHandler*  handler;
      int32                   number;
      Source                  source;
      Mux                     mux;
    };  
  
    struct Reg
    {
      Reg(){
        reset();
      }

      void reset()
      {
        muxh = 0;
        muxl = 0;
        extpol = 0;
      }

      void* operator new(uint32, uint32 ptr)
      {
        return reinterpret_cast<void*>(ptr);
      }

      uint32                  muxh;
      uint32                  muxl;
      uint32                  extpol;
    };
    
    bool                      isAllocated();
    bool                      setMux(int32, uint32, Mux*);
    static bool               init();
    static void               deinit();
    static void               handler(int32);
    static bool               disableLow(uint32);
    static void               enableLow(uint32, bool);
    static void               setLow(uint32);
    static void               clearLow(uint32);
    static void               jumpLow(uint32);
    static bool               globalDisableLow();
    static void               globalEnableLow(bool);

    static const uint32       NUMBER_VECTORS = 12;
    static const uint32       REG_MUX_BASE = 0x019c0000;

    static Reg*               reg_;
    static Stack*             stack_;
    static Register*          register_;
    static Global*            global_;
    static Context            context_[NUMBER_VECTORS];
    static ContextLow         contextLow_[NUMBER_VECTORS];
    Context*                  ctx_;

    friend class              Core;
  };
}
#endif // BOOS_CORE_INTERRUPT_HPP_
