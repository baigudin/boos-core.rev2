/** 
 * Illegal value interface.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_ILLEGAL_VALUE_HPP_
#define BOOS_API_ILLEGAL_VALUE_HPP_

#include "boos.Types.hpp"

namespace api
{
  /** 
   * @param Type data type of illegal value.
   */ 
  template <typename Type>
  class IllegalValue
  {
    
  public:
  
    /**
     * Destructor.
     */
    virtual ~IllegalValue(){}

    /**
     * Returns illegal element which will be returned as error value.
     *
     * @return illegal element.
     */
    virtual Type illegal() const = 0;

    /**
     * Sets illegal element which will be returned as error value.
     *
     * @param value illegal value.
     */
    virtual void illegal(const Type value) = 0;

    /**
     * Tests if given value is an illegal.
     *
     * @param value testing value.
     * @param true if value is an illegal.
     */
    virtual bool isIllegal(const Type& value) const = 0;

  };
}
#endif // BOOS_API_ILLEGAL_VALUE_HPP_
