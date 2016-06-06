/**
 * Runnable interface for a thread executing.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2015 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_RUNNABLE_HPP_
#define BOOS_API_RUNNABLE_HPP_

#include "boos.Types.hpp"

namespace api
{
  class Runnable
  {
    
  public:

    /** 
     * Destructor.
     */
    virtual ~Runnable(){}
    
    /**
     * Default run method.
     */  
    virtual void run() = 0;

  };
}
#endif // BOOS_API_RUNNABLE_HPP_
