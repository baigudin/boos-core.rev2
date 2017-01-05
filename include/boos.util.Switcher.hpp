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
   *
   * @param Alloc heap memory allocator class.
   */  
  template <class Alloc=Allocator>
  class Switcher : public ::util::Object<Alloc>, public ::api::Switchable
  {
    typedef ::util::Object<Alloc> Parent;

  public:
  
    /** 
     * Constructor.
     *
     * Default constructor is used for creating 
     * the object which will switch nothing.
     */
    Switcher() : Parent(),
      pointer_ (NULL),      
      switch_  (&pointer_){
    }  

    /** 
     * Constructor.
     *
     * @param sw reference to Switchable interface for controlling its.
     */
    Switcher(::api::Switchable& sw) : Parent(),
      pointer_ (&sw),      
      switch_  (&pointer_){
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
    Switcher(::api::Switchable*& sw) : Parent(),
      pointer_ (NULL),    
      switch_  (&sw){
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
      if(!this->Parent::isConstructed()) return false;
      return *switch_ == NULL ? false : true;
    }

    /** 
     * Disables a controller.
     *
     * @return an enable source bit value of a controller before method was called.
     */ 
    virtual bool disable()
    {
      if(!isConstructed()) return false;    
      ::api::Switchable* switcher = *switch_;
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
      ::api::Switchable* switcher = *switch_;
      switcher->enable(status);
    }

  private:

    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    Switcher(const Switcher& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     */
    Switcher& operator =(const Switcher& obj);
  
    /**
     * Pointer to always existent interface.
     */
    ::api::Switchable* pointer_;  
    
    /**
     * Pointer to pointer to maybe existent interface.
     */
    ::api::Switchable** switch_;

  };
}
#endif // BOOS_UTIL_SWITCHER_HPP_
