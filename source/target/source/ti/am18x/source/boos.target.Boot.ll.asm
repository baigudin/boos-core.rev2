; ----------------------------------------------------------------------------
; Core boot routine.
;
; The module performs the tasks to initialize C/C++ run-time environment.
; 
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
    .state32

    .def  _c_int00
    .ref  m_core_start

    ; EABI 
    .if   __TI_EABI_ASSEMBLER

    ; COFF ABI
    .else
    
    .def  _getCRecord__Q2_6target4BootSFv
    .def  _getPRecord__Q2_6target4BootSFv
    
    .ref  ___cinit__
    .ref  ___pinit__
                 
    .asg  _c_int00,   m_bootstrap
    .asg  ___cinit__, v_cinit
    .asg  ___pinit__, v_pinit
    .asg  _getCRecord__Q2_6target4BootSFv, m_get_cinit
    .asg  _getPRecord__Q2_6target4BootSFv, m_get_pinit
    
    .endif    
   
; ----------------------------------------------------------------------------
; The bootstrap routine.        
; ----------------------------------------------------------------------------
    .text
m_bootstrap:
    ldr     pc, a_m_core_start

a_m_core_start .word m_core_start

; ----------------------------------------------------------------------------
; Returns the first record adderess.
;
; @return R0 memory address of .cinit section or NULL.
; ----------------------------------------------------------------------------
    .text
m_get_cinit:
    ldr     r0, a_v_cinit
    ldr     r1, a_v_cinit_err
    cmp     r0, r1
    moveq   r0, #0
    bx      lr

a_v_cinit     .word v_cinit
a_v_cinit_err .word 0ffffffffh

; ----------------------------------------------------------------------------
; Returns the first record adderess.
;
; @return R0 memory address of .pinit section or NULL.
; ----------------------------------------------------------------------------
    .text
m_get_pinit:
    ldr     r0, a_v_pinit
    ldr     r1, a_v_pinit_err
    cmp     r0, r1
    moveq   r0, #0
    bx      lr

a_v_pinit     .word v_pinit
a_v_pinit_err .word 0ffffffffh
