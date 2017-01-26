/** 
 * System class of the kernel.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_SYSTEM_HPP_
#define BOOS_CORE_SYSTEM_HPP_

#include "boos.core.Types.hpp"

namespace core
{
  class System
  {
    
  public:
    
    /** 
     * Returns a current value of the running system in milliseconds.
     *
     * @return time in milliseconds.
     */
    static int64 currentTimeMillis();

    /** 
     * Returns a current value of the running system.
     *
     * @return time in nanoseconds.
     */      
    static int64 nanoTime();

  };
}
#endif // BOOS_CORE_SYSTEM_HPP_
