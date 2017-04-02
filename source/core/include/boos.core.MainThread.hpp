/**
 * Main thread.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_MAIN_THREAD_HPP_
#define BOOS_CORE_MAIN_THREAD_HPP_

#include "boos.Main.hpp"
#include "boos.core.Thread.hpp"
 
namespace core
{
  class MainThread : public ::core::Thread
  {
    typedef ::core::Thread Parent;
    
  public:

    /** 
     * Constructor.
     */
    MainThread() : Parent(),
      error_ (-1){
    }

    /** 
     * Destructor.
     */
    virtual ~MainThread()
    {
    }
    
    /**
     * The method with self context.
     */  
    virtual void main()
    {
      error_ = ::Main::main();
    }
    
    /**
     * Returns execution error.
     */  
    virtual int32 error()
    {
      return error_;
    }    
    
  private:
    
    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    MainThread(const MainThread& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     * @return reference to this object.     
     */
    MainThread& operator =(const MainThread& obj);      
    
    /**
     * Execution error.
     */
    int32 error_;
    
  };
}
#endif // BOOS_CORE_MAIN_THREAD_HPP_
