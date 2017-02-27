/** 
 * Target kernel configuration.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.Configuration.hpp"
 
namespace target
{
  /** 
   * Constructor.
   */     
  Configuration::Configuration() :
    sourceClock        (30000000),
    cpuClock           (150000000),
    heapAddr           (reinterpret_cast<void*>(0x00000400)),
    heapSize           (0x00000400){
  }
}
