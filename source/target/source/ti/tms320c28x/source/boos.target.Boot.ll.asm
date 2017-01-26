; ----------------------------------------------------------------------------
; Boot routine.
;
; The module performs the tasks to initialize C/C++ run-time environment.
; 
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
    .c28_amode
    .def  _c_int00

    .ref  m_core_start
    
    .def  _getCRecord__Q2_6target4BootSFv
    .def  _getPRecord__Q2_6target4BootSFv
    
    .ref  cinit
    .ref  pinit
    
    .asg  _c_int00,                        m_bootstrap    
    .asg  _getCRecord__Q2_6target4BootSFv, m_get_cinit
    .asg  _getPRecord__Q2_6target4BootSFv, m_get_pinit
    .asg  cinit,                           v_cinit
    .asg  pinit,                           v_pinit   

; ----------------------------------------------------------------------------
; The bootstrap routine.        
; ----------------------------------------------------------------------------
        .text
m_bootstrap:
        b              m_core_start, unc

; ----------------------------------------------------------------------------
; Returns the first record adderess.
;
; @return AR4 memory address of .cinit section or NULL.
; ----------------------------------------------------------------------------
        .text
m_get_cinit:
        mov            al, #v_cinit
        mov            ah, #hi16(v_cinit)
        addb           acc, #1
        b              m_c0?, eq 
        movl           xar4, #v_cinit
        lretr
m_c0?   movl           xar4, #0        
        lretr
        
; ----------------------------------------------------------------------------
; Returns the first record adderess.
;
; @return AR4 memory address of .pinit section or NULL.
; ----------------------------------------------------------------------------
        .text
m_get_pinit:
        mov            al, #v_pinit
        mov            ah, #hi16(v_pinit)
        addb           acc, #1
        b              m_p0?, eq 
        movl           xar4, #v_pinit
        lretr
m_p0?   movl           xar4, #0        
        lretr
            