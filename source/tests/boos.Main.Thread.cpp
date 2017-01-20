/** 
 * User main class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.Main.hpp"
#include "boos.core.Thread.hpp"
#include "boos.core.Mutex.hpp"
#include "boos.core.System.hpp"

/**
 * User thread class.
 */   
class Thread : public ::core::Thread
{
  
public:
  
  /** 
   * Constructor.
   *
   * @param index an index of this thread.   
   */
  Thread(int32 index) :
    index_   (index){
  }
  
  /**
   * Destructor.
   */
  virtual ~Thread()
  {
  }
  
  /**
   * The main method of this thread.
   */  
  void main()
  {
    volatile uint32 v = 0;  
    volatile bool exe = true;
    while(exe) v = v + 1;
  }
  
  /**
   * Returns size of thread stack.
   *
   * The method returns size of thread stack in bytes which should be allocated for the task.
   *
   * @return stack size in bytes.
   */  
  virtual int32 stackSize() const
  {
    return 0x80;
  }  
  
  /**
   * The index of this thread.
   */
  int32 index_;
  
};

/**
 * User method which will be stated as first.
 *
 * @return error code or zero.
 */   
int32 Main::main()
{
  // Create the threads
  Thread thr1(1);
  Thread thr2(2);  
  Thread thr3(3);  
  // Check the threads
  if(!thr1.isConstructed() || 
     !thr2.isConstructed() || 
     !thr3.isConstructed()) return 1;
  // Start the threads
  thr1.start();  
  thr2.start();
  thr3.start();  
  // Wait the threads will be completed
  thr1.join();
  thr2.join();  
  thr3.join();    
  return 0;
}
