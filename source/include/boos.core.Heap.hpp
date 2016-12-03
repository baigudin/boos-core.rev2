/** 
 * System heap memory.
 *
 * Hardware address for system heap memory has to be aligned to eight.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_HEAP_HPP_
#define BOOS_CORE_HEAP_HPP_

#include "boos.api.Heap.hpp"
#include "boos.util.Switcher.hpp"

namespace core
{
  class HeapBlock;

  class Heap : public ::api::Heap
  {
    
  public:
  
    /** 
     * Constructor.
     *
     * Reference to global interrupt interface pointer is used for
     * possibility to change a value of that pointer.
     * Until that pointer is NULL global interrupt is not used.
     * This gives you a possibility to change using global interrupts
     * on fly.     
     *
     * @param size total heap size.
     * @param sw   reference to global interrupt switchable interface.
     */    
    Heap(int64 size, ::api::Switchable*& sw);
    
    /** 
     * Destructor.
     */
    virtual ~Heap();

    /**
     * Allocates memory.
     *
     * @param size required memory size in byte.
     * @param ptr  NULL value becomes to allocate memory, and 
     *             other given values are simply returned 
     *             as memory address.
     * @return pointer to allocated memory or NULL.
     */    
    virtual void* alloc(size_t size, void* ptr);
      
    /**
     * Frees an allocated memory.
     *
     * @param ptr pointer to allocated memory.
     */      
    virtual void free(void* ptr);

    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const;
    
    /**
     * Operator new.
     *
     * Method initiates a building of heap memory
     * checks and tests self memory structure data
     * and leads to call the class constructor.
     *
     * @param size unused.
     * @param ptr  aligned to eight memory address.
     * @return address of memory or NULL.
     */
    void* operator new(size_t, void* ptr);

  private:
  
    /**
     * Sets the object constructed flag.
     *
     * @param flag constructed flag.
     */      
    void setConstruct(bool flag);
    
    /** 
     * Copy constructor.
     *
     * @param src reference to source object.
     */ 
    Heap(const Heap&);
    
    /**
     * Assignment operator.
     *
     * @param src reference to source object.
     */    
    void operator =(const Heap&);
    
    /**
     * Operator new.
     *
     * Method is defined for blocking operator new.
     *
     * @param size number of bytes to allocate.
     * @return always null pointer.
     */
    void* operator new(size_t size); 
    
    /**
     * Operator delete.
     *
     * Method does nothing and is defined for blocking operator delete.
     *
     * @param ptr address of allocated memory.
     */  
    void operator delete(void* ptr);
    
    /** 
     * Operator delete.
     *
     * @param ptr   address of allocated memory block or a null pointer.
     * @param place pointer used as the placement parameter in the matching placement new.
     */  
    void operator delete(void* ptr, void* place);
    
    /** 
     * Operator new.
     *
     * @param size number of bytes to allocate.
     * @return allocated memory address or a null pointer.
     */  
    void* operator new[](size_t size);
    
    /** 
     * Operator delete.
     *
     * @param ptr address of allocated memory block or a null pointer.
     */  
    void operator delete[](void* ptr);

    /** 
     * Operator new.
     *
     * @param size number of bytes to allocate.
     * @param ptr  pointer to a memory area to initialize the object
     * @return allocated memory address or a null pointer.
     */  
    void* operator new[](size_t size, void* ptr);
    
    /** 
     * Operator delete.
     *
     * @param ptr   address of allocated memory block or a null pointer.
     * @param place pointer used as the placement parameter in the matching placement new.
     */  
    void operator delete[](void* ptr, void* place);
    
    /** 
     * Constructor.
     *
     * @return true if object has been constructed successfully.
     */
    bool construct();
    
    /**
     * Returns a first heap block address.
     *
     * @return pointer to heap block.
     */
    HeapBlock* firstBlock();
    
    /**
     * Returns a heap block by user data address.
     *
     * @return pointer to heap block.
     */
    HeapBlock* heapBlock(void* data);
    
    /**
     * Tests memory.
     *
     * @param addr memory address pointer.
     * @param size size in byte.
     * @return true if test complete.
     */
    static bool isMemoryAvailable(void* addr, int64 size);
    
    /**
     * Heap class aligner aligns that to eight.
     *
     * Note: if given SIZEOF is already multiple 8, 
     * the class size will be 8 bytes.
     *
     * @param SIZEOF size of Heap class.
     */  
    template <int32 SIZEOF>
    struct Aligner
    {
    
    public:
    
      /** 
       * Constructor.
       */
      Aligner()
      {
        #ifdef BS_DEBUG
        for(int32 i=0; i<SIZE; i++) val_[i] = 0xAA;
        #endif
      }
      
      /** 
       * Destructor.
       */
     ~Aligner(){}       
    
    private:
      
      /**
       * Aligning data size.
       */
      static const int32 SIZE = (SIZEOF & ~0x7) + 0x8 - SIZEOF;
      
      /**
       * Temp array.
       */      
      uint8 val_[SIZE];

    };
    
    /**
     * Contains a Virtual Function Table only.
     *
     * Probably, decision for using this empty class 
     * is not delicate, but it is working for understanding 
     * about size of Heap class Virtual Function Table.
     *
     * Note: int64 was used because some compilers can put 64 bit variable 
     * to aligned 8 memory address. Therefore, size of classes 
     * with 32 bit pointer to virtual table and one 64 bit variable is 16 bytes.
     */    
    class VirtualTable : public ::api::Heap{int64 temp;};

    /**
     * Heap data.
     *
     * This structure is need for aligning heap data or otherwise 
     * this Heap class can not de aligned because it is incompleted.
     */
    struct HeapData
    {
    
    public:
    
      /** 
       * Constructor.
       *
       * @param size total heap size.
       * @param sw   reference to global interrupt interface.       
       */
      HeapData(int64 size, ::api::Switchable*& sw, int32 key) :
        block_  (NULL),  
        switch_ (sw),
        size_   ((size & ~0x7) - sizeof(Heap)),
        key_    (key){
      }
      
      /** 
       * Destructor.
       */
     ~HeapData(){}       
        
      /**
       * First memory block of heap page memory.
       */
      HeapBlock* block_;
      
      /**
       * Threads switchinf off key.
       *
       * This class controls a global thread switch off key
       * by switchable interface. That interface has to disable
       * a changing thread context. The most useful case is to give
       * a global interrupt switchable interface.       
       */    
      util::Switcher<> switch_;
      
      /**
       * Actual size of heap.
       */        
      int64 size_;
      
      /**
       * Heap page memory definition key.
       */        
      int32 key_;

    };
    
    /**
     * Heap page memory definition key.
     */
    static const int32 KEY_HEAP = 0x19811019;
    
    /**
     * Size of this Heap class without aligned data.
     */    
    static const int32 SIZEOF_HEAP = sizeof(HeapData) + sizeof(VirtualTable) - sizeof(int64);
    
    /**
     * Data of this heap.
     */    
    HeapData data_;
    
    /**
     * Aligning data.
     */        
    Aligner<SIZEOF_HEAP> temp_;

  };
}
#endif // BOOS_CORE_HEAP_HPP_
