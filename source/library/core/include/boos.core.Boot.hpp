/** 
 * Core boot routine.
 *
 * The module performs the tasks to initialize C/C++ run-time environment.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_BOOT_HPP_
#define BOOS_CORE_BOOT_HPP_

#include "boos.core.Object.hpp"

namespace core
{
  class Boot : public Object<>
  {
    friend class Core;

  private:
  
    /**
     * Initialization record in .cinit section.
     */    
    struct CRecord
    {
      /**
       * The size of the initialization data in bytes.
       */
      int32 size;
      
      /**
       * The starting address of the area within the .bss section.
       */
      int8* addr;
      
      /**
       * The data of a variable.
       */
      int8 data[1];
      
    };  
    
    /**
     * Initialization record in .pinit section.
     */    
    struct PRecord
    {
      /**
       * Address of constructor.
       */
      void (*constructor)();
      
    };    
  
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    static bool init();

    /**
     * Deinitialization.
     */
    static void deinit();
    
    /**
     * Returns the first record adderess.
     * 
     * @return memory address of .cinit section or NULL.
     */
    static CRecord* getCRecord();
    
    /**
     * Returns the next record adderess.
     * 
     * @param record the record address for getting next record after this.
     * @return memory address of the next record or NULL.
     */
    static CRecord* getCRecord(CRecord* record);

    /**
     * Returns the first record adderess.
     * 
     * @return memory address of .pinit section or NULL.
     */
    static PRecord* getPRecord();
    
    /**
     * Returns the next record adderess.
     * 
     * @param record the record address for getting next record after this.
     * @return memory address of the next record or NULL.
     */
    static PRecord* getPRecord(PRecord* record);
    
  };
}
#endif // BOOS_CORE_BOOT_HPP_
