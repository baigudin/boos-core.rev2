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
class Object : public api::Object
{
  
public:

  /** 
   * Constructor.
   */  
  Object() : 
    isConstructed_ (true){
  }
  
  /** 
   * Destructor.
   */    
  virtual ~Object()
  {
    isConstructed_ = false;
  }    
  
  /**
   * Tests if this object is constructed.
   *
   * @return true if object is constructed successfully.
   */    
  virtual bool isConstructed() const
  {
    return isConstructed_;
  }    
  
  /**
   * Tests if given object is constructed.
   *
   * @param obj pointer to object interface.
   * @return true if object is constructed successfully.
   */    
  static bool isConstructed(const api::Object* obj)
  {
    return obj != NULL ? obj->isConstructed() : false;
  }    

  /**
   * Operator new.
   *
   * @param size size in byte.
   * @return allocated memory address or 0, if error.
   */
  void* operator new(size_t size)
  {
    return Alloc::alloc(size);
  }

  /**
   * Operator new.
   *
   * @param size unused.
   * @param ptr  address of memory.
   * @return address of memory.
   */
  void* operator new(size_t, void* ptr)
  {
    return ptr;
  }
  
  /**
   * Operator delete.
   *
   * @param ptr address of allocated memory.
   */
  void operator delete(void* ptr)
  {
    Alloc::free(ptr);
  }

protected:

  /**
   * Sets the object construct flag.
   *
   * @param flag construct flag.
   */      
  virtual void setConstruct(bool flag)
  {
    if(isConstructed_ == true) isConstructed_ = flag;
  }

  /**
   * Allocates memory.
   *
   * NOTE: You need to use "this->template alloc<Type>(size);" 
   * syntax, if your class is a template and inherits this class.
   *
   * @param size required memory size in byte.
   * @return pointer to allocated memory or NULL.
   */    
  template<typename Type>
  static Type alloc(size_t size)
  {
    return reinterpret_cast<Type>( Alloc::alloc(size) );
  }    
         
  /**
   * Frees an allocated memory.
   *
   * @param ptr pointer to allocated memory.
   */      
  static void free(void* ptr)
  {
    Alloc::free(ptr);
  }

private:

                            Object(const Object&);
  void                      operator =(const Object&);
  void                      operator delete(void*, void*);
  void*                     operator new[](size_t);
  void                      operator delete[](void*);
  void*                     operator new[](size_t, void*);
  void                      operator delete[](void*, void*);
  
  bool                      isConstructed_;

};
#endif // BOOS_OBJECT_HPP_
