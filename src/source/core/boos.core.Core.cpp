/** 
 * Core of system.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.Main.hpp"
#include "boos.core.Core.hpp"
#include "boos.core.Allocator.hpp"
#include "boos.core.Interrupt.hpp"
#include "boos.core.Timer.hpp"
#include "boos.core.Thread.hpp"
#include "boos.core.MainThread.hpp"
#include "boos.core.TimerInterrupt.hpp"
#include "boos.core.CoreTimerInterrupt.hpp"

#ifdef __TI_EABI__
#error "ELF EABI is being developed by BAIGUDIN SOFTWARE"
#endif

namespace core
{
  /**
   * Core default configuration.
   */
  const CoreConfig*         Core::config_ = NULL;
  CoreTimerInterrupt*       Core::interrupt_ = NULL;  
  api::Switchable*          Core::globalInterrupt_ = NULL;
  
  /** 
   * Returns a current value of the running core.
   *
   * @return time in nanoseconds.
   */      
  int64 Core::nanoTime()
  {
    return interrupt_ != NULL ? interrupt_->nanoTime() : 0;
  }
  
  /**
   * Returns a core configuration structure.
   *
   * @return configuration structure.
   */    
  const CoreConfig& Core::config()
  {
    return *config_;
  }
  
  /**
   * Returns a global interrupt interface.
   *
   * @return global interrupt interface.
   */    
  api::Switchable*& Core::global()
  {
    return globalInterrupt_;
  }
  
  /**
   * Starts the core.
   *
   * @param config core configuration.
   */    
  void Core::start(const CoreConfig* config)
  {
    int32 stage = 0;  
    config_ = config;
    do{
      // Stage 1
      stage++;
      if( !Allocator::init() ) break;
      // Stage 2
      stage++;
      if( !Interrupt::init() ) break;
      // Stage 3
      stage++;
      if( !Timer::init() ) break;      
      // Stage 5
      stage++;
      if( !Thread::init() ) break;      
      // Stage 4
      stage++;
      if( !Core::init() ) break;
      // Stage complete
      stage = -1;
      start();
    }while(false);
    switch(stage)
    {
      default:
      case  5: Core::deinit();      
      case  4: Thread::deinit();
      case  3: Timer::deinit();
      case  2: Interrupt::deinit();
      case  1: Allocator::deinit();
      case  0: break;
    }
  }
  
  /**
   * Starts to execute the core.
   */
  void Core::start()
  {
    MainThread main = MainThread();
    if(!main.isConstructed()) return;
    main.setPriority(config_->mainThreadPriority);
    main.start();
    Thread::execute();
  }

  /**
   * Initialization.
   *
   * @return true if no errors.
   */
  bool Core::init()
  {
    initClassesLow();
    CoreTimerInterrupt* res = new CoreTimerInterrupt();
    if(!isConstructed(res)) return false;    
    interrupt_ = res; 
    globalInterrupt_ = &res->global();
    return true;
  }
  
  /**
   * Deinitialization.
   */
  void Core::deinit()
  {
    // This pointer has to be set to NULL 
    // before deleting the interrupt resource
    // for a lock to call an enable and disable methods.
    globalInterrupt_ = NULL;  
    delete interrupt_;
    interrupt_ = NULL;
  }
  
  /** 
   * Terminates the core.
   */      
  void Core::fail()
  {
    Interrupt::globalDisableLow();
    while(true);
  }
    
}
