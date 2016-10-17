; ----------------------------------------------------------------------------
; AM18x registers memory map.
;
; @author    Sergey Baigudin, baigudin@mail.ru
; @copyright 2016 Sergey Baigudin
; @license   http://baigudin.software/license/
; @link      http://baigudin.software
; ----------------------------------------------------------------------------
    .state32

; ----------------------------------------------------------------------------
; System Configuration Module (SYSCFG0)
;
; Start address: 0x01c14000
; End address:   0x01e14fff 
; Size:          0x00001000
; ----------------------------------------------------------------------------    
    .def REG_SYSCFG0_REVID                 
    .def REG_SYSCFG0_DIEIDR0               
    .def REG_SYSCFG0_DIEIDR1               
    .def REG_SYSCFG0_DIEIDR2               
    .def REG_SYSCFG0_DIEIDR3               
    .def REG_SYSCFG0_DEVIDR0               
    .def REG_SYSCFG0_BOOTCFG               
    .def REG_SYSCFG0_KICK0R                
    .def REG_SYSCFG0_KICK1R                
    .def REG_SYSCFG0_HOST0CFG              
    .def REG_SYSCFG0_IRAWSTAT              
    .def REG_SYSCFG0_IENSTAT               
    .def REG_SYSCFG0_IENSET                
    .def REG_SYSCFG0_IENCLR                
    .def REG_SYSCFG0_EOI                   
    .def REG_SYSCFG0_FLTADDRR              
    .def REG_SYSCFG0_FLTSTAT               
    .def REG_SYSCFG0_MSTPRI0               
    .def REG_SYSCFG0_MSTPRI1               
    .def REG_SYSCFG0_MSTPRI2               
    .def REG_SYSCFG0_PINMUX0               
    .def REG_SYSCFG0_PINMUX1               
    .def REG_SYSCFG0_PINMUX2               
    .def REG_SYSCFG0_PINMUX3               
    .def REG_SYSCFG0_PINMUX4               
    .def REG_SYSCFG0_PINMUX5               
    .def REG_SYSCFG0_PINMUX6               
    .def REG_SYSCFG0_PINMUX7               
    .def REG_SYSCFG0_PINMUX8               
    .def REG_SYSCFG0_PINMUX9               
    .def REG_SYSCFG0_PINMUX10              
    .def REG_SYSCFG0_PINMUX11              
    .def REG_SYSCFG0_PINMUX12              
    .def REG_SYSCFG0_PINMUX13              
    .def REG_SYSCFG0_PINMUX14              
    .def REG_SYSCFG0_PINMUX15              
    .def REG_SYSCFG0_PINMUX16              
    .def REG_SYSCFG0_PINMUX17              
    .def REG_SYSCFG0_PINMUX18              
    .def REG_SYSCFG0_PINMUX19              
    .def REG_SYSCFG0_SUSPSRC               
    .def REG_SYSCFG0_CHIPSIG               
    .def REG_SYSCFG0_CHIPSIG_CLR           
    .def REG_SYSCFG0_CFGCHIP0              
    .def REG_SYSCFG0_CFGCHIP1              
    .def REG_SYSCFG0_CFGCHIP2              
    .def REG_SYSCFG0_CFGCHIP3              
    .def REG_SYSCFG0_CFGCHIP4              

    .sect                ".regs_syscfg0"          
REG_SYSCFG0_REVID         .word  0
                          .space 4h
REG_SYSCFG0_DIEIDR0       .word  0
REG_SYSCFG0_DIEIDR1       .word  0
REG_SYSCFG0_DIEIDR2       .word  0
REG_SYSCFG0_DIEIDR3       .word  0
REG_SYSCFG0_DEVIDR0       .word  0
                          .space 4h
REG_SYSCFG0_BOOTCFG       .word  0
                          .space 14h
REG_SYSCFG0_KICK0R        .word  0
REG_SYSCFG0_KICK1R        .word  0
REG_SYSCFG0_HOST0CFG      .word  0
                          .space 9ch         
REG_SYSCFG0_IRAWSTAT      .word  0
REG_SYSCFG0_IENSTAT       .word  0
REG_SYSCFG0_IENSET        .word  0
REG_SYSCFG0_IENCLR        .word  0
REG_SYSCFG0_EOI           .word  0
REG_SYSCFG0_FLTADDRR      .word  0
REG_SYSCFG0_FLTSTAT       .word  0
                          .space 14h
REG_SYSCFG0_MSTPRI0       .word  0
REG_SYSCFG0_MSTPRI1       .word  0
REG_SYSCFG0_MSTPRI2       .word  0
                          .space 4h
