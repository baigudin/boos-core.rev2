/** 
 * Toggle of toggle interface.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_UTIL_TOGGLE_HPP_
#define BOOS_UTIL_TOGGLE_HPP_

#include "boos.util.Object.hpp"
#include "boos.api.Toggle.hpp"

namespace util
{
  /** 
   *
   * @param Alloc heap memory allocator class.
   */  
  template <class Alloc=Allocator>
  class Toggle : public ::util::Object<Alloc>, public ::api::Toggle
  {
    typedef ::util::Object<Alloc> Parent;

  public:
  
    /** 
     * Constructor.
     *
     * Default constructor is used for creating 
     * the object which will switch nothing.
     */
    Toggle() : Parent(),
      pointer_ (NULL),      
      toggle_  (&pointer_){
    }  

    /** 
     * Constructor.
     *
     * @param sw reference to toggle interface for controlling its.
     */
    Toggle(::api::Toggle& sw) : Parent(),
      pointer_ (&sw),      
      toggle_  (&pointer_){
    }
    
    /** 
     * Constructor.
     *
     * Until the referenced pointer equals NULL the Toggle will not switch
     * given controller. This feature is the most important when a controller
     * might be used before it is initialized.
     *
     * @param sw reference to pointer of toggle interface for controlling its.
     */
    Toggle(::api::Toggle*& sw) : Parent(),
      pointer_ (NULL),    
      toggle_  (&sw){
    }

    /** 
     * Destructor.
     */
    virtual ~Toggle(){}
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const
    {
      if(!this->Parent::isConstructed()) return false;
      return *toggle_ == NULL ? false : true;
    }

    /** 
     * Disables a controller.
     *
     * @return an enable source bit value of a controller before method was called.
     */ 
    virtual bool disable()
    {
      if(!isConstructed()) return false;    
      ::api::Toggle* switcher = *toggle_;
      return switcher->disable();      
    }

    /** 
     * Enables a controller.
     *
     * @param status returned status by disable method.
     */    
    virtual void enable(bool status)
    {
      if(!isConstructed()) return;
      ::api::Toggle* switcher = *toggle_;
      switcher->enable(status);
    }

  private:

    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    Toggle(const Toggle& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     */
    Toggle& operator =(const Toggle& obj);
  
    /**
     * Pointer to always existent interface.
     */
    ::api::Toggle* pointer_;  
    
    /**
     * Pointer to pointer to maybe existent interface.
     */
    ::api::Toggle** toggle_;

  };
}
#endif // BOOS_UTIL_TOGGLE_HPP_
