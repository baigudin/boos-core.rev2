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

/**
 * User thread class.
 */   
class Thread : public ::core::Thread
{
  
public:
  
  /** 
   * Constructor.
   *
   * @param sem  a semaphore of critical area.
   * @param time some working time in critical area in seconds.  
   * @param name a name of this thread.  
   */
  Thread(::api::Semaphore& sem, int32 time, const char* name) :
    sem_  (sem),
    time_ (time * 1000),
    name_ (name){
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
    volatile bool exe = true;
    while(exe) 
    {
      sem_.acquire(1);
      Thread::sleep(time_);
      sem_.release(1);
    }
  }
  
  /**
   * The semaphore of critical area.
   */
  ::api::Semaphore& sem_;
  
  /**
   * The working time in critical area in seconds.
   */
  int32 time_;
  
  /**
   * The name of this thread.
   */
  const char* name_;
};

/**
 * The user application entry method.
 *
 * @param argc count of array elements.
 * @param argv array of arguments.
 * @return error code or zero.
 */   
int Main::main(int argc, char* argv[])
{
  // Create and check one semaphore of all threads
  ::core::Semaphore sem = ::core::Semaphore(2, true);
  if(!sem.isConstructed()) return 1;
  // Create the threads
  Thread thr1 = Thread(sem, 5, "Thread1");
  Thread thr2 = Thread(sem, 2, "Thread2");  
  Thread thr3 = Thread(sem, 1, "Thread3");  
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