REG_SYSCFG0_PINMUX0       .word  0
REG_SYSCFG0_PINMUX1       .word  0
REG_SYSCFG0_PINMUX2       .word  0
REG_SYSCFG0_PINMUX3       .word  0
REG_SYSCFG0_PINMUX4       .word  0
REG_SYSCFG0_PINMUX5       .word  0
REG_SYSCFG0_PINMUX6       .word  0
REG_SYSCFG0_PINMUX7       .word  0
REG_SYSCFG0_PINMUX8       .word  0
REG_SYSCFG0_PINMUX9       .word  0
REG_SYSCFG0_PINMUX10      .word  0
REG_SYSCFG0_PINMUX11      .word  0
REG_SYSCFG0_PINMUX12      .word  0
REG_SYSCFG0_PINMUX13      .word  0
REG_SYSCFG0_PINMUX14      .word  0
REG_SYSCFG0_PINMUX15      .word  0
REG_SYSCFG0_PINMUX16      .word  0
REG_SYSCFG0_PINMUX17      .word  0
REG_SYSCFG0_PINMUX18      .word  0
REG_SYSCFG0_PINMUX19      .word  0
REG_SYSCFG0_SUSPSRC       .word  0
REG_SYSCFG0_CHIPSIG       .word  0
REG_SYSCFG0_CHIPSIG_CLR   .word  0
REG_SYSCFG0_CFGCHIP0      .word  0
REG_SYSCFG0_CFGCHIP1      .word  0
REG_SYSCFG0_CFGCHIP2      .word  0
REG_SYSCFG0_CFGCHIP3      .word  0
REG_SYSCFG0_CFGCHIP4      .word  0

; ----------------------------------------------------------------------------
; System Configuration Module (SYSCFG1)
;
; Start address: 0x01e2c000
; End address:   0x01e1cfff 
; Size:          0x00001000
; ----------------------------------------------------------------------------
    .def REG_SYSCFG1_VTPIO_CTL             
    .def REG_SYSCFG1_DDR_SLEW              
    .def REG_SYSCFG1_DEEPSLEEP             
    .def REG_SYSCFG1_PUPD_ENA              
    .def REG_SYSCFG1_PUPD_SEL              
    .def REG_SYSCFG1_RXACTIVE              
    .def REG_SYSCFG1_PWRDN                 

    .sect                ".regs_syscfg1"          
REG_SYSCFG1_VTPIO_CTL     .word  0
REG_SYSCFG1_DDR_SLEW      .word  0
REG_SYSCFG1_DEEPSLEEP     .word  0
REG_SYSCFG1_PUPD_ENA      .word  0
REG_SYSCFG1_PUPD_SEL      .word  0
REG_SYSCFG1_RXACTIVE      .word  0
REG_SYSCFG1_PWRDN         .word  0

; ----------------------------------------------------------------------------
; System Timers 0-3
;         
;                Timer 0     Timer 1     Timer 2     Timer 3
; Start address: 0x01c20000  0x01c21000  0x01f0c000  0x01f0d000
; End address:   0x01c20fff  0x01c21fff  0x01f0cfff  0x01f0dfff
; Size:          0x00001000  0x00001000  0x00001000  0x00001000
; ----------------------------------------------------------------------------
    .eval   0, i
    .loop   4   
           
    .def REG_TIMER:i:_ID                    
    .def REG_TIMER:i:_EMUMGT                
    .def REG_TIMER:i:_GPINTGPEN             
    .def REG_TIMER:i:_GPDATGPDIR            
    .def REG_TIMER:i:_TIM12                 
    .def REG_TIMER:i:_TIM34                 
    .def REG_TIMER:i:_PRD12                 
    .def REG_TIMER:i:_PRD34                 
    .def REG_TIMER:i:_TCR                   
    .def REG_TIMER:i:_TGCR                  
    .def REG_TIMER:i:_WDTCR                 
    .def REG_TIMER:i:_REL12                 
    .def REG_TIMER:i:_REL34                 
    .def REG_TIMER:i:_CAP12                 
    .def REG_TIMER:i:_CAP34                 
    .def REG_TIMER:i:_INTCTLSTAT            
    .def REG_TIMER:i:_CMP0                  
    .def REG_TIMER:i:_CMP1                  
    .def REG_TIMER:i:_CMP2                  
    .def REG_TIMER:i:_CMP3                  
    .def REG_TIMER:i:_CMP4                  
    .def REG_TIMER:i:_CMP5                  
    .def REG_TIMER:i:_CMP6                  
    .def REG_TIMER:i:_CMP7                  
          
    .sect                ".regs_timer:i:"          
REG_TIMER:i:_ID           .word  0
REG_TIMER:i:_EMUMGT       .word  0
REG_TIMER:i:_GPINTGPEN    .word  0
REG_TIMER:i:_GPDATGPDIR   .word  0
REG_TIMER:i:_TIM12        .word  0
REG_TIMER:i:_TIM34        .word  0
REG_TIMER:i:_PRD12        .word  0
REG_TIMER:i:_PRD34        .word  0
REG_TIMER:i:_TCR          .word  0
REG_TIMER:i:_TGCR         .word  0
REG_TIMER:i:_WDTCR        .word  0
                          .space 0x08
