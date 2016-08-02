; ----------------------------------------------------------------------------
; Assembler macro commands
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2014-2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
               .asg            b15, sp

; ----------------------------------------------------------------------------
; Function call
; ----------------------------------------------------------------------------
call           .macro          lable
               b               lable
mr?            addkpc          mr?+4, b3, 4
               .endm

; ----------------------------------------------------------------------------
; Function call by CPU register
; ----------------------------------------------------------------------------
bacc           .macro          ac
               b               ac
mr?            addkpc          mr?+4, b3, 4
               .endm

; ----------------------------------------------------------------------------
; Return from interrupt
; ----------------------------------------------------------------------------
rete           .macro
               b               irp
               nop             5
               .endm

; ----------------------------------------------------------------------------
; Return from function
; ----------------------------------------------------------------------------
ret            .macro      
               b               b3
               nop             5
               .endm

; ----------------------------------------------------------------------------
; Push register to stack
; ----------------------------------------------------------------------------
pushr         .macro           ac   
              stw              ac, *sp--[2]
              .endm
             
; ----------------------------------------------------------------------------
; Pop register from stack
; ----------------------------------------------------------------------------
popr          .macro           ac
              ldw              *++sp[2], ac
              nop 4
              .endm

; ----------------------------------------------------------------------------
; Restores a context.
;
; 21 cycles is restore time of context and return from interrupt by IRP.

; @param a28m is register which contain an address of A28 register data.
; @param b28m is register which contain an address of B28 register data.
; ----------------------------------------------------------------------------
restore       .macro          a28m, b28m
              ldw             *+a28m[8], a1
           || ldw             *+b28m[7], b1
              lddw            *+a28m[2], a31:a30
           || lddw            *+b28m[2], b31:b30
           || mv              a28m, a0
           || mv              b28m, b0
              lddw            *a0--[2], a29:a28
           || lddw            *b0--[2], b29:b28
              lddw            *a0--[2], a27:a26
           || lddw            *b0--[2], b27:b26
              lddw            *a0--[2], a25:a24
           || lddw            *b0--[2], b25:b24
              lddw            *a0--[2], a23:a22
           || lddw            *b0--[2], b23:b22
           || mvc             a1, amr
              lddw            *a0--[2], a21:a20
           || lddw            *b0--[2], b21:b20
           || mvc             b1, irp
              lddw            *a0--[2], a19:a18
           || lddw            *b0--[2], b19:b18
              lddw            *a0--[2], a17:a16
           || lddw            *b0--[2], b17:b16
              lddw            *a0--[2], a15:a14
           || lddw            *b0--[2], b15:b14
              lddw            *a0--[2], a13:a12
           || lddw            *b0--[2], b13:b12
              lddw            *a0--[2], a11:a10
           || lddw            *b0--[2], b11:b10
              lddw            *a0--[2], a9:a8
           || lddw            *b0--[2], b9:b8
              lddw            *a0--[2], a7:a6
           || lddw            *b0--[2], b7:b6
              lddw            *a0--[2], a5:a4
           || lddw            *b0--[2], b5:b4
              lddw            *a0--[2], a3:a2
           || lddw            *b0--[2], b3:b2
           || b               irp
              lddw            *a0--[2], a1:a0
           || lddw            *b0--[2], b1:b0
              nop             4
              .endm

