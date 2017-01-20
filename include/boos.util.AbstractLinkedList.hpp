/** 
 * Abstract class for sequential accessing to data store.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_UTIL_ABSTRACT_LINKED_LIST_HPP_
#define BOOS_UTIL_ABSTRACT_LINKED_LIST_HPP_

#include "boos.util.Object.hpp"
#include "boos.util.Buffer.hpp"
#include "boos.util.LinkedNode.hpp"
#include "boos.api.List.hpp"
#include "boos.api.Queue.hpp"
#include "boos.api.Iterable.hpp"

namespace util
{  
  /** 
   * @param Type  data type of container element.
   * @param Alloc heap memory allocator class.
   */
  template <typename Type, class Alloc=Allocator>
  class AbstractLinkedList : 
    public ::util::Object<Alloc>, 
    public ::api::List<Type>, 
    public ::api::Queue<Type> , 
    public ::api::Iterable<Type>{

    typedef ::util::Object<Alloc>          Parent;
    typedef ::util::LinkedNode<Type,Alloc> Node;

  public:      

    /** 
     * Constructor.
     */    
    AbstractLinkedList() : Parent(),
      illegal_ (),
      last_    (NULL),
      count_   (0){
      this->setConstruct( construct() );
    }

    /**
     * Constructor.
     *
     * @param illegal illegal element.
     */
    AbstractLinkedList(const Type& illegal) : Parent(),
      illegal_ (illegal),
      last_    (NULL),
      count_   (0){
      this->setConstruct( construct() );
    }

    /**
     * Destructor.
     */
    virtual ~AbstractLinkedList()
    {
      clear();
    }
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const
    {
      return this->Parent::isConstructed();
    }
    
    /**
     * Inserts new element to the end of this list.
     *
     * Given element will be copied to self nodes structure by copy constructor calling.
     *
     * @param element inserting element.
     * @return true if element is added.
     */      
    virtual bool add(const Type& element)
    {
      return isConstructed() ? addNode(length(), element) : false;
    }

    /**
     * Inserts new element to the specified position in this list.
     *
     * Given element will be copied to self nodes structure by a copy constructor calling.
     *
     * @param index   position in this list.  
     * @param element inserting element.
     * @return true if element is inserted.
     */
    virtual bool add(int32 index, const Type& element)
    {
      return isConstructed() ? addNode(index, element) : false;
    }      

    /**
     * Removes all elements from this list.       
     */  
    virtual void clear()
    {
      if(!isConstructed()) return;
      int32 b = length()-1;
      for(int32 i=b; i>=0; i--) removeNode( getNodeByIndex(i) ); 
    }

    /**
     * Removes the first element from this list.
     *
     * @return true if an element is removed successfully.
     */
    virtual bool removeFirst()
    {
      return remove(0);
    }

    /**
     * Removes the last element from this list.
     *
     * @return true if an element is removed successfully.
     */
    virtual bool removeLast()
    {
      return remove( length()-1 );
    }

    /**
     * Removes the head element of this queue or list.
     *
     * @return true if an element is removed successfully.
     */
    virtual bool remove()
    {
      return remove(0);
    }

    /**
     * Removes the element at the specified position in this list.
     *
     * @param index   position in this list.
     * @return true if an element is removed successfully.
     */
    virtual bool remove(int32 index)
    {
      return isConstructed() ? removeNode( getNodeByIndex(index) ) : false;
    }

    /**
     * Removes the first occurrence of the specified element from this list.
     *
     * @param element reference to element.
     * @return true if an element is removed successfully.
     */
    virtual bool removeElement(const Type& element)
    {
      return isConstructed() ? removeNode( getNodeByElement(element) ) : false;
    }

    /**
     * Examines the head element of this queue (list).
     *
     * @return the head element.
     */
    virtual Type element() const
    {
      return get(0);
    }

    /**
     * Returns the first element in this list.
     *
     * @return the first element in this list.
     */
    virtual Type getFirst() const
    {
      return get(0);
    }

    /**
     * Returns the last element in this list.
     *
     * @return the last element in this list.
     */
    virtual Type getLast() const
    {
      return get( length()-1 );      
    }
    
    /**
     * Returns an element from this list by index.
     *
     * @param index position in this list.  
     * @return indexed element of this list.
     */
    virtual Type get(int32 index) const
    {
      if(!isConstructed()) return illegal_;
      Node* node = getNodeByIndex(index);
      return node != NULL ? node->element() : illegal_;
    }  

    /**
     * Returns a number of elements in this list.
     *
     * @return number of elements.
     */
    virtual int32 length() const
    {
      return last_ == NULL ? 0 : last_->index() + 1;
    }
    
    /**
     * Tests if this list has elements.
     *
     * @return true if this list does not contain any elements.
     */
    virtual bool isEmpty() const
    {
      return last_ == NULL ? true : false;    
    }

    /**
     * Returns illegal element which will be returned as error value.
     *
     * If illegal value is not set method returns uninitialized variable.
     *
     * @return illegal element.
     */
    virtual Type illegal() const
    {
      return illegal_;
    }

    /**
     * Sets illegal element which will be returned as error value.
     *
     * @param value illegal value.
     */
    virtual void illegal(const Type value)
    {
      if( isConstructed() ) illegal_ = value;
    }

    /**
     * Tests if given value is an illegal.
     *
     * @param value testing value.
     * @param true if value is an illegal.
     */
    virtual bool isIllegal(const Type& value) const
    {
      if(!isConstructed()) return false;
      return illegal_ == value ? true : false;
    }

    /**
     * Returns the index of the first occurrence of the specified element in this list.
     *
     * @param element reference to the element.
     * @return index or -1 if this list does not contain the element.
     */
    virtual int32 indexOf(const Type& element) const
    {
      Node* node = getNodeByElement(element);
      return node != NULL ? node->index() : -1;
    }

    /**
     * Tests if given index is available.
     *
     * @param index checking position in this list.
     * @return true if index is present.
     */  
    virtual bool isIndex(int32 index) const
    {
      return (0 <= index && index < length()) ? true : false;
    }      

    /**
     * Returns an array of all list links to elements.
     *
     * You have to call delete operator for returned value after it have used.
     *
     * @return pointer to reference of elements or NULL if list is empty.
     */  
    virtual ::util::Buffer<Type,0,Alloc>* toArray() const
    {
      if(!isConstructed()) return NULL;
      int32 count = length();
      if(count == 0) return NULL;
      Buffer<Type,0,Alloc>* buf = new Buffer<Type,0,Alloc>(count, illegal_);
      if(buf == NULL || !buf->isConstructed())
      {
        delete buf;
        return NULL;
      }
      Node* node = last_->next();
      for(int32 i=0; i<count; i++) 
      {
        (*buf)[i] = node->element();
        node = node->next();
      }
      return buf;
    }

    /**
     * Returns an iterator of this list elements.
     *
     * @return pointer to new itererator.
     */
    virtual ::api::Iterator<Type>* iterator()
    {
      return this->listIterator(0);
    }

  protected:

    /**
     * Inserts new element to the specified position in this list.
     *
     * Given element will be copied to self nodes structure by a copy constructor calling.
     *
     * @param index   position in this list.  
     * @param element inserting element.
     * @return true if element is inserted.
     */
    bool addNode(int32 index, const Type& element)
    {
      if(isIndexOutOfBounds(index)) return false;
      Node* node = new Node(element);
      if(node == NULL || !node->isConstructed())
      {
        delete node;
        return false;
      }
      if(last_ == NULL) 
      {
        last_ = node;
        count_++;
        return true;
      }
      if(index > 0)
      {
        Node* after = getNodeByIndex(index - 1);
        if(after == NULL)
        {
          delete node;
          return false;
        }
        after->after(node);
        if(after == last_) last_ = node;
      }
      else
      {
        Node* before = getNodeByIndex(0);
        if(before == NULL)
        {
          delete node;
          return false;
        }
        before->before(node);
      }
      count_++;
      return true;  
    }      

    /**
     * Returns a node of this list by index.
     *
     * @param index position in this list.  
     * @return pointer to the node of this list.
     */
    Node* getNodeByIndex(int32 index) const
    {
      if(!isIndex(index)) return NULL;
      if(index == length() - 1) return last_;
      Node* node = last_->next();
      for(int32 i=0; i<index; i++) node = node->next();
      return node;
    }

    /**
     * Returns a node of this list by element.
     *
     * @param element reference to element.  
     * @return pointer to the node of this list.
     */
    Node* getNodeByElement(const Type& element) const
    {
      int32 len = length();
      if(len == 0) return NULL;
      Node* node = last_->next();      
      for(int32 i=0; i<len; i++, node = node->next()) 
        if(element == node->element()) return node;
      return NULL;
    }

    /**
     * Removes a node of this list.
     *
     * @param node pointer to node.
     * @return true if a node is removed successfully.
     */
    bool removeNode(Node* node)
    {
      if(node == NULL) return false;
      if(node == last_) 
      {
        if(length() == 1) last_ = NULL;
        else last_ = last_->prev();
      }
      delete node;
      count_++;
      return true;   
    }

    /**
     * Tests if index is out of this list bounds.
     *
     * @param index checking position in this list.
     * @return true if index is outed.
     */  
    bool isIndexOutOfBounds(int32 index) const
    {
      return (index < 0 || index > length()) ? true : false;
    }

    /**
     * Returns reference to self data value.
     *
     * @return data value.
     */  
    int32& getReferenceToCount()
    {
      return count_;
    }

    /**
     * Returns reference to self data value.
     *
     * @return data value.
     */  
    Node*& getReferenceToLast()
    {
      return last_;
    } 

    /**
     * Returns reference to self data value.
     *
     * @return data value.
     */  
    Type& getReferenceToIllegal()
    {
      return illegal_;
    }

  private:
    
    /** 
     * Constructor.
     *
     * @return true if object has been constructed successfully.
     */
    bool construct()
    {
      return isConstructed();
    }

    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    AbstractLinkedList(const AbstractLinkedList& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     */
    AbstractLinkedList& operator =(const AbstractLinkedList& obj);

    /**
     * Illegal element of this list.
     */
    Type illegal_;
    
    /**
     * Last node of this list.
     */
    Node* last_;
    
    /**
     * Number of changes in this list.
     */
    int32 count_;

  };
}
#endif // BOOS_UTIL_ABSTRACT_LINKED_LIST_HPP_
