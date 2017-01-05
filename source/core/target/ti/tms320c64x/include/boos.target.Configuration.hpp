/** 
 * Target core configuration.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_CONFIGURATION_HPP_
#define BOOS_TARGET_CONFIGURATION_HPP_

#include "boos.Types.hpp"

namespace target
{
  class Configuration
  {

  public:

    /** 
     * Constructor.
     */     
    Configuration();
    
    /** 
     * Copy constructor.
     */     
    Configuration(const Configuration& obj) :
      sourceClock (obj.sourceClock),
      cpuClock    (obj.cpuClock),
      heapAddr    (obj.heapAddr),
      heapSize    (obj.heapSize){
    }
        
    /** 
     * Destructor.
     */
   ~Configuration()
    {
    } 
    
    /**
     * Source clock in Hz.
     */      
    int64 sourceClock;
    
    /**
     * CPU clock in Hz.
     */  
    int64 cpuClock;

    /**
     * Start address of heap page.
     */      
    void* heapAddr;    
    
    /**
     * Size of heap page in bytes.
     */
    int64 heapSize; 
       
  };
}
#endif // BOOS_TARGET_CONFIGURATION_HPP_
