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
#include "boos.core.CoreConfig.hpp"
#include "boos.api.Switchable.hpp"

namespace core
{
  class CoreTimerInterrupt;

  class Core : private Object<>
  {

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
     * @return pointer to configuration structure.
     */    
    static const CoreConfig& config();

    /** 
     * Terminates the core.
     */      
    static void fail();

    /**
     * Returns a Switchable interface for global interrupt.
     *
     * @return switchable global interrupt interface.
     */    
    static api::Switchable*& global();

  private:

    static void                   start(const CoreConfig* config);
    static void                   start();
    static bool                   init();
    static void                   deinit();
    static void                   initClassesLow(); //Describe in ASM file

    /** 
     * Initializer of class.
     *
     * @param Type initializing object.
     */  
    template <typename Type>
    class Initializer : public api::Object
    {
      
    public:

      /** 
       * Constructor.
       */
      Initializer() :
        isConstructed_ (true){
        setConstruct( Type::init() );
      }

      /** 
       * Destructor.
       */
      virtual ~Initializer()
      {
        Type::deinit();
      }

      /**
       * Tests if this object is constructed.
       *
       * @return true if object is constructed successfully.
       */    
      virtual bool isConstructed() const
      {
        return isConstructed_;
      }

    private:

      /**
       * Sets the object construct flag.
       *
       * @param flag construct flag.
       */      
      void setConstruct(bool flag)
      {
        if(isConstructed_ == true) isConstructed_ = flag;
      }

      bool                       isConstructed_;

    };

    static const CoreConfig*     config_;
    static CoreTimerInterrupt*   interrupt_;
    static api::Switchable*      globalInterrupt_;

  };
}
#endif // BOOS_CORE_CORE_HPP_
