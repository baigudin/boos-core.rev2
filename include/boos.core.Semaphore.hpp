/**
 * Semaphore class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_SEMAPHORE_HPP_
#define BOOS_CORE_SEMAPHORE_HPP_

#include "boos.core.Thread.hpp"
#include "boos.api.Semaphore.hpp"
#include "boos.util.LinkedList.hpp"

namespace core
{
  class Semaphore : public ::core::Object<>, public ::api::Semaphore
  {
    typedef ::core::Object<> Parent;
   
  public:

    /** 
     * Constructor.
     *
     * @param permits the initial number of permits available.   
     */      
    Semaphore(int32 permits);
    
    /** 
     * Constructor.
     *
     * @param permits the initial number of permits available.      
     * @param fair true if this semaphore will guarantee FIFO granting of permits under contention.
     */      
    Semaphore(int32 permits, bool fair);
                            
    /** 
     * Destructor.
     */
    virtual ~Semaphore();
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const;

    /**
     * Acquires a permit, blocking until one is available.
     *
     * @return true if the semaphore is acquire successfully.
     */  
    virtual bool acquire();

    /**
     * Acquires the given number of permits.
     *
     * @param permits the number of permits to acquire.
     * @return true if the semaphore is acquire successfully.
     */  
    virtual bool acquire(int32 permits);

    /**
     * Releases a permit.
     *
     * @return true if the semaphore is release successfully.
     */
    virtual bool release();

    /**
     * Releases the given number of permits.
     *
     * @param permits the number of permits to release.
     * @return true if the semaphore is release successfully.
     */  
    virtual bool release(int32 permits);

    /**
     * Tests if this semaphore is fair.
     *
     * @return true if this semaphore has fairness set true.
     */  
    virtual bool isFair() const;

    /** 
     * Tests if this resource is blocked.
     *
     * @return true if this resource is blocked.
     */ 
    virtual bool isBlocked();

  private:
  
    /** 
     * Node for semaphore lists.
     */  
    class Node
    {

    public:
    
      /** 
       * Constructor.
       *
       * @param permits number of permits to release.
       * @param thread  current executing thread.
       * @return true if the semaphore is release successfully.
       */
      Node(Thread& thread, int32 permits) : 
        thread_  (&thread),
        permits_ (permits){
      }

      /** 
       * Copy constructor.
       *
       * @param obj reference to source node.       
       */    
      Node(const Node& obj) :
        thread_  (obj.thread_), 
        permits_ (obj.permits_){
      }
      
      /** 
       * Constructor.
       *
       * Constructs this object as illegal.
       *
       * @param permits number of permits to release.
       * @return true if the semaphore is release successfully.
       */
      Node(int32 permits) : 
        thread_  (NULL),
        permits_ (permits){
      }      

      /**
       * Destructor.
       */
     ~Node(){}

      /** 
       * Assignment operator.
       *
       * @param node reference to source node.
       */  
      Node& operator =(const Node& node)
      {
        thread_ = node.thread_;
        permits_ = node.permits_;
        return *this;
      }

      /**
       * Returns this permits.
       *
       * @return this permits value.
       */
      int32 permits()
      {
        return permits_;
      }

      /**
       * Returns this thread.
       *
       * @return this thread value.
       */
      Thread* thread()
      {
        return thread_;
      }

    private:

      /** 
       * Executing thread.
       */
      Thread* thread_;
      
      /** 
       * Number of permits to release for this thread.
       */
      int32 permits_;

      friend bool operator ==(const Node& node1, const Node& node2);
      friend bool operator !=(const Node& node1, const Node& node2);

    };

    /** 
     * Contain lists for the semaphore.
     */  
    class List : public ::api::Object
    {

    public:

      /** 
       * Constructor.
       */
      List() : 
        illegal_ (-1),
        exec_    (illegal_), 
        lock_    (illegal_){
      }

      /**
       * Destructor.
       */
     ~List(){}
     
      /**
       * Returns this list of executing threads for fair semaphores.
       */
      ::api::Queue<Node>& exec()
      {
        return exec_;
      }

      /**
       * Returns this list of locked threads.
       */
      ::api::Queue<Node>& lock()
      {
        return lock_;      
      }
      
      /**
       * Tests if this object has been constructed.
       *
       * @return true if object has been constructed successfully.
       */    
      virtual bool isConstructed() const
      {
        if(!exec_.isConstructed()) return false;
        if(!lock_.isConstructed()) return false;        
        return true;
      }       
     
    private:
    
      /**
       * Illegal value for all this lists.
       */
      Node illegal_;    

      /**
       * List of executing threads for fair semaphores.
       */      
      util::LinkedList<Node> exec_;
      
      /**
       * List of locked threads.
       */      
      util::LinkedList<Node> lock_;

    };

    /**
     * Constructor.
     *
     * @return true if object has been constructed successfully.     
     */    
    bool construct();
    
    /**
     * Removes last element from list.
     *
     * @param list reference to SemaphoreList class.
     * @param node reference to node.     
     */    
    bool removeNode(::api::Queue<Node>& list, Node& node);
    
    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    Semaphore(const Semaphore& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     */
    Semaphore& operator =(const Semaphore& obj);     

    /**
     * Switchable interface of global interrupts.
     */
    ::api::Switchable& switch_;
    
    /**
     * Number of permits for acquiring this semaphore.
     */
    int32 permits_;
    
    /**
     * Semaphore fair flag.
     */    
    bool isFair_;

    /** 
     * Lists of this semaphore.
     */     
    List list_;

    friend bool operator ==(const Node& node1, const Node& node2);
    friend bool operator !=(const Node& node1, const Node& node2);

  };

  /**
   * Operator "==" for node of list.
   *
   * @param node1 reference to object 1.
   * @param node2 reference to object 2.
   * @return boolean result.
   */
  inline bool operator ==(const Semaphore::Node& node1, const Semaphore::Node& node2)
  {
    return node1.thread_ == node2.thread_ ? true : false;
  }

  /**
   * Operator "!=" for node of list.
   *
   * @param node1 reference to object 1.
   * @param node2 reference to object 2.
   * @return boolean result.
   */
  inline bool operator !=(const Semaphore::Node& node1, const Semaphore::Node& node2)
  {
    return node1.thread_ != node2.thread_ ? true : false;
  }
}
#endif //BOOS_CORE_SEMAPHORE_HPP_
