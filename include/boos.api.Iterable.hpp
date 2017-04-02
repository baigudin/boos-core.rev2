/** 
 * Iterable interface. 
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_ITERABLE_HPP_
#define BOOS_API_ITERABLE_HPP_

#include "boos.api.Object.hpp"
#include "boos.api.Iterator.hpp"

namespace api
{
  /** 
   * @param Type data type of element.
   */ 
  template <typename Type>
  class Iterable : public ::api::Object
  {
    
  public:
  
    /**
     * Destructor.
     */
    virtual ~Iterable(){}

    /**
     * Returns an iterator of elements.
     *
     * You have to call delete operator for returned iterator after it is used.
     *
     * @return pointer to new iterator.
     */
    virtual ::api::Iterator<Type>* iterator() = 0;

  };
}
#endif // BOOS_API_ITERABLE_HPP_
