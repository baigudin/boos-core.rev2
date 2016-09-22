; ----------------------------------------------------------------------------
; Interrupt low level module
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2014-2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
  .include    "boos.core.register.inc"
  .include    "boos.core.macro.inc"

  .def  os_int_enable
  .def  os_int_disable
  
  .asg  b15, sp
  .asg  b14, dp
  .asg  a15, fp

  ; EABI
  .if   __TI_EABI__
  
  .def  globalDisableLow__Q2_4core9InterruptSFv
  .def  globalEnableLow__Q2_4core9InterruptSFb
  .def  disableLow__Q2_4core9InterruptSFUi
  .def  enableLow__Q2_4core9InterruptSFUib
  .def  setLow__Q2_4core9InterruptSFUi
  .def  clearLow__Q2_4core9InterruptSFUi
  .def  jumpLow__Q2_4core9InterruptSFUi
 
  .ref  __TI_STATIC_BASE
  .ref  handler__Q2_4core9InterruptSFi
  .ref  contextLow___Q2_4core9Interrupt
  
  .asg  __TI_STATIC_BASE,                         m_bss
  .asg  globalDisableLow__Q2_4core9InterruptSFv,  m_global_disable
  .asg  globalEnableLow__Q2_4core9InterruptSFb,   m_global_enable
  .asg  disableLow__Q2_4core9InterruptSFUi,       m_disable
  .asg  enableLow__Q2_4core9InterruptSFUib,       m_enable
  .asg  setLow__Q2_4core9InterruptSFUi,           m_set
  .asg  clearLow__Q2_4core9InterruptSFUi,         m_clear
  .asg  jumpLow__Q2_4core9InterruptSFUi,          m_jump
  .asg  handler__Q2_4core9InterruptSFi,           m_handler
  .asg  contextLow___Q2_4core9Interrupt,          v_context
  
  ; COFF ABI
  .else
  
  .def  _globalDisableLow__Q2_4core9InterruptSFv
  .def  _globalEnableLow__Q2_4core9InterruptSFb
  .def  _disableLow__Q2_4core9InterruptSFUi
  .def  _enableLow__Q2_4core9InterruptSFUib
  .def  _setLow__Q2_4core9InterruptSFUi
  .def  _clearLow__Q2_4core9InterruptSFUi
  .def  _jumpLow__Q2_4core9InterruptSFUi
 
  .ref  ___bss__
  .ref  _handler__Q2_4core9InterruptSFi
  .ref  _contextLow___Q2_4core9Interrupt
  
  .asg  ___bss__,                                  m_bss
  .asg  _globalDisableLow__Q2_4core9InterruptSFv,  m_global_disable
  .asg  _globalEnableLow__Q2_4core9InterruptSFb,   m_global_enable
  .asg  _disableLow__Q2_4core9InterruptSFUi,       m_disable
  .asg  _enableLow__Q2_4core9InterruptSFUib,       m_enable
  .asg  _setLow__Q2_4core9InterruptSFUi,           m_set
  .asg  _clearLow__Q2_4core9InterruptSFUi,         m_clear
  .asg  _jumpLow__Q2_4core9InterruptSFUi,          m_jump
  .asg  _handler__Q2_4core9InterruptSFi,           m_handler
  .asg  _contextLow___Q2_4core9Interrupt,          v_context
 
  .endif  

  .bss  bss_t, 16, 8

; ----------------------------------------------------------------------------
; Hardware interrupt handler.
;
; This is a macro command for interrupts table 
; that is used for reserved vectors.
; It has fixed size that equals eight.
; ----------------------------------------------------------------------------
reserve .macro
os_ri?  b               os_ri?
        nop             1
        nop             1
        nop             1
        nop             1
        nop             1
        nop             1
        nop             1
        .endm

; ----------------------------------------------------------------------------
; Hardware nonmaskable interrupt handler.
;
; This is a macro command for nonmaskable interrupt table.
; It has fixed size that equals eight.
; ----------------------------------------------------------------------------
nmi     .macro
        b               nrp
        nop             5
        nop             1
        nop             1
        nop             1
        nop             1
        nop             1
        nop             1
        .endm

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
     || b               os_interrupt_handler
        ldw             *++b1[ (num - 4) * 2 ], a0
        mvk             num - 4, b0
        nop             3
        .endm

; ----------------------------------------------------------------------------
; Hardware interrupts table (Part 2)
; ----------------------------------------------------------------------------
        .sect           ".hwi"
