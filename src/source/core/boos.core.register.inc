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
C_REG_CSR_GIE_BITMASK   .set  0x00000001
C_REG_CSR_PGIE_BITMASK  .set  0x00000002
C_REG_CSR_DCC_BITMASK   .set  0x0000001C
C_REG_CSR_PCC_BITMASK   .set  0x000000E0
C_REG_CSR_EN_BITMASK    .set  0x00000100
C_REG_CSR_SAT_BITMASK   .set  0x00000200
C_REG_CSR_PWDR_BITMASK  .set  0x0000FC00
C_REG_CSR_REVID_BITMASK .set  0x00FF0000
C_REG_CSR_CPUID_BITMASK .set  0xFF000000

C_REG_CSR_GIE           .set  0x00000001
C_REG_CSR_PGIE          .set  0x00000002
C_REG_CSR_EN            .set  0x00000100
C_REG_CSR_SAT           .set  0x00000200

; ----------------------------------------------------------------------------
; External Memory Interface registers
; ----------------------------------------------------------------------------
DREG_EMIFA_GBLCTL       .set  0x01800000
DREG_EMIFA_CECTL0       .set  0x01800008
DREG_EMIFA_CECTL1       .set  0x01800004
DREG_EMIFA_CECTL2       .set  0x01800010
DREG_EMIFA_CECTL3       .set  0x01800014
DREG_EMIFA_CESEC0       .set  0x01800048
DREG_EMIFA_CESEC1       .set  0x01800044
DREG_EMIFA_CESEC2       .set  0x01800050
DREG_EMIFA_CESEC3       .set  0x01800054
DREG_EMIFA_SDTIM        .set  0x0180001C
DREG_EMIFA_SDEXT        .set  0x01800020
DREG_EMIFA_SDCTL        .set  0x01800018

DREG_EMIFB_GBLCTL       .set  0x01A80000
DREG_EMIFB_CECTL0       .set  0x01A80008
DREG_EMIFB_CECTL1       .set  0x01A80004
DREG_EMIFB_CECTL2       .set  0x01A80010
DREG_EMIFB_CECTL3       .set  0x01A80014
DREG_EMIFB_CESEC0       .set  0x01A80048
DREG_EMIFB_CESEC1       .set  0x01A80044
DREG_EMIFB_CESEC2       .set  0x01A80050
DREG_EMIFB_CESEC3       .set  0x01A80054
DREG_EMIFB_SDTIM        .set  0x01A8001C
DREG_EMIFB_SDEXT        .set  0x01A80020
DREG_EMIFB_SDCTL        .set  0x01A80018

; ----------------------------------------------------------------------------
; Cache registers
; ----------------------------------------------------------------------------
DREG_CCFG               .set  0x01840000
DREG_L2ALLOC0           .set  0x01842000
DREG_L2ALLOC1           .set  0x01842004
DREG_L2ALLOC2           .set  0x01842008
DREG_L2ALLOC3           .set  0x0184200C
DREG_L2FBAR             .set  0x01844000
DREG_L2FWC              .set  0x01844004
DREG_L2CBAR             .set  0x01844010
DREG_L2CWC              .set  0x01844014
DREG_L1PFBAR            .set  0x01844020
DREG_L1PFWC             .set  0x01844024
DREG_L1DFBAR            .set  0x01844030
DREG_L1DFWC             .set  0x01844034
DREG_L2FLUSH            .set  0x01845000
DREG_L2CLEAN            .set  0x01845004

; ----------------------------------------------------------------------------
; Interrupt Selector registers                                   (spru646.pdf)
; ----------------------------------------------------------------------------
DREG_MUXH               .set	0x019C0000
DREG_MUXL               .set	0x019C0004
DREG_EXTPOL             .set	0x019C0008

; ----------------------------------------------------------------------------
; Timer registers
; ----------------------------------------------------------------------------
DREG_CTL0               .set  0x01940000
DREG_PRD0               .set  0x01940004
DREG_CNT0               .set  0x01940008

DREG_CTL1               .set  0x01980000
DREG_PRD1               .set  0x01980004
DREG_CNT1               .set  0x01980008

DREG_CTL2               .set  0x01AC0000
DREG_PRD2               .set  0x01AC0004
DREG_CNT2               .set  0x01AC0008

; ----------------------------------------------------------------------------
; GPIO registers                                                  (spru584.pdf)
; ----------------------------------------------------------------------------
DREG_GPEN               .set  0x01B00000
DREG_GPDIR              .set  0x01B00004
DREG_GPVAL              .set  0x01B00008
DREG_GPDH               .set  0x01B00010
DREG_GPHM               .set  0x01B00014
DREG_GPDL               .set  0x01B00018
DREG_GPLM               .set  0x01B0001C
DREG_GPGC               .set  0x01B00020
DREG_GPPOL              .set  0x01B00024
