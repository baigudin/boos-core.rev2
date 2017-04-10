/** 
 * TI TMS320F28x3x DSC controller of protected registers.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_REGISTER_CONTROLLER_HPP_
#define BOOS_TARGET_REGISTER_CONTROLLER_HPP_

#include "boos.target.Core.hpp"
#include "boos.target.Object.hpp"
#include "boos.api.Toggle.hpp"

namespace target
{
  class RegisterController : public ::target::Object<>, public ::api::Toggle
  {
    typedef ::target::Object<> Parent;  
  
  public:
  
    /** 
     * Constructor.
     */    
    RegisterController() : Parent(),
      isConstructed_ (getConstruct()){
    }

    /** 
     * Destructor.
     */
    virtual ~RegisterController()
    {
    }
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const
    {
      return isConstructed_;
    }
    
    /** 
     * Disables access to protected registers.
     *
     * @return regularly true, of false if error has been occurred.
     */ 
    virtual bool disable()
    {
      if(!isConstructed_) return false;    
      Core::registerProtected();
      return true;
    }
    
    /** 
     * Enables access to protected registers.
     *
     * @param status returned status by disable method, or true for directly turning a controller on.
     */    
    virtual void enable(bool status)
    {
      if(!isConstructed_ || status == false) return;
      Core::registerPublic();
    }
    
  private:
    
    /** 
     * Reference the root object constructed flag.
     */  
    const bool& isConstructed_;  
  
  };
}
#endif // BOOS_TARGET_REGISTER_CONTROLLER_HPP_
