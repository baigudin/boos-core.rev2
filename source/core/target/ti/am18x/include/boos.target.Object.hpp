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
    typedef ::Object<Alloc> Parent;  
    
  public:

    /** 
     * Constructor.
     */  
    Object() : Parent()
    {
    }     
    
    /** 
     * Copy constructor.
     *
     * @param obj reference to source object.
     */ 
    Object(const Object& obj) : Parent(obj)
    {
    }
    
    /** 
     * Destructor.
     */    
    virtual ~Object(){}     
    
    /** 
     * Assignment operator.
     *
     * @param obj reference to source object.
     */  
    Object& operator =(const Object& obj)
    {
      Parent::operator=(obj);
      return *this;
    }    

  };
}
#endif // BOOS_TARGET_OBJECT_HPP_

