; ----------------------------------------------------------------------------
; Core of Operation System
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
    .state32

    .def    _c_int00    
  
; ----------------------------------------------------------------------------
; Hardware interrupts table
; ----------------------------------------------------------------------------
    .sect    ".hwi"
    b       _int_reset_handler      ; Reset
    b       _int_undef_handler      ; Undefined instructions
    b       _int_swi_handler        ; Software interrupt (SWI/SYS)
    b       _int_prefetch_handler   ; Prefetch abort
    b       _int_abort_handler      ; Data abort
    b       _int_not_used_handler   ; RESERVED
    b       _int_irq_handler        ; IRQ
    b       _int_fiq_handler        ; FIQ
    
    .sect    ".hwi_handler"
; ----------------------------------------------------------------------------
; Reset 
; ----------------------------------------------------------------------------
_int_reset_handler:
    b       _int_reset_handler
    
; ----------------------------------------------------------------------------
; Undefined instructions
; ----------------------------------------------------------------------------
_int_undef_handler:   
    b       _int_undef_handler
    
; ----------------------------------------------------------------------------
; Software interrupt (SWI/SYS)
; ----------------------------------------------------------------------------
_int_swi_handler:  
    b       _int_swi_handler
    
; ----------------------------------------------------------------------------
; Prefetch abort
; ----------------------------------------------------------------------------
_int_prefetch_handler:
    b       _int_prefetch_handler
    
; ----------------------------------------------------------------------------
; Data abort
; ----------------------------------------------------------------------------
_int_abort_handler:
    b       _int_abort_handler
    
; ----------------------------------------------------------------------------
; Reserved
; ----------------------------------------------------------------------------
_int_not_used_handler:
    b       _int_not_used_handler
    
; ----------------------------------------------------------------------------
; IRQ
; ----------------------------------------------------------------------------
_int_irq_handler:
    b       _int_irq_handler
    
; ----------------------------------------------------------------------------
; FIQ
; ----------------------------------------------------------------------------
_int_fiq_handler:
    b       _int_fiq_handler

; ----------------------------------------------------------------------------
; Initializes the low level core.
;
; The entry point after CPU hardware is reseted.
; ----------------------------------------------------------------------------
     .text
_c_int00:
    nop
    b       _c_int00
