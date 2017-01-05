/** 
 * Synchronization of one executing program of processor units.
 * 
 * This class provides a synchronization of one program 
 * which is being executed by several processor units.  
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_SYNCHRONIZER_HPP_
#define BOOS_CORE_SYNCHRONIZER_HPP_

#include "boos.core.Object.hpp"
#include "boos.api.Synchronizable.hpp"

namespace core
{
  class Core;
  
  class Synchronizer : public ::core::Object<>, public ::api::Synchronizable
  {
    friend class Core;
    typedef ::core::Object<> Parent;

  public:
    
    /** 
     * Constructor.
     */    
    Synchronizer();
    
    /** 
     * Destructor.
     */
    virtual ~Synchronizer();
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const;
    
    /** 
     * Synchronizes an executing code section.
     */ 
    virtual void synchronize();
    
    /** 
     * Recasts given data to a gauge.
     *
     * @param ptr     address of data for synchronizing.
     * @param size    number of bytes for synchronizing.
     * @param channel number of processor core which data is the gauge of synchronization.
     * @return true if given data was recast to the gauge.
     */ 
    virtual bool recast(void* ptr, int32 size, int32 channel);
    
    /** 
     * Tests if given data equals the gauge.
     *
     * @param ptr     address of data for synchronizing.
     * @param size    number of bytes for synchronizing.
     * @param channel number of processor core which data is the gauge of synchronization.
     * @return true if given data equals to the gauge.
     */ 
    virtual bool isEqual(void* ptr, int32 size, int32 channel);  

  private:
    
    /**
     * Constructor.
     *
     * @return true if object has been constructed successfully.     
     */    
    bool construct();
    
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
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    Synchronizer(const Synchronizer& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     */
    Synchronizer& operator =(const Synchronizer& obj);         

  };
}
#endif // BOOS_CORE_SYNCHRONIZER_HPP_
