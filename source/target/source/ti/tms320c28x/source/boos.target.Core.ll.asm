; ----------------------------------------------------------------------------
; The kernel
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2014-2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
    .c28_amode
    
    .def  m_core_start
    
    .def  _registerProtected__Q2_6target4CoreSFv    
    .def  _registerPublic__Q2_6target4CoreSFv
    
    .ref  bss
    .ref  _main__Q2_6target4MainSFv
    
    .asg  bss,                                    m_bss
    .asg  _main__Q2_6target4MainSFv,              m_main
    .asg  _registerProtected__Q2_6target4CoreSFv, m_dallow        
    .asg  _registerPublic__Q2_6target4CoreSFv,    m_eallow
    ; Mode stacks sizes
    .asg  3c0h, STACK_SIZE_CORE
    ; Mode stacks
    .bss  v_stack_core, STACK_SIZE_CORE, 8

; ----------------------------------------------------------------------------
; Initializes the low level core.
;
; The entry point after CPU hardware is reseted.
; ----------------------------------------------------------------------------
        .text
m_core_start:
        dint
        c28obj                             ; Enable C28x Object Mode
        c28addr                            ; Enable C28x Address Mode
        c28map                             ; Enable C28x Mapping Of M0 and M1 blocks
        mov             sp, #v_stack_core  ; Set kernel stack pointer
        clrc            c, tc, ovm, sxm    ; Clear Status Register 0
        spm             0                  ; Set product shift mode
        clrc            vmap, page0        ; Clear Status Register 1
        setc            dbgm, intm         ; Set Status Register 1
        movw            dp, #0             ; Initialize DP
        nop             *, arp0            ; Set ARP pointer to XAR0        
        asp                                ; Ensure SP is aligned
        mov             acc, #0            ; Set CPU registers to zero
        mov             pl, #0
        mov             ph, #0        
        movl            xt, p        
        and             ier, #0
        and             ifr, #0        
        movb            xar0, #0
        movb            xar1, #0        
        movb            xar2, #0                
        movb            xar3, #0                        
        movb            xar4, #0        
        movb            xar5, #0        
        movb            xar6, #0                
        movb            xar7, #0
        .if             .TMS320C2800_FPU32        
        setflg          rndf32=1           ; Enable rounding in FPU32 mode.
        .endif
        lcr             m_main             ; Call target kernel
        
; ----------------------------------------------------------------------------
; Finishes the kernel executing
; ----------------------------------------------------------------------------
        .text
m_core_deinit:
        b               m_core_deinit, unc
        
; ----------------------------------------------------------------------------
; Disables access to protected space.
; ----------------------------------------------------------------------------
        .text
m_dallow:        
        edis
        lretr

; ----------------------------------------------------------------------------
; Enables access to protected space.
; ----------------------------------------------------------------------------
        .text
m_eallow:
        eallow
        lretr        
