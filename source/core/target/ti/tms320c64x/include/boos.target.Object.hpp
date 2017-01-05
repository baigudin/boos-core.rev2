/** 
 * Root class of the target namespace class hierarchy.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_OBJECT_HPP_
#define BOOS_TARGET_OBJECT_HPP_

#include "boos.Object.hpp"
#include "boos.target.Allocator.hpp"

namespace target
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
#endif // BOOS_TARGET_OBJECT_HPP_

