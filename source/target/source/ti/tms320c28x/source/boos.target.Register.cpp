/** 
 * Target processor registers factory.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.target.Register.hpp"
#include "boos.target.RegisterController.hpp"

namespace target
{
  /**
   * Returns the register interface of a target processor.
   *
   * @return target processor register interface, or NULL if error has been occurred.
   */
  ::target::Register* Register::create()
  {
    return NULL;
  }
  
  /** 
   * Access to protected memory mapped CPU registers.
   *
   * @return the interface, or NULL if CPU family does not have protected registers, or error has been occurred.
   */    
  ::api::Toggle* Register::access()
  {
    RegisterController* controller = new RegisterController();
    if(controller != NULL && controller->isConstructed()) return controller;
    delete controller;
    return NULL;
  }  
}
