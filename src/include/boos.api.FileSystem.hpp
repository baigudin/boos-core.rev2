/**
 * File System interface.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2015-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_FILE_SYSTEM_HPP_
#define BOOS_API_FILE_SYSTEM_HPP_

#include "boos.api.FileStore.hpp"

namespace api
{  
  class FileSystem
  {

  public:

    /**
     * Destructor.
     */
    virtual ~FileSystem(){}

    /** 
     * Returns a file stores number of this file system.
     *
     * @return number of file stores.
     */
    virtual int32 getFileStoreCount() = 0;

    /** 
     * Returns a file store interface by given index.
     *
     * @param index file store index.
     * @return pointer to file store interface.
     */
    virtual api::FileStore* getFileStore(int32 index) = 0;
    
  };
}
#endif // BOOS_API_FILE_SYSTEM_H_
