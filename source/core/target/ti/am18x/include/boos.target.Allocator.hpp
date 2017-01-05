/** 
 * Memory allocator for target library.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_ALLOCATOR_HPP_
#define BOOS_TARGET_ALLOCATOR_HPP_

#include "boos.api.Heap.hpp"

namespace target
{
  class Core;

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
     * @param heap constructed heap memory(no boot).
     * @return true if no errors.
     */
    static bool init(::api::Heap& heap);

    /**
     * Deinitialization.
     */
    static void deinit();
    
    /**
     * Pointer to constructed heap memory (no boot).
     */
    static ::api::Heap* heap_;

  };
}
#endif // BOOS_TARGET_ALLOCATOR_HPP_
