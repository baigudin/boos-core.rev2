/** 
 * Core configuration.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_CORE_CONFIG_HPP_
#define BOOS_CORE_CORE_CONFIG_HPP_

namespace core
{
  class Configuration
  {

  public:

    /** 
     * Constructor.
     */     
    Configuration() :
      sourceClock        (0),
      cpuClock           (0),
      quant              (0),
      threadStackSize    (0),
      interruptStackSize (0),
      mainThreadPriority (0),
      heapCount          (0),
      heap               (0){
    }      
        
    /** 
     * Destructor.
     */
   ~Configuration()
    {
    } 

    /**
     * Core heap configuration.
     */
    struct Heap
    {
    
    private:
    
      /**
       * For alignment to four.
       */
      int32 temp_;
      
    public:

      /**
       * Start address of heap page.
       */      
      void* addr;
      
      /**
       * Size of heap page in bytes.
       */  
      int64 size;
      
    };                       
    
    /**
     * Source clock in Hz.
     */      
    int64 sourceClock;
    
    /**
     * CPU clock in Hz.
     */  
    int64 cpuClock;
    
    /**
     * Process switch time in microseconds.
     */  
    int32 quant;
    
    /**
     * Size of thread stack by default.
     */  
    int32 threadStackSize;
    
    /**
     * Size of interrupt stack by default.
     */  
    int32 interruptStackSize;

    /**
     * Priority of main thread.
     */  
    int32 mainThreadPriority;

    /**
     * Count of system heap memories.
     */  
    int32 heapCount;

    /**
     * Pointer to system heap table.
     */    
    Heap* heap;
    
  };
}
#endif // BOOS_CORE_CORE_CONFIG_HPP_
