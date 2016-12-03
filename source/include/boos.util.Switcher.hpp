/** 
 * Switcher of switchable interface.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_UTIL_SWITCHER_HPP_
#define BOOS_UTIL_SWITCHER_HPP_

#include "boos.util.Object.hpp"
#include "boos.api.Switchable.hpp"

namespace util
{
  /** 
   * @param Alloc heap memory allocator class.
   */  
  template <class Alloc=Allocator>
  class Switcher : public Object<Alloc>, public ::api::Switchable
  {
    typedef util::Object<Alloc> Parent;

  public:
  
    /** 
     * Constructor.
     */
    Switcher() :
      pSwitch_  (NULL),      
      ppSwitch_ (&pSwitch_){
    }

    /** 
     * Constructor.
     *
     * @param sw reference to Switchable interface for controlling its.
     */
    Switcher(::api::Switchable& sw) :
      pSwitch_  (&sw),      
      ppSwitch_ (&pSwitch_){
    }
    
    /** 
     * Constructor.
     *
     * Until the referenced pointer equals NULL the Switcher will not switch
     * given controller. This feature is the most important when a controller
     * might be used before it is initialized.
     *
     * @param sw reference to pointer of Switchable interface for controlling its.
     */
    Switcher(::api::Switchable*& sw) : 
      pSwitch_  (NULL),    
      ppSwitch_ (&sw){
    }

    /** 
     * Destructor.
     */
    virtual ~Switcher(){}
    
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
     * Disables a controller.
     *
     * @return an enable source bit value of a controller before method was called.
     */ 
    virtual bool disable()
    {
      return isConstructed() && *ppSwitch_ != NULL ? (*ppSwitch_)->disable() : false;
    }

    /** 
     * Enables a controller.
     *
     * @param status returned status by disable method.
     */    
    virtual void enable(bool status)
    {
      if(isConstructed() && *ppSwitch_ != NULL) (*ppSwitch_)->enable(status);
    }
    
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

  private:
  
    /**
     * Pointer to always existent interface.
     */
    ::api::Switchable* pSwitch_;  
    
    /**
     * Pointer to pointer to maybe existent interface.
     */
    ::api::Switchable** ppSwitch_;

  };
}
#endif // BOOS_UTIL_SWITCHER_HPP_