os_hwi:
        ; Nonmaskable interrupt vector
        nmi
        reserve
        reserve
        ; Nonreset interrupts vectors
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

; ----------------------------------------------------------------------------
; Nonreset interrupt service routine.
;
; 07 cycles is vector execution
; 21 cycles is save time of context and branch to routine.
; 26 cycles is restore time of context and return from interrupt.
; 
; 54 cycles is total service time.
; ----------------------------------------------------------------------------
        .text
os_interrupt_handler:
        ; Save context 
        stdw            b1:b0, *-sp[1]
     || add             a0, 8, b0
     || mv              sp, a1
     || mv              sp, b1
        stdw            a3:a2, *+a0[2]
     || stdw            b3:b2, *+b0[2]
        lddw            *-a1[2], a3:a2
     || lddw            *-b1[3], b3:b2
        stdw            a5:a4, *++a0[4]
     || stdw            b5:b4, *++b0[4]
        ; Load a vector number to A4 argument register
        lddw            *-sp[1], a5:a4        
        stdw            a7:a6, *++a0[2]
     || stdw            b7:b6, *++b0[2]
        stdw            a9:a8, *++a0[2]
     || stdw            b9:b8, *++b0[2]
        stdw            a3:a2, *-a0[8]
     || stdw            b3:b2, *-b0[8]	    
        stdw            a11:a10, *++a0[2]
     || stdw            b11:b10, *++b0[2]
        stdw            a13:a12, *++a0[2]
     || stdw            b13:b12, *++b0[2]
        stdw            a15:a14, *++a0[2]
     || stdw            b15:b14, *++b0[2]
        ; Load an interrupt TOS address to B15 (SP) register and
        ; Store an address of contexLow table to A14
        lddw            *a5, b15:b14
     || mv              a5, a14
     || mvc             amr, b1
     || zero            a2
        stdw            a17:a16, *++a0[2]
     || stdw            b17:b16, *++b0[2]
     || mv              b1, a1
     || mvc             irp, b1
        stdw            a19:a18, *++a0[2]
     || stdw            b19:b18, *++b0[2]
        stdw            a21:a20, *++a0[2]
     || stdw            b21:b20, *++b0[2]
        stdw            a23:a22, *++a0[2]
     || stdw            b23:b22, *++b0[2]
        ; Call an interrupt handler
     || b               m_handler
        stdw            a25:a24, *++a0[2]
     || stdw            b25:b24, *++b0[2]
     || mvkl            m_bss, dp
        stdw            a27:a26, *++a0[2]
     || stdw            b27:b26, *++b0[2]
     || mvkh            m_bss, dp
        stdw            a29:a28, *++a0[2]
     || stdw            b29:b28, *++b0[2]
     || mvc             a2, amr
        stdw            a31:a30, *++a0[2]
     || stdw            b31:b30, *++b0[2]
     || mvc             a2, irp
        ; A10 and B10 registers contain pointers to A29:A28 and B29:B28
     || mv              a0, a10
     || mv              b0, b10
        ; Save AMR form A1 and IRP from B1 to context
        stw             a1, *+a0[4]
     || stw             b1, *+b0[3]
     || zero            fp
     || addkpc          restore?, b3, 0
restore?
        ;Load context:
        ldw             *a14, a31
        mvk             32, a30
        nop             3
        lddw            *+a31[a30], a29:a28
     || add             a31, 8, b31
        lddw            *a31++[2], a1:a0
     || lddw            *b31++[2], b1:b0
        lddw            *a31++[2], a3:a2
     || lddw            *b31++[2], b3:b2
        lddw            *a31++[2], a5:a4
     || lddw            *b31++[2], b5:b4
        lddw            *a31++[2], a7:a6
     || lddw            *b31++[2], b7:b6
        lddw            *a31++[2], a9:a8
     || lddw            *b31++[2], b9:b8
     || mvc             a28, amr
        lddw            *a31++[2], a11:a10
     || lddw            *b31++[2], b11:b10
     || mvc             a29, irp
        lddw            *a31++[2], a13:a12
     || lddw            *b31++[2], b13:b12
        lddw            *a31++[2], a15:a14
     || lddw            *b31++[2], b15:b14
        lddw            *a31++[2], a17:a16
     || lddw            *b31++[2], b17:b16
        lddw            *a31++[2], a19:a18
     || lddw            *b31++[2], b19:b18
        lddw            *a31++[2], a21:a20
     || lddw            *b31++[2], b21:b20
        lddw            *a31++[2], a23:a22
     || lddw            *b31++[2], b23:b22
        lddw            *a31++[2], a25:a24
     || lddw            *b31++[2], b25:b24
        lddw            *a31++[2], a27:a26
     || lddw            *b31++[2], b27:b26
        lddw            *a31++[2], a29:a28
     || lddw            *b31++[2], b29:b28
     || b               irp
        lddw            *a31++[2], a31:a30
     || lddw            *b31++[2], b31:b30
        nop             4