REG_TIMER:i:_REL12        .word  0
REG_TIMER:i:_REL34        .word  0
REG_TIMER:i:_CAP12        .word  0
REG_TIMER:i:_CAP34        .word  0
REG_TIMER:i:_INTCTLSTAT   .word  0
                          .space 0x18
REG_TIMER:i:_CMP0         .word  0
REG_TIMER:i:_CMP1         .word  0
REG_TIMER:i:_CMP2         .word  0
REG_TIMER:i:_CMP3         .word  0
REG_TIMER:i:_CMP4         .word  0
REG_TIMER:i:_CMP5         .word  0
REG_TIMER:i:_CMP6         .word  0
REG_TIMER:i:_CMP7         .word  0

          .eval   i+1, i
          .endloop
   
; ----------------------------------------------------------------------------
; Phase-Locked Loop Controller (PLLC0)
;
; Start address: 0x01c11000
; End address:   0x01c11fff 
; Size:          0x00001000
; ----------------------------------------------------------------------------
    .def REG_PLLC0_REVID  
    .def REG_PLLC0_RSTYPE 
    .def REG_PLLC0_RSCTRL 
    .def REG_PLLC0_PLLCTL 
    .def REG_PLLC0_OCSEL  
    .def REG_PLLC0_PLLM   
    .def REG_PLLC0_PREDIV 
    .def REG_PLLC0_PLLDIV1
    .def REG_PLLC0_PLLDIV2
    .def REG_PLLC0_PLLDIV3
    .def REG_PLLC0_OSCDIV 
    .def REG_PLLC0_POSTDIV
    .def REG_PLLC0_PLLCMD 
    .def REG_PLLC0_PLLSTAT
    .def REG_PLLC0_ALNCTL 
    .def REG_PLLC0_DCHANGE
    .def REG_PLLC0_CKEN   
    .def REG_PLLC0_CKSTAT 
    .def REG_PLLC0_SYSTAT 
    .def REG_PLLC0_PLLDIV4
    .def REG_PLLC0_PLLDIV5
    .def REG_PLLC0_PLLDIV6
    .def REG_PLLC0_PLLDIV7
    .def REG_PLLC0_EMUCNT0
    .def REG_PLLC0_EMUCNT1

    .sect                ".regs_pllc0"
REG_PLLC0_REVID           .word  0
                          .space 0e0h
REG_PLLC0_RSTYPE          .word  0
REG_PLLC0_RSCTRL          .word  0
                          .space 14h
REG_PLLC0_PLLCTL          .word  0
REG_PLLC0_OCSEL           .word  0
                          .space 8h
REG_PLLC0_PLLM            .word  0
REG_PLLC0_PREDIV          .word  0
REG_PLLC0_PLLDIV1         .word  0
REG_PLLC0_PLLDIV2         .word  0
REG_PLLC0_PLLDIV3         .word  0
REG_PLLC0_OSCDIV          .word  0
REG_PLLC0_POSTDIV         .word  0
                          .space 0ch
REG_PLLC0_PLLCMD          .word  0
REG_PLLC0_PLLSTAT         .word  0
REG_PLLC0_ALNCTL          .word  0
REG_PLLC0_DCHANGE         .word  0
REG_PLLC0_CKEN            .word  0
REG_PLLC0_CKSTAT          .word  0
REG_PLLC0_SYSTAT          .word  0
                          .space 0ch
REG_PLLC0_PLLDIV4         .word  0
REG_PLLC0_PLLDIV5         .word  0
REG_PLLC0_PLLDIV6         .word  0
REG_PLLC0_PLLDIV7         .word  0
                          .space 80h
REG_PLLC0_EMUCNT0         .word  0
REG_PLLC0_EMUCNT1         .word  0

; ----------------------------------------------------------------------------
; Phase-Locked Loop Controller (PLLC1)
;
; Start address: 0x01e1a000
; End address:   0x01e1afff 
; Size:          0x00001000
; ----------------------------------------------------------------------------
    .def REG_PLLC1_REVID  
    .def REG_PLLC1_PLLCTL 
    .def REG_PLLC1_OCSEL  
    .def REG_PLLC1_PLLM   
    .def REG_PLLC1_PLLDIV1
    .def REG_PLLC1_PLLDIV2
    .def REG_PLLC1_PLLDIV3
    .def REG_PLLC1_OSCDIV 
    .def REG_PLLC1_POSTDIV
    .def REG_PLLC1_PLLCMD 
    .def REG_PLLC1_PLLSTAT
    .def REG_PLLC1_ALNCTL 
    .def REG_PLLC1_DCHANGE
    .def REG_PLLC1_CKEN   
    .def REG_PLLC1_CKSTAT 
    .def REG_PLLC1_SYSTAT 
    .def REG_PLLC1_EMUCNT0
    .def REG_PLLC1_EMUCNT1
    .sect                ".regs_pllc1"
