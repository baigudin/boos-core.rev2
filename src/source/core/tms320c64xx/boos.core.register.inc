; ----------------------------------------------------------------------------
; CPU core registers constants
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2014-2015 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------

; ----------------------------------------------------------------------------
; Control Status Register (CSR)
; ----------------------------------------------------------------------------
C_REG_CSR_GIE_BITMASK   .set  00000001h
C_REG_CSR_PGIE_BITMASK  .set  00000002h
C_REG_CSR_DCC_BITMASK   .set  0000001Ch
C_REG_CSR_PCC_BITMASK   .set  000000e0h
C_REG_CSR_EN_BITMASK    .set  00000100h
C_REG_CSR_SAT_BITMASK   .set  00000200h
C_REG_CSR_PWDR_BITMASK  .set  0000FC00h
C_REG_CSR_REVID_BITMASK .set  00FF0000h
C_REG_CSR_CPUID_BITMASK .set 0FF000000h

C_REG_CSR_GIE           .set  00000001h
C_REG_CSR_PGIE          .set  00000002h
C_REG_CSR_EN            .set  00000100h
C_REG_CSR_SAT           .set  00000200h

; ----------------------------------------------------------------------------
; External Memory Interface registers
; ----------------------------------------------------------------------------
DREG_EMIFA_GBLCTL       .set  01800000h
DREG_EMIFA_CECTL0       .set  01800008h
DREG_EMIFA_CECTL1       .set  01800004h
DREG_EMIFA_CECTL2       .set  01800010h
DREG_EMIFA_CECTL3       .set  01800014h
DREG_EMIFA_CESEC0       .set  01800048h
DREG_EMIFA_CESEC1       .set  01800044h
DREG_EMIFA_CESEC2       .set  01800050h
DREG_EMIFA_CESEC3       .set  01800054h
DREG_EMIFA_SDTIM        .set  0180001Ch
DREG_EMIFA_SDEXT        .set  01800020h
DREG_EMIFA_SDCTL        .set  01800018h

DREG_EMIFB_GBLCTL       .set  01A80000h
DREG_EMIFB_CECTL0       .set  01A80008h
DREG_EMIFB_CECTL1       .set  01A80004h
DREG_EMIFB_CECTL2       .set  01A80010h
DREG_EMIFB_CECTL3       .set  01A80014h
DREG_EMIFB_CESEC0       .set  01A80048h
DREG_EMIFB_CESEC1       .set  01A80044h
DREG_EMIFB_CESEC2       .set  01A80050h
DREG_EMIFB_CESEC3       .set  01A80054h
DREG_EMIFB_SDTIM        .set  01A8001Ch
DREG_EMIFB_SDEXT        .set  01A80020h
DREG_EMIFB_SDCTL        .set  01A80018h

; ----------------------------------------------------------------------------
; Cache registers
; ----------------------------------------------------------------------------
DREG_CCFG               .set  01840000h
DREG_L2ALLOC0           .set  01842000h
DREG_L2ALLOC1           .set  01842004h
DREG_L2ALLOC2           .set  01842008h
DREG_L2ALLOC3           .set  0184200Ch
DREG_L2FBAR             .set  01844000h
DREG_L2FWC              .set  01844004h
DREG_L2CBAR             .set  01844010h
DREG_L2CWC              .set  01844014h
DREG_L1PFBAR            .set  01844020h
DREG_L1PFWC             .set  01844024h
DREG_L1DFBAR            .set  01844030h
DREG_L1DFWC             .set  01844034h
DREG_L2FLUSH            .set  01845000h
DREG_L2CLEAN            .set  01845004h

; ----------------------------------------------------------------------------
; Interrupt Selector registers                                   (spru646.pdf)
; ----------------------------------------------------------------------------
DREG_MUXH               .set	019C0000h
DREG_MUXL               .set	019C0004h
DREG_EXTPOL             .set	019C0008h

; ----------------------------------------------------------------------------
; Timer registers
; ----------------------------------------------------------------------------
DREG_CTL0               .set  01940000h
DREG_PRD0               .set  01940004h
DREG_CNT0               .set  01940008h

DREG_CTL1               .set  01980000h
DREG_PRD1               .set  01980004h
DREG_CNT1               .set  01980008h

DREG_CTL2               .set  01AC0000h
DREG_PRD2               .set  01AC0004h
DREG_CNT2               .set  01AC0008h

; ----------------------------------------------------------------------------
; GPIO registers                                                 (spru584.pdf)
; ----------------------------------------------------------------------------
DREG_GPEN               .set  01B00000h
DREG_GPDIR              .set  01B00004h
DREG_GPVAL              .set  01B00008h
DREG_GPDH               .set  01B00010h
DREG_GPHM               .set  01B00014h
DREG_GPDL               .set  01B00018h
DREG_GPLM               .set  01B0001Ch
DREG_GPGC               .set  01B00020h
DREG_GPPOL              .set  01B00024h
