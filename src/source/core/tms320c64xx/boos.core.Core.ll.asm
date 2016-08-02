; ----------------------------------------------------------------------------
; Core of Operation System
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2014-2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
  .include        "boos.core.register.inc"
  .include        "boos.core.macro.inc"

  .def  _c_int00
    
  .ref  os_config
  .ref  os_int_enable
  .ref  os_int_disable
  
  ; EABI 
  .if   __TI_EABI__
  
  .def  __TI_decompress_none                 
  .def  __TI_decompress_rle24            
  .def  __TI_zero_init  
  .def  initClassesLow__Q2_4core4CoreSFv
  
  .ref  start__Q2_4core4CoreSFPCQ2_4core10CoreConfig    
  .ref  __TI_STATIC_BASE
  
  .asg  __TI_STATIC_BASE, m_bss
  .asg  initClassesLow__Q2_4core4CoreSFv,             m_init_classes
  .asg  start__Q2_4core4CoreSFPCQ2_4core10CoreConfig, m_start  
  
  ; COFF ABI
  .else

  .def  _initClassesLow__Q2_4core4CoreSFv
  
  .ref  _start__Q2_4core4CoreSFPCQ2_4core10CoreConfig  
  .ref  ___bss__
  .ref  ___cinit__
  .ref  ___pinit__
  
  .asg  ___bss__,   m_bss
  .asg  ___cinit__, m_cinit
  .asg  ___pinit__, m_pinit    
  .asg  _initClassesLow__Q2_4core4CoreSFv,             m_init_classes
  .asg  _start__Q2_4core4CoreSFPCQ2_4core10CoreConfig, m_start  
  
  .endif
  
  .asg  b15, sp
  .asg  b14, dp
  .asg  a15, fp
        
  .asg  2000h, C_CORE_STACK_SIZE

m_core_stack .usect ".core", C_CORE_STACK_SIZE

; ----------------------------------------------------------------------------
; Hardware interrupts table (Part 1)
; ----------------------------------------------------------------------------
        .sect           ".reset"
os_reset:
        ; Reset interrupt vector
        b               os_reset+24
        mvc             csr, b0
        and            ~(C_REG_CSR_GIE|C_REG_CSR_PGIE), b0, b0
        mvc             b0, csr
        mvkl            os_core_init, b0
        mvkh            os_core_init, b0
        b               b0
        nop             5

; ----------------------------------------------------------------------------
; Initializes the low level core.
;
; The entry point after CPU hardware is reseted.
; ----------------------------------------------------------------------------
        .text
_c_int00:
os_core_init:
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
        call            os_int_disable
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
        ; Named section initialization
        call            os_core_init_cinit
        ; Set CPU register to zero
        .eval           0, i
        .loop           32
        mvk             0, a:i:
     || mvk             0, b:i:
        .eval           i+1, i
        .endloop
        ; Initialize OS core pointers
        mvkl            m_core_stack + C_CORE_STACK_SIZE - 8, sp
     || mvkl            os_config, a4
        mvkh            m_core_stack + C_CORE_STACK_SIZE - 8, sp
     || mvkh            os_config, a4
        mvkl            m_bss, dp
     || mvkl            0, fp
        mvkh            m_bss, dp
     || mvkl            0, fp
        ; Call hi level initialization and
        ; set core executing finish procedure as return point
        mvkl            os_core_deinit, b3
     || mvkl            m_start, a3
        mvkh            os_core_deinit, b3
     || mvkh            m_start, a3
        b               a3
        nop             5

; ----------------------------------------------------------------------------
; Finishes the core executing
; ----------------------------------------------------------------------------
        .text
os_core_deinit:
        idle
        b               os_core_deinit

; ----------------------------------------------------------------------------
; Initializes the ".cinit" constant section.
; ----------------------------------------------------------------------------
        .text
os_core_init_cinit:
        .if             __TI_EABI__
        b               b3
        nop             5        
        .else
        mvkl            m_cinit, a10
     || mvkl            0ffffffffh, b0
        mvkh            m_cinit, a10         ; A10 pointer to record
     || mvkh            0ffffffffh, b0
        xor             a10, b0, b0
  [!b0] bnop            m_cinit_return?, 5
mc_cinit_00?:
        ldw             *a10++[1], b0         ; B0 copy size
        nop             4
  [!b0] bnop            m_cinit_return?, 5
        ldw             *a10++[1], a11        ; A11 pointer to .bss
        mv              b0, a12
        and             a12, 7, a12
        mvk             8, a13
        sub             a13, a12, a12           ; A12 size shift data
        and             a12, 7, a12
mc_cinit_01?:
        ldb             *a10++[1], a13
        nop             4
        stb             a13, *a11++[1]
        sub             b0, 1, b0
        nop             1
   [b0] bnop            mc_cinit_01?, 5
        add             a10, a12, a10
        bnop            mc_cinit_00?, 5
m_cinit_return?:
        b               b3
        nop             5
        .endif

; ----------------------------------------------------------------------------
; Initializes the ".pinit" global classes section.
; ----------------------------------------------------------------------------
        .text
os_core_init_pinit:
m_init_classes:
        .if             __TI_EABI__
        b               b3
        nop             5        
        .else
        mv              b3, b10     
        mvkl            m_pinit, a10
     || mvkl            0ffffffffh, b0
        mvkh            m_pinit, a10         ; A10 pointer to record
     || mvkh            0ffffffffh, b0
        xor             a10, b0, b0
  [!b0] bnop            m_pinit_return?, 5
mc_pinit_00?:
        ldw             *a10++[1], b0
        nop             4
  [!b0] bnop            m_pinit_return?, 5
        bacc            b0
        bnop            mc_pinit_00?, 5
m_pinit_return?:
        b               b10
        nop             5
        .endif

        .if             __TI_EABI__
;-----------------------------------------------------------------------------        
__TI_decompress_none:
        b               b3
        nop             5        
    
;-----------------------------------------------------------------------------        
__TI_decompress_rle24:
        b               b3
        nop             5        
    
;-----------------------------------------------------------------------------        
__TI_zero_init
        b               b3
        nop             5        
        .endif        
            