REG_PLLC1_REVID           .word  0
                          .space 0fch
REG_PLLC1_PLLCTL          .word  0
REG_PLLC1_OCSEL           .word  0
                          .space 8h
REG_PLLC1_PLLM            .word  0
                          .space 4h
REG_PLLC1_PLLDIV1         .word  0
REG_PLLC1_PLLDIV2         .word  0
REG_PLLC1_PLLDIV3         .word  0
REG_PLLC1_OSCDIV          .word  0
REG_PLLC1_POSTDIV         .word  0
                          .space 0ch
REG_PLLC1_PLLCMD          .word  0
REG_PLLC1_PLLSTAT         .word  0
REG_PLLC1_ALNCTL          .word  0
REG_PLLC1_DCHANGE         .word  0
REG_PLLC1_CKEN            .word  0
REG_PLLC1_CKSTAT          .word  0
REG_PLLC1_SYSTAT          .word  0
                          .space 9ch
REG_PLLC1_EMUCNT0         .word  0
REG_PLLC1_EMUCNT1         .word  0    
    
; ----------------------------------------------------------------------------
; DDR2/mDDR Memory Controller
;
; Start address: 0xb0000000
; End address:   0xb0007fff 
; Size:          0x00008000
; ----------------------------------------------------------------------------
    .def REG_DDR_REVID              
    .def REG_DDR_SDRSTAT            
    .def REG_DDR_SDCR               
    .def REG_DDR_SDRCR              
    .def REG_DDR_SDTIMR1            
    .def REG_DDR_SDTIMR2            
    .def REG_DDR_SDCR2              
    .def REG_DDR_PBBPR              
    .def REG_DDR_PC1                
    .def REG_DDR_PC2                
    .def REG_DDR_PCC                
    .def REG_DDR_PCMRS              
    .def REG_DDR_PCT                
    .def REG_DDR_DRPYRCR            
    .def REG_DDR_IRR                
    .def REG_DDR_IMR                
    .def REG_DDR_IMSR               
    .def REG_DDR_IMCR               
    .def REG_DDR_DRPYC1R            

    .sect                ".regs_ddr2"
REG_DDR_REVID             .word  0
REG_DDR_SDRSTAT           .word  0
REG_DDR_SDCR              .word  0
REG_DDR_SDRCR             .word  0
REG_DDR_SDTIMR1           .word  0
REG_DDR_SDTIMR2           .word  0
                          .space 04h
REG_DDR_SDCR2             .word  0
REG_DDR_PBBPR             .word  0
                          .space 1ch
REG_DDR_PC1               .word  0
REG_DDR_PC2               .word  0
REG_DDR_PCC               .word  0
REG_DDR_PCMRS             .word  0
REG_DDR_PCT               .word  0
                          .space 0ch
REG_DDR_DRPYRCR           .word  0
                          .space 5ch
REG_DDR_IRR               .word  0
REG_DDR_IMR               .word  0
REG_DDR_IMSR              .word  0
REG_DDR_IMCR              .word  0
                          .space 14h
REG_DDR_DRPYC1R           .word  0    

; ----------------------------------------------------------------------------
; ARM Interrupt Controller (AINTC)
;
; Start address: 0xfffee000
; End address:   0xfffeffff
; Size:          0x00002000
; ----------------------------------------------------------------------------
    .def REG_AINTC_REVID          
    .def REG_AINTC_CR             
    .def REG_AINTC_GER            
    .def REG_AINTC_GNLR           
    .def REG_AINTC_SISR           
    .def REG_AINTC_SICR           
    .def REG_AINTC_EISR           
    .def REG_AINTC_EICR           
    .def REG_AINTC_HIEISR
    .def REG_AINTC_HIEICR          
    .def REG_AINTC_VBR            
    .def REG_AINTC_VSR            
    .def REG_AINTC_VNR            
    .def REG_AINTC_GPIR           
    .def REG_AINTC_GPVR           
    .def REG_AINTC_SRSR1          
    .def REG_AINTC_SRSR2          
    .def REG_AINTC_SRSR3          
    .def REG_AINTC_SRSR4          
    .def REG_AINTC_SECR1          
    .def REG_AINTC_SECR2          
    .def REG_AINTC_SECR3          
    .def REG_AINTC_SECR4          
    .def REG_AINTC_ESR1           
    .def REG_AINTC_ESR2           
    .def REG_AINTC_ESR3           
    .def REG_AINTC_ESR4           
    .def REG_AINTC_ECR1           
    .def REG_AINTC_ECR2           
    .def REG_AINTC_ECR3           
    .def REG_AINTC_ECR4           
    .eval   0, i
    .loop   26 
    .def REG_AINTC_CMR:i:         
    .eval   i+1, i
    .endloop
    .def REG_AINTC_HIPIR1          
    .def REG_AINTC_HIPIR2          
    .def REG_AINTC_HINLR1          
    .def REG_AINTC_HINLR2          
    .def REG_AINTC_HIER           
    .def REG_AINTC_HIPVR1          
    .def REG_AINTC_HIPVR2          
    
    .sect                ".regs_aintc"
