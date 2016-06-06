/** 
 * Root class of the util namespace class hierarchy.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_UTIL_OBJECT_HPP_
#define BOOS_UTIL_OBJECT_HPP_

#include "boos.Object.hpp"
#include "boos.util.Allocator.hpp"

namespace util
{
  /** 
   * @param Alloc heap memory allocator class.
   */
  template <class Alloc=Allocator>
  class Object : public ::Object<Alloc>
  {
    
  public:

    /** 
     * Constructor.
     */  
    Object()
    {
    }     
    
    /** 
     * Destructor.
     */    
    virtual ~Object()
    {
    }    
    
  };
}
#endif // BOOS_UTIL_OBJECT_HPP_
