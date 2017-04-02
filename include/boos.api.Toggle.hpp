/** 
 * Toggle interface of some controllers.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_TOGGLE_HPP_
#define BOOS_API_TOGGLE_HPP_

#include "boos.api.Object.hpp"

namespace api
{
  class Toggle : public ::api::Object
  {

  public:
    
    /** 
     * Destructor.
     */                               
    virtual ~Toggle(){}
    
    /** 
     * Disables a controller.
     *
     * @return an enable source bit value of a controller before method was called.
     */ 
    virtual bool disable() = 0;
    
    /** 
     * Enables a controller.
     *
     * The true passed argument directly turns a controller on, 
     * and the false does nothing, a controller stays in the current state.
     * 
     * @param status returned status by disable method, or true for directly turning a controller on.
     */    
    virtual void enable(bool status=true) = 0;

    /** 
     * Enables a controller.
     *
     * @param status returned status by disable method.
     * @param ret    value which will be returned.
     * @return given value.
     */
    template<typename Type>
    Type enable(bool status, Type ret)
    {
      enable(status);
      return ret;
    }

  };
}
#endif // BOOS_API_TOGGLE_HPP_
