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
#include "boos.util.Switcher.hpp"

namespace core
{
  class CoreTimerInterrupt;

  class Core
  {

  public:
  
    /**
     * Starts the core.
     *
     * @param heap a target core heap interface.
     */   
    static void start(::api::Heap& heap);

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
     * Executes the core.
     */
    static void execute();

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

  };
}
#endif // BOOS_CORE_CORE_HPP_
