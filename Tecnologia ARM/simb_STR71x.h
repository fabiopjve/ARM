/*******************************************************************************

 Arquivo de definições utilizadas para o microcontrolador STR711, desenvolvi-
 do para uso com o livro:
  
  Tecnologia ARM: Microcontroladores de 32 bits

  Autor: Fábio Pereira

  ScTec Eletrônica - Automação e Projetos Especiais

  www.sctec.com.br

*******************************************************************************/

#define BIT(val) 1<<val
#define BIT0  0x00000001
#define BIT1  0x00000002
#define BIT2  0x00000004
#define BIT3  0x00000008
#define BIT4  0x00000010
#define BIT5  0x00000020
#define BIT6  0x00000040
#define BIT7  0x00000080
#define BIT8  0x00000100
#define BIT9  0x00000200
#define BIT10 0x00000400
#define BIT11 0x00000800
#define BIT12 0x00001000
#define BIT13 0x00002000
#define BIT14 0x00004000
#define BIT15 0x00008000
#define BIT16 0x00010000
#define BIT17 0x00020000
#define BIT18 0x00040000
#define BIT19 0x00080000
#define BIT20 0x00100000
#define BIT21 0x00200000
#define BIT22 0x00400000
#define BIT23 0x00800000
#define BIT24 0x01000000
#define BIT25 0x02000000
#define BIT26 0x04000000
#define BIT27 0x08000000
#define BIT28 0x10000000
#define BIT29 0x20000000
#define BIT30 0x40000000
#define BIT31 0x80000000

#define NOP() asm("MOV R0,R0")

#ifdef __GNUC__
  #define P0PC0 GPIO0->PC0
  #define P0PC1 GPIO0->PC1
  #define P0PC2 GPIO0->PC2
  #define P1PC0 GPIO1->PC0
  #define P1PC1 GPIO1->PC1
  #define P1PC2 GPIO1->PC2
#endif

#define CONFIG_PIN_AIN(port,pin) GPIO##port##PC0 &= ~BIT(pin); GPIO##port##PC1 &= ~BIT(pin); GPIO##port##PC2 &= ~BIT(pin)
#define CONFIG_PIN_TTLIN(port,pin) GPIO##port##PC0 |= BIT(pin); GPIO##port##PC1 &= ~BIT(pin); GPIO##port##PC2 &= ~BIT(pin)
#define CONFIG_PIN_CMOSIN(port,pin) GPIO##port##PC0 &= ~BIT(pin); GPIO##port##PC1 |= BIT(pin); GPIO##port##PC2 &= ~BIT(pin)
#define CONFIG_PIN_PULLIN(port,pin) GPIO##port##PC0 |= BIT(pin); GPIO##port##PC1 |= BIT(pin); GPIO##port##PC2 &= ~BIT(pin)
#define CONFIG_PIN_ODOUT(port,pin) GPIO##port##PC0 &= ~BIT(pin); GPIO##port##PC1 &= ~BIT(pin); GPIO##port##PC2 |= BIT(pin)
#define CONFIG_PIN_OUT(port,pin) GPIO##port##PC0 |= BIT(pin); GPIO##port##PC1 &= ~BIT(pin); GPIO##port##PC2 |= BIT(pin)
#define CONFIG_PIN_ODALT(port,pin) GPIO##port##PC0 &= ~BIT(pin); GPIO##port##PC1 |= BIT(pin); GPIO##port##PC2 |= BIT(pin)
#define CONFIG_PIN_OUTALT(port,pin) GPIO##port##PC0 |= BIT(pin); GPIO##port##PC1 |= BIT(pin); GPIO##port##PC2 |= BIT(pin)
#define CONFIG_PORT_AIN(port,value) GPIO##port##PC0 &= ~value; GPIO##port##PC1 &= ~value; GPIO##port##PC2 &= ~value
#define CONFIG_PORT_TTLIN(port,value) GPIO##port##PC0 |= value; GPIO##port##PC1 &= ~value; GPIO##port##PC2 &= ~value
#define CONFIG_PORT_CMOSIN(port,value) GPIO##port##PC0 &= ~value; GPIO##port##PC1 |= value; GPIO##port##PC2 &= ~value
#define CONFIG_PORT_PULLIN(port,value) GPIO##port##PC0 |= value; GPIO##port##PC1 |= value; GPIO##port##PC2 &= ~value
#define CONFIG_PORT_ODOUT(port,value) GPIO##port##PC0 &= ~value; GPIO##port##PC1 &= ~value; GPIO##port##PC2 |= value
#define CONFIG_PORT_OUT(port,value) GPIO##port##PC0 |= value; GPIO##port##PC1 &= ~value; GPIO##port##PC2 |= value
#define CONFIG_PORT_ODALT(port,value) GPIO##port##PC0 &= ~value; GPIO##port##PC1 |= value; GPIO##port##PC2 |= value
#define CONFIG_PORT_OUTALT(port,value) GPIO##port##PC0 |= value; GPIO##port##PC1 |= value; GPIO##port##PC2 |= value

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de suporte à CPU - RCCU e PCU