REG_AINTC_REVID           .word  0
REG_AINTC_CR              .word  0
                          .space 8
REG_AINTC_GER             .word  0
                          .space 8
REG_AINTC_GNLR            .word  0
REG_AINTC_SISR            .word  0
REG_AINTC_SICR            .word  0
REG_AINTC_EISR            .word  0
REG_AINTC_EICR            .word  0
                          .space 4
REG_AINTC_HIEISR          .word  0
REG_AINTC_HIEICR          .word  0
                          .space 14h
REG_AINTC_VBR             .word  0
REG_AINTC_VSR             .word  0
REG_AINTC_VNR             .word  0
                          .space 24h
REG_AINTC_GPIR            .word  0
REG_AINTC_GPVR            .word  0
                          .space 178h
REG_AINTC_SRSR1           .word  0
REG_AINTC_SRSR2           .word  0
REG_AINTC_SRSR3           .word  0
REG_AINTC_SRSR4           .word  0
                          .space 70h
REG_AINTC_SECR1           .word  0
REG_AINTC_SECR2           .word  0
REG_AINTC_SECR3           .word  0
REG_AINTC_SECR4           .word  0
                          .space 70h
REG_AINTC_ESR1            .word  0
REG_AINTC_ESR2            .word  0
REG_AINTC_ESR3            .word  0
REG_AINTC_ESR4            .word  0
                          .space 70h
REG_AINTC_ECR1            .word  0
REG_AINTC_ECR2            .word  0
REG_AINTC_ECR3            .word  0
REG_AINTC_ECR4            .word  0
                          .space 70h
          .eval   0, i
          .loop   26 
REG_AINTC_CMR:i:          .word  0
          .eval   i+1, i
          .endloop
                          .space 498h          
REG_AINTC_HIPIR1          .word  0
REG_AINTC_HIPIR2          .word  0
                          .space 7f8h
REG_AINTC_HINLR1          .word  0
REG_AINTC_HINLR2          .word  0
                          .space 3f8h
REG_AINTC_HIER            .word  0
                          .space 0fch
REG_AINTC_HIPVR1          .word  0
REG_AINTC_HIPVR2          .word  0

