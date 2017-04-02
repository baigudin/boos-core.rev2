/** 
 * The root interface of some collections.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_COLLECTION_HPP_
#define BOOS_API_COLLECTION_HPP_

#include "boos.api.IllegalValue.hpp"

namespace api
{
  /** 
   * @param Type data type of collection element.
   */ 
  template <typename Type>
  class Collection : public ::api::IllegalValue<Type>
  {
    
  public:
  
    /**
     * Destructor.
     */
    virtual ~Collection(){}

    /**
     * Returns a number of elements in this container.
     *
     * @return number of elements.
     */
    virtual int32 length() const = 0;

    /**
     * Tests if this collection has elements.
     *
     * @return true if this collection does not contain any elements.
     */
    virtual bool isEmpty() const = 0;

  };
}
#endif // BOOS_API_COLLECTION_HPP_
