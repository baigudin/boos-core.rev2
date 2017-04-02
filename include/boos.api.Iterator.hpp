/** 
 * Iterator interface. 
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_ITERATOR_HPP_
#define BOOS_API_ITERATOR_HPP_

#include "boos.Types.hpp"
#include "boos.api.IllegalValue.hpp"

namespace api
{
  /** 
   * @param Type data type of iterator element.
   */ 
  template <typename Type>
  class Iterator : public ::api::IllegalValue<Type>
  {
    
  public:
  
    /**
     * Destructor.
     */
    virtual ~Iterator(){}

    /**
     * Returns next element and advances the cursor position.
     *
     * @return reference to element.
     */      
    virtual Type next() = 0;

    /**
     * Tests if this iteration may return a next element.
     *
     * @return true if next element is had.
     */      
    virtual bool hasNext() const = 0;

    /**
     * Removes the last element returned by this iterator.
     *
     * @return true if an element is removed successfully.
     */
    virtual bool remove() = 0;

  };
}
#endif // BOOS_API_ITERATOR_HPP_
