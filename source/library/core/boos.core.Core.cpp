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
#include "boos.core.Boot.hpp"
#include "boos.core.Allocator.hpp"
#include "boos.core.Interrupt.hpp"
#include "boos.core.Timer.hpp"
#include "boos.core.Thread.hpp"
#include "boos.core.Environment.hpp"
#include "boos.core.MainThread.hpp"
#include "boos.core.CoreTimerInterrupt.hpp"

namespace core
{
  /**
   * Configuration of core which is pointed to core.config.asm structure (no boot).
   */
  const Configuration* Core::config_;

  /**
   * Hardware timer interrupt resource of core (no boot).
   */
  CoreTimerInterrupt* Core::interrupt_;

  /**
   * Switchable interface of global interrupt (no boot).
   */
  ::api::Switchable* Core::global_;

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
  const Configuration& Core::configuration()
  {
    return *config_;
  }
  
  /**
   * Returns a global interrupt interface.
   *
   * @return global interrupt interface.
   */    
  ::api::Switchable*& Core::global()
  {
    return global_;
  }
  
  /**
   * Starts the core.
   *
   * @param config core configuration.
   */    
  void Core::start(const Configuration* config)
  {
    int32 stage = 0;  
    // Default configuration of global core variables
    config_ = config;
    interrupt_ = NULL;  
    global_ = NULL;
    do{
      // Stage 1
      stage++;
      if( !Allocator::init() ) break;
      // Stage 2
      stage++;
      if( !Environment::init() ) break;
      // Stage 3
      stage++;
      if( !Interrupt::init() ) break;
      // Stage 4
      stage++;
      if( !Timer::init() ) break;      
      // Stage 5
      stage++;
      if( !Thread::init() ) break;      
      // Stage 6
      stage++;
      if( !Core::init() ) break;      
      // Stage 7
      stage++;
      if( !Boot::init() ) break;                  
      // Stage complete
      stage = -1;
      start();
    }while(false);
    switch(stage)
    {
      default:
      case  7: Boot::deinit();
      case  6: Core::deinit();
      case  5: Thread::deinit();
      case  4: Timer::deinit();
      case  3: Interrupt::deinit();
      case  2: Environment::deinit();
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
    CoreTimerInterrupt* res = new CoreTimerInterrupt();
    interrupt_ = res;    
    if(!res->isObject<CoreTimerInterrupt>(res)) return false;
    ::api::Switchable& global = Interrupt::global();
    global_ = &global;
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
    global_ = NULL;  
    delete interrupt_;
    interrupt_ = NULL;
  }
  
  /** 
   * Terminates the core.
   */      
  void Core::fail()
  {
    if(global_ != NULL) global_->disable();
    while(true);
  }
    
}
