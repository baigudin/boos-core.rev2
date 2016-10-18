/**
 * System memory configuration for TI TMS320C64xx DSPs.
 * 
 * This is an example of command linker file which represents 
 * 256K internal RAM memory map for TI TMS320C64xx DSPs.
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
  /** Reset hardware interrupt */
  RESET      : origin = 0x00000000, len = 0x00000020
  /** Hardware interrupts */
  HWI        : origin = 0x00000020, len = 0x000001e0
  /** Programme memory */
  CODE       : origin = 0x00000200, len = 0x0002fe00
  /** Heap of TI RTS Library */
  HEAPLIB    : origin = 0x00030000, len = 0x00001000    
  /** Core heap of BOOS Core */
  HEAPCORE   : origin = 0x00031000, len = 0x00001000
  /** User heap of BOOS Core */
  HEAPSYSTEM : origin = 0x00032000, len = 0x0000e000
}

SECTIONS
{
  /** BOOS Core sections */
  .reset      : load = RESET
  .hwi        : load = HWI

  /** Compiler sections */
  .text       : load = CODE
  .data       : load = CODE
  .bss        : load = CODE
  .cinit      : load = CODE
  .pinit      : load = CODE
  .const      : load = CODE
  .far        : load = CODE
  .cio        : load = CODE
  .switch     : load = CODE
  .sysmem     : load = HEAPLIB

  /** ELF EABI sections */
  .init_array : load = CODE
  .fardata    : load = CODE
  .neardata   : load = CODE
  .rodata     : load = CODE
}
