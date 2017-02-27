/** 
 * Target kernel system.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_SYSTEM_HPP_
#define BOOS_TARGET_SYSTEM_HPP_

#include "boos.Types.hpp"

namespace target
{
  class System
  {

  public:

    /**
     * Fails the target kernel.
     */
    static void fail();

  };
}
#endif // BOOS_TARGET_SYSTEM_HPP_
