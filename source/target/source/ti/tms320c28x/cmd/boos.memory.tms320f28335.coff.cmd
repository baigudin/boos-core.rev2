/**
 * System memory configuration for TI TMS320F2833x DSCs.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
-heap  0x100
-stack 0x100

MEMORY
{
  /** Program Memory */
PAGE 0:    

  HWI0        : origin = 0x000000, length = 0x000040
  CODE        : origin = 0x008000, length = 0x006000
  HWI1        : origin = 0x3fffc0, length = 0x000040

  /** Data Memory */
PAGE 1:
   
  DATA1       : origin = 0x000040, length = 0x0003c0
  DATA        : origin = 0x00e000, length = 0x002000   
  MEMORY      : origin = 0x000400, length = 0x000400
}

SECTIONS
{
   /** Hardware interrupts */    
   .hwi                : > HWI0,    PAGE = 0

   /** Allocate program areas */
   .cinit              : > CODE,    PAGE = 0
   .pinit              : > CODE,    PAGE = 0
   .text               : > CODE,    PAGE = 0

   /** Initalized data sections */
   .cio                : > DATA,    PAGE = 1
   .econst             : > DATA,    PAGE = 1
   .switch             : > DATA,    PAGE = 1     

   /** Uninitalized data sections */
   .stack              : > DATA,    PAGE = 1   
   .ebss               : > DATA,    PAGE = 1
   .esysmem            : > DATA,    PAGE = 1
   .bss                : > DATA1,   PAGE = 1   
   
}
