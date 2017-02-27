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
; Hardware interrupt vector
; ----------------------------------------------------------------------------
vector  .macro          n
vec_:n: .ulong          han_:n:
        .endm    

; ----------------------------------------------------------------------------
; Hardware interrupt handler.
; ----------------------------------------------------------------------------
handler .macro          n
han_:n: b               han_:n:, unc
        .endm
        
; ----------------------------------------------------------------------------
; Hardware interrupts table.
; ----------------------------------------------------------------------------
        .sect           ".hwi"
        vector          0
        vector          1
        vector          2
        vector          3
        vector          4
        vector          5
        vector          6
        vector          7
        vector          8
        vector          9
        vector          10
        vector          11
        vector          12
        vector          13
        vector          14
        vector          15
        vector          16
        vector          17
        vector          18
        vector          19
        vector          20
        vector          21
        vector          22
        vector          23
        vector          24
        vector          25
        vector          26
        vector          27
        vector          28
        vector          29
        vector          30                                                                                        
        vector          31
        
; ----------------------------------------------------------------------------
; Hardware interrupts table.
; ----------------------------------------------------------------------------
        .text
        handler         0
        handler         1
        handler         2
        handler         3
        handler         4
        handler         5
        handler         6
        handler         7
        handler         8
        handler         9
        handler         10
        handler         11
        handler         12
        handler         13
        handler         14
        handler         15
        handler         16
        handler         17
        handler         18
        handler         19
        handler         20
        handler         21
        handler         22
        handler         23
        handler         24
        handler         25
        handler         26
        handler         27
        handler         28
        handler         29
        handler         30                                                                                        
        handler         31
                
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
; @return AL global interrupt enable bit value before method was called.
; ----------------------------------------------------------------------------
        .text
m_global_disable:
m_core_int_disable:
        nop
        b               m_global_disable, unc

; ----------------------------------------------------------------------------
; Enables all maskable interrupts.
;
; @param AR4 the returned status by disable method.
; ----------------------------------------------------------------------------
        .text
m_global_enable:
m_core_int_enable:
        nop
        b               m_global_enable, unc

; ----------------------------------------------------------------------------
; Locks maskable interrupt source.
;
; @param AR4 hardware interrupt vector number.
; @return AL an interrupt enable source bit in low bit before method was called.
; ----------------------------------------------------------------------------
        .text
m_disable:
        nop
        b               m_disable, unc

; ----------------------------------------------------------------------------
; Unlocks maskable interrupt source.
;
; @param AR4 hardware interrupt vector number.
; @param AR5 returned status by m_disable procedure.
; ----------------------------------------------------------------------------
        .text
m_enable:
        nop
        b               m_enable, unc
   
; ----------------------------------------------------------------------------
; Sets a maskable interrupt status.
;
; @param AR4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_set:
        nop
        b               m_set, unc

; ----------------------------------------------------------------------------
; Clears a maskable interrupt status.
;
; @param AR4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_clear:
        nop
        b               m_clear, unc
          
; ----------------------------------------------------------------------------
; Jumps to interrupt HW vector.
;
; @param AR4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_jump:
        nop
        b               m_jump, unc
