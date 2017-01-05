/**
 * Task interface.
 * 
 * The interface of a task that is being executed in self context.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_TASK_HPP_
#define BOOS_API_TASK_HPP_

#include "boos.api.Object.hpp"

namespace api
{
  class Task : public Object
  {
    
  public:

    /** 
     * Destructor.
     */
    virtual ~Task(){}
    
    /**
     * The method with self context.
     */  
    virtual void main() = 0;
    
    /**
     * Returns size of stack.
     *
     * The method returns size of stack in bytes which should be allocated for the task.
     *
     * @return stack size in bytes.
     */  
    virtual int32 stackSize() const = 0;

  };
}
#endif // BOOS_API_TASK_HPP_
