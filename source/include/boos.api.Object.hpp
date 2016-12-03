/**
 * Root interface of the system class hierarchy.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2015-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software.com
 */
#ifndef BOOS_API_OBJECT_HPP_
#define BOOS_API_OBJECT_HPP_

#include "boos.Types.hpp"

namespace api
{  
  class Object
  {

  public:

    /** 
     * Destructor.
     */
    virtual ~Object(){}

    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const = 0;
    
    /**
     * Tests if given object has been constructed object.
     *
     * @param obj pointer to object.
     * @return true if object has been constructed successfully.
     */
    template<class Type>
    static inline bool isObject(const Type* obj)
    {
      return obj != NULL ? obj->Type::isConstructed() : false;    
    }

  };
}
#endif // BOOS_API_OBJECT_HPP_
