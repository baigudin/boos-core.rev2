/** 
 * Memory allocator.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_ALLOCATOR_HPP_
#define BOOS_ALLOCATOR_HPP_

#include "boos.util.Heap.hpp"

class Allocator
{

public:

  /**
   * Allocates memory.
   *
   * @param size number of bytes to allocate.
   * @return allocated memory address or a null pointer.
   */    
  static void* alloc(size_t size)
  {
    return heap_ != NULL ? heap_->alloc(size, NULL) : NULL;
  }

  /**
   * Frees an allocated memory.
   *
   * @param ptr address of allocated memory block or a null pointer.
   */      
  static void free(void* ptr)
  {
    if(heap_ != NULL && ptr != NULL) heap_->free(ptr);  
  }

  /**
   * Sets heap memory.
   *
   * @param add  address of heap memory.
   * @param size number of bytes of heap memory.   
   * @return true if no errors.
   */
  static void setHeap(void* addr, int64 size)
  {
    heap_ = addr != NULL && size > 0 ? new (addr) ::util::Heap(size) : NULL;
    if(heap_ == NULL || !heap_->isConstructed()) heap_ = NULL;
  }
  
  /**
   * Sets heap memory.
   *
   * @param add  address of heap memory.
   * @param size number of bytes of heap memory.   
   * @return true if no errors.
   */
  static ::api::Heap* getHeap()
  {
    return heap_;
  }  
  
private:  

  /**
   * Pointer to constructed heap memory (no boot).
   */
  static ::api::Heap* heap_;  
  
};
#endif // BOOS_CORE_ALLOCATOR_HPP_