********************************************************************************
********************************************************************************
*******************************************************************************/

#define bEN_HALT    BIT11
#define bEN_STOP    BIT10
#define bEN_CK2_16  BIT9
#define bEN_CKAF    BIT8
#define bEN_LOCK    BIT7
#define bSRESEN     BIT3
#define bCKAF_SEL   BIT2
#define bWFI_CKSEL  BIT1
#define bLPOWFI     BIT0

#define bDIV2       BIT15
#define bSTOP_I     BIT14
#define bCK2_16_I   BIT13
#define bCKAF_I     BIT12
#define bLOCK_I     BIT11
#define bWKP_RES    BIT10
#define bLVD_RES    BIT9
#define bRTC_ALARM  BIT7
#define bWDG_RES    BIT6
#define bSOFTRES    BIT5
#define bCKSTOP_EN  BIT4
#define bCK2_16     BIT3
#define bCKAF_ST    BIT2
#define bLOCK       BIT1
#define bCSU_CKSEL  BIT0
#define RCLK_CLK2_DIV16 0
#define RCLK_CLK2       bCK2_16
#define RCLK_PLL1       bCK2_16 + bCSU_CKSEL

#define bFREEN      BIT7
#define bFREF_RANGE BIT6
#define bMX1        BIT5
#define bMX0        BIT4
#define bDX2        BIT2
#define bDX1        BIT1
#define bDX0        BIT0
#define CLOCK2x12   bMX0
#define CLOCK2x16   bMX1 + bMX0
#define CLOCK2x20   0
#define CLOCK2x24   bMX1
#define CLOCK2x28   bMX1
#define PLLCLOCK_DIV_1 0
#define PLLCLOCK_DIV_2 1
#define PLLCLOCK_DIV_3 2
#define PLLCLOCK_DIV_4 3
#define PLLCLOCK_DIV_5 4
#define PLLCLOCK_DIV_6 5
#define PLLCLOCK_DIV_7 6
#define PLLOFF 7
#define PLL1_FREE_RUNNING_125K bFREEN + bMX0 + PLLOFF
#define PLL1_FREE_RUNNING_250K bFREEN + PLLOFF
#define PLL1_FREE_RUNNING_500K bFREEN + bFREF_RANGE + PLLOFF

#define bEMI_EN   BIT2
#define bUSBCLKON BIT4

#define bHALT     BIT1
#define bWFI      BIT0

#define RCLK_DIV_1 0
#define RCLK_DIV_2 1
#define RCLK_DIV_4 2
#define RCLK_DIV_8 3

#define PCLK2_RCLK_DIV_1  0
#define PCLK2_RCLK_DIV_2  BIT8
#define PCLK2_RCLK_DIV_4  BIT9
#define PCLK2_RCLK_DIV_8  BIT8 + BIT9
#define PCLK1_RCLK_DIV_1  0
#define PCLK1_RCLK_DIV_2  1
#define PCLK1_RCLK_DIV_4  2
#define PCLK1_RCLK_DIV_8  3

#define bEMIRST   BIT2

#define bPLL2LOCK   BIT15
#define bIRQPEND    BIT10
#define bIRQMASK    BIT9
#define bUSBEN      BIT8
#define bPLLEN      BIT7
#define bFRQRNG     BIT6

#define bPKG64      BIT9
#define bHDLC       BIT7
#define bCAN        BIT6
#define bADCEN      BIT5
#define bLPOWDBGEN  BIT4
#define bUSBFILTEN  BIT3
#define bSPI0EN     BIT2
#define bBOOT1      BIT1
#define bBOOT0      BIT0
#define BOOT_FLASH  0
#define BOOT_RAM    BIT1
#define BOOT_EXT    BIT1+BIT0

