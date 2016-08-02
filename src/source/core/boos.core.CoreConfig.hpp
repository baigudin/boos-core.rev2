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
  class CoreConfig
  {

  public:

    /** 
     * Constructor.
     */     
    CoreConfig() :
      cpuFrequency       (0),
      timerFrequency     (0),
      quant              (0),
      threadStackSize    (0),
      interruptStackSize (0),
      mainThreadPriority (0),
      heapCount          (0),
      temp_              (0),
      heap               (0),
      addr               (0),
      size               (0){
    }      
        
    /** 
     * Destructor.
     */
   ~CoreConfig()
    {
    } 

  public:

    /**
     * Core heap configuration.
     */
    struct Heap
    {
      int32                 temp;               // For alignment to four
      void*                 addr;               // Start address of heap page
      int64                 size;               // Size of heap page in bytes
    };                       

    int64                   cpuFrequency;       // CPU frequency in Hz
    int64                   timerFrequency;     // CPU frequency in Hz
    int32                   quant;              // Process switch time in microseconds
    int32                   threadStackSize;    // Size of thread stack by default
    int32                   interruptStackSize; // Size of interrupt stack by default
    int32                   mainThreadPriority; // Priority of main thread
    int32                   heapCount;          // Count of system heap memories

  private:

    int32                   temp_;              // Temp value for align to eight

  public:

    Heap*                   heap;               // Pointer to system heap table
    void*                   addr;               // Start address of core heap
    int64                   size;               // Size of core heap in bytes
    
  };
}
#endif // BOOS_CORE_CORE_CONFIG_HPP_
