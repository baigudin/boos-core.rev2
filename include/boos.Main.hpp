/** 
 * User main class.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2015 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_MAIN_HPP_
#define BOOS_MAIN_HPP_

#include "boos.Types.hpp"

class Main
{

public:
  
  /**
   * User method which will be stated as first.
   *
   * @param argc count of array elements.
   * @param argv array of arguments.
   * @return error code or zero.
   */
  static int main(int argc, char* argv[]);

};
#endif // BOOS_MAIN_HPP_
