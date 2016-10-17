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
    .ref  os_reset

    ; EABI 
    .if   __TI_EABI_ASSEMBLER

    ; COFF ABI
    .else
    
    .def  _getCRecord__Q2_4core4BootSFv
    .def  _getPRecord__Q2_4core4BootSFv
    
    .ref  ___cinit__
    .ref  ___pinit__
    
    .asg  ___cinit__, m_cinit
    .asg  ___pinit__, m_pinit 
    .asg  _getCRecord__Q2_4core4BootSFv, m_get_cinit
    .asg  _getPRecord__Q2_4core4BootSFv, m_get_pinit
    
    .endif    
   
; ----------------------------------------------------------------------------
; The bootstrap routine.        
; ----------------------------------------------------------------------------
    .text
_c_int00:
    ldr     pc, a_os_reset

a_os_reset .word os_reset

; ----------------------------------------------------------------------------
; Returns the first record adderess.
;
; @return R0 memory address of .cinit section or NULL.
; ----------------------------------------------------------------------------
    .text
m_get_cinit:
    ldr     r0, a_m_cinit
    ldr     r1, v_m_cinit_err
    cmp     r0, r1
    moveq   r0, #0
    bx      lr

a_m_cinit     .word m_cinit
v_m_cinit_err .word 0ffffffffh

; ----------------------------------------------------------------------------
; Returns the first record adderess.
;
; @return R0 memory address of .pinit section or NULL.
; ----------------------------------------------------------------------------
    .text
m_get_pinit:
    ldr     r0, a_m_pinit
    ldr     r1, v_m_pinit_err
    cmp     r0, r1
    moveq   r0, #0
    bx      lr

a_m_pinit     .word m_pinit
v_m_pinit_err .word 0ffffffffh
