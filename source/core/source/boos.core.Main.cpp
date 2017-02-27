/** 
 * The common core main class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Main.hpp" 
#include "boos.core.Core.hpp"
#include "boos.core.Interrupt.hpp"
#include "boos.core.Thread.hpp"
#include "boos.core.Synchronizer.hpp"
#include "boos.core.MainThread.hpp"
#include "boos.Allocator.hpp"

namespace core
{
  /**
   * Common kernel method which will be stated by target kernel.
   * 
   * @return error code or zero.
   */   
  int32 Main::main()  
  {
    int32 stage = 0;
    int32 error = -1;
    do{
      // Stage 1 
      stage++;
      if( not Interrupt::init() ) break;
      // Stage 2
      stage++;
      if( not Thread::init() ) break;      
      // Stage 3
      stage++;
      if( not Synchronizer::init() ) break;      
      // Stage 4
      stage++;
      if( not Core::init() ) break;      
      // Stage complete
      stage = -1;
      {
        MainThread main;
        if(main.isConstructed())
        {
          main.start();
          Thread::execute();
          error = main.error();
        }
      }
    }while(false);
    switch(stage)
    {
      default:
      case  4: Core::deinit();
      case  3: Synchronizer::deinit();      
      case  2: Thread::deinit();
      case  1: Interrupt::deinit();      
      case  0: break;
    }
    return error;
  }
}

/**
 * Pointer to constructed heap memory (no boot).
 */
::api::Heap* ::Allocator::heap_;

