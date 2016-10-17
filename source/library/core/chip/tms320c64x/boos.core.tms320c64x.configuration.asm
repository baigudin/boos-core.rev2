; ----------------------------------------------------------------------------
; Configuration of core for TI TMS320C64x DSPs.
;
; This is an example file of core configuration which represents 
; 256K internal RAM memory map for TI TMS320C64x DSPs. 
; Note: Every user project should have a self core configuration file 
; which should correspond with a command linker file.
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2014-2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
  .def    os_config

  .data
os_config:            ; Core configuration
  .align  8
  .word   36000000    ; Source clock in Hz [low word]
  .word   0           ; Source clock in Hz [hi word]  
  .word   720000000   ; CPU clock in Hz [low word]
  .word   0           ; CPU clock in Hz [hi word]
  .word   1000        ; Process switch time in microseconds
  .word   2000h       ; Size of thread stack by default
  .word   1000h       ; Size of interrupt stack by default
  .word   5           ; Priority of main thread
  .word   1           ; Count of system heap memories
  .word   heap?       ; Pointer to system heap table
  ; System heaps configuration
heap?
  .align  8
  .word   0ffffffffh  ; For alignment to four
  .word   00031000h   ; Start address of heap page
  .word   0000f000h   ; Size of heap page in bytes [hi word]
  .word   00000000h   ; Size of heap page in bytes [low word]

