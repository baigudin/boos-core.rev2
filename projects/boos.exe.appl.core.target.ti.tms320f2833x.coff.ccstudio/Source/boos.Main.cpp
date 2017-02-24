/** 
 * User main class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.Main.hpp"
#include "boos.driver.Pwm.hpp"
#include "boos.driver.Object.hpp"

using namespace driver;

/**
 * User method which will be stated as first.
 *
 * @return error code or zero.
 */   
int32 Main::main()
{
  // Initializes the PWM driver. Normally, called in Board initialization
  if( Pwm::init() == false ) return -1;
  // Create a PWM resource with T = 100 mks, and D = 35%
  Pwm* res = Pwm::create(1, 100, 35);
  if(res != NULL)
  {
    // Get the 35% duty value of the PWM 1
    int32 v = res->getDuty();
    // Delete the PWM resource
    delete res;
  }
  // Deinitializes the PWM driver. Normally, called in Board deinitialization
  Pwm::deinit();  
  return 0;
}
