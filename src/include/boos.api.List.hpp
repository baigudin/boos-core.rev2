/** 
 * List interface.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_LIST_HPP_
#define BOOS_API_LIST_HPP_

#include "boos.api.ListIterator.hpp"
#include "boos.api.IllegalValue.hpp"

namespace api
{
  /** 
   * @param Type data type of list element.
   */ 
  template <typename Type>
  class List : public IllegalValue<Type>
  {
    
  public:
  
    /**
     * Destructor.
     */
    virtual ~List(){}

    /**
     * Inserts new element to the end of this list.
     *
     * Given element will be copied to self items structure by copy constructor calling.
     *
     * @param element inserting element.
     * @return true if element is added.
     */      
    virtual bool add(const Type& element) = 0;

    /**
     * Inserts new element to the specified position in this list.
     *
     * Given element will be copied to self items structure by a copy constructor calling.
     *
     * @param index   position in this list.  
     * @param element inserting element.
     * @return true if element is inserted.
     */
    virtual bool add(int32 index, const Type& element) = 0;

    /**
     * Removes all elements from this list.
     */  
    virtual void clear() = 0;

    /**
     * Removes the element at the specified position in this list.
     *
     * @param index   position in this list.
     * @return true if an element is removed successfully.
     */
    virtual bool remove(int32 index) = 0;

    /**
     * Removes the first element from this list.
     *
     * @return true if an element is removed successfully.
     */
    virtual bool removeFirst() = 0;

    /**
     * Removes the last element from this list.
     *
     * @return true if an element is removed successfully.
     */
    virtual bool removeLast() = 0;
    
    /**
     * Removes the first occurrence of the specified element from this list.
     *
     * @param element reference to element.
     * @return true if an element is removed successfully.
     */
    virtual bool removeElement(const Type& element) = 0;

    /**
     * Returns an element from this list by index.
     *
     * @param index position in this list.  
     * @return indexed element of this list.
     */
    virtual Type get(int32 index) const = 0;

    /**
     * Returns the first element in this list.
     *
     * @return the first element in this list.
     */
    virtual Type getFirst() const = 0;

    /**
     * Returns the last element in this list.
     *
     * @return the last element in this list.
     */
    virtual Type getLast() const = 0;

    /**
     * Returns a number of elements in this list.
     *
     * @return number of elements.
     */
    virtual int32 length() const = 0;

    /**
     * Returns an iterator of this list elements.
     *
     * You have to call delete operator for returned iterator after it is used.
     *
     * @return pointer to new itererator.
     */
    virtual api::Iterator<Type>* iterator() = 0;

    /**
     * Returns a list iterator of this list elements.
     *
     * You have to call delete operator for returned iterator after it is used.
     * Given index must not be out of bounds (index < 0 || index > length()).
     *
     * @param index start position in this list.  
     * @return pointer to new list itererator.
     */
    virtual api::ListIterator<Type>* listIterator(int32 index) = 0;

    /**
     * Returns the index of the first occurrence of the specified element in this list.
     *
     * @param element reference to the element.
     * @return index or -1 if this list does not contain the element.
     */
    virtual int32 indexOf(const Type& element) const = 0;

    /**
     * Tests if given index is available.
     *
     * @param index checking position in this list.
     * @return true if index is present.
     */  
    virtual bool isIndex(int32 index) const = 0;

  };
}
#endif // BOOS_API_LIST_HPP_
