; ----------------------------------------------------------------------------
; Core of Operation System
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
    .state32
    .include "boos.core.am18x.constants.inc"    
    
    .def  os_start
    .ref  os_config
    ; EABI 
    .if   __TI_EABI_ASSEMBLER
    ; COFF ABI
    .else   
    .ref  _start__Q2_4core4CoreSFPCQ2_4core13Configuration
    .asg  _start__Q2_4core4CoreSFPCQ2_4core13Configuration, m_start         
    .endif
    ; Mode stacks
    .bss  m_stack_fiq, STACK_SIZE_FIQ, 8
    .bss  m_stack_svc, STACK_SIZE_SVC, 8
    .bss  m_stack_abt, STACK_SIZE_ABT, 8
    .bss  m_stack_irq, STACK_SIZE_IRQ, 8
    .bss  m_stack_und, STACK_SIZE_UND, 8
    .bss  m_stack_sys, STACK_SIZE_SYS, 8

; ----------------------------------------------------------------------------
; Initializes the low level core.
;
; The entry point after CPU hardware is reseted.
; ----------------------------------------------------------------------------
    .text
os_start:
    ; Set FIQ mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_FIQ
    msr     cpsr_cxsf, r0
    mov     r7,  #0
    mov     r8,  #0
    mov     r9,  #0
    mov     r10, #0
    mov     r11, #0
    mov     r12, #0
    ldr     sp,  a_m_stack_fiq    
    mov     lr,  #0
    ; Set Supervisor mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_SVC
    msr     cpsr_cxsf, r0
    ldr     sp,  a_m_stack_svc    
    mov     lr,  #0
    ; Set Abort mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_ABT
    msr     cpsr_cxsf, r0
    ldr     sp,  a_m_stack_abt    
    mov     lr,  #0
    ; Set IRQ mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_IRQ
    msr     cpsr_cxsf, r0
    ldr     sp,  a_m_stack_irq    
    mov     lr,  #0
    ; Set Undefined mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_UND
    msr     cpsr_cxsf, r0
    ldr     sp,  a_m_stack_und    
    mov     lr,  #0
    ; Set System and User mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_SYS    
    msr     cpsr_cxsf, r0
    mov     r0,  #0
    mov     r1,  #0
    mov     r2,  #0
    mov     r3,  #0
    mov     r4,  #0
    mov     r5,  #0
    mov     r6,  #0
    mov     r7,  #0
    mov     r8,  #0
    mov     r9,  #0
    mov     r10, #0
    mov     r11, #0
    mov     r12, #0
    ldr     sp,  a_m_stack_sys        
    mov     lr,  #0
    ; Call hi level initialization and
    ; set core executing finish procedure as return point
    ldr     r0,  a_os_config
    ldr     lr,  a_os_core_deinit
    b       m_start

a_os_config      .word os_config    
a_os_core_deinit .word os_core_deinit
a_m_stack_fiq    .word m_stack_fiq, STACK_SIZE_FIQ
a_m_stack_svc    .word m_stack_svc, STACK_SIZE_SVC
a_m_stack_abt    .word m_stack_abt, STACK_SIZE_ABT
a_m_stack_irq    .word m_stack_irq, STACK_SIZE_IRQ
a_m_stack_und    .word m_stack_und, STACK_SIZE_UND
a_m_stack_sys    .word m_stack_sys, STACK_SIZE_SYS
    
; ----------------------------------------------------------------------------
; Finishes the core executing
; ----------------------------------------------------------------------------
    .text
os_core_deinit:
    b       os_core_deinit    