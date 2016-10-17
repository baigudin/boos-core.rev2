/** 
 * System class of core.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_SYSTEM_HPP_
#define BOOS_CORE_SYSTEM_HPP_

#include "boos.core.Object.hpp"

namespace core
{
  class System : public Object<>
  {
    
  public:
  
    /** 
     * Constructor.
     */    
    System();

    /** 
     * Destructor.
     */      
    virtual ~System();
    
    /** 
     * Returns a current value of the running system in milliseconds.
     *
     * @return time in milliseconds.
     */
    static int64 currentTimeMillis();

    /** 
     * Returns a current value of the running system.
     *
     * @return time in nanoseconds.
     */      
    static int64 nanoTime();      

    /** 
     * Terminates the running system.
     *
     * @param status exit status.
     */      
    static void exit(int32 status);    

  };
}
#endif // BOOS_CORE_SYSTEM_HPP_
