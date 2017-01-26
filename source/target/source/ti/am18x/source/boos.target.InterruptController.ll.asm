; ----------------------------------------------------------------------------
; The kernel.
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
    .state32
    .include "boos.target.constants.inc"    
    
    .ref  m_core_start
    
    ; EABI 
    .if   __TI_EABI_ASSEMBLER

    ; COFF ABI
    .else 
    
    .def  _handlerBaseLow__Q2_6target19InterruptControllerSFv
    .def  _handlerNullLow__Q2_6target19InterruptControllerSFv
    .def  _globalDisable__Q2_6target19InterruptControllerSFv
    .def  _globalEnable__Q2_6target19InterruptControllerSFb
    .def  _jumpLow__Q2_6target19InterruptControllerSFi
    
    .ref  _handler__Q2_6target19InterruptControllerSFi
    .ref  _supervisor__Q2_6target19InterruptControllerSFi
    
    .asg  _handler__Q2_6target19InterruptControllerSFi,        m_handler
    .asg  _supervisor__Q2_6target19InterruptControllerSFi,     m_supervisor
    .asg  _handlerBaseLow__Q2_6target19InterruptControllerSFv, m_handler_base
    .asg  _handlerNullLow__Q2_6target19InterruptControllerSFv, m_handler_null
    .asg  _globalDisable__Q2_6target19InterruptControllerSFv,  m_global_disable
    .asg  _globalEnable__Q2_6target19InterruptControllerSFb,   m_global_enable
    .asg  _jumpLow__Q2_6target19InterruptControllerSFi,        m_jump
  
    .endif

; ----------------------------------------------------------------------------
; Hardware interrupt vectors
; ----------------------------------------------------------------------------
    .sect   ".hwi"                             ; Priorities
    ldr     pc, a_m_core_handler_rst           ; 0
    ldr     pc, a_m_core_handler_und           ; 5
    ldr     pc, a_m_core_handler_svc           ; 5
    ldr     pc, a_m_core_handler_abt_prefetch  ; 4
    ldr     pc, a_m_core_handler_abt_data      ; 1
    ldr     pc, a_m_core_handler_res           ;
    ldr     pc, a_m_core_handler_irq           ; 3
    ldr     pc, a_m_core_handler_fiq           ; 2
    
a_m_core_handler_rst          .word m_core_handler_rst
a_m_core_handler_und          .word m_core_handler_und
a_m_core_handler_svc          .word m_core_handler_svc
a_m_core_handler_abt_prefetch .word m_core_handler_abt_prefetch
a_m_core_handler_abt_data     .word m_core_handler_abt_data
a_m_core_handler_res          .word m_core_handler_res
a_m_core_handler_irq          .word m_core_handler_irq
a_m_core_handler_fiq          .word m_core_handler_fiq
    
; ----------------------------------------------------------------------------
; Reset 
; ----------------------------------------------------------------------------    
    .text   
m_core_handler_rst:
    ldr     pc, a_m_core_start

a_m_core_start .word m_core_start   
 
; ----------------------------------------------------------------------------
; Undefined instructions
; ----------------------------------------------------------------------------
    .text
m_core_handler_und:   
    b       m_core_handler_und
    
; ----------------------------------------------------------------------------
; Supervisor mode
;
; @param R0 hardware interrupt source number.
; ----------------------------------------------------------------------------
    .text
m_core_handler_svc:
    push    {lr}
    bl      m_supervisor
    blx     r0      
    pop     {lr}    
    movs    pc, lr
    
; ----------------------------------------------------------------------------
; Prefetch abort
; ----------------------------------------------------------------------------
    .text
m_core_handler_abt_prefetch:
    b       m_core_handler_abt_prefetch
    
; ----------------------------------------------------------------------------
; Data abort
; ----------------------------------------------------------------------------
    .text
m_core_handler_abt_data:
    b       m_core_handler_abt_data
    
; ----------------------------------------------------------------------------
; Reserved
; ----------------------------------------------------------------------------
    .text
m_core_handler_res:
    b       m_core_handler_res
    
; ----------------------------------------------------------------------------
; IRQ
; ----------------------------------------------------------------------------
    .text
m_core_handler_irq:
    sub     lr, lr, #4
    ; Test if no interrupt is pending
    push    {lr}                      ; Push Interrupt Return Point to stack
    ldr     lr, a_r_aintc_gpir
    ldr     lr, [lr]
    subs    lr, lr, #0h
    bmi     m_core_handler_irq_return?
    ; An interrupt is pending
    ldr     lr, a_r_aintc_gpvr
    ldr     lr, [lr]
    stmfd   sp, {lr}
    ldr     lr, a_m_core_handler_irq_return
    ; Branch to the source routine
    ldmea   sp, {pc}
