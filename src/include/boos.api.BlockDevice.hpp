/** 
 * Block device access interface.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2015 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_BLOCK_DEVICE_HPP_
#define BOOS_API_BLOCK_DEVICE_HPP_

#include "boos.Types.hpp"

namespace api
{
  class BlockDevice
  {

  public:
  
    /** 
     * Destructor.
     */
    virtual ~BlockDevice(){}

    /**
     * Reads sectors from a device.
     *
     * @param buf   pointer to buffer.
     * @param lba   start logical block address.
     * @param count count of logical blocks.
     * @return true if all data is readed.
     */
    virtual bool read(void* buf, int32 lba, int32 count) = 0;

    /**
     * Writes sectors to a device.
     *
     * @param buf   pointer to buffer.
     * @param lba   start logical block address.
     * @param count count of logical blocks.
     * @return true if all data is written.
     */
    virtual bool write(void* buf, int32 lba, int32 count) = 0;

    /**
     * Returns count of logical blocks.
     *
     * @return count of total blocks.
     */
    virtual int32 getSectorsCount() = 0;

    /**
     * Returns size of one logical block.
     *
     * @return size of block in byte.
     */
    virtual int32 getSectorSize() = 0;

    /**
     * Tests if a device is read-only.
     *
     * @return true if a device is read-only access.
     */
    virtual bool isReadOnly() = 0;

  };
}
#endif // BOOS_API_BLOCK_DEVICE_HPP_