#define bWREN       BIT15
#define bBUSY       BIT14
#define bWKUP_ALRM  BIT13
#define bVR_OK      BIT12
#define bFLASH_LP   BIT9
#define bLVD_DIS    BIT8
#define bOSCBYP     BIT7
#define bPWRDWN     BIT6
#define bLPVRBYP    BIT5
#define bLPVRWFI    BIT4
#define bVRBYP      BIT3

#define CLOCK_4MHZx12 RCCU_PLL1CR = bFREF_RANGE + CLOCK2x24 + PLLCLOCK_DIV_2; RCCU_CFR = RCLK_PLL1

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores do controlador de interrupções - EIC

********************************************************************************
********************************************************************************
*******************************************************************************/

#define bIRQ_EN   BIT0
#define bFIQ_EN   BIT1

#define bFIE0   BIT0
#define bFIE1   BIT1
#define bFIP0   BIT2
#define bFIP1   BIT3

#define bIRQ0   BIT0
#define bIRQ1   BIT1
#define bIRQ2   BIT2
#define bIRQ3   BIT3
#define bIRQ4   BIT4
#define bIRQ5   BIT5
#define bIRQ6   BIT6
#define bIRQ7   BIT7
#define bIRQ8   BIT8
#define bIRQ9   BIT9
#define bIRQ10  BIT10
#define bIRQ11  BIT11
#define bIRQ12  BIT12
#define bIRQ13  BIT13
#define bIRQ14  BIT14
#define bIRQ15  BIT15
#define bIRQ16  BIT16
#define bIRQ17  BIT17
#define bIRQ18  BIT18
#define bIRQ19  BIT19
#define bIRQ20  BIT20
#define bIRQ21  BIT21
#define bIRQ22  BIT22
#define bIRQ23  BIT23
#define bIRQ24  BIT24
#define bIRQ25  BIT25
#define bIRQ26  BIT26
#define bIRQ27  BIT27
#define bIRQ28  BIT28
#define bIRQ29  BIT29
#define bIRQ30  BIT30
#define bIRQ31  BIT31

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores do módulo de interrupção externa - XTI

********************************************************************************
********************************************************************************
*******************************************************************************/

#define bWKUP_INT BIT0
#define bID1S BIT1
#define bSTOP BIT2

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de controle das pontes APB1 e APB2

********************************************************************************
********************************************************************************
*******************************************************************************/

#define bI2C0_RES     BIT0
#define bI2C1_RES     BIT1
#define bUART0_RES    BIT3
#define bUART1_RES    BIT4
#define bUART2_RES    BIT5
#define bUART3_RES    BIT6
#define bUSB_RES      BIT7
#define bCAN_RES      BIT8
#define bSPI0_RES     BIT9
#define bSPI1_RES     BIT10
#define bHDLC_RES     BIT13

#define bI2C0_CKDIS     BIT0
#define bI2C1_CKDIS     BIT1
#define bUART0_CKDIS    BIT3
#define bUART1_CKDIS    BIT4
#define bUART2_CKDIS    BIT5
#define bUART3_CKDIS    BIT6
#define bUSB_CKDIS      BIT7
#define bCAN_CKDIS      BIT8
#define bSPI0_CKDIS     BIT9
#define bSPI1_CKDIS     BIT10
#define bHDLC_CKDIS     BIT13

#define bXTI_RES    BIT0
#define bPORT0_RES  BIT2
#define bPORT1_RES  BIT3
#define bPORT2_RES  BIT4
#define bADC_RES    BIT6
#define bCKOUT_RES  BIT7
#define bTIMER0_RES BIT8
#define bTIMER1_RES BIT9
#define bTIMER2_RES BIT10
#define bTIMER3_RES BIT11
#define bRTC_RES    BIT12
#define b_WDG_RES   BIT13
#define bEIC_RES    BIT14

#define bXTI_CKDIS    BIT0
#define bPORT0_CKDIS  BIT2
#define bPORT1_CKDIS  BIT3
#define bPORT2_CKDIS  BIT4
#define bADC_CKDIS    BIT6
#define bCKOUT_CKDIS  BIT7
#define bTIMER0_CKDIS BIT8
#define bTIMER1_CKDIS BIT9
#define bTIMER2_CKDIS BIT10
#define bTIMER3_CKDIS BIT11
#define bRTC_CKDIS    BIT12
#define bWDG_CKDIS    BIT13
#define bEIC_CKDIS    BIT14

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de controle do RTC

