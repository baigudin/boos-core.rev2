; ----------------------------------------------------------------------------
; The kernel.
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
    .state32
    .copy    "boos.target.registers.inc"
    .include "boos.target.constants.inc"
    
    .def  m_core_start
    ; EABI 
    .if   __TI_EABI_ASSEMBLER
    ; COFF ABI
    .else   
    .ref  _main__Q2_6target4MainSFv
    .asg  _main__Q2_6target4MainSFv, m_main         
    .endif
    ; Mode stacks sizes
    .asg  0008h,  STACK_SIZE_UND
    .asg  0020h,  STACK_SIZE_SVC
    .asg  0008h,  STACK_SIZE_ABT            
    .asg  0020h,  STACK_SIZE_IRQ
    .asg  0008h,  STACK_SIZE_FIQ    
    .asg  0400h,  STACK_SIZE_SYS
    ; Mode stacks
    .bss  v_stack_und, STACK_SIZE_UND, 8
    .bss  v_stack_svc, STACK_SIZE_SVC, 8
    .bss  v_stack_abt, STACK_SIZE_ABT, 8            
    .bss  v_stack_irq, STACK_SIZE_IRQ, 8    
    .bss  v_stack_fiq, STACK_SIZE_FIQ, 8
    .bss  v_stack_sys, STACK_SIZE_SYS, 8

; ----------------------------------------------------------------------------
; Initializes the low level kernel.
;
; The entry point after CPU hardware is reseted.
; ----------------------------------------------------------------------------
    .text
m_core_start:
    ; Set FIQ mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_FIQ
    msr     cpsr_cxsf, r0
    mov     r7,  #0
    mov     r8,  #0
    mov     r9,  #0
    mov     r10, #0
    mov     r11, #0
    mov     r12, #0
    ldr     sp,  a_v_stack_fiq    
    mov     lr,  #0
    ; Set Supervisor mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_SVC
    msr     cpsr_cxsf, r0
    ldr     sp,  a_v_stack_svc    
    mov     lr,  #0
    ; Set Abort mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_ABT
    msr     cpsr_cxsf, r0
    ldr     sp,  a_v_stack_abt    
    mov     lr,  #0
    ; Set IRQ mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_IRQ
    msr     cpsr_cxsf, r0
    ldr     sp,  a_v_stack_irq    
    mov     lr,  #0
    ; Set Undefined mode registers
    mov     r0,  #PSR_I|PSR_F|PSR_UND
    msr     cpsr_cxsf, r0
    ldr     sp,  a_v_stack_und    
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
    ldr     sp,  a_v_stack_sys        
    mov     lr,  #0
    ; Call hi level initialization and
    ; set kernel executing finish procedure as return point
    ldr     lr,  a_m_core_deinit
    b       m_main

a_m_core_deinit .word m_core_deinit
a_v_stack_und   .word v_stack_und + STACK_SIZE_UND
a_v_stack_svc   .word v_stack_svc + STACK_SIZE_SVC
a_v_stack_abt   .word v_stack_abt + STACK_SIZE_ABT
a_v_stack_irq   .word v_stack_irq + STACK_SIZE_IRQ
a_v_stack_fiq   .word v_stack_fiq + STACK_SIZE_FIQ
a_v_stack_sys   .word v_stack_sys + STACK_SIZE_SYS

; ----------------------------------------------------------------------------
; Finishes the kernel executing
; ----------------------------------------------------------------------------
    .text
m_core_deinit:
    b       m_core_deinit    