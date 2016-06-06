/**
 * Output stream interface.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_OUT_STREAM_HPP_
#define BOOS_API_OUT_STREAM_HPP_

#include "boos.Types.hpp"

namespace api
{
  class OutStream
  {
    
  public:

    /** 
     * Destructor.
     */
    virtual ~OutStream(){}
    
    /** 
     * Writes to an output stream given string.
     *
     * @param str pointer to out putting string.
     * @return reference to this object.
     */    
    virtual api::OutStream& operator <<(const char* str) = 0;
    
  };
}
#endif // BOOS_API_OUT_STREAM_HPP_
