/**
 * System memory configuration for TI TMS320C64x DSPs.
 * 
 * This is an example of command linker file which represents 
 * 256K internal RAM memory map for TI TMS320C64x DSPs.
 * Note: Every user project should have a self command file; 
 * map of that should be mirrored in a self assembly file 
 * of core configuration (boos.core.config.asm).
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
-heap 0x1000

MEMORY
{
  /** Hardware interrupts */
  HWI        : origin = 0x00000000, len = 0x00000200
  /** Programme memory */
  CODE       : origin = 0x00000200, len = 0x0002fe00
  /** Heap of TI RTS Library */
  HEAP       : origin = 0x00030000, len = 0x00001000    
  /** User heap of BOOS Core */
  MEMORY     : origin = 0x00031000, len = 0x0000f000
}

SECTIONS
{
  .hwi       : load = HWI
  .text      : load = CODE
  .data      : load = CODE
  .bss       : load = CODE, fill = 0x00000000
  .far       : load = CODE, fill = 0x00000000
  .cinit     : load = CODE
  .pinit     : load = CODE
  .const     : load = CODE
  .cio       : load = CODE
  .switch    : load = CODE
/*.template  : load = CODE IS ILLEGAL FOR 7.2 CCS COMPILER.*/
  .sysmem    : load = HEAP
}
