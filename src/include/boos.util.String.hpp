/** 
 * String class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_UTIL_STRING_HPP_
#define BOOS_UTIL_STRING_HPP_

#include "boos.core.Object.hpp"
#include "boos.util.Buffer.hpp"
#include "boos.util.Memory.hpp"

namespace util
{
  class String : public core::CoreObject, private Memory
  {
  
  public:      
  
    /** 
     * Constructor.
     */    
    String() :
      ptr_ (NULL){
    }
  
    /** 
     * Constructor.
     *
     * @param val integer value.
     */    
    String(int32 val) :
      ptr_ (NULL){
      char ptr[BUFLEN];
      itoa(val, ptr);
      setConstruct( construct(ptr) );
    }
  
    /** 
     * Constructor.
     *
     * @param ptr pointer to c-string.
     */    
    String(const char* ptr) :
      ptr_ (NULL){
      setConstruct( construct(ptr) );
    }
  
    /** 
     * Copy constructor.
     *
     * @param str reference to String object.
     */    
    String(const String& str) :
      ptr_ (NULL){
      setConstruct( construct(str) );
    }
  
    /**
     * Destructor.
     */
    virtual ~String()
    {
      if(ptr_ != NULL) free(ptr_);
    }
  
    /**
     * Gets string length.
     *
     * @return count of characters.
     */
    virtual int32 length()
    {
      return isConstructed() ? strlen(ptr_) : 0;
    }
  
    /**
     * Gets allocated memory size in bytes.
     *
     * @return bytes size.
     */
    virtual int32 size()
    {
      return isConstructed() ? strlen(ptr_) + 1 : 0;
    }
  
    /**
     * Gets pointer to C-string.
     *
     * @return pointer.
     */
    virtual const char* cString() const
    {
      return isConstructed() ? ptr_ : NULL;
    }

    /**
     * Assignment operator.
     *
     * @param str reference to String object.
     */
    void operator =(const String& str)
    {
      if(isConstructed()) copy(str.cString());
    }
  
    /**
     * Conversion operator to signed integer.
     */
    operator int32()
    {
      return atoi(ptr_);
    }
  
  private:
  
    /** 
     * Constructor.
     *
     * @param str reference to String object.
     * @return boolean result.
     */
    bool construct(const String& str)
    {
      return copy(str.cString());
    }
  
    /** 
     * Constructor.
     *
     * @param ptr pointer to c-string.
     * @return boolean result.
     */
    bool construct(const char* ptr)
    {
      return copy(ptr);
    }

    /** 
     * Sets a new ptr.
     *
     * @param ptr pointer to c-string.
     * @return boolean result.
     */
    bool copy(const char* ptr)
    {
      if(ptr_ != NULL) 
      {
        free(ptr_);
        ptr_ = NULL;
      }
      if(ptr == NULL) return false;
      ptr_ = alloc<char*>(strlen(ptr)+1);
      if(ptr_ == NULL) return false;
      strcpy(ptr_, ptr);
      return true;
    }
  
    /** 
     * Converts integer to string.
     */
    static int32 itoa(int32 val, char* buffer)
    {
      int8 tempc[BUFLEN];
      register int8 *bufptr;
      register int32 neg = val < 0;
      register int32 uval = neg ? -val : val;
      *( bufptr = &tempc[BUFLEN-1] ) = 0;
      do { *--bufptr = ( uval % 10 ) + '0'; } while( uval /= 10 );
      if (neg) *--bufptr = '-';
      memcpy( buffer, bufptr, uval = ( tempc + BUFLEN ) - bufptr );
      return uval - 1;
    }
  
    /** 
     * Converts string to integer.
     */
    static int32 atoi(const char* st)
    {
      int32 result = 0;
      char cp;
      int32 sign;
      while( isspace( (*st) ) ) ++st;
      if( sign = ( ( cp = (*st) ) == '-') ) cp = *++st;
      else if( cp == '+' ) cp = *++st;
      while( isdigit( cp ) )
      {
        result *= 10;
        result += cp - '0';
        cp = *++st;
      }
      if( sign ) result *= -1;
      return result;
    }
  
    /** 
     * Converts string to integer.
     */
    static int32 isspace( int c )
    {
      if( ( ( c >= 9 ) && ( c <= 13 ) ) || ( c == 32 ) ) return 1;
      return 0;
    }
  
    /** 
     * Converts string to integer.
     */
    static int32 isdigit( int c )
    {
      if( ( c >= 48 ) && ( c <= 57 ) ) return 1;
      return 0;
    }
  
    static const              int32 BUFLEN = 20;

    char*                     ptr_;
  
    friend bool   operator== (const String& str1, const String& str2);
    friend bool   operator!= (const String& str1, const String& str2);
    friend String operator+  (const String& str1, const String& str2);
  
  };
  
  /**
   * Operator ==.
   *
   * @param str reference to String 1 object.
   * @param str reference to String 2 object.
   * @return boolean result.
   */
  inline bool operator ==(const String& str1, const String& str2)
  {
    return String::strcmp(str1.ptr_, str2.ptr_) == 0 ? true : false; 
  }
  
  /**
   * Operator !=.
   *
   * @param str reference to String 1 object.
   * @param str reference to String 2 object.
   * @return boolean result.
   */
  inline bool operator !=(const String& str1, const String& str2)
  {
    return String::strcmp(str1.ptr_, str2.ptr_) != 0 ? true : false;
  }
  
  /**
   * Operator +.
   *
   * @param str reference to String 1 object.
   * @param str reference to String 2 object.
   * @return boolean result.
   */
  inline String operator +(const String& str1, const String& str2)
  {
    String str = String();
    return str;
  }

}
#endif // BOOS_UTIL_STRING_HPP_
