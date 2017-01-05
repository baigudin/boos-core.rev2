/**
 * Base structure for memory mapped registers description.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_REGISTERS_MAPPED_HPP_
#define BOOS_TARGET_REGISTERS_MAPPED_HPP_

#include "boos.Types.hpp"

namespace target
{
  namespace registers
  {  
    struct Mapped
    { 
    
    public:
  
      /** 
       * Constructor.
       */  
      Mapped(){}
      
      /** 
       * Destructor.
       */    
     ~Mapped(){}
     
      /**
       * Operator new.
       *
       * @param size unused.
       * @param ptr  address of memory.
       * @return address of memory.
       */     
      void* operator new(uint32, uint32 ptr)
      {
        return reinterpret_cast<void*>(ptr);
      }     
  
    };
  }
}
#endif // BOOS_TARGET_REGISTERS_MAPPED_HPP_
