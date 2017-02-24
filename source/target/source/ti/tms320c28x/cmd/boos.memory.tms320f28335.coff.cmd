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
  RAML        : origin = 0x008000, length = 0x008000
  HWI1        : origin = 0x3fffc0, length = 0x000040

  /** Data Memory */
PAGE 1:
   
  RAMM0       : origin = 0x000040, length = 0x0003C0 
  RAMM1       : origin = 0x000400, length = 0x000400
}

SECTIONS
{
   /** Hardware interrupts */    
   .hwi                : > HWI0,    PAGE = 0, TYPE = DSECT

   /** Allocate program areas */
   .cinit              : > RAML,    PAGE = 0
   .pinit              : > RAML,    PAGE = 0
   .text               : > RAML,    PAGE = 0

   /** Initalized data sections */
   .cio                : > RAML,    PAGE = 0
   .econst             : > RAML,    PAGE = 0
   .switch             : > RAML,    PAGE = 0     

   /** Uninitalized data sections */
   .bss                : > RAML,    PAGE = 0   
   .stack              : > RAMM0,   PAGE = 1   
   .ebss               : > RAMM0,   PAGE = 1
   .esysmem            : > RAMM0,   PAGE = 1

}
