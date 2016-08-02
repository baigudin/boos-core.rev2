/**
 * Files storage interface of file systems.
 *
 * A FileStore class represents a storage for partition, volume, 
 * concrete file system, etc. And provide access to the content
 * of a file in this store.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2015-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_FILE_STORE_HPP_
#define BOOS_API_FILE_STORE_HPP_

#include "boos.api.File.hpp"

namespace api
{  
  class FileStore
  {

  public:

    /**
     * Destructor.
     */
    virtual ~FileStore(){}

    /** 
     * Returns a file interface.
     *
     * @param path absolute file path for this store.
     * @return pointer to file interface.
     */
    virtual api::File* getFile(const char* path) = 0;

    /** 
     * Returns a size of this file store.
     *
     * @return a size of this file store in bytes.
     */
    virtual int64 getTotalSpace() const = 0;

    /** 
     * Tests if this store has read-only access.
     *
     * @return true if access is read-only.
     */
    virtual bool isReadOnly() const = 0;

    /** 
     * Returns this file store name.
     *
     * @return pointer to char string of file store name.
     */
    virtual const char* name() const = 0;

  };
}
#endif // BOOS_API_FILE_STORE_HPP_
