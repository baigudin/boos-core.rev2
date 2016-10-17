; ----------------------------------------------------------------------------
; Configuration of core for TI AM18x ARM Microprocessors.
;
; This is an example file of core configuration which represents 
; 8K ARM Local RAM and 128K On-chip RAM for TI AM18x ARM Microprocessors.
; Note: Every user project should have a self core configuration file 
; which should correspond with a command linker file.
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2014-2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
  .state32
  
  .def    os_config

  .data
os_config:            ; Core configuration
  .align  8
  .word   25000000    ; Source clock in Hz [low word]
  .word   0           ; Source clock in Hz [hi word]  
  .word   375000000   ; CPU clock in Hz [low word]
  .word   0           ; CPU clock in Hz [hi word]
  .word   1000        ; Process switch time in microseconds
  .word   200h        ; Size of thread stack by default
  .word   200h        ; Size of interrupt stack by default
  .word   5           ; Priority of main thread
  .word   1           ; Count of system heap memories
  .word   heap?       ; Pointer to system heap table
  ; System heaps configuration
heap?
  .align  8
  .word   0ffffffffh  ; For alignment to four
  .word   0ffff0800h  ; Start address of heap page
  .word   00001800h   ; Size of heap page in bytes [hi word]
  .word   00000000h   ; Size of heap page in bytes [low word]
