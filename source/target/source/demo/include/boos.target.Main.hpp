/** 
 * The target kernel main class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_MAIN_HPP_
#define BOOS_TARGET_MAIN_HPP_

#include "boos.Types.hpp"

namespace target
{
  class Main
  {
  
  public:
  
    /**
     * Target kernel method.
     * 
     * @return error code or zero.
     */
    static int32 main();
    
  };
}
#endif // BOOS_TARGET_MAIN_HPP_
