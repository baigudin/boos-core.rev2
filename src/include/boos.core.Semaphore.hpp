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
  class Semaphore : public Object<>, public api::Semaphore
  {
   
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
     * Semaphore list node.
     */  
    class Node
    {

    public:

      /** 
       * Constructor.
       */
      Node() : 
        thread_  (NULL), 
        permits_ (0){
      }

      /** 
       * Constructor.
       */
      Node(Thread* thread, int32 count) : 
        thread_  (thread), 
        permits_ (count){
      }

      /** 
       * Copy constructor.
       */    
      Node(const Node& node) :
        thread_  (node.thread_), 
        permits_ (node.permits_){
      }

      /**
       * Destructor.
       */
     ~Node(){}

      /**
       * Operator =.
       */
      void operator =(const Node& node)
      {
        thread_ = node.thread_;
        permits_ = node.permits_;
      }

      /**
       * Returns this permits.
       */
      int32 permits()
      {
        return permits_;
      }

      /**
       * Returns this thread.
       */
      Thread* thread()
      {
        return thread_;
      }

    private:

      Thread*                 thread_;
      int32                   permits_;

      friend bool operator ==(const Node& node1, const Node& node2);
      friend bool operator !=(const Node& node1, const Node& node2);
    };

    /** 
     * Contain lists for the semaphore.
     */  
    class List
    {

    public:

      /** 
       * Constructor.
       */
      List() : 
        illegal_ (NULL, -1),
        exec     (illegal_), 
        lock     (illegal_){
      }

      /**
       * Destructor.
       */
     ~List(){}

    private:

      Node                    illegal_;

    public:

      typedef util::LinkedList<Node> SemaphoreList;

      SemaphoreList           exec;
      SemaphoreList           lock;
    };

    bool                      construct();
    bool                      removeNode(List::SemaphoreList& list, Node& node);

    api::Switchable&          switch_;
    int32                     permits_;
    bool                      fair_;
    List                      list_;

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
