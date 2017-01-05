/** 
 * Core types.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2014-2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CORE_TYPES_HPP_
#define BOOS_CORE_TYPES_HPP_

#include "boos.util.Align.hpp"

namespace core
{
  typedef util::Align<int16>     Int16a;
  typedef util::Align<int32>     Int32a;
  typedef util::Align<int64>     Int64a;
  typedef util::Align<uint16>    Uint16a;
  typedef util::Align<uint32,3>  Uint24a;
  typedef util::Align<uint32>    Uint32a;
  typedef util::Align<uint64>    Uint64a;
}
 
#endif // BOOS_CORE_TYPES_HPP_
