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
#include "boos.core.Configuration.hpp"
#include "boos.util.Switcher.hpp"

namespace core
{
  class CoreTimerInterrupt;

  class Core : public Object<>
  {
    typedef Object<> Parent;

  public:

    /** 
     * Returns a current value of the running core.
     *
     * @return time in nanoseconds.
     */      
    static int64 nanoTime();

    /**
     * Returns a core configuration structure.
     *
     * @return configuration structure.
     */    
    static const Configuration& configuration();

    /** 
     * Terminates the core.
     */      
    static void fail();

    /**
     * Returns a Switchable interface for global interrupt.
     *
     * @return switchable global interrupt interface.
     */    
    static ::api::Switchable*& global();

  private:

    /**
     * Starts the core.
     *
     * @param config core configuration.
     */    
    static void start(const Configuration* config);

    /**
     * Starts to execute the core.
     */
    static void start();

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
     * Configuration of core which is pointed to core.config.asm structure (no boot).
     */
    static const Configuration* config_;

    /**
     * Hardware timer interrupt resource of core (no boot).
     */
    static CoreTimerInterrupt* interrupt_;

    /**
     * Switchable interface of global interrupt (no boot).
     */
    static ::api::Switchable* global_;

  };
}
#endif // BOOS_CORE_CORE_HPP_
