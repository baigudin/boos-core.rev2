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
    sourceClock        (25000000),
    cpuClock           (375000000),
    heapAddr           (reinterpret_cast<void*>(0xffff0800)),
    heapSize           (0x00001800){
  }
}
