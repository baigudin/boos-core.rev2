/** 
 * Target kernel of system.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_CORE_HPP_
#define BOOS_TARGET_CORE_HPP_

#include "boos.api.Heap.hpp"

namespace target
{
  class Core
  {

  public:
    
    /**
     * Fails the target kernel.
     */
    static void fail();
    
  };
}
#endif // BOOS_TARGET_CORE_HPP_
