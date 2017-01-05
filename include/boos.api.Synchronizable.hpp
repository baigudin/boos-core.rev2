/** 
 * Synchronizable interface for synchronizing one program in some processor units.
 * 
 * This interface provides a synchronization of one program 
 * which is being executed by several processor units. 
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_SYNCHRONIZABLE_HPP_
#define BOOS_CORE_SYNCHRONIZABLE_HPP_

#include "boos.api.Object.hpp"

namespace api
{
  class Synchronizable : public Object
  {

  public:
    
    /** 
     * Destructor.
     */
    virtual ~Synchronizable(){};
    
    /** 
     * Synchronizes an executing code section.
     *
     * The method waits while other processor units get this program pointer
     * and continues executing the program after this.
     */ 
    virtual void synchronize() = 0;
    
    /** 
     * Recasts given data to a gauge.
     *
     * The method compares given data with a gauge and recasts to it 
     * if the data does not equal to the gauge.
     *
     * @param ptr     address of data for synchronizing.
     * @param size    number of bytes for synchronizing.
     * @param channel number of processor core which data is the gauge of synchronization.
     * @return true if given data was recast to the gauge.
     */ 
    virtual bool recast(void* ptr, int32 size, int32 channel) = 0;
    
    /** 
     * Tests if given data equals the gauge.
     *
     * @param ptr     address of data for synchronizing.
     * @param size    number of bytes for synchronizing.
     * @param channel number of processor core which data is the gauge of synchronization.
     * @return true if given data equals to the gauge.
     */ 
    virtual bool isEqual(void* ptr, int32 size, int32 channel) = 0;    

  };
}
#endif // BOOS_CORE_SYNCHRONIZABLE_HPP_
