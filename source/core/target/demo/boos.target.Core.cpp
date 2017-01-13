/** 
 * Core of system.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.Core.hpp"
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
   * @param addr pointer to heap memory.
   * @param size size of heap memory in byte
   */
  void Core::start(void* addr, int32 size)
  {
    ::api::Heap* heap = NULL;    
    int32 stage = 0;  
    do{
      // Stage 1 creates heap
      stage++;
      heap = new (addr) ::util::Heap(size);
      if(heap == NULL || !heap->isConstructed()) break;
      // Stage 2
      stage++;
      if( !Allocator::init(*heap) ) break;
      // Stage 3
      stage++;
      if( !InterruptController::init() ) break;
      // Stage 4
      stage++;
      if( !TimerController::init() ) break;
      // Stage complete
      stage = -1;
      // Start the main core
      core::Main::main(*heap);
    }while(false);
    switch(stage)
    {
      default:
      case  4: TimerController::deinit();
      case  3: InterruptController::deinit();
      case  2: Allocator::deinit();
      case  1: delete heap;
      case  0: break;
    }
  }
  
  /**
   * Fails the target core.
   */
  void Core::fail()
  {
    while(true);
  }  
}
