/** 
 * The common core main class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_MAIN_HPP_
#define BOOS_CORE_MAIN_HPP_

#include "boos.api.Heap.hpp"

namespace core
{
  class Main
  {
  
  public:
  
    /**
     * The core main method.
     * 
     * This method will be called by a target core and 
     * is an entry point for executing the common core.
     *
     * @param heap a target core heap interface.
     */
    static void main(::api::Heap& heap);
    
  };
}
#endif // BOOS_CORE_MAIN_HPP_
