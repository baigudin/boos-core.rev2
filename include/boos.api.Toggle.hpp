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
  class Toggle : public Object
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
     * @param status returned status by disable method.
     */    
    virtual void enable(bool status) = 0;

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
