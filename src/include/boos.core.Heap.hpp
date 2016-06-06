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

#include "boos.api.Object.hpp"
#include "boos.api.Heap.hpp"
#include "boos.api.Switchable.hpp"

namespace core
{
  class HeapBlock;

  class Heap : public api::Object, public api::Heap
  {
    
  public:

    /** 
     * Constructor.
     *
     * Reference to global interrupt interface pointer is used for
     * possibility to change a value of that pointer.
     * Until that pointer is NULL golobal interrupt is not used.
     * This gives you a possibility to change using golobal interrupts
     * on fly.
     *
     * @param size total heap size.
     * @param ires reference to pointer of global interrupt switchable interface.
     */    
    Heap(int64 size, api::Switchable*& ires);
    
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
     * Tests if this object is constructed.
     *
     * @return true if object is constructed successfully.
     */    
    virtual bool isConstructed() const;
    
    /**
     * Operator new.
     *
     * Method initiates a building of heap memory
     * checks and tests self memory structure data
     * and leads to call a class constructor.
     *
     * @param size unused.
     * @param ptr  aligned to eight memory address.
     * @return address of memory or NULL.
     */
    void* operator new(size_t, void* ptr);

    /**
     * Operator new.
     *
     * Method is defined for blocking operator new.
     *
     * @param size size in byte.
     * @return always NULL value.
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

  protected:
  
    /**
     * Sets the object construct flag.
     *
     * @param flag construct flag.
     */      
    virtual void setConstruct(bool flag);

  private:

    /**
     * Thread switch off key.
     *
     * This structure controls a global åhread switch off key
     * by switchable interface. That interface has to disable
     * a changing thread context. The most useful case is to give
     * a global interrupt switchable interface.
     */      
    struct Switcher
    {

    public:

      /** 
       * Constructor.
       */
      Switcher(api::Switchable*& sw) : 
        switch_ (&sw){
      }

      /** 
       * Destructor.
       */
     ~Switcher(){}

      /** 
       * Disables a controller.
       *
       * @return an enable source bit value of a controller before method was called.
       */ 
      bool disable()
      {
        return (*switch_) != NULL ? (*switch_)->disable() : false;
      }

      /** 
       * Enables a controller.
       *
       * @param status returned status by disable method.
       */    
      void enable(bool status)
      {
        if((*switch_) != NULL) (*switch_)->enable(status);
      }

    private: 
      
      api::Switchable**       switch_;

    };

                              Heap(const Heap&);       //Copy not allowed
    void                      operator =(const Heap&); //Assignment not allowed
    void                      operator delete(void*, void*);
    void*                     operator new[](size_t);
    void                      operator delete[](void*);
    void*                     operator new[](size_t, void*);
    void                      operator delete[](void*, void*);
    bool                      construct();
    HeapBlock*                firstBlock();
    HeapBlock*                heapBlock(void* data);
    static bool               isMemoryAvailable(void* addr, int64 size);

    static const int32        KEY_HEAP = 0x19811019;

    // Eight bytes of parent interface virtual table pointers
    // TI compiler puts at the start of class data.
    // Self class data adds class size to eight bytes align boundary.
    HeapBlock*                block_;
    Switcher                  switch_;
    int64                     size_;
    int32                     key_;
    int32                     temp_;

  };
}
#endif // BOOS_CORE_HEAP_HPP_
