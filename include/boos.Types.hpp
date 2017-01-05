/** 
 * System types.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TYPES_HPP_
#define BOOS_TYPES_HPP_

#ifdef NULL
#undef NULL
#endif

#if __cplusplus >= 201103L  // Since C++11
  #define BOOS_CPP11
#elif __cplusplus           // Until C++11
  #define BOOS_CPP
#endif

#if defined(BOOS_CPP11)
  typedef decltype(nullptr)  nullptr_t;
  const nullptr_t NULL = nullptr;
#elif defined(BOOS_CPP)
  const int NULL = 0;
#else
  #error "The source file must be compiled by C++ compiler"
#endif

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long long  uint64;
typedef signed char         int8;
typedef signed short        int16;
typedef signed int          int32;
typedef signed long long    int64;
typedef float               float32;
typedef double              float64;
typedef unsigned int        size_t;
  
#endif // BOOS_TYPES_HPP_
