/** 
 * Core of system.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_CORE_HPP_
#define BOOS_CORE_CORE_HPP_

#include "boos.core.Object.hpp"
#include "boos.api.Toggle.hpp"

namespace core
{
  class Main;
  class CoreTimerInterrupt;

  class Core
  {
    friend class Main;

  public:

    /** 
     * Returns a current value of the running core.
     *
     * @return time in nanoseconds.
     */      
    static int64 nanoTime();

    /** 
     * Terminates the core.
     */      
    static void fail();

  private:

    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    static bool init();

    /**
     * Deinitialization.
     */
    static void deinit();

    /**
     * Hardware timer interrupt resource of core (no boot).
     */
    static CoreTimerInterrupt* interrupt_;
    
    /**
     * Global interrupt resource (no boot).
     */
    static ::api::Toggle* global_;

  };
}
#endif // BOOS_CORE_CORE_HPP_
