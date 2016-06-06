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

#include "boos.Types.hpp"

namespace core
{
  class  Heap;

  class Allocator
  {
    
  public:

    /**
     * Allocates memory.
     *
     * @param size required memory size in byte.
     * @return pointer to allocated memory or NULL.
     */    
    static void* alloc(size_t size);

    /**
     * Frees an allocated memory.
     *
     * @param ptr pointer to allocated memory.
     */      
    static void free(void* ptr);    

  private:

    static bool               init();
    static void               deinit();

    static Heap*              heap_;

    friend class              Core;
  };
}
#endif // BOOS_CORE_ALLOCATOR_HPP_
