/** 
 * The common core main class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Main.hpp"
#include "boos.core.Core.hpp"

namespace core
{
  /**
   * The core main method.
   *
   * @param heap a target core heap interface.
   */   
  void Main::main(::api::Heap& heap)
  {
    Core::start(heap);
  }
}
