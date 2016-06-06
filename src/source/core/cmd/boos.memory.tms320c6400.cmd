/**
 * System memory configuration for TI TMS320C6400.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */

MEMORY
{
  RESET      : origin = 0x00000000, len = 0x00000020
  HWI        : origin = 0x00000020, len = 0x000001e0
  CODE       : origin = 0x00001000, len = 0x0008e000
  HEAPLIB    : origin = 0x0008F000, len = 0x00001000    
  HEAPCORE   : origin = 0x00090000, len = 0x00010000
  HEAPSYSTEM : origin = 0x000A0000, len = 0x00060000
}

SECTIONS
{
  .reset     : load = RESET
  .hwi       : load = HWI
  .text      : load = CODE
  .data      : load = CODE
  .bss       : load = CODE
  .core      : load = CODE    
  .cinit     : load = CODE
  .pinit     : load = CODE
  .const     : load = CODE
  .far       : load = CODE
  .cio       : load = CODE
  .switch    : load = CODE
  .template  : load = CODE
  .sysmem    : load = HEAPLIB
}

-heap 0x1000
