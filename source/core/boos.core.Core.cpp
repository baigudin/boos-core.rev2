/** 
 * Core of system.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Core.hpp"
#include "boos.core.Allocator.hpp"
#include "boos.core.Synchronizer.hpp"
#include "boos.core.Thread.hpp"
#include "boos.core.MainThread.hpp"
#include "boos.core.CoreTimerInterrupt.hpp"

namespace core
{
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
   * Starts the core.
   *
   * @param heap a target core heap interface.
   */   
  void Core::start(::api::Heap& heap)   
  {
    int32 stage = 0;  
    // Default configuration of global core variables
    interrupt_ = NULL;  
    do{
      // Stage 1
      stage++;
      if( !Allocator::init(heap) ) break;
      // Stage 4
      stage++;
      if( !Thread::init() ) break;      
      // Stage 5
      stage++;
      if( !Synchronizer::init() ) break;      
      // Stage 6
      stage++;
      if( !Core::init() ) break;      
      // Stage complete
      stage = -1;
      execute();
    }while(false);
    switch(stage)
    {
      default:
      case  4: Core::deinit();
      case  3: Synchronizer::deinit();      
      case  2: Thread::deinit();
      case  1: Allocator::deinit();
      case  0: break;
    }
  }
  
  /**
   * Starts to execute the core.
   */
  void Core::execute()
  {
    MainThread main;
    if(!main.isConstructed()) return;
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
    interrupt_ = new CoreTimerInterrupt();
    return interrupt_ != NULL ? interrupt_->isConstructed() : false;
  }
  
  /**
   * Deinitialization.
   */
  void Core::deinit()
  {
    delete interrupt_;
    interrupt_ = NULL;
  }
  
  /** 
   * Terminates the core.
   */      
  void Core::fail()
  {
    if(interrupt_ != NULL) interrupt_->global().disable();
    while(true);
  }

  /**
   * Hardware timer interrupt resource of core (no boot).
   */
  CoreTimerInterrupt* Core::interrupt_;
}
