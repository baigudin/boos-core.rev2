/** 
 * The common kernel main class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_MAIN_HPP_
#define BOOS_CORE_MAIN_HPP_

#include "boos.Types.hpp"

namespace core
{
  class Main
  {
  
  public:
  
    /**
     * Common kernel method which will be stated by target kernel.
     * 
     * @return error code or zero.
     */
    static int32 main();
    
  };
}
#endif // BOOS_CORE_MAIN_HPP_