; ----------------------------------------------------------------------------
; Disables all maskable interrupts.
;
; @return A4 global interrupt enable bit value before method was called.
; ----------------------------------------------------------------------------
        .text
m_global_disable:
os_int_disable:
        b               b3
        mvc             csr, b0
        and             C_REG_CSR_GIE, b0, a4
        and            ~C_REG_CSR_GIE, b0, b0
        mvc             b0, csr
        nop             1

; ----------------------------------------------------------------------------
; Enables all maskable interrupts.
;
; @param A4 returned status by disable method.
; ----------------------------------------------------------------------------
        .text
m_global_enable:
os_int_enable:
        b               b3
        and             1, a4, a1
   [a1] mvc             csr, b0
   [a1] or              C_REG_CSR_GIE, b0, b0
   [a1] mvc             b0, csr
        nop             1

; ----------------------------------------------------------------------------
; Locks maskable interrupt source.
;
; @param A4 hardware interrupt vector number.
; @return an interrupt enable source bit in low bit before method was called.
; ----------------------------------------------------------------------------
        .text
m_disable:
        b               m10?      
        mvk             1, a1      
        shl             a1, a4, a1 
     || mvc             csr, b0    
        mv              b0, b1  
     || and            ~C_REG_CSR_GIE, b0, b0 
        mvc             b0, csr
        mvc             ier, b0            
m10?:   b               b3         
     || not             a1, a1     
     || shr             b0, a4, a4 
        and             a4, 1, a4
        and             b0, a1, a1 
        or              a1, 3, a1  
        mvc             a1, ier    
        mvc             b1, csr

; ----------------------------------------------------------------------------
; Unlocks maskable interrupt source.
;
; @param A4 hardware interrupt vector number.
; @param B4 returned status by m_disable procedure.
; ----------------------------------------------------------------------------
        .text
m_enable:
        b               m20?    
        and             1, b4, a1
        shl             a1, a4, a1 
     || mvc             csr, b0    
        mv              b0, b1  
        and            ~C_REG_CSR_GIE, b0, b0 
        mvc             b0, csr    
     || or              a1, 3, a1  
m20?:   b               b3         
        mvc             ier, b0    
        or              b0, a1, b0 
        mvc             b0, ier    
        mvc             b1, csr    
        mvk             0, a4 
   
; ----------------------------------------------------------------------------
; Sets a maskable interrupt status.
;
; @param A4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_set:
        b               b3        
        mvk             1, a1     
        shl             a1, a4, a0
        mvc             a0, isr   
        mvk             0, a4         
        nop             1         

; ----------------------------------------------------------------------------
; Clears a maskable interrupt status.
;
; @param A4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_clear:
        b               b3        
        mvk             1, a1     
        shl             a1, a4, a0
        mvc             a0, icr   
        mvk             0, a4         
        nop             1 
          
; ----------------------------------------------------------------------------
; Jumps to interrupt HW vector.
;
; @param A4 hardware interrupt vector number.
; ----------------------------------------------------------------------------
        .text
m_jump:
        ; Interrupt disable and calc vector address
        bnop            mj?, 1
        mvc             csr, b0
     || shl             a4, 5, a4
        and             C_REG_CSR_GIE, b0, a0
     || mvkl            os_hwi - 32, b4 
        and            ~C_REG_CSR_GIE, b0, b0
     || mvkh            os_hwi - 32, b4
        mvc             b0, csr
     || add             b4, a4, a4
        ; Jump to handler
mj?:    bnop            a4, 2
        mvkl            mr?, b0
        mvkh            mr?, b0
        mvc             b0, irp
        ; Return point
mr?:    bnop            b3, 1
        mvc             csr, b0
        and            ~C_REG_CSR_GIE, b0, b0
   [a0] or              C_REG_CSR_GIE, b0, b0
        mvc             b0, csr