m_core_handler_irq_return?
    push    {r0, r1}
    ldr     r0, a_r_aintc_gpir
    ldr     r1, a_r_aintc_sicr
    ldr     r0, [r0]
    str     r0, [r1]
    pop     {r0, r1, lr}
    movs    pc, lr

a_m_core_handler_irq_return .word m_core_handler_irq_return?   
a_r_aintc_sicr              .word 0fffee024h
a_r_aintc_gpir              .word 0fffee080h
a_r_aintc_gpvr              .word 0fffee084h

; ----------------------------------------------------------------------------
; FIQ
; ----------------------------------------------------------------------------
    .text
m_core_handler_fiq:
    b       m_core_handler_fiq
    
; ----------------------------------------------------------------------------
; HW interrupt service routines.
;
; Interrupt Service Routines contains 101 handlers for each interrupt source. 
; Stack pointer (for full stacks) has to point to IRP, which points to
; instruction that will be executed after returning form interrupt, and 
; CPU registers have to contain a status of interrupted program, 
; except LR which has to contain a return address of calling handler
; for returning from these routines. Execution result is current or new, 
; for example for scheduler interrupt, context and IRP.
;
; @param stack contains an PC of interrupted user task.
; @return stack contains an PC of new or interrupted user task.
; ----------------------------------------------------------------------------
    .text
m_handler_base:
    .eval    0, i
    .loop    101

m_handler_source_:i:
    push    {r0, r1, r2, r4}
    ldr     r4, a_ctx_:i:
    ldr     pc, a_hnd_:i:

a_hnd_:i: .word m_handler_general?
a_ctx_:i: .word v_arg_:i:
v_arg_:i: .word 0h
v_reg_:i: .word 0h
v_tos_:i: .word 0h
            
    .eval    i+1, i
    .endloop

m_handler_general?
    ldmia   r4, {r0, r1, r2}      ; Load argument, CTX pointer, and user SP
    stmia   r1!, {r3, r5-r12}     ; Store R3, R5-R12 registers
    pop     {r5, r6, r7, r8, r9}  ; Load R0, R1, R2, R4, and PC(IRP)
    mrs     r10, spsr             ; Move saved PSR to R10
    stmia   r1, {r5-r10, sp, lr}^ ; Store R0-R2, R4, PC, PSR, SP, and LR
    mov     r5, lr                ; Move LR to preserved register by ABI
    mov     r6, sp                ; Move SP to preserved register by ABI
    mov     sp, r2                ; Set user handler SP
    bl      m_handler             ; Call C++ handler
    mov     sp, r6                ; Set preserved SP of an exeption
    mov     lr, r5                ; Set preserved LR of an exeption
    ldr     r0, [r4, #+4]         ; Load new CTX pointer
    ldmia   r0!, {r3, r5-r12}     ; Restore R3, R5-R12 registers
    add     r0, r0, #10h          ; Set CTX pointer to the saved PC(IRP)
    ldmia   r0, {r1, r2, sp, lr}^ ; Restore SP, LR and load PC(IRP), PSR
    push    {r1}                  ; Push PC(IRP) to stack
    msr     spsr_cxsf, r2         ; Restore PSR
    ldmdb   r0, {r0, r1, r2, r4}  ; Restore R0-R2, R4
    bx      lr
    
; ----------------------------------------------------------------------------
; HW interrupt handle null routing.
; ----------------------------------------------------------------------------
    .text
m_handler_null:
    b       m_handler_null
    
; ----------------------------------------------------------------------------
; Disables all maskable interrupts.
;
; @return R0 global interrupts enable bit value before method was called.
; ----------------------------------------------------------------------------
    .text
m_global_disable:
    mrs     r0, cpsr
    lsr     r1, r0, #7h
    ldr     r2, a_psr_irq_disable
    orr     r0, r0, r2
    msr     cpsr_c, r0
    and     r1, r1, #1h
    eor     r0, r1, #1h
    bx      lr

a_psr_irq_disable .word PSR_I

; ----------------------------------------------------------------------------
; Enables all maskable interrupts.
;
; @param R0 the returned status by disable method.
; ----------------------------------------------------------------------------
    .text
m_global_enable:
    cmp     r0, #1h
    bxne    lr
    mrs     r0, cpsr
    ldr     r1, a_psr_irq_enable
    and     r0, r0, r1
    msr     cpsr_c, r0
    bx      lr
    
a_psr_irq_enable .word ~PSR_I

; ----------------------------------------------------------------------------
; Jumps to interrupt HW vector.
;
; @param R0 hardware interrupt source number.
; ----------------------------------------------------------------------------
    .text
m_jump:
    svc     #0
    bx      lr
