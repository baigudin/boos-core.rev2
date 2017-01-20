/** 
 * Target processor registers factory.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_REGISTER_HPP_
#define BOOS_TARGET_REGISTER_HPP_

#include "boos.api.Object.hpp"
#include "boos.api.Stack.hpp"

namespace target
{
  class Register : public ::api::Object
  {
    
  public:
  
    /** 
     * Destructor.
     */    
    virtual ~Register(){}
  
    /** 
     * Initializes the registers.
     *
     * Usually, this method is used for normally restoring 
     * from some interrupt service routines. 
     *
     * @param stack a stack.
     * @param entry router entry point.
     * @param arg1  first router argument.
     * @param arg2  second router argument.     
     */  
    virtual void initialize(::api::Stack<int64>& stack, int32 entry, int32 arg1, int32 arg2) = 0;
  
    /** 
     * Returns a pointer to the first register of registers.
     *
     * @return memory address of registers order, or NULL if error has been occurred.
     */    
    virtual void* registers() = 0;
  
    /**
     * Returns the register interface of a target processor.
     *
     * @return target processor register interface, or NULL if error has been occurred.
     */
    static ::target::Register* create();
    
  };
}
#endif // BOOS_TARGET_REGISTER_HPP_
