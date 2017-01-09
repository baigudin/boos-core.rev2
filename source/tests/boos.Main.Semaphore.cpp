/** 
 * User main class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.Main.hpp"
#include "boos.core.System.hpp"
#include "boos.core.Thread.hpp"
#include "boos.core.Semaphore.hpp"
#include "boos.core.Mutex.hpp"

using namespace ::core;

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
  Semaphore sem(1);
  if(!sem.isConstructed()) return 1;
  int64 time[2], result;
  time[0] = System::nanoTime();
  for(int32 i=0; i<1000000; i++)
  {
    sem.acquire(1);
    sem.release(1);
  }
  time[1] = System::nanoTime();
  // The test results:
  //
  // AMD Phenom II X4 B55 @ 3200 MHz at Windows 7
  // 499_000_000 ns  
  //
  // Intel Core i5-3570 @ 3400 MHz at Windows 7
  // 514_000_000 ns
  //
  // Intel Pentium Dual-Core E5400 @ 2700 MHz at Windows 7
  // 1_075_000_000 ns
  //
  // AMD FX-8150 Eight-Core Processor @ 3600 MHz at Windows 10
  // 1_234_000_000 ns
  //
  // Intel Pentium 4 @ 3000 MHz at Windows XP
  // 1_750_000_000 ns
  //
  // TI TMS320C6416 @ 720 MHz at BOOS Core 2.2
  // 2_091_456_845 ns -opt3  
  // 3_655_013_066 ns -none
  //
  // TI TMS320C6412 @ 500 MHz at BOOS Core 2.2
  // 3_013_296_928 ns -opt3
  // 5_582_179_376 ns -none
  // 
  // TI AM1808 @ 375 MHz at BOOS Core 2.2
  // 26_383_328_280 ns -opt3  
  // 52_789_288_840 ns -none
  result = time[1] - time[0];
  return result ? 0 : 1;
}
