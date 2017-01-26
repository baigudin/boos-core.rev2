; ----------------------------------------------------------------------------
; Interrupt low level module
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2014-2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
    .c28_amode
    .def  m_core_int_enable
    .def  m_core_int_disable
    
    .ref  m_core_start

    .def  _globalDisable__Q2_6target19InterruptControllerSFv
    .def  _globalEnable__Q2_6target19InterruptControllerSFb
    .def  _disableLow__Q2_6target19InterruptControllerSFUi
    .def  _enableLow__Q2_6target19InterruptControllerSFUib
    .def  _setLow__Q2_6target19InterruptControllerSFUi
    .def  _clearLow__Q2_6target19InterruptControllerSFUi
    .def  _jumpLow__Q2_6target19InterruptControllerSFUi
   
    .ref  bss
    .ref  _handler__Q2_6target19InterruptControllerSFi
    .ref  _contextLow___Q2_6target19InterruptController
    
    .asg  bss,                                                m_bss
    .asg  _globalDisable__Q2_6target19InterruptControllerSFv, m_global_disable
    .asg  _globalEnable__Q2_6target19InterruptControllerSFb,  m_global_enable
    .asg  _disableLow__Q2_6target19InterruptControllerSFUi,   m_disable
    .asg  _enableLow__Q2_6target19InterruptControllerSFUib,   m_enable
    .asg  _setLow__Q2_6target19InterruptControllerSFUi,       m_set
    .asg  _clearLow__Q2_6target19InterruptControllerSFUi,     m_clear
    .asg  _jumpLow__Q2_6target19InterruptControllerSFUi,      m_jump
    .asg  _handler__Q2_6target19InterruptControllerSFi,       m_handler
    .asg  _contextLow___Q2_6target19InterruptController,      v_context

; ----------------------------------------------------------------------------
; Hardware interrupt handler (the execution is 7 cycles).
;
; This is a macro command for interrupts table.
; It has fixed size that equals eight.
; ----------------------------------------------------------------------------
handler .macro          num
        stdw            b1:b0, *-sp[3]
     || mvkl            v_context, b1
        stdw            a1:a0, *-sp[2]
     || mvkh            v_context, b1
     || b               m_core_handler
        ldw             *++b1[ (num - 4) * 2 ], a0
        mvk             num - 4, b0
        nop             3
        .endm
        
; ----------------------------------------------------------------------------
; Hardware interrupts table.
; ----------------------------------------------------------------------------
        .sect           ".hwi"
m_core_reset:
        nop 
        b               m_core_reset, unc        
        
; ----------------------------------------------------------------------------
; Nonreset interrupt service routine.
; ----------------------------------------------------------------------------
        .text
m_core_handler:
        nop
        b               m_core_handler, unc

; ----------------------------------------------------------------------------
; Disables all maskable interrupts.
;
; @return A4 global interrupt enable bit value before method was called.
; ----------------------------------------------------------------------------
        .text
m_global_disable:
m_core_int_disable:
        nop
        b               m_global_disable, unc

; ----------------------------------------------------------------------------
; Enables all maskable interrupts.
;
; @param A4 the returned status by disable method.
; ----------------------------------------------------------------------------
        .text
m_global_enable:
m_core_int_enable:
        nop
        b               m_global_enable, unc

; ----------------------------------------------------------------------------
; Locks maskable interrupt source.
;
; @param A4 hardware interrupt vector number.
; @return an interrupt enable source bit in low bit before method was called.
; ----------------------------------------------------------------------------
        .text
m_disable:
        nop
        b               m_disable, unc

; ----------------------------------------------------------------------------
; Unlocks maskable interrupt source.
;
; @param A4 hardware interrupt vector number.
; @param B4 returned status by m_disable procedure.
; ----------------------------------------------------------------------------
        .text
m_enable:
        nop
        b               m_enable, unc
   
; ----------------------------------------------------------------------------
; Sets a maskable interrupt status.
;
; @param A4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_set:
        nop
        b               m_set, unc

; ----------------------------------------------------------------------------
; Clears a maskable interrupt status.
;
; @param A4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_clear:
        nop
        b               m_clear, unc
          
; ----------------------------------------------------------------------------
; Jumps to interrupt HW vector.
;
; @param A4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_jump:
        nop
        b               m_jump, unc
