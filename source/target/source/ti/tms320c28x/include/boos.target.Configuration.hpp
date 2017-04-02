/** 
 * Target kernel configuration.
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
  struct Configuration
  {

  public:
  
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
     * Assignment operator.
     *
     * @param obj reference to source object.
     * @return reference to this object.     
     */
    Configuration& operator =(const Configuration& obj)
    {
      sourceClock = obj.sourceClock;
      cpuClock    = obj.cpuClock;
      heapAddr    = obj.heapAddr;
      heapSize    = obj.heapSize;
      return *this;
    }
       
  };
}
#endif // BOOS_TARGET_CONFIGURATION_HPP_