; ----------------------------------------------------------------------------
; Universal Serial Bus 2.0 (USB) Controller
;
; Start address: 0x01e00000
; End address:   0x01e10000
; Size:          0x00010000
; ----------------------------------------------------------------------------
    .def REG_USB20_REVID      
    .def REG_USB20_CTRLR      
    .def REG_USB20_STATR      
    .def REG_USB20_EMUR       
    .def REG_USB20_MODE       
    .def REG_USB20_AUTOREQ    
    .def REG_USB20_SRPFIXTIME 
    .def REG_USB20_TEARDOWN   
    .def REG_USB20_INTSRCR    
    .def REG_USB20_INTSETR    
    .def REG_USB20_INTCLRR    
    .def REG_USB20_INTMSKR    
    .def REG_USB20_INTMSKSETR 
    .def REG_USB20_INTMSKCLRR 
    .def REG_USB20_INTMASKEDR 
    .def REG_USB20_EOIR       
    .def REG_USB20_GENRNDISSZ1
    .def REG_USB20_GENRNDISSZ2
    .def REG_USB20_GENRNDISSZ3
    .def REG_USB20_GENRNDISSZ4
    ; Common USB Registers
    .def REG_USB20_FADDR   
    .def REG_USB20_POWER   
    .def REG_USB20_INTRTX  
    .def REG_USB20_INTRRX  
    .def REG_USB20_INTRTXE 
    .def REG_USB20_INTRRXE 
    .def REG_USB20_INTRUSB 
    .def REG_USB20_INTRUSBE
    .def REG_USB20_FRAME   
    .def REG_USB20_INDEX   
    .def REG_USB20_TESTMODE
    ; Indexed Registers
    .def REG_USB20_INDX_TXMAXP         
    .def REG_USB20_INDX_PERI_CSR0      
    .def REG_USB20_INDX_HOST_CSR0      
    .def REG_USB20_INDX_PERI_TXCSR     
    .def REG_USB20_INDX_HOST_TXCSR     
    .def REG_USB20_INDX_RXMAXP         
    .def REG_USB20_INDX_PERI_RXCSR     
    .def REG_USB20_INDX_HOST_RXCSR     
    .def REG_USB20_INDX_COUNT0         
    .def REG_USB20_INDX_RXCOUNT        
    .def REG_USB20_INDX_HOST_TYPE0     
    .def REG_USB20_INDX_HOST_TXTYPE    
    .def REG_USB20_INDX_HOST_NAKLIMIT0 
    .def REG_USB20_INDX_HOST_TXINTERVAL
    .def REG_USB20_INDX_HOST_RXTYPE    
    .def REG_USB20_INDX_HOST_RXINTERVAL
    .def REG_USB20_INDX_CONFIGDATA     
    ; FIFO
    .def REG_USB20_FIFO0
    .def REG_USB20_FIFO1
    .def REG_USB20_FIFO2
    .def REG_USB20_FIFO3
    .def REG_USB20_FIFO4
    ; OTG Device Control
    .def REG_USB_DEVCTL
    ; Dynamic FIFO Control
    .def REG_USB20_TXFIFOSZ
    .def REG_USB20_RXFIFOSZ
    .def REG_USB20_TXFIFOADDR
    .def REG_USB20_RXFIFOADDR
    .def REG_USB20_HWVERS
    ; Target Endpoint 0-4 Control Registers
    .eval  0, i
    .loop  5 
    .def REG_USB20_TXFUNCADDR:i:
    .def REG_USB20_TXHUBADDR:i: 
    .def REG_USB20_TXHUBPORT:i: 
    .def REG_USB20_RXFUNCADDR:i:
    .def REG_USB20_RXHUBADDR:i: 
    .def REG_USB20_RXHUBPORT:i: 
    .eval   i+1, i
    .endloop
    ; Control and Status Register for Endpoint 0 
    .def REG_USB20_PERI_CSR0
    .def REG_USB20_HOST_CSR0     
    .def REG_USB20_COUNT0        
    .def REG_USB20_HOST_TYPE0    
    .def REG_USB20_HOST_NAKLIMIT0
    .def REG_USB20_CONFIGDATA0   
    ; Control and Status Register for Endpoint 1-4
    .eval  1, i
    .loop  4 
    .def REG_USB20_TXMAXP:i:         
    .def REG_USB20_PERI_TXCSR:i:     
    .def REG_USB20_HOST_TXCSR:i:     
    .def REG_USB20_RXMAXP:i:         
    .def REG_USB20_PERI_RXCSR:i:     
    .def REG_USB20_HOST_RXCSR:i:     
    .def REG_USB20_RXCOUNT:i:        
    .def REG_USB20_HOST_TXTYPE:i:    
    .def REG_USB20_HOST_TXINTERVAL:i:
    .def REG_USB20_HOST_RXTYPE:i:    
    .def REG_USB20_HOST_RXINTERVAL:i:
    .eval   i+1, i
    .endloop
    ; CDMA Registers
    .def REG_USB20_DMAREVID
    .def REG_USB20_TDFDQ   
    .def REG_USB20_DMAEMU  
    .eval  0, i
    .loop  4 
    .def REG_USB20_TXGCR:i:  
    .def REG_USB20_RXGCR:i:  
    .def REG_USB20_RXHPCRA:i:
    .def REG_USB20_RXHPCRB:i:
    .eval   i+1, i
    .endloop
    .def REG_USB20_DMA_SCHED_CTRL
    .def REG_USB20_WORD
    ; Queue Manager (QMGR) Registers
    .def REG_USB20_QMGRREVID  
    .def REG_USB20_DIVERSION  
    .def REG_USB20_FDBSC0     
    .def REG_USB20_FDBSC1     
    .def REG_USB20_FDBSC2     
    .def REG_USB20_FDBSC3     
    .def REG_USB20_LRAM0BASE  
    .def REG_USB20_LRAM0SIZE  
    .def REG_USB20_LRAM1BASE  
    .def REG_USB20_PEND0      
    .def REG_USB20_PEND1      
    .def REG_USB20_QMEMRBASE_R
    .def REG_USB20_QMEMRCTRL_R
    .def REG_USB20_CTRLD_N    
    .def REG_USB20_QSTATA_N   
    .def REG_USB20_QSTATB_N   
    .def REG_USB20_QSTATC_N   
          
;USB 2.0 Universal Serial Bus OTG Controller
    .sect                    ".regs_usb20"
