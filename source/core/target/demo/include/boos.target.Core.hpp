/** 
 * Core of system.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_CORE_HPP_
#define BOOS_TARGET_CORE_HPP_

#include "boos.Types.hpp"

namespace target
{
  class Core
  {

  public:

    /**
     * Starts the target core.
     *
     * @param addr pointer to heap memory.
     * @param size size of heap memory in byte
     */
    static void start(void* addr, int32 size);
    
    /**
     * Fails the target core.
     */
    static void fail();
    
  private:    
    
  };
}
#endif // BOOS_TARGET_CORE_HPP_
