; ----------------------------------------------------------------------------
; The kernel.
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2014-2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
    .def  m_core_start
    
    .ref  m_core_int_enable
    .ref  m_core_int_disable
    ; EABI 
    .if   __TI_EABI__
    ; COFF ABI
    .else
    .ref  ___bss__
    .ref  _main__Q2_6target4MainSFv
    .asg  ___bss__,                  m_bss    
    .asg  _main__Q2_6target4MainSFv, m_main
    .endif

    .asg  01840000h, DREG_CCFG
    .asg  019C0000h, DREG_MUXH
    .asg  019C0004h, DREG_MUXL
    
    .asg  b15, sp
    .asg  b14, dp
    .asg  a15, fp
    ; Mode stacks sizes
    .asg  2000h, STACK_SIZE_CORE
    ; Mode stacks
    .bss  v_stack_core, STACK_SIZE_CORE, 8

; ----------------------------------------------------------------------------
; Initializes the low level kernel.
;
; The entry point after CPU hardware is reseted.
; ----------------------------------------------------------------------------
        .text
m_core_start:
        ; Reset Interrupt Selector Registers
        mvk             0, a0
        mvkl            DREG_MUXH, b0
        mvkh            DREG_MUXH, b0
        stw             a0, *b0
        nop             2
        mvkl            DREG_MUXL, b0
        mvkh            DREG_MUXL, b0
        stw             a0, *b0
        nop             2
        ; Interrupt disable
        b               m_core_int_disable
mr_i0?  addkpc          mr_i0?+4, b3, 4
        ; Set CPU register
        mvk             0, a0
        mvc             a0, istp
        mvc             a0, amr
        mvc             a0, irp
        mvc             a0, nrp
        mvk             -1, a0
        mvc             a0, icr
        mvk             3,  a0
        mvc             a0, ier ; set NMIE to enable
        nop
        ; Reset Cache Configuration Register
        mvkl            DREG_CCFG, b0
     || mvk             0300h, a0
        mvkh            DREG_CCFG, b0
        stw             a0, *b0
        nop             2
        ; Set CPU registers to zero
        .eval           0, i
        .loop           32
        mvk             0, a:i:
     || mvk             0, b:i:
        .eval           i+1, i
        .endloop
        ; Initialize OS kernel pointers
        mvkl            v_stack_core + STACK_SIZE_CORE - 8, sp
        mvkh            v_stack_core + STACK_SIZE_CORE - 8, sp
        mvkl            m_bss, dp
     || mvkl            0, fp
        mvkh            m_bss, dp
     || mvkl            0, fp
        ; Call hi level initialization and
        ; set kernel executing finish procedure as return point
        mvkl            m_core_deinit, b3
     || mvkl            m_main, a3
        mvkh            m_core_deinit, b3
     || mvkh            m_main, a3
        b               a3
        nop             5

; ----------------------------------------------------------------------------
; Finishes the kernel executing
; ----------------------------------------------------------------------------
        .text
m_core_deinit:
        idle
        b               m_core_deinit