********************************************************************************
********************************************************************************
*******************************************************************************/

#define bSEN    BIT0
#define bAEN    BIT1
#define bOWEN   BIT2
#define bGEN    BIT3

#define bSIR    BIT0
#define bAIR    BIT1
#define bOWIR   BIT2
#define bGIR    BIT3
#define bCNF    BIT4
#define bRTOFF  BIT5

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de controle dos Timers 0, 1, 2 e 3

********************************************************************************
********************************************************************************
*******************************************************************************/

#define bEN     BIT15
#define bPWMI   BIT14
#define bFOLVB  BIT11
#define bFOLVA  BIT10
#define bOLVLB  BIT9
#define bOLVLA  BIT8
#define bOCBE   BIT7
#define bOCAE   BIT6
#define bOPM    BIT5
#define bPWM    BIT4
#define bIEDGB  BIT3
#define bIEDGA  BIT2
#define bEXEDG  BIT1
#define bECKEN  BIT0

#define bICAIE  BIT15
#define bOCAIE  BIT14
#define bTOIE   BIT13
#define bICBIE  BIT12
#define bOCBIE  BIT11

#define bICFA   BIT15
#define bOCFA   BIT14
#define bTOF    BIT13
#define bICFB   BIT12
#define bOCFB   BIT11

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de controle das UARTs 0, 1, 2 e 3

********************************************************************************
********************************************************************************
*******************************************************************************/

#define bFIFOEN         BIT10
#define bSCEN           BIT9
#define bRXEN           BIT8
#define bRUN            BIT7
#define bLOOP           BIT6
#define bPARITY         BIT5
#define bUART_0_5STOP   0
#define bUART_1STOP     BIT3
#define bUART_1_5STOP   BIT4
#define bUART_2STOP     BIT4+BIT3
#define bUART_8BIT      BIT0
#define bUART_7BIT_PAR  BIT0+BIT1
#define bUART_9BIT      BIT2
#define bUART_8BIT_ADD  BIT2+BIT0
#define bUART_8BIT_PAR  7

#define bRXBHFIE        BIT8
#define bTOIDLEIE       BIT7
#define bTONEIE         BIT6
#define bOEIE           BIT5
#define bFEIE           BIT4
#define bPEIE           BIT3
#define bTXBHEIE        BIT2
#define bTXBEIE         BIT1
#define bRXBNEIE        BIT0

#define bTXBF           BIT9
#define bRXBHF          BIT8
#define bTOIDLE         BIT7
#define bTONE           BIT6
#define bOERR           BIT5
#define bFRERR          BIT4
#define bPARERR         BIT3
#define bTXBHE          BIT2
#define bTXBE           BIT1
#define bRXBNE          BIT0

#define bFRAMERR        BIT9

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de controle das interfaces BSPI0 e BSPI1

********************************************************************************
********************************************************************************
*******************************************************************************/

#define SPI_RXFIFO_1W   0
#define SPI_RXFIFO_2W   BIT12
#define SPI_RXFIFO_3W   BIT13
#define SPI_RXFIFO_4W   BIT13+BIT12
#define SPI_RXFIFO_5W   BIT14
#define SPI_RXFIFO_6W   BIT14+BIT12
#define SPI_RXFIFO_7W   BIT14+BIT13
#define SPI_RXFIFO_8W   BIT14+BIT13+BIT12
#define SPI_RXFIFO_9W   BIT15
#define SPI_RXFIFO_10W  BIT15+BIT12
#define SPI_8BITS       0
#define SPI_16BITS      BIT10
#define bCPHA           BIT9
#define bCPOL           BIT8
#define bBEIE           BIT7
#define bREIE           BIT4
#define SPI_INT_RXFNE   BIT2
#define SPI_INT_RXFF    BIT3+BIT2
#define bMSTR           BIT1
#define bBSPE           BIT0

