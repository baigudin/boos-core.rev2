/** 
 * Alignment of simple types to byte boundary of memory.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_UTIL_ALIGN_HPP_
#define BOOS_UTIL_ALIGN_HPP_

#include "boos.Types.hpp"
#include "boos.util.Allocator.hpp"

namespace util
{
  /** 
   * @param Type   type of aligning data.
   * @param SIZEOF size of aligning data.
   * @param Alloc  heap memory allocator class.
   */  
  template <typename Type, int32 SIZEOF=sizeof(Type), class Alloc=Allocator>
  class Align
  {
    
  public:
    
    /** 
     * Constructor.
     */     
    Align()
    {
    }

    /** 
     * Constructor.
     *
     * @param val data value.     
     */
    Align(register Type val)
    {
      assignment(val);
    }
    
    /**
     * Copy constructor.
     *
     * @param obj reference to source object.    
     */
    Align(register const Align& obj)
    {
      copy(obj);
    }
    
    /**
     * Destructor.
     */    
   ~Align()
    {
    }
    
    /**
     * Assignment operator.
     *
     * @param val source data value.
     */
    void operator =(register Type val)
    {
      assignment(val);
    }
    
    /**
     * Assignment operator.
     *
     * @param obj reference to source object. 
     */    
    void operator =(register const Align& obj)
    {
      copy(obj);
    }
    
    /**
     * Conversion operator to type of aligning data.
     */
    operator Type() const 
    {
      return typecast();
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
  
  private:
  
    /**
     * Assigns given value to self data.
     *
     * @param val source data value.
     */ 
    inline void assignment(register Type val)
    {
      for(register int32 i=0; i<SIZE; i++) 
      { 
        val_[i] = val & 0xff; 
        val >>= 8; 
      } 
    }
  
    /**
     * Copies given object to self data.
     *
     * @param obj reference to source object.    
     */  
    inline void copy(register const Align& obj)
    {
      for(register int32 i=0; i<SIZE; i++) 
      {
        val_[i] = obj.val_[i];
      }
    }
  
    /**
     * Returns conversed data to type of aligning data.
     *
     * @return conversed data.     
     */  
    inline Type typecast() const
    {
      register Type r = 0;
      for(register int32 i=SIZE-1; i>=0; i--) 
      { 
        r <<= 8; 
        r |= (Type)val_[i] & 0xff; 
      } 
      return r; 
    }
    
    static const int32        SIZE = SIZEOF;
    uint8                     val_[SIZE];
  };
  
  /**
   * Comparison operator to equal.
   *
   * @param obj1 reference to object.
   * @param obj2 reference to object.
   * @return true if objects are equal.
   */
  template <typename Type> 
  inline bool operator ==(const Align<Type>& obj1, const Align<Type>& obj2)
  {
    Type t1 = obj1;
    Type t2 = obj2;
    return t1 == t2;
  }

  /**
   * Comparison operator to unequal.
   *
   * @param obj1 reference to object.
   * @param obj2 reference to object.
   * @return true if objects are not equal.
   */  
  template <typename Type> 
  inline bool operator !=(const Align<Type>& obj1, const Align<Type>& obj2)
  {
    Type t1 = obj1;
    Type t2 = obj2;
    return t1 != t2;
  }
} 
#endif // BOOS_UTIL_ALIGN_HPP_
