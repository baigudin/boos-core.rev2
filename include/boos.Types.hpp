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

// NULL definition
#if __cplusplus >= 201103L  // Since C++11
  typedef decltype(nullptr)  nullptr_t;
  const nullptr_t NULL = nullptr;
#elif __cplusplus           // Until C++11
  const int NULL = 0;
#else
  #error "The source file must be compiled by C++ compiler"
#endif

// LP32 or 2/4/4 (int is 16-bit, long and pointer are 32-bit)
#ifdef BOOS_TYPE_WIDTH_LP32
typedef signed   int        int16;
typedef unsigned int        uint16;
typedef signed   long       int32;
typedef unsigned long       uint32;
typedef signed   long long  int64;
typedef unsigned long long  uint64;
typedef float               float32;
typedef double              float64;

// ILP32 or 4/4/4 (int, long, and pointer are 32-bit)
#elif BOOS_TYPE_WIDTH_ILP32
typedef signed   short      int16;
typedef unsigned short      uint16;
typedef signed   int        int32;
typedef unsigned int        uint32;
typedef signed   long long  int64;
typedef unsigned long long  uint64;
typedef float               float32;
typedef double              float64;

// LLP64 or 4/4/8 (int and long are 32-bit, pointer is 64-bit)
#elif BOOS_TYPE_WIDTH_LLP64
typedef signed   short      int16;
typedef unsigned short      uint16;
typedef signed   int        int32;
typedef unsigned int        uint32;
typedef signed   long long  int64;
typedef unsigned long long  uint64;
typedef float               float32;
typedef double              float64;

// LP64 or 4/8/8 (int is 32-bit, long and pointer are 64-bit)
#elif BOOS_TYPE_WIDTH_LP64
typedef signed   short      int16;
typedef unsigned short      uint16;
typedef signed   int        int32;
typedef unsigned int        uint32;
typedef signed   long       int64;
typedef unsigned long       uint64;
typedef float               float32;
typedef double              float64;

// C++ standard
#else
typedef signed   short      int16;
typedef unsigned short      uint16;
typedef signed   int        int32;
typedef unsigned int        uint32;
typedef signed   long long  int64;
typedef unsigned long long  uint64;
typedef float               float32;
typedef double              float64;
#endif 

// The type returned by sizeof
typedef uint32              size_t;
// Minimal addressable memory cell
typedef char                cell;
typedef unsigned char       ucell;
// Byte types of byte addressing cores
typedef signed char         int8;
typedef unsigned char       uint8;

#endif // BOOS_TYPES_HPP_
