/**
 * File interface of file systems.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2015-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_FILE_HPP_
#define BOOS_API_FILE_HPP_

#include "boos.Types.hpp"

namespace api
{  
  class File
  {

  public:

    /**
     * File access attributes.
     */
    enum Access
    {
      READ  = 0x01,
      WRITE = 0x02
    };

    /**
     * Destructor.
     */
    virtual ~File(){}

    /** 
     * Opens this stream.
     *
     * @param attr stream access.
     * @return true if stream is opened.
     */
    virtual bool open(int32 attr) = 0;

    /** 
     * Closes this stream.
     *
     * @return true if stream is closed.
     */
    virtual bool close() = 0;

    /** 
     * Reads data from this file.
     *
     * @param buf  pointer to a buffer.
     * @param size number of bytes.
     * @return number of read bytes.
     */
    virtual int64 read(void* buf, int64 size) = 0;

    /** 
     * Writes data to this file.
     *
     * @param buf  pointer to a buffer.
     * @param size number of bytes.
     * @return number of written bytes.
     */
    virtual int64 write(const void* buf, int64 size) = 0;

    /** 
     * Sets offset in this file stream.
     *
     * @param offset byte position in this file stream.
     * @return true if offset is set.
     */
    virtual bool seek(int64 offset) = 0;

    /** 
     * Gets this file stream offset.
     *
     * @return offset byte position of this file stream.
     */
    virtual int64 tell() = 0;

    /** 
     * Tests the end of this file stream.
     *
     * @return true if file stream is arrived to end.
     */
    virtual bool eof() = 0;

  };
}
#endif // BOOS_API_FILE_HPP_
