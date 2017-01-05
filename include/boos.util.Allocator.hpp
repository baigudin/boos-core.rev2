/** 
 * Memory allocator for utility library.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_UTIL_ALLOCATOR_HPP_
#define BOOS_UTIL_ALLOCATOR_HPP_

#include "boos.core.Allocator.hpp"

namespace util
{
  class Allocator : public ::core::Allocator
  {
    typedef ::core::Allocator Parent;
    
  public:

    /**
     * Allocates memory.
     *
     * @param size number of bytes to allocate.
     * @return allocated memory address or a null pointer.
     */    
    static void* alloc(size_t size)
    {
      return Parent::alloc(size);
    }

    /**
     * Frees an allocated memory.
     *
     * @param ptr address of allocated memory block or a null pointer.
     */      
    static void free(void* ptr)
    {
      Parent::free(ptr);
    }

  protected:

    /**
     * Constructor.
     */
    Allocator() : Parent(){}

    /**
     * Destructor.
     */
    virtual ~Allocator(){}

  };
}
#endif // BOOS_UTIL_ALLOCATOR_HPP_
