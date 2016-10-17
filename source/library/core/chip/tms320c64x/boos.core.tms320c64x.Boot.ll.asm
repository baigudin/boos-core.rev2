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
    .def  _c_int00

    .ref  os_reset

    .asg  b15, sp
    .asg  b14, dp
    .asg  a15, fp

    ; EABI 
    .if   __TI_EABI__

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
        b              os_reset
        nop            5

; ----------------------------------------------------------------------------
; Returns the first record adderess.
;
; @return A4 memory address of .cinit section or NULL.
; ----------------------------------------------------------------------------
        .text
m_get_cinit:
        .if             __TI_EABI__
        b               b3
        mvk             0, a4
        nop             4        
        .else
        b               b3
        mvkl            m_cinit, a4
     || mvkl            0ffffffffh, b0
        mvkh            m_cinit, a4
     || mvkh            0ffffffffh, b0
        xor             a4, b0, b0
  [!b0] mvk             0, a4
        nop             1
        .endif
        
; ----------------------------------------------------------------------------
; Returns the first record adderess.
;
; @return A4 memory address of .pinit section or NULL.
; ----------------------------------------------------------------------------
        .text
m_get_pinit
        .if             __TI_EABI__
        b               b3
        mvk             0, a4
        nop             4        
        .else
        b               b3
        mvkl            m_pinit, a4
     || mvkl            0ffffffffh, b0
        mvkh            m_pinit, a4
     || mvkh            0ffffffffh, b0
        xor             a4, b0, b0
  [!b0] mvk             0, a4
        nop             1
        .endif
            