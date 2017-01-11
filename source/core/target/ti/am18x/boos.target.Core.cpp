/** 
 * Core of system.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.Core.hpp"
#include "boos.target.Boot.hpp"
#include "boos.target.Configuration.hpp"
#include "boos.target.Environment.hpp"
#include "boos.target.TimerController.hpp"
#include "boos.target.InterruptController.hpp"
#include "boos.target.Allocator.hpp"
#include "boos.core.Main.hpp"
#include "boos.util.Heap.hpp"

namespace target
{
  /**
   * Starts the target core.
   *
   * Reference to global interrupts interface pointer is used for
   * possibility to change a value of that pointer.
   * Until that pointer is NULL global interrupts is not used.
   * This gives you a possibility to change using global interrupts
   * on fly.     
   *
   */
  void Core::start()
  {
    const Configuration cfg = Configuration();  
    ::api::Heap* heap = NULL;    
    // The target interrupt controller will not have been initialized 
    // by the heap object will be created. So, set the pointer to null 
    // for allowing the heap object does not switch global interrupts until 
    // the pointer will have gotten a value by the interrupt controller.
    ::api::Toggle* global = NULL;    
    int32 stage = 0;  
    do{
      // Stage 1 initializes target hardware
      stage++;
      if( !Environment::init(cfg) ) break;    
      // Stage 2 creates heap
      stage++;
      heap = new (cfg.heapAddr) ::util::Heap(cfg.heapSize, global);
      if(heap == NULL || !heap->isConstructed()) break;
      // Stage 3
      stage++;
      if( !Allocator::init(*heap) ) break;
      // Stage 4
      stage++;
      if( !InterruptController::init(cfg) ) break;
      // Stage 5
      stage++;
      if( !TimerController::init(cfg) ) break;
      // Stage 6 enables controlling global interrupts for allocating heap memory
      global = &InterruptController::global();
      // Stage 7 initializes global variables and calls global class constructors
      stage++;
      if( !Boot::init() ) break;                  
      // Stage complete
      stage = -1;
      // Start the main core
      core::Main::main(*heap);
    }while(false);
    switch(stage)
    {
      default:
      case  7: Boot::deinit();
      case  6: global = NULL;
      case  5: TimerController::deinit();
      case  4: InterruptController::deinit();
      case  3: Allocator::deinit();
      case  2: delete heap;
      case  1: Environment::deinit();
      case  0: break;
    }
  }
  
  /**
   * Fails the target core.
   */
  void Core::fail()
  {
    InterruptController::globalDisable();
    while(true);
  }      
}