#define SPI_INT_TXFE    BIT14
#define SPI_INT_TXFU    BIT15
#define SPI_INT_TXF     BIT15+BIT14
#define SPI_TXFIFO_1W   0
#define SPI_TXFIFO_2W   BIT10
#define SPI_TXFIFO_3W   BIT11
#define SPI_TXFIFO_4W   BIT11+BIT10
#define SPI_TXFIFO_5W   BIT12
#define SPI_TXFIFO_6W   BIT12+BIT10
#define SPI_TXFIFO_7W   BIT12+BIT11
#define SPI_TXFIFO_8W   BIT12+BIT11+BIT10
#define SPI_TXFIFO_9W   BIT13
#define SPI_TXFIFO_10W  BIT13+BIT10
#define bTFNE           BIT9
#define bTFF            BIT8
#define bTUFL           BIT7
#define bTFE            BIT6
#define bROFL           BIT5
#define bRFF            BIT4
#define bRFNE           BIT3
#define bSPI_BERR       BIT2
#define bDFIFO          BIT0

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de controle das interfaces I2C0 e I2C1

********************************************************************************
********************************************************************************
*******************************************************************************/

#define bPE         BIT5
#define bENGC       BIT4
#define bSENDSTART  BIT3
#define bACK        BIT2
#define bSENDSTOP   BIT1
#define bITE        BIT0

#define bEVF      BIT7
#define bADD10    BIT6
#define bTRA      BIT5
#define bI2CBUSY  BIT4
#define bBTF      BIT3
#define bADSL     BIT2
#define bMSL      BIT1
#define bSB       BIT0

#define bENDAD  BIT5
#define bAF     BIT4
#define bSTOPF  BIT3
#define bARLO   BIT2
#define bBERR   BIT1
#define bGCAL   BIT0

#define bFM     BIT7

#define bFR2    BIT7
#define bFR1    BIT6
#define bFR0    BIT5

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de controle do ADC12

********************************************************************************
********************************************************************************
*******************************************************************************/

#define bADCOR        BIT13
#define bADCIE3       BIT11
#define bADCIE2       BIT10
#define bADCIE1       BIT9
#define bADCIE0       BIT8
#define bAXT          BIT6
#define bA1           BIT5
#define bA0           BIT4
#define bADC_DA3      BIT3
#define bADC_DA2      BIT2
#define bADC_DA1      BIT1
#define bADC_DA0      BIT0
#define bSINGLE_CHAN  bAXT
#define bADC_CH0      0
#define bADC_CH1      bA0
#define bADC_CH2      bA1
#define bADC_CH3      bA1+bA0

/*******************************************************************************
********************************************************************************
********************************************************************************

 Símbolos do controlador da FLASH

********************************************************************************
********************************************************************************
*******************************************************************************/

#define bWMS        BIT31
#define bSUSP       BIT30
#define bWPG        BIT29
#define bDWPG       BIT28
#define bSER        BIT27
#define bSPR        BIT24
#define bINTM       BIT21
#define bINTP       BIT20
#define bPWD        BIT15
#define bFLOCK      BIT4
#define bBSY1       BIT2
#define bBSY0       BIT1

#define bB1S        BIT25
#define bB0S        BIT24
#define bB1F1       BIT17
#define bB1F0       BIT16
#define bB0F7       BIT7
#define bB0F6       BIT6
#define bB0F5       BIT5
#define bB0F4       BIT4
#define bB0F3       BIT3
#define bB0F2       BIT2
#define bB0F1       BIT1
#define bB0F0       BIT0

#define bWPF        BIT8
#define bRESER      BIT7
#define bSEQER      BIT6
#define b10ER       BIT3
#define bPGER       BIT2
#define bERER       BIT1
#define bERR        BIT0

#define bW1P1       BIT17
#define bW1P0       BIT16
#define bW0P7       BIT7
#define bW0P6       BIT6
#define bW0P5       BIT5
#define bW0P4       BIT4
#define bW0P3       BIT3
#define bW0P2       BIT2
#define bW0P1       BIT1
#define bW0P0       BIT0

#define bDBGP       BIT1
#define bREADOUT    BIT0

#define bPEN15      BIT31
#define bPEN14      BIT30
#define bPEN13      BIT29
#define bPEN12      BIT28
#define bPEN11      BIT27
#define bPEN10      BIT26
#define bPEN9       BIT25
#define bPEN8       BIT24
#define bPEN7       BIT23
#define bPEN6       BIT22
#define bPEN5       BIT21
#define bPEN4       BIT20
#define bPEN3       BIT19
#define bPEN2       BIT18
#define bPEN1       BIT17
#define bPEN0       BIT16
#define bPDS15      BIT15
#define bPDS14      BIT14
#define bPDS13      BIT13
#define bPDS12      BIT12
#define bPDS11      BIT11
#define bPDS10      BIT10
#define bPDS9       BIT9
#define bPDS8       BIT8
#define bPDS7       BIT7
#define bPDS6       BIT6
#define bPDS5       BIT5
#define bPDS4       BIT4
#define bPDS3       BIT3
#define bPDS2       BIT2
#define bPDS1       BIT1
#define bPDS0       BIT0

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores da interface USB

