/** 
 * Memory for system heap.
 *
 * HeapBlock struct has to be align to 8.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2015 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
namespace core
{
  class HeapBlock    
  {

  public:

    /** 
     * Constructor.
     *
     * @param heap pointer to heap class.
     * @param size size of byte given to this new block.
     */    
    HeapBlock(Heap* heap, size_t size) :
      prev_  (NULL),
      next_  (NULL),
      heap_  (heap),
      attr_  (0),
      size_  (size - sizeof(HeapBlock)),
      key_   (KEY_BLOCK),
      temp_  (-1){
    }
    
    /** 
     * Destructor.
     */
    ~HeapBlock()
    {
    }

    /**
     * Operator new.
     *
     * @param size unused.
     * @param ptr  address of memory.
     * @return address of memory.
     */   
    void* operator new(uint32, void* ptr)
    {
      // Size of this class has to be multipled to eight
      if(sizeof(HeapBlock) & 0x7) return NULL;
      return ptr;
    }
   
    /**
     * Allocates a memory block.
     *
     * @param size size in byte.
     * @return pointer to an allocated memory.
     */  
    void* alloc(size_t size)
    {
      if(size == 0) return NULL;    
      // Align a size to 8 byte boudary
      if(size & 0x7) size = (size & ~0x7) + 0x8;
      HeapBlock* curr = this;
      while(curr)
      {
        if(curr->isUsed())
        {
          curr = curr->next_;
          continue;
        }
        if(curr->size_ < size)
        {
          curr = curr->next_;
          continue;
        }
        break;
      }
      if(curr == NULL) return NULL;
      // has a need size of memory and new heap block
      if(curr->size_ >= size + sizeof(HeapBlock))
      {
        HeapBlock* next = new ( curr->next(size) ) HeapBlock(heap_, curr->size_ - size);
        next->next_ = curr->next_;
        next->prev_ = curr;
        if(next->next_) next->next_->prev_ = next;        
        curr->next_ = next;        
        curr->size_ = size;
      }
      curr->attr_|= ATTR_USED;
      return curr->data();
    }

    /**
     * Frees an allocated memory by this block.
     *
     * @return true if this block is freed.
     */  
    bool free()
    {
      if(isDelete() == false) return false;
      int32 sibling = 0;
      if((prev_ != NULL) && (prev_->isUsed() == false)) sibling |= PREV_FREE;
      if((next_ != NULL) && (next_->isUsed() == false)) sibling |= NEXT_FREE;    
      switch(sibling)
      {
        case PREV_FREE|NEXT_FREE:
        {
          prev_->size_ += 2 * sizeof(HeapBlock) + size_ + next_->size_;
          prev_->next_ = next_->next_;
          if(prev_->next_ != NULL) prev_->next_->prev_ = prev_;
          #ifdef BOOS_DEBUG
          util::Memory::memset((void*)((uint32)prev_+sizeof(HeapBlock)), 0, prev_->size_);
          #endif
        }
        break;
        case PREV_FREE:
        {
          prev_->size_ += sizeof(HeapBlock) + size_;
          prev_->next_ = next_;
          if(next_ != NULL) next_->prev_ = prev_;
          #ifdef BOOS_DEBUG
          util::Memory::memset((void*)((uint32)prev_+sizeof(HeapBlock)), 0, prev_->size_);
          #endif      
        }
        break;
        case NEXT_FREE:
        {
          size_ += sizeof(HeapBlock) + next_->size_;
          next_ = next_->next_;
          if(next_ != NULL) next_->prev_ = this;
          attr_ &= ~ATTR_USED;
          #ifdef BOOS_DEBUG
          util::Memory::memset((void*)((uint32)this+sizeof(HeapBlock)), 0, size_);
          #endif
        }
        break;
        default:
        {
          attr_ &= ~ATTR_USED;
          #ifdef BOOS_DEBUG
          util::Memory::memset((void*)((uint32)this+sizeof(HeapBlock)), 0, size_);
          #endif      
        }
      }
      return true;
    }

  private:

    /**
     * Tests if this memory block is available for deleting.
     *
     * @return true if it may be deleted.
     */  
    bool isDelete()
    {
      if(!isMemory()) return false;
      if(!heap_->isConstructed()) return false;
      return true;
    }

    /**
     * Tests if this memory block is available.
     *
     * @return true if memory block is available.
     */  
    bool isMemory()
    {
      return key_ == KEY_BLOCK ? true : false;
    }

    /**
     * Tests if this memory block is available.
     *
     * @return true if memory block is available.
     */  
    bool isUsed()
    {
      return (attr_ & ATTR_USED) != 0 ? true : false;
    }
    
    /**
     * Returns an address to data of this block.
     *
     * @return pointer to memory.
     */
    void* data()
    {
      register uint32 addr = reinterpret_cast<uint32>(this) + sizeof(HeapBlock);
      return reinterpret_cast<void*>(addr);
    }

    /**
     * Returns an address to next block.
     *
     * @return pointer to memory.
     */
    void* next(size_t size)
    {
      register uint32 addr = reinterpret_cast<uint32>(this) + sizeof(HeapBlock) + size;
      return reinterpret_cast<void*>(addr);
    }

    static const int32        KEY_BLOCK = 0x19820401;
    static const int32        ATTR_USED = 0x00000001;
    static const int32        NEXT_FREE = 0x00000001;
    static const int32        PREV_FREE = 0x00000002;

    HeapBlock*                prev_;
    HeapBlock*                next_;
    Heap*                     heap_;
    int32                     attr_;
    int64                     size_;
    int32                     key_;
    int32                     temp_;

  };
}

