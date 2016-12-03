/** 
 * System heap memory.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.util.Memory.hpp"
#include "boos.core.Heap.hpp"
#include "boos.core.HeapBlock.hpp"

namespace core
{
  /** 
   * Constructor.
   *
   * @param size total heap size.
   * @param sw   reference to pointer of global interrupt interface.
   */    
  Heap::Heap(int64 size, ::api::Switchable*& sw) :
    data_ (size, sw, KEY_HEAP){
    setConstruct( construct() );
  }
  
  /** 
   * Destructor.
   */
  Heap::~Heap()
  {
    data_.key_ = 0;
  }
  
  /**
   * Operator new.
   *
   * @param size unused.
   * @param ptr  aligned to eight memory address.
   * @return address of memory.
   */
  void* Heap::operator new(size_t, void* ptr)
  {
    // Size of this class has to be multipled to eight
    if(sizeof(Heap) & 0x7) return NULL;
    // Testing memory for self structure data
    if(!isMemoryAvailable(ptr, sizeof(Heap))) return NULL;
    // Memory address has to be aligned to eight   
    return reinterpret_cast<uint32>(ptr) & 0x7 ? NULL : ptr;
  }
  
  /**
   * Allocates memory.
   *
   * @param size required memory size in byte.
   * @param ptr  NULL value becomes to allocate memory, and 
   *             other given values are simply returned 
   *             as memory address.
   * @return pointer to allocated memory or NULL.
   */    
  void* Heap::alloc(size_t size, void* addr)
  {
    if(!isConstructed()) return NULL;
    if(addr != NULL) return addr;
    bool is = data_.switch_.disable();
    addr = firstBlock()->alloc(size);
    return data_.switch_.enable(is, addr);
  }
    
  /**
   * Frees an allocated memory.
   *
   * @param addr pointer to allocated memory.
   */      
  void Heap::free(void* addr)
  {
    if(addr == NULL) return;
    if(!isConstructed()) return;  
    bool is = data_.switch_.disable();
    heapBlock(addr)->free();
    data_.switch_.enable(is);
  }
  
  /**
   * Tests if this object has been constructed.
   *
   * @return true if object has been constructed successfully.
   */    
  bool Heap::isConstructed() const
  {
    return data_.key_ == KEY_HEAP ? true : false;
  }
  
  /**
   * Sets the object constructed flag.
   *
   * @param flag constructed flag.
   */      
  void Heap::setConstruct(bool flag)
  {
    if(data_.key_ == KEY_HEAP) data_.key_ = flag ? KEY_HEAP : 0;
  }
  
  /** 
   * Constructor.
   *
   * @return true if object has been constructed successfully.
   */
  bool Heap::construct()
  {
    // Crop a size to multiple of eight
    if(sizeof(HeapBlock) + 16 > data_.size_) return false;
    // Test Heap and HeapBlock structures sizes witch has to be multipled to eight
    if(sizeof(Heap) & 0x7) return false;
    if(sizeof(HeapBlock) & 0x7) return false;
    // Test memory
    uint32 addr = reinterpret_cast<uint32>(this) + sizeof(Heap);
    void*  ptr  = reinterpret_cast<void*>(addr);
    if( !isMemoryAvailable(ptr, data_.size_) ) return false;
    // Alloc first heap block
    data_.block_ = new ( firstBlock() ) HeapBlock(this, data_.size_);
    return data_.block_ != NULL ? true : false;
  }
  
  /**
   * Returns a first heap block address.
   *
   * @return pointer to heap block.
   */
  HeapBlock* Heap::firstBlock()
  {
    register uint32 addr = reinterpret_cast<uint32>(this) + sizeof(Heap);
    return reinterpret_cast<HeapBlock*>(addr);
  }
  
  /**
   * Returns a heap block by user data address.
   *
   * @return pointer to heap block.
   */
  HeapBlock* Heap::heapBlock(void* data)
  {
    register uint32 addr = reinterpret_cast<uint32>(data) - sizeof(HeapBlock);
    return reinterpret_cast<HeapBlock*>(addr);
  }
  
  /**
   * Tests memory.
   *
   * @param addr memory address pointer.
   * @param size size in byte.
   * @return true if test complete.
   */
  bool Heap::isMemoryAvailable(void* addr, int64 size)
  {
    int64  i;
    uint8* ptr;
    
    for( ptr=(uint8*)addr, i=0; i<size; i++, ptr++ ) 
      (*ptr) = i;
    for( ptr=(uint8*)addr, i=0; i<size; i++, ptr++ ) 
      if( (*ptr) != (uint8)( i & 0x000000ff ) ) 
        return false;
        
    util::Memory::memset(addr, 0x55, size);
    ptr = (uint8*)addr;
    for( uint32 i=0; i<size; i++, ptr++ ) 
      if( (*ptr) != 0x55 ) 
        return false;    
        
    util::Memory::memset(addr, 0xaa, size);
    ptr = (uint8*)addr;
    for( uint32 i=0; i<size; i++, ptr++ ) 
      if( (*ptr) != 0xaa )     
        return false;    
        
    util::Memory::memset(addr, 0, size);
    return true;
  }       

  /**
   * Operator new.
   *
   * Method is defined for blocking operator new.
   *
   * @param size number of bytes to allocate..
   * @return always null pointer.
   */  
  void* Heap::operator new(size_t size)
  {
    return NULL;
  }
  
  /**
   * Operator delete.
   *
   * @param ptr address of allocated memory.
   */  
  void Heap::operator delete(void* ptr)
  {
  }  
}

