/** 
 * Target core configuration.
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
    sourceClock        (36000000),
    cpuClock           (720000000),
    heapAddr           (reinterpret_cast<void*>(0x00031000)),
    heapSize           (0x0000f000){
  }
}
