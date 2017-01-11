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
  Semaphore sem(1, true);
  if(!sem.isConstructed()) return 1;
  volatile int64 time[2], result;
  time[0] = System::nanoTime();
  for(int32 i=0; i<1000000; i++)
  {
    sem.acquire(1);
    sem.release(1);
  }
  time[1] = System::nanoTime();
  // The test results:
  //
  // Windows 7 & AMD Phenom II X4 B55 @ 3200 MHz
  // 499_000_000 ns  
  //
  // Windows 7 & Intel Core i5-3570 @ 3400 MHz
  // 514_000_000 ns
  //
  // Windows 7 & Intel Pentium Dual-Core E5400 @ 2700 MHz
  // 1_075_000_000 ns
  //
  // Windows 10 & AMD FX-8150 Eight-Core Processor @ 3600 MHz
  // 1_234_000_000 ns
  //
  // Windows XP & Intel Pentium 4 @ 3000 MHz
  // 1_750_000_000 ns
  //
  // ZOSRT Hydra & TI TMS320C6416 @ 720 MHz
  // 417_114_355 ns
  //
  // BOOS Core 2.2 & TI TMS320C6416 @ 720 MHz
  // 533_970_345 ns : unfair  
  // 624_355_345 ns : fair
  //
  // BOOS Core 2.2 & TI TMS320C6412 @ 500 MHz
  // 787_355_280 ns : unfair  
  // 899_546_288 ns : fair
  // 
  // BOOS Core 2.2 & TI AM1808 @ 375 MHz
  // 7_833_976_200 ns : unfair  
  // 8_511_705_080 ns : fair
  result = time[1] - time[0];
  return result ? 0 : 1;
}
