/** 
 * One program synchronization for executing in several processor units.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.core.Synchronizer.hpp"
 
namespace core
{
  /**
   * Constructor.
   */
  Synchronizer::Synchronizer() : Parent()
  {
    setConstruct( construct() );
  }  
  
  /**
   * Destructor.
   */
  Synchronizer::~Synchronizer()
  {
  }
  
  /**
   * Constructor.
   *
   * @return true if object has been constructed successfully.
   */
  bool Synchronizer::construct()
  {
    return true;
  }

  /**
   * Tests if this object has been constructed.
   *
   * @return true if object has been constructed successfully.
   */    
  bool Synchronizer::isConstructed() const
  {
    return this->Parent::isConstructed();
  }
  
  /** 
   * Synchronizes an executing code section.
   */ 
  void Synchronizer::synchronize()
  {
  }
  
  /** 
   * Recasts given data to a gauge.
   *
   * @param ptr     address of data for synchronizing.
   * @param size    number of bytes for synchronizing.
   * @param channel number of processor core which data is the gauge of synchronization.
   * @return true if given data was recast to the gauge.
   */ 
  bool Synchronizer::recast(void* ptr, int32 size, int32 channel)
  {
    return ptr == NULL || size == 0 || channel > 0 ? false : true;
  }
  
  /** 
   * Tests if given data equals the gauge.
   *
   * @param ptr     address of data for synchronizing.
   * @param size    number of bytes for synchronizing.
   * @param channel number of processor core which data is the gauge of synchronization.
   * @return true if given data equals to the gauge.
   */ 
  bool Synchronizer::isEqual(void* ptr, int32 size, int32 channel)
  {
    return ptr == NULL || size == 0 || channel > 0 ? false : true;
  }
  
  /**
   * Initialization.
   *
   * @return true if no errors.
   */
  bool Synchronizer::init()
  {
    return true;
  }    
  
  /**
   * Deinitialization.
   */
  void Synchronizer::deinit()
  {
  }
}

