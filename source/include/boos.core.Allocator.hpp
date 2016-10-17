/** 
 * System memory allocator.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_ALLOCATOR_HPP_
#define BOOS_CORE_ALLOCATOR_HPP_

#include "boos.api.Heap.hpp"

namespace core
{
  class Allocator
  {
    friend class Core;
    
  public:

    /**
     * Allocates memory.
     *
     * @param size number of bytes to allocate.
     * @return allocated memory address or a null pointer.
     */    
    static void* alloc(size_t size);

    /**
     * Frees an allocated memory.
     *
     * @param ptr address of allocated memory block or a null pointer.
     */      
    static void free(void* ptr);    

  private:

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
     * Pointer to allocated heap memory block (no boot).
     */
    static ::api::Heap* heap_;

  };
}
#endif // BOOS_CORE_ALLOCATOR_HPP_
