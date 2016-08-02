/**
 * System memory configuration for TI AM1808.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */

MEMORY
{
  LOCAL_RAM  : origin = 0xffff0000, len = 0x00002000
  CODE       : origin = 0x80004000, len = 0x00012000
  HEAPLIB    : origin = 0x80016000, len = 0x00001000    
  HEAPCORE   : origin = 0x80017000, len = 0x00001000
  HEAPSYSTEM : origin = 0x80018000, len = 0x00008000

}

SECTIONS
{
  GROUP:
  {
    .hwi         : { }
    .hwi_handler : { }
  }                                                     > LOCAL_RAM
  .cinit        : { }                                   > CODE
  .const        : { }                                   > CODE
  .data         : { }                                   > CODE
  .init_array   : { __init_array__ = .; }               > CODE
  .text         : { }                                   > CODE
  .bss          : { }                                   > CODE
/*.stack        : { }                                   > CODE*/
  .sysmem       : { }                                   > CODE
}
