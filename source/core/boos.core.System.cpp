/** 
 * System class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Core.hpp" 
#include "boos.core.System.hpp"

namespace core
{
  /**
   * Current value of the running system in milliseconds.
   *
   * @return time in milliseconds.
   */  
  int64 System::currentTimeMillis()
  {
    return nanoTime() / 1000000;
  }

  /**
   * Current value of the running system.
   *
   * @return time in nanoseconds.
   */  
  int64 System::nanoTime()
  {
    return Core::nanoTime();
  }
}
