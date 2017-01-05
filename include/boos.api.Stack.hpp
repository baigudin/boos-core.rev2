/**
 * Stack interface.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_STACK_HPP_
#define BOOS_API_STACK_HPP_

#include "boos.api.Collection.hpp"

namespace api
{
  /** 
   * @param Type data type of default stack element.
   */ 
  template <typename Type>  
  class Stack : public Collection<Type>
  { 
  
  public:
  
    /** 
     * Destructor.
     */    
    virtual ~Stack(){}

    /** 
     * Returns an initial top of stack.
     *
     * @return a memory address to top of this stack when object was built.
     */    
    virtual const Type* tos() = 0;

  };
}
#endif // BOOS_API_STACK_HPP_
