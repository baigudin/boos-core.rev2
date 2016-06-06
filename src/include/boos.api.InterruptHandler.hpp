/**
 * Interrupt handler interface.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2015-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_INTERRUPT_HANDLER_HPP_
#define BOOS_API_INTERRUPT_HANDLER_HPP_

#include "boos.Types.hpp"

namespace api
{
  class InterruptHandler
  {

  public:

    /** 
     * Destructor.
     */
    virtual ~InterruptHandler(){}

    /** 
     * Hardware interrupt handler.
     */      
    virtual void handler() = 0;

  };
}
#endif // BOOS_API_INTERRUPT_HANDLER_HPP_