REG_USB20_REVID               .word  0
REG_USB20_CTRLR               .word  0
REG_USB20_STATR               .word  0
REG_USB20_EMUR                .word  0
REG_USB20_MODE                .word  0
REG_USB20_AUTOREQ             .word  0
REG_USB20_SRPFIXTIME          .word  0
REG_USB20_TEARDOWN            .word  0
REG_USB20_INTSRCR             .word  0
REG_USB20_INTSETR             .word  0
REG_USB20_INTCLRR             .word  0
REG_USB20_INTMSKR             .word  0
REG_USB20_INTMSKSETR          .word  0
REG_USB20_INTMSKCLRR          .word  0
REG_USB20_INTMASKEDR          .word  0
REG_USB20_EOIR                .word  0
                              .space 10h
REG_USB20_GENRNDISSZ1         .word  0
REG_USB20_GENRNDISSZ2         .word  0
REG_USB20_GENRNDISSZ3         .word  0
REG_USB20_GENRNDISSZ4         .word  0
                              .space 3a0h
; Common USB Registers
REG_USB20_FADDR               .byte  0
REG_USB20_POWER               .byte  0
REG_USB20_INTRTX              .half  0
REG_USB20_INTRRX              .half  0
REG_USB20_INTRTXE             .half  0
REG_USB20_INTRRXE             .half  0
REG_USB20_INTRUSB             .byte  0
REG_USB20_INTRUSBE            .byte  0
REG_USB20_FRAME               .half  0
REG_USB20_INDEX               .byte  0
REG_USB20_TESTMODE            .byte  0

; Indexed Registers
REG_USB20_INDX_TXMAXP          .half  0
REG_USB20_INDX_PERI_CSR0         
REG_USB20_INDX_HOST_CSR0         
REG_USB20_INDX_PERI_TXCSR        
REG_USB20_INDX_HOST_TXCSR      .half  0
REG_USB20_INDX_RXMAXP          .half  0
REG_USB20_INDX_PERI_RXCSR        
REG_USB20_INDX_HOST_RXCSR      .half  0
REG_USB20_INDX_COUNT0            
REG_USB20_INDX_RXCOUNT         .half  0
REG_USB20_INDX_HOST_TYPE0        
REG_USB20_INDX_HOST_TXTYPE     .byte  0
REG_USB20_INDX_HOST_NAKLIMIT0   
REG_USB20_INDX_HOST_TXINTERVAL .byte  0
REG_USB20_INDX_HOST_RXTYPE     .byte  0
REG_USB20_INDX_HOST_RXINTERVAL .byte  0
                               .space 1
REG_USB20_INDX_CONFIGDATA      .byte  0

; FIFO
REG_USB20_FIFO0               .word  0
REG_USB20_FIFO1               .word  0
REG_USB20_FIFO2               .word  0
REG_USB20_FIFO3               .word  0
REG_USB20_FIFO4               .word  0
                              .space 2ch
; OTG Device Control
REG_USB_DEVCTL                .half  0

; Dynamic FIFO Control
REG_USB20_TXFIFOSZ            .byte  0
REG_USB20_RXFIFOSZ            .byte  0
REG_USB20_TXFIFOADDR          .half  0
REG_USB20_RXFIFOADDR          .half  0
                              .space 4h
REG_USB20_HWVERS              .half  0
                              .space 11h
; Target Endpoint 0-4 Control Registers
                              .eval  0, i
                              .loop  5 
REG_USB20_TXFUNCADDR:i:       .half  0
REG_USB20_TXHUBADDR:i:        .byte  0
REG_USB20_TXHUBPORT:i:        .byte  0
REG_USB20_RXFUNCADDR:i:       .half  0
REG_USB20_RXHUBADDR:i:        .byte  0
REG_USB20_RXHUBPORT:i:        .byte  0
                              .eval   i+1, i
                              .endloop
                              .space 59h                              
; Control and Status Register for Endpoint 0
REG_USB20_PERI_CSR0
REG_USB20_HOST_CSR0           .half  0
                              .space 4h
REG_USB20_COUNT0              .half  0
REG_USB20_HOST_TYPE0          .byte  0
REG_USB20_HOST_NAKLIMIT0      .byte  0
                              .space 3h
REG_USB20_CONFIGDATA0         .byte  0
; Control and Status Register for Endpoint 1-4
                              .eval  1, i
                              .loop  4 
REG_USB20_TXMAXP:i:           .half  0
REG_USB20_PERI_TXCSR:i:       
REG_USB20_HOST_TXCSR:i:       .half  0
REG_USB20_RXMAXP:i:           .half  0
REG_USB20_PERI_RXCSR:i:       
REG_USB20_HOST_RXCSR:i:       .half  0
REG_USB20_RXCOUNT:i:          .half  0
REG_USB20_HOST_TXTYPE:i:      .byte  0
REG_USB20_HOST_TXINTERVAL:i:  .byte  0
REG_USB20_HOST_RXTYPE:i:      .byte  0
REG_USB20_HOST_RXINTERVAL:i:  .byte  0
                              .space 2h
                              .eval   i+1, i
                              .endloop
                              .space 0ab0h
