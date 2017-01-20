/** 
 * Root class of the system class hierarchy.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_OBJECT_HPP_
#define BOOS_OBJECT_HPP_

#include "boos.api.Object.hpp"

/** 
 * @param Alloc heap memory allocator class.
 */ 
template <class Alloc>
class Object : public ::api::Object
{
  
public:

  /** 
   * Constructor.
   */  
  Object() : 
    isConstructed_ (true){
  }
  
  /** 
   * Copy constructor.
   *
   * @param obj reference to source object.
   */ 
  Object(const Object& obj) :
    isConstructed_ (obj.isConstructed_){
  }
  
  /** 
   * Destructor.
   */    
  virtual ~Object()
  {
    isConstructed_ = false;
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
   * Assignment operator.
   *
   * @param obj reference to source object.
   */  
  Object& operator =(const Object& obj)
  {
    isConstructed_ = obj.isConstructed_;
    return *this;
  }

  /** 
   * Operator new.
   *
   * @param size number of bytes to allocate.
   * @return allocated memory address or a null pointer.
   */  
  void* operator new(size_t size)
  {
    return Alloc::alloc(size);
  }

  /** 
   * Operator new.
   *
   * @param size unused.
   * @param ptr  pointer to reserved memory area
   * @return given pointer.
   */  
  void* operator new(size_t size, void* ptr)
  {
    return ptr;
  }
  
  /**
   * Operator delete.
   *
   * @param ptr address of allocated memory block or a null pointer.
   */
  void operator delete(void* ptr)
  {
    Alloc::free(ptr);
  }

protected:

  /**
   * Sets the object constructed flag.
   *
   * @param flag constructed flag.
   */      
  virtual void setConstruct(bool flag)
  {
    if(isConstructed_ == true) isConstructed_ = flag;
  }
  
  /**
   * Gets the object constructed flag.
   *
   * @return reference to the constructed flag.
   */      
  virtual const bool& getConstruct()
  {
    return isConstructed_;
  }  

  /**
   * Allocates memory.
   *
   * NOTE: You need to use "this->template alloc<Type>(size);" 
   * syntax, if your class is a template and inherits this class.
   *
   * @param size number of bytes to allocate.
   * @return allocated memory address or a null pointer.
   */    
  template<typename Type>
  static Type alloc(size_t size)
  {
    return static_cast<Type>( Alloc::alloc(size) );
  }    
         
  /**
   * Frees an allocated memory.
   *
   * @param ptr address of allocated memory block or a null pointer.
   */      
  static void free(void* ptr)
  {
    Alloc::free(ptr);
  }

private:
  
  /** 
   * Operator delete.
   *
   * @param ptr   address of allocated memory block or a null pointer.
   * @param place pointer used as the placement parameter in the matching placement new.
   */  
  void operator delete(void* ptr, void* place);
  
  /** 
   * Operator new.
   *
   * @param size number of bytes to allocate.
   * @return allocated memory address or a null pointer.
   */  
  void* operator new[](size_t size);
  
  /** 
   * Operator delete.
   *
   * @param ptr address of allocated memory block or a null pointer.
   */  
  void operator delete[](void* ptr);

  /** 
   * Operator new.
   *
   * @param size number of bytes to allocate.
   * @param ptr  pointer to a memory area to initialize the object
   * @return allocated memory address or a null pointer.
   */  
  void* operator new[](size_t size, void* ptr);
  
  /** 
   * Operator delete.
   *
   * @param ptr   address of allocated memory block or a null pointer.
   * @param place pointer used as the placement parameter in the matching placement new.
   */  
  void operator delete[](void* ptr, void* place);
  
  /** 
   * Object constructed flag.
   */  
  bool isConstructed_;

};
#endif // BOOS_OBJECT_HPP_
