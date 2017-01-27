/** 
 * The target kernel main class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.Board.hpp"
#include "boos.target.InterruptController.hpp"
#include "boos.target.TimerController.hpp"
#include "boos.target.Boot.hpp"
#include "boos.target.Configuration.hpp"
#include "boos.target.Main.hpp"
#include "boos.core.Main.hpp"

namespace target
{
  /**
   * Target kernel method.
   * 
   * @return error code or zero.
   */
  int32 Main::main()   
  {
    const Configuration config = Configuration();
    ::Allocator::setHeap(config.heapAddr, config.heapSize);
    int32 error = -1;
    int32 stage = 0;  
    do{
      // Stage 1
      stage++;
      if( !Board::init(config) ) break;        
      // Stage 2
      stage++;
      if( !Boot::init() ) break;     
      // Stage 3
      stage++;
      if( !InterruptController::init(config) ) break;
      // Stage 4
      stage++;
      if( !TimerController::init(config) ) break;
      // Stage complete
      stage = -1;
      // Start the common kernel
      error = ::core::Main::main();
    }while(false);
    switch(stage)
    {
      default:
      case  4: TimerController::deinit();
      case  3: InterruptController::deinit();
      case  2: Boot::deinit();            
      case  1: Board::deinit();      
      case  0: break;
    }
    return error;
  }
}