; CDMA Registers
REG_USB20_DMAREVID            .word  0
REG_USB20_TDFDQ               .word  0
REG_USB20_DMAEMU              .word  0
                              .space 7f4h
                              .eval  0, i
                              .loop  4 
REG_USB20_TXGCR:i:            .word  0
                              .space 4h
REG_USB20_RXGCR:i:            .word  0
REG_USB20_RXHPCRA:i:          .word  0
REG_USB20_RXHPCRB:i:          .word  0
                              .space 0ch
                              .eval   i+1, i
                              .endloop
                              .space 780h                              
REG_USB20_DMA_SCHED_CTRL      .word  0
                              .space 7fch                              
REG_USB20_WORD                .space 100h
                              .space 1700h
; Queue Manager (QMGR) Registers 
REG_USB20_QMGRREVID           .word  0
                              .space 4h
REG_USB20_DIVERSION           .word  0
                              .space 14h
REG_USB20_FDBSC0              .word  0
REG_USB20_FDBSC1              .word  0
REG_USB20_FDBSC2              .word  0
REG_USB20_FDBSC3              .word  0
                              .space 50h
REG_USB20_LRAM0BASE           .word  0
REG_USB20_LRAM0SIZE           .word  0
REG_USB20_LRAM1BASE           .word  0
                              .space 4h
REG_USB20_PEND0               .word  0
REG_USB20_PEND1               .word  0
                              .space 0f68h
REG_USB20_QMEMRBASE_R         .word  0
REG_USB20_QMEMRCTRL_R         .word  0
REG_USB20_CTRLD_N             .word  0
REG_USB20_QSTATA_N            .word  0
REG_USB20_QSTATB_N            .word  0
REG_USB20_QSTATC_N            .word  0

; ----------------------------------------------------------------------------
; Universal Serial Bus OHCI Host Controller
;
; Start address: 0x01e25000
; End address:   0x01e25fff
; Size:          0x00001000
; ----------------------------------------------------------------------------
    .def REG_USB11_HCREVISION                  
    .def REG_USB11_HCCONTROL                   
    .def REG_USB11_HCCOMMANDSTATUS             
    .def REG_USB11_HCINTERRUPTSTATUS           
    .def REG_USB11_HCINTERRUPTENABLE           
    .def REG_USB11_HCINTERRUPTDISABLE          
    .def REG_USB11_HCHCCA                      
    .def REG_USB11_HCPERIODCURRENTED           
    .def REG_USB11_HCCONTROLHEADED             
    .def REG_USB11_HCCONTROLCURRENTED          
    .def REG_USB11_HCBULKHEADED                
    .def REG_USB11_HCBULKCURRENTED             
    .def REG_USB11_HCDONEHEAD                  
    .def REG_USB11_HCFMINTERVAL                
    .def REG_USB11_HCFMREMAINING               
    .def REG_USB11_HCFMNUMBER                  
    .def REG_USB11_HCPERIODICSTART             
    .def REG_USB11_HCLSTHRESHOLD               
    .def REG_USB11_HCRHDESCRIPTORA             
    .def REG_USB11_HCRHDESCRIPTORB             
    .def REG_USB11_HCRHSTATUS                  
    .def REG_USB11_HCRHPORTSTATUS1             
    .def REG_USB11_HCRHPORTSTATUS2           
    
; USB 1.1 Host Controller
          .sect              ".regs_usb11"
REG_USB11_HCREVISION          .word  0
REG_USB11_HCCONTROL           .word  0
REG_USB11_HCCOMMANDSTATUS     .word  0
REG_USB11_HCINTERRUPTSTATUS   .word  0
REG_USB11_HCINTERRUPTENABLE   .word  0
REG_USB11_HCINTERRUPTDISABLE  .word  0
REG_USB11_HCHCCA              .word  0
REG_USB11_HCPERIODCURRENTED   .word  0
REG_USB11_HCCONTROLHEADED     .word  0
REG_USB11_HCCONTROLCURRENTED  .word  0
REG_USB11_HCBULKHEADED        .word  0
REG_USB11_HCBULKCURRENTED     .word  0
REG_USB11_HCDONEHEAD          .word  0
REG_USB11_HCFMINTERVAL        .word  0
REG_USB11_HCFMREMAINING       .word  0
REG_USB11_HCFMNUMBER          .word  0
REG_USB11_HCPERIODICSTART     .word  0
REG_USB11_HCLSTHRESHOLD       .word  0
REG_USB11_HCRHDESCRIPTORA     .word  0
REG_USB11_HCRHDESCRIPTORB     .word  0
REG_USB11_HCRHSTATUS          .word  0
REG_USB11_HCRHPORTSTATUS1     .word  0
REG_USB11_HCRHPORTSTATUS2     .word  0

