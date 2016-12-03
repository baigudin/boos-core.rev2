/**
 * Stack.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_UTIL_STACK_HPP_
#define BOOS_UTIL_STACK_HPP_

#include "boos.util.Object.hpp"
#include "boos.util.Buffer.hpp"
#include "boos.api.Stack.hpp"

namespace util
{
  /** 
   * @param Type  data type of default stack element.
   * @param Alloc heap memory allocator class.
   */ 
  template <typename Type, class Alloc=Allocator>
  class Stack : public Object<Alloc>, public ::api::Stack<Type>
  { 
    typedef Object<Alloc> Parent;  
  
  public:
  
    /**
     * Stack operations.
     *
     * Stack operations:
     * - Full stacks have stack pointers that point to the last used (full) location.
     * - Empty stacks have stack pointers that point to the first unused (empty) location.
     * - Descending stacks grow towards decreasing memory addresses (towards the bottom of memory).
     * - Ascending stacks grow towards increasing memory addresses (towards the top of memory).
     */
    enum Operation
    {
      /**
       * Full Descending.
       */
      FD = 0,
      
      /**
       * Empty Descending.
       */      
      ED = 1,
      
      /**
       * Full Ascending.
       */       
      FA = 2,
      
      /**
       * Empty Ascending.
       */       
      EA = 3

    };

    /** 
     * Constructor.
     *
     * @param type  type of this stack.
     * @param count count of buffer elements.
     */    
    Stack(Operation type, int32 count) :
      stack_ (count),
      type_  (type){
      this->setConstruct( construct() );
    }     
    
    /** 
     * Constructor.
     *
     * @param type  type of this stack.     
     * @param count   count of buffer elements.
     * @param illegal illegal value.
     */    
    Stack(Operation type, int32 count, const Type illegal) :
      stack_ (count, illegal),
      type_  (type){
      this->setConstruct( construct() );
    }    
    
    /** 
     * Destructor.
     */    
    virtual ~Stack()
    {
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
     * Returns an initial top of stack.
     *
     * @return pointer to TOS.
     */    
    virtual const Type* tos()
    {
      if(!isConstructed()) return NULL;
      Type* stack = &stack_[0];
      switch(type_)
      {
        case FD: return &stack[stack_.length()];
        case ED: return &stack[stack_.length() - 1];
        case FA: return &stack[0] - 1;
        case EA: return &stack[0];
        default: return NULL;  
      }
    }
    
    /**
     * Returns a number of elements.
     *
     * @return number of elements.
     */
    virtual int32 length() const
    {
      return stack_.length();
    }

    /**
     * Tests if this collection has elements.
     *
     * @return true if this collection does not contain any elements.
     */
    virtual bool isEmpty() const
    {
      return false;
    }

    /**
     * Returns illegal element which will be returned as error value.
     *
     * If illegal value is not set method returns uninitialized variable.
     *
     * @return reference to illegal element.
     */
    virtual Type illegal() const
    {
      return stack_.illegal();
    }

    /**
     * Sets illegal element which will be returned as error value.
     *
     * @param value illegal value.
     */
    virtual void illegal(const Type value)
    {
      return stack_.illegal(value);
    }

    /**
     * Tests if given value is an illegal.
     *
     * @param value testing value.
     * @param true if value is an illegal.
     */
    virtual bool isIllegal(const Type& value) const
    {
      return stack_.isIllegal(value);
    }
    
  private:

    /** 
     * Constructor.
     *
     * @return boolean result.
     */
    bool construct()
    {
      if(!isConstructed()) return false;
      if(!stack_.isConstructed()) return false;
      return true;
    }

    /**
     * Stack memory buffer.
     */
    Buffer<Type> stack_;

    /**
     * Stack type.
     */    
    Operation type_;

  };
}
#endif // BOOS_UTIL_STACK_HPP_
