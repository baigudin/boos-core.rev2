/** 
 * User main class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.Main.hpp"

/**
 * User method which will be stated as first.
 *
 * @param argc count of array elements.
 * @param argv array of arguments.
 * @return error code or zero.
 */   
int Main::main(int argc, char* argv[])
{
  return argc > 0 && argv != NULL ? 1 : 0;
}
