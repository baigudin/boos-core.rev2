/**
 * System memory configuration for TI AM18x ARM Microprocessor.
 * 
 * This is an example of command linker file which represents 
 * 8K ARM Local RAM and 128K On-chip RAM for TI AM18x ARM Microprocessors.
 * Note: Every user project should have a self command file; 
 * map of that should be mirrored in a self assembly file 
 * of core configuration (boos.core.config.asm).
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
-heap 0x00c0 
 
MEMORY
{
  /** ARM Exceptions */
  HWI          : origin = 0xffff0000, len = 0x00000040
  /** TI RTS Library heap */
  HEAP         : origin = 0xffff0040, len = 0x000000c0
  /** BOOS Core heap */
  MEMORY       : origin = 0xffff0100, len = 0x00001f00
  /** Programme memory */
  CODE         : origin = 0x80000000, len = 0x00020000
  /** Chip registers mamory map */
  REGS_PLLC0   : origin = 0x01c11000, len = 0x00001000
  REGS_SYSCFG0 : origin = 0x01c14000, len = 0x00001000
  REGS_TIMER0  : origin = 0x01c20000, len = 0x00001000
  REGS_TIMER1  : origin = 0x01c21000, len = 0x00001000
  REGS_USB0    : origin = 0x01e00000, len = 0x00010000
  REGS_PLLC1   : origin = 0x01e1a000, len = 0x00001000
  REGS_USB1    : origin = 0x01e25000, len = 0x00001000
  REGS_SYSCFG1 : origin = 0x01e2c000, len = 0x00001000
  REGS_TIMER2  : origin = 0x01f0c000, len = 0x00001000
  REGS_TIMER3  : origin = 0x01f0d000, len = 0x00001000
  REGS_DDR2    : origin = 0xb0000000, len = 0x00008000
  REGS_AINTC   : origin = 0xfffee000, len = 0x00002000  
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
  .sysmem    : load = HEAP
  /** Chip registers sections */
  .regs_syscfg0 : type=NOLOAD { } > REGS_SYSCFG0
  .regs_syscfg1 : type=NOLOAD { } > REGS_SYSCFG1
  .regs_pllc0   : type=NOLOAD { } > REGS_PLLC0
  .regs_pllc1   : type=NOLOAD { } > REGS_PLLC1
  .regs_timer0  : type=NOLOAD { } > REGS_TIMER0
  .regs_timer1  : type=NOLOAD { } > REGS_TIMER1
  .regs_timer2  : type=NOLOAD { } > REGS_TIMER2
  .regs_timer3  : type=NOLOAD { } > REGS_TIMER3
  .regs_ddr2    : type=NOLOAD { } > REGS_DDR2
  .regs_aintc   : type=NOLOAD { } > REGS_AINTC
  .regs_usb20   : type=NOLOAD { } > REGS_USB0
  .regs_usb11   : type=NOLOAD { } > REGS_USB1  
}
