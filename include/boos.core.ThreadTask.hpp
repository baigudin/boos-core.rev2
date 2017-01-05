/**
 * Skeleton thread task class with default settings.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_THREAD_TASK_HPP_
#define BOOS_CORE_THREAD_TASK_HPP_

#include "boos.core.Object.hpp"
#include "boos.api.Task.hpp"

namespace core
{
  class ThreadTask : public ::core::Object<>, public ::api::Task  
  {
    typedef ::core::Object<> Parent;    
    
  public:
  
    /** 
     * Constructor.
     */    
    ThreadTask() : Parent(){}

    /** 
     * Destructor.
     */
    virtual ~ThreadTask(){}
    
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
     * Returns size of thread stack.
     *
     * The method returns size of thread stack in bytes which should be allocated for the task.
     *
     * @return stack size in bytes.
     */  
    virtual int32 stackSize() const
    {
      return 0x800;
    }
    
  private:    

    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    ThreadTask(const ThreadTask& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     */
    ThreadTask& operator =(const ThreadTask& obj);        

  };
}
#endif // BOOS_CORE_THREAD_TASK_HPP_
