/**
 * Core stack.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_STACK_HPP_
#define BOOS_CORE_STACK_HPP_

#include "boos.core.Object.hpp"
#include "boos.util.Buffer.hpp"

namespace core
{
  class Stack : public Object<> 
  { 
  
  public:

    /** 
     * Constructor.
     *
     * @param size size of stack in bytes has to be aligned to eight.
     */  
    Stack(size_t size) :
      stack_ (size >> 3, ILLEGAL_VALUE){
      setConstruct( construct(size) );
    }     
    
    /** 
     * Destructor.
     */    
    virtual ~Stack()
    {
    }

    /** 
     * Returns an initial top of stack.
     *
     * @return pointer to TOS.
     */    
    void* tos()
    {
      return isConstructed() ? &stack_[stack_.length()-1] : NULL;
    }
    
  private:

    /** 
     * Constructor.
     *
     * @param size size of stack in bytes has to be aligned to eight.
     * @return boolean result.
     */
    bool construct(size_t size)
    {
      if(!isConstructed()) return false;
      if(!stack_.isConstructed()) return false;
      if(size & 0x3) return false;
      #ifdef BOOS_DEBUG
      stack_.fill(ILLEGAL_VALUE);
      #endif
      return true;
    }

    static const int64        ILLEGAL_VALUE = -1;

    util::Buffer<int64>       stack_;
  };
}
#endif // BOOS_CORE_STACK_HPP_