********************************************************************************
********************************************************************************
*******************************************************************************/

#define bCTRM       BIT15
#define bDOVRM      BIT14
#define bERRM       BIT13
#define bWKUPM      BIT12
#define bSUSPM      BIT11
#define bRESETM     BIT10
#define bSOFM       BIT9
#define bESOFM      BIT8
#define bRESUME     BIT4
#define bFSUSP      BIT3
#define bLPMODE     BIT2
#define bPDWN       BIT1
#define bFRES       BIT0

#define bCTR        BIT15
#define bDOVR       BIT14
#define bUSB_ERR    BIT13
#define bUSB_WKUP   BIT12
#define bUSB_SUSP   BIT11
#define bUSB_RESET  BIT10
#define bSOF        BIT9
#define bESOF       BIT8
#define bDIR        BIT4

#define bRXDP       BIT15
#define bRXDM       BIT14
#define bLCK        BIT13

#define bEF         BIT7

#define bCTR_RX     BIT15
#define bDTOG_RX    BIT14
#define bSTAT_RX1   BIT13
#define bSTAT_RX0   BIT12
#define bSETUP      BIT11
#define bEP_TYPE1   BIT10
#define bEP_TYPE0   BIT9
#define bEP_KIND    BIT8
#define bCTR_TX     BIT7
#define bDTOG_TX    BIT6
#define bSTAT_TX1   BIT5
#define bSTAT_TX0   BIT4

#define USB_RX_DISABLE    0
#define USB_RX_STALL      bSTAT_RX0
#define USB_RX_NAK        bSTAT_RX1
#define USB_RX_VALID      bSTAT_RX0 + bSTAT_RX1

#define USB_RX_VALID_TO_NAK       bSTAT_RX0
#define USB_RX_VALID_TO_STALL     bSTAT_RX1
#define USB_RX_VALID_TO_DISABLE   bSTAT_RX0 + bSTAT_RX1
#define USB_RX_NAK_TO_VALID       bSTAT_RX0
#define USB_RX_NAK_TO_STALL       bSTAT_RX0 + bSTAT_RX1
#define USB_RX_NAK_TO_DISABLE     bSTAT_RX1
#define USB_RX_STALL_TO_VALID     bSTAT_RX1
#define USB_RX_STALL_TO_NAK       bSTAT_RX0 + bSTAT_RX1
#define USB_RX_STALL_TO_DISABLE   bSTAT_RX0

#define USB_EP_BULK       0
#define USB_EP_CTRL       bEP_TYPE0
#define USB_EP_ISO        bEP_TYPE1
#define USB_EP_INT        bEP_TYPE1 + bEP_TYPE0

#define USB_EP_BULK_DOUBLE_BUFFERED bEP_KIND
#define USB_EP_STATUS_OUT bEP_KIND

#define USB_TX_DISABLE    0
#define USB_TX_STALL      bSTAT_TX0
#define USB_TX_NAK        bSTAT_TX1
#define USB_TX_VALID      bSTAT_TX0 + bSTAT_TX1

#define USB_TX_VALID_TO_NAK       bSTAT_TX0
#define USB_TX_VALID_TO_STALL     bSTAT_TX1
#define USB_TX_VALID_TO_DISABLE   bSTAT_TX0 + bSTAT_TX1
#define USB_TX_NAK_TO_VALID       bSTAT_TX0
#define USB_TX_NAK_TO_STALL       bSTAT_TX0 + bSTAT_TX1
#define USB_TX_NAK_TO_DISABLE     bSTAT_TX1
#define USB_TX_STALL_TO_VALID     bSTAT_TX1
#define USB_TX_STALL_TO_NAK       bSTAT_TX0 + bSTAT_TX1
#define USB_TX_STALL_TO_DISABLE   bSTAT_TX0

#define BLSIZE2           0
#define BLSIZE32          BIT15
#define BLSIZE32_0        BIT15
#define BLSIZE32_1        BIT31

// 2007 - ScTec
