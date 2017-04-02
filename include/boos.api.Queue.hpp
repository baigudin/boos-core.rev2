/** 
 * Queue interface.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_QUEUE_HPP_
#define BOOS_API_QUEUE_HPP_

#include "boos.api.Collection.hpp"

namespace api
{
  /** 
   * @param Type data type of queue element.
   */
  template <typename Type>
  class Queue : public ::api::Collection<Type>
  {
    
  public:
  
    /**
     * Destructor.
     */
    virtual ~Queue(){}

    /**
     * Inserts new element to this container.
     *
     * Given element will be copied to self items structure by copy constructor calling.
     *
     * @param element inserting element.
     * @return true if element is added.
     */      
    virtual bool add(const Type& element) = 0;

    /**
     * Removes the head element of this container.
     *
     * @return true if an element is removed successfully.
     */
    virtual bool remove() = 0;

    /**
     * Examines the head element of this container.
     *
     * @return the head element.
     */
    virtual Type element() const = 0;
    
  };
}
#endif // BOOS_API_QUEUE_HPP_
