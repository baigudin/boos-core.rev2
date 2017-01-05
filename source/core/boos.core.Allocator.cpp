/** 
 * System memory allocation.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Allocator.hpp" 

namespace core
{
  /**
   * Allocates memory.
   *
   * @param size number of bytes to allocate.
   * @return allocated memory address or a null pointer.
   */    
  void* Allocator::alloc(size_t size)
  {
    return heap_ != NULL ? heap_->alloc(size, NULL) : NULL;
  }

  /**
   * Frees an allocated memory.
   *
   * @param ptr address of allocated memory block or a null pointer.
   */
  void Allocator::free(void* ptr)
  {
    if(heap_ != NULL && ptr != NULL) heap_->free(ptr);
  }

  /**
   * Initialization.
   *
   * @param heap a heap interface.   
   * @return true if no errors.
   */
  bool Allocator::init(::api::Heap& heap)
  {
    heap_ = &heap;
    return true;
  }
  
  /**
   * Deinitialization.
   */
  void Allocator::deinit()
  {
    heap_ = NULL;
  }
  
  /**
   * Pointer to allocated heap memory block (no boot).
   */
  ::api::Heap* Allocator::heap_;
}
