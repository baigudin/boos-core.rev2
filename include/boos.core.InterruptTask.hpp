/**
 * Skeleton interrupt task class with default settings.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_INTERRUPT_TASK_HPP_
#define BOOS_CORE_INTERRUPT_TASK_HPP_

#include "boos.core.Object.hpp"
#include "boos.api.Task.hpp"

namespace core
{
  class InterruptTask : public ::core::Object<>, public ::api::Task
  {
    typedef ::core::Object<> Parent;  
    
  public:
  
    /** 
     * Constructor.
     */    
    InterruptTask() : Parent(){}

    /** 
     * Destructor.
     */
    virtual ~InterruptTask(){}
    
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
     * Returns size of interrupt stack.
     *
     * The method returns size of interrupt stack in bytes which should be allocated for the task.
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
    InterruptTask(const InterruptTask& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     */
    InterruptTask& operator =(const InterruptTask& obj);    

  };
}
#endif // BOOS_CORE_INTERRUPT_TASK_HPP_
