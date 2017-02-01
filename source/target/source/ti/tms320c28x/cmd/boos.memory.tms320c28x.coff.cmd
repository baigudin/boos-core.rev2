/**
 * System memory configuration for TI TMS320F2833x DSCs.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
-heap  0x100
-stack 0x3B0

MEMORY
{
  /** 
   * Program Memory
   * Memory (RAM/FLASH/OTP) blocks can be moved to PAGE1 for data allocation 
   */
PAGE 0:    

  HWI0        : origin = 0x000000,  length = 0x000040     /* HW Interrupt Vectors */  
  ZONE0       : origin = 0x004000,  length = 0x001000     /* XINTF zone 0 */
  RAML0       : origin = 0x008000,  length = 0x001000     /* on-chip RAM block L0 */
  RAML1       : origin = 0x009000,  length = 0x001000     /* on-chip RAM block L1 */
  RAML2       : origin = 0x00A000,  length = 0x001000     /* on-chip RAM block L2 */
  RAML3       : origin = 0x00B000,  length = 0x001000     /* on-chip RAM block L3 */
  ZONE6       : origin = 0x0100000, length = 0x100000     /* XINTF zone 6 */ 
  ZONE7A      : origin = 0x0200000, length = 0x00FC00     /* XINTF zone 7 - program space */ 
  FLASHH      : origin = 0x300000,  length = 0x008000     /* on-chip FLASH */
  FLASHG      : origin = 0x308000,  length = 0x008000     /* on-chip FLASH */
  FLASHF      : origin = 0x310000,  length = 0x008000     /* on-chip FLASH */
  FLASHE      : origin = 0x318000,  length = 0x008000     /* on-chip FLASH */
  FLASHD      : origin = 0x320000,  length = 0x008000     /* on-chip FLASH */
  FLASHC      : origin = 0x328000,  length = 0x008000     /* on-chip FLASH */
  FLASHB      : origin = 0x330000,  length = 0x008000     /* on-chip FLASH */  
  FLASHA      : origin = 0x338000,  length = 0x007F80     /* on-chip FLASH */
  CSM_RSVD    : origin = 0x33FF80,  length = 0x000076     /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */
  BEGIN       : origin = 0x33FFF6,  length = 0x000002     /* Part of FLASHA.  Used for "boot to Flash" bootloader mode. */
  CSM_PWL     : origin = 0x33FFF8,  length = 0x000008     /* Part of FLASHA.  CSM password locations in FLASHA */
  OTP         : origin = 0x380400,  length = 0x000400     /* on-chip OTP */
  ADC_CAL     : origin = 0x380080,  length = 0x000009     /* ADC_cal function in Reserved memory */
  
  IQTABLES    : origin = 0x3FE000,  length = 0x000b50     /* IQ Math Tables in Boot ROM */
  IQTABLES2   : origin = 0x3FEB50,  length = 0x00008c     /* IQ Math Tables in Boot ROM */  
  FPUTABLES   : origin = 0x3FEBDC,  length = 0x0006A0     /* FPU Tables in Boot ROM */
  ROM         : origin = 0x3FF27C,  length = 0x000D44     /* Boot ROM */        
  HWI1        : origin = 0x3FFFC0,  length = 0x000040     /* HW Interrupt Vectors */

  /**
   * Data Memory
   * Memory (RAM/FLASH/OTP) blocks can be moved to PAGE0 for program allocation
   * Registers remain on PAGE1
   */
PAGE 1:
   
  RAMM0       : origin = 0x000040, length = 0x0003C0     /* on-chip RAM block M0 */
  RAMM1       : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
  RAML4       : origin = 0x00C000, length = 0x001000     /* BOOS Heap is on-chip RAM block L1 */
  RAML5       : origin = 0x00D000, length = 0x001000     /* on-chip RAM block L1 */
  RAML6       : origin = 0x00E000, length = 0x001000     /* on-chip RAM block L1 */
  RAML7       : origin = 0x00F000, length = 0x001000     /* on-chip RAM block L1 */
  ZONE7B      : origin = 0x20FC00, length = 0x000400     /* XINTF zone 7 - data space */
  FLASHB      : origin = 0x330000, length = 0x008000     /* on-chip FLASH */
}

SECTIONS
{
    /** Hardware interrupts */    
   .hwi                : > HWI0,       PAGE = 0, TYPE = DSECT

   /** Allocate program areas */
   .cinit              : > FLASHA      PAGE = 0
   .pinit              : > FLASHA,     PAGE = 0
   .text               : > FLASHA      PAGE = 0

   /** Initalized data sections */
   .cio                : > FLASHB      PAGE = 0
   .econst             : > FLASHB      PAGE = 0
   .switch             : > FLASHB      PAGE = 0     

   /** Uninitalized data sections */
   .stack              : > RAMM0       PAGE = 1
   .bss                : > RAML5       PAGE = 1   
   .ebss               : > RAMM1       PAGE = 1
   .esysmem            : > RAMM1       PAGE = 1

}
