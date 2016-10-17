/** 
 * System memory allocation.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Core.hpp" 
#include "boos.core.Allocator.hpp" 
#include "boos.core.Heap.hpp" 
#include "boos.api.Switchable.hpp"

namespace core
{
  /**
   * Pointer to allocated heap memory block (no boot).
   */
  ::api::Heap* Allocator::heap_;
  
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
   * @return true if no errors.
   */
  bool Allocator::init()
  {
    heap_ = NULL;
    const Configuration& cfg = Core::configuration();
    ::api::Switchable*& ires = Core::global();
    if(cfg.heapCount < 1) return false;
    heap_ = new (cfg.heap[0].addr) Heap(cfg.heap[0].size, ires);
    return heap_ == NULL ? false : true;
  }
  
  /**
   * Deinitialization.
   */
  void Allocator::deinit()
  {
    if(heap_ == NULL) return;
    delete heap_;
    heap_ = NULL;
  }  
}
