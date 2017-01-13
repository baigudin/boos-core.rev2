/**
 * Escalator class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_ESCALATOR_HPP_
#define BOOS_CORE_ESCALATOR_HPP_

#include "boos.core.Thread.hpp"
#include "boos.api.Semaphore.hpp"
#include "boos.util.LinkedList.hpp"

namespace core
{
  class Escalator : public ::core::Object<>, public ::api::Semaphore
  {
    typedef ::core::Object<> Parent;
   
  public:

    /** 
     * Constructor.
     *
     * @param permits the initial number of permits available.   
     */      
    Escalator(int32 permits);
    
    /** 
     * Constructor.
     *
     * @param permits the initial number of permits available.      
     * @param fair true if this escalator will guarantee FIFO granting of permits under contention.
     */      
    Escalator(int32 permits, bool fair);
                            
    /** 
     * Destructor.
     */
    virtual ~Escalator();
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const;

    /**
     * Acquires one permit from this escalator.
     *
     * @return true if the escalator is acquired successfully.
     */  
    virtual bool acquire();

    /**
     * Acquires the given number of permits from this escalator.
     *
     * @param permits the number of permits to acquire.
     * @return true if the escalator is acquired successfully.
     */  
    virtual bool acquire(int32 permits);

    /**
     * Releases one permit.
     *
     * @return true if the escalator is released successfully.
     */
    virtual bool release();

    /**
     * Releases the given number of permits.
     *
     * @param permits the number of permits to release.
     * @return true if the escalator is released successfully.
     */  
    virtual bool release(int32 permits);

    /**
     * Tests if this escalator is fair.
     *
     * @return true if this escalator has fairness set true.
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
     * Node for escalator lists.
     */  
    class Node
    {

    public:
    
      /** 
       * Constructor.
       *
       * @param ipermits number of permits to release.
       * @param thread   current executing thread.
       * @return true if the escalator is release successfully.
       */
      Node(Thread& thread, int32 ipermits) :
        permits (ipermits),
        thread_ (&thread){
      }

      /** 
       * Copy constructor.
       *
       * @param obj reference to source node.       
       */    
      Node(const Node& obj) :
        permits (obj.permits),
        thread_ (obj.thread_){
      }
      
      /** 
       * Constructor.
       *
       * Constructs this object as illegal.
       *
       * @param ipermits number of permits to release.
       * @return true if the escalator is release successfully.
       */
      Node(int32 ipermits) :
        permits (ipermits),
        thread_ (NULL){
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
        permits = node.permits;
        return *this;
      }
      
      /**
       * Inequality operator.
       *
       * @param obj1 reference first object.
       * @param obj2 reference second object.
       * @return true if object are equal.
       */
      friend bool operator ==(const Node& obj1, const Node& obj2);
      
      /**
       * Inequality operator.
       *
       * @param obj1 reference first object.
       * @param obj2 reference second object.
       * @return true if object are not equal.
       */      
      friend bool operator !=(const Node& obj1, const Node& obj2);

      /** 
       * Number of permits to release for this thread.
       */
      int32 permits;
      
    private:

      /** 
       * Executing thread.
       */
      Thread* thread_;

    };

    /** 
     * Contain lists for the escalator.
     */  
    class List
    {

    public:

      /** 
       * Constructor.
       */
      List() : 
        illegal_ (-1),
        exec     (illegal_), 
        lock     (illegal_){
      }

      /**
       * Destructor.
       */
     ~List(){}
      
      /**
       * Tests if this object has been constructed.
       *
       * @return true if object has been constructed successfully.
       */    
      bool isConstructed() const
      {
        if(!exec.isConstructed()) return false;
        if(!lock.isConstructed()) return false;        
        return true;
      }

    private:

      /**
       * Illegal value for all this lists.
       */
      Node illegal_;

    public:
      
      /**
       * List of executing threads for fair escalator.
       *
       * ::api::Queue interface of the list is only used by the escalator.
       */      
      util::LinkedList<Node> exec;
      
      /**
       * List of locked threads.
       *
       * ::api::Queue interface of the list is only used by the escalator.
       */      
      util::LinkedList<Node> lock;
     
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
     * @param list reference to a queue.
     * @param node reference to node.     
     */    
    bool removeNode(::api::Queue<Node>& list, Node& node);
    
    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    Escalator(const Escalator& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     */
    Escalator& operator =(const Escalator& obj);     

    /**
     * Toggle interface of global interrupts.
     */
    ::api::Toggle& toggle_;
    
    /**
     * Number of permits for acquiring this escalator.
     */
    int32 permits_;
    
    /**
     * Escalator fair flag.
     */    
    bool isFair_;

    /** 
     * Lists of this escalator.
     */     
    List list_;

    friend bool operator ==(const Node& node1, const Node& node2);
    friend bool operator !=(const Node& node1, const Node& node2);    
  };
  
  /**
   * Inequality operator.
   *
   * @param obj1 reference first object.
   * @param obj2 reference second object.
   * @return true if object are equal.
   */
  inline bool operator ==(const Escalator::Node& obj1, const Escalator::Node& obj2)
  {
    return obj1.thread_ == obj2.thread_ ? true : false;
  }
  
  /**
   * Inequality operator.
   *
   * @param obj1 reference first object.
   * @param obj2 reference second object.
   * @return true if object are not equal.
   */      
  inline bool operator !=(const Escalator::Node& obj1, const Escalator::Node& obj2)
  {
    return obj1.thread_ != obj2.thread_ ? true : false;
  }
  
}
#endif //BOOS_CORE_ESCALATOR_HPP_
