; ----------------------------------------------------------------------------
; Configuration of core.
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2014-2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
  .def    os_config

  .data
os_config: ; Core configuration
  .align  8
  .word   720000000   ; CPU frequency in Hz [low word]
  .word   0           ; CPU frequency in Hz [hi word]
  .word   90000000    ; Core timer frequency in Hz [low word]
  .word   0           ; Core timer frequency in Hz [hi word]
  .word   1000        ; Process switch time in microseconds
  .word   0x2000      ; Size of thread stack by default
  .word   0x1000      ; Size of interrupt stack by default
  .word   5           ; Priority of main thread
  .word   1           ; Count of system heap memories
  .word   -1          ; Temp value for align to eight
  .word   heap?       ; Pointer to system heap table
  .word   0x00090000  ; Start address of core heap
  .word   0x00010000  ; Size of core heap in bytes [low word]
  .word   0x00000000  ; Size of core heap in bytes [hi word]
  ; System heaps configuration
heap?
  .align  8
  .word   0xffffffff  ; For alignment to four
  .word   0x000A0000  ; Start address of heap page
  .word   0x00060000  ; Size of heap page in bytes [hi word]
  .word   0x00000000  ; Size of heap page in bytes [low word]

