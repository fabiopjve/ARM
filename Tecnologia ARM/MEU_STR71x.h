/*******************************************************************************

 Arquivo de definições utilizadas para o microcontrolador STR711, desenvolvi-
 do para uso com o livro:
  
  Tecnologia ARM: Microcontroladores de 32 bits

  Autor: Fábio Pereira

  ScTec Eletrônica - Automação e Projetos Especiais

  www.sctec.com.br

*******************************************************************************/

#include "simb_STR71x.h"

#define RAM_BASE        0x20000000

#define FLASHR_BASE     0x40100000
#define FLASHPR_BASE    0x4010DFB0

#define EXTMEM_BASE     0x60000000
#define RCCU_BASE       0xA0000000
#define PCU_BASE        0xA0000040
#define APB1_BASE       0xC0000000
#define APB2_BASE       0xE0000000
#define EIC_BASE        0xFFFFF800

#define I2C0_BASE       (APB1_BASE + 0x1000)
#define I2C1_BASE       (APB1_BASE + 0x2000)
#define UART0_BASE      (APB1_BASE + 0x4000)
#define UART1_BASE      (APB1_BASE + 0x5000)
#define UART2_BASE      (APB1_BASE + 0x6000)
#define UART3_BASE      (APB1_BASE + 0x7000)
#define CAN_BASE        (APB1_BASE + 0x9000)
#define BSPI0_BASE      (APB1_BASE + 0xA000)
#define BSPI1_BASE      (APB1_BASE + 0xB000)
#define USB_BASE        (APB1_BASE + 0x8800)

#define XTI_BASE        (APB2_BASE + 0x1000)
#define GPIO0_BASE      (APB2_BASE + 0x3000)
#define GPIO1_BASE      (APB2_BASE + 0x4000)
#define GPIO2_BASE      (APB2_BASE + 0x5000)
#define ADC12_BASE      (APB2_BASE + 0x7000)
#define TIM0_BASE       (APB2_BASE + 0x9000)
#define TIM1_BASE       (APB2_BASE + 0xA000)
#define TIM2_BASE       (APB2_BASE + 0xB000)
#define TIM3_BASE       (APB2_BASE + 0xC000)
#define RTC_BASE        (APB2_BASE + 0xD000)
#define WDG_BASE        (APB2_BASE + 0xE000)

#define EMI_BASE        (EXTMEM_BASE + 0x0C000000)

/*******************************************************************************
********************************************************************************
********************************************************************************

 Registradores das portas de E/S GPIO

********************************************************************************
********************************************************************************
*******************************************************************************/

union uporta
{
  unsigned int full;
  struct
  {
    int bit0 : 1;
    int bit1 : 1;
    int bit2 : 1;
    int bit3 : 1;
    int bit4 : 1;
    int bit5 : 1;
    int bit6 : 1;
    int bit7 : 1;
    int bit8 : 1;
    int bit9 : 1;
    int bit10 : 1;
    int bit11 : 1;
    int bit12 : 1;
    int bit13 : 1;
    int bit14 : 1;
    int bit15 : 1;
  };
};

// Definições dos registradores módulo GPIO0
__no_init volatile unsigned long GPIO0PC0 @ GPIO0_BASE;
__no_init volatile unsigned long GPIO0PC1 @ GPIO0_BASE + 4;
__no_init volatile unsigned long GPIO0PC2 @ GPIO0_BASE + 8;
__no_init volatile union uporta GPIO0PD_bit @ GPIO0_BASE + 12;
#define GPIO0PD GPIO0PD_bit.full

// Definições dos registradores do módulo GPIO1
__no_init volatile unsigned long GPIO1PC0 @ GPIO1_BASE;
__no_init volatile unsigned long GPIO1PC1 @ GPIO1_BASE + 4;
__no_init volatile unsigned long GPIO1PC2 @ GPIO1_BASE + 8;
__no_init volatile union uporta GPIO1PD_bit @ GPIO1_BASE + 12;
#define GPIO1PD GPIO1PD_bit.full

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de suporte à CPU - RCCU e PCU

********************************************************************************
********************************************************************************
*******************************************************************************/

union urccu_ccr
{
  unsigned int full;
  struct
  {
    int LPOWFI    : 1;
    int WFI_CKSEL : 1;
    int CKAF_SEL  : 1;
    int SRESEN    : 1;
    int           : 3;
    int EN_LOCK   : 1;
    int EN_CKAF   : 1;
    int EN_CK2_16 : 1;
    int EN_STOP   : 1;
    int EN_HALT   : 1;
  };
};
__no_init volatile union urccu_ccr RCCU_CCR_bit @ RCCU_BASE;
#define RCCU_CCR    RCCU_CCR_bit.full

union urccu_cfr
{
  unsigned int full;
  struct
  {
    int CSU_CKSEL : 1;
    int LOCK      : 1;
    int CKAF_ST   : 1;
    int CK2_16    : 1;
    int CKSTOP_EN : 1;
    int SOFTRES   : 1;
    int WDG_RES   : 1;
    int RTC_ALARM : 1;
    int           : 1;
    int LVD_RES   : 1;
    int WKP_RES   : 1;
    int LOCK_I    : 1;
    int CKAF_I    : 1;
    int CK2_16_I  : 1;
    int STOP_I    : 1;
    int DIV2      : 1;
  };
};
__no_init volatile union urccu_cfr RCCU_CFR_bit @ RCCU_BASE + 8;
#define RCCU_CFR    RCCU_CFR_bit.full

union urccu_pll1cr
{
  unsigned int full;
  struct
  {
    int DX0       : 1;
    int DX1       : 1;
    int DX2       : 1;
    int           : 1;
    int MX0       : 1;
    int MX1       : 1;
    int FREF_RANGE: 1;
    int FREEN     : 1;
  };
};

__no_init volatile union urccu_pll1cr RCCU_PLL1CR_bit @ RCCU_BASE + 0x18;
#define RCCU_PLL1CR RCCU_PLL1CR_bit.full

union urccu_per
{
  unsigned int full;
  struct
  {
    int PH_CK0    : 1;
    int PH_CK1    : 1;
    int PH_CK2    : 1;
    int PH_CK3    : 1;
    int PH_CK4    : 1;
  };
};
__no_init volatile union urccu_per RCCU_PER_bit @ RCCU_BASE + 0x1C;
#define RCCU_PER RCCU_PER_bit.full

union urccu_smr
{
  unsigned int full;
  struct
  {
    int WFI       : 1;
    int HALT      : 1;
  };
};
__no_init volatile union urccu_smr RCCU_SMR_bit @ RCCU_BASE + 0x20;
#define RCCU_SMR RCCU_SMR_bit.full

union upcu_mdivr
{
  unsigned int full;
  struct
  {
    int FACT      : 2;
  };
};
__no_init volatile union upcu_mdivr PCU_MDIVR_bit @ RCCU_BASE + 0x40;
#define PCU_MDIVR PCU_MDIVR_bit.full

union upcu_pdivr
{
  unsigned int full;
  struct
  {
    int FACT1     : 2;
    int           : 6;
    int FACT2     : 2;
 };
};
__no_init volatile union upcu_pdivr PCU_PDIVR_bit @ RCCU_BASE + 0x44;
#define PCU_PDIVR PCU_PDIVR_bit.full

union upcu_prstr
{
  unsigned int full;
  struct
  {
    int           : 2;
    int EMIRST    : 1;
  };
};
__no_init volatile union upcu_prstr PCU_PRSTR_bit @ RCCU_BASE + 0x48;
#define PCU_PRSTR PCU_PRSTR_bit.full

union upcu_pll2cr
{
  unsigned int full;
  struct
  {
    int DX        : 3;
    int           : 1;
    int MX        : 2;
    int FRQRNG    : 1;
    int PLLEN     : 1;
    int USBEN     : 1;
    int IRQMASK   : 1;
    int IRQPEND   : 1;
    int           : 4;
    int LOCK      : 1;
  };
};
__no_init volatile union upcu_pll2cr PCU_PLL2CR_bit @ RCCU_BASE + 0x4C;
#define PCU_PLL2CR  PCU_PLL2CR_bit.full

union upcu_bootcr
{
  unsigned int full;
  struct
  {
    int BOOT      : 2;
    int SPI0EN    : 1;
    int USBFILTEN : 1;
    int LPOWDBGEN : 1;
    int ADCEN     : 1;
    int CAN       : 1;
    int HDLC      : 1;
    int           : 1;
    int PKG64     : 1;
  };
};
__no_init volatile union upcu_bootcr PCU_BOOTCR_bit @ RCCU_BASE + 0x50;
#define PCU_BOOTCR  PCU_BOOTCR_bit.full

union upcu_pwrcr
{
  unsigned int full;
  struct
  {
    int           : 3;
    int VRBYP     : 1;
    int LPVRWFI   : 1;
    int LPVRBYP   : 1;
    int PWRDWN    : 1;
    int OSCBYP    : 1;
    int LVD_DIS   : 1;
    int FLASH_LP  : 1;
    int VROK      : 1;
    int WKUP_ALRM : 1;
    int BUSY      : 1;
    int WREN      : 1;
  };
};
__no_init volatile union upcu_pwrcr PCU_PWRCR_bit @ RCCU_BASE + 0x54;
#define PCU_PWRCR   PCU_PWRCR_bit.full

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores do controlador de interrupções - EIC

********************************************************************************
********************************************************************************
*******************************************************************************/

union ueic_icr
{
  unsigned int full;
  struct
  {
    int IRQ_EN : 1;
    int FIQ_EN : 1;
  };
};

__no_init volatile union ueic_icr EIC_ICR_bit @ EIC_BASE;
#define EIC_ICR EIC_ICR_bit.full

union ueic_cicr
{
  unsigned int full;
  struct
  {
    int CIC : 5;
  };
};

__no_init volatile union ueic_cicr EIC_CICR_bit @ EIC_BASE + 4;
#define EIC_CICR EIC_CICR_bit.full

union ueic_cipr
{
  unsigned int full;
  struct
  {
    int CIP : 4;
  };
};

__no_init volatile union ueic_cipr EIC_CIPR_bit @ EIC_BASE + 8;
#define EIC_CIPR EIC_CIPR_bit.full

__no_init volatile long int EIC_IVR @ EIC_BASE + 0x18;

union ueic_fir
{
  unsigned int full;
  struct
  {
    int FIE0 : 1;
    int FIE1 : 1;
    int FIP0 : 1;
    int FIP1 : 1;
  };
};

__no_init volatile union ueic_fir EIC_FIR_bit @ EIC_BASE + 0x1C;
#define EIC_FIR EIC_FIR_bit.full

union u32irq
{
  unsigned int full;
  struct
  {
    int IRQ0 : 1;
    int IRQ1 : 1;
    int IRQ2 : 1;
    int IRQ3 : 1;
    int IRQ4 : 1;
    int IRQ5 : 1;
    int IRQ6 : 1;
    int IRQ7 : 1;
    int IRQ8 : 1;
    int IRQ9 : 1;
    int IRQ10 : 1;
    int IRQ11 : 1;
    int IRQ12 : 1;
    int IRQ13 : 1;
    int IRQ14 : 1;
    int IRQ15 : 1;
    int IRQ16 : 1;
    int IRQ17 : 1;
    int IRQ18 : 1;
    int IRQ19 : 1;
    int IRQ20 : 1;
    int IRQ21 : 1;
    int IRQ22 : 1;
    int IRQ23 : 1;
    int IRQ24 : 1;
    int IRQ25 : 1;
    int IRQ26 : 1;
    int IRQ27 : 1;
    int IRQ28 : 1;
    int IRQ29 : 1;
    int IRQ30 : 1;
    int IRQ31 : 1;
  };
};

__no_init volatile union u32irq EIC_IER_bit @ EIC_BASE + 0x20;
#define EIC_IER EIC_IER_bit.full

__no_init volatile union u32irq EIC_IPR_bit @ EIC_BASE + 0x40;
#define EIC_IPR EIC_IPR_bit.full

__no_init volatile long int EIC_SIR0 @ EIC_BASE + 0x60;
__no_init volatile long int EIC_SIR1 @ EIC_BASE + 0x64;
__no_init volatile long int EIC_SIR2 @ EIC_BASE + 0x68;
__no_init volatile long int EIC_SIR3 @ EIC_BASE + 0x6C;
__no_init volatile long int EIC_SIR4 @ EIC_BASE + 0x70;
__no_init volatile long int EIC_SIR5 @ EIC_BASE + 0x74;
__no_init volatile long int EIC_SIR6 @ EIC_BASE + 0x78;
__no_init volatile long int EIC_SIR7 @ EIC_BASE + 0x7C;
__no_init volatile long int EIC_SIR8 @ EIC_BASE + 0x80;
__no_init volatile long int EIC_SIR9 @ EIC_BASE + 0x84;
__no_init volatile long int EIC_SIR10 @ EIC_BASE + 0x88;
__no_init volatile long int EIC_SIR11 @ EIC_BASE + 0x8C;
__no_init volatile long int EIC_SIR12 @ EIC_BASE + 0x90;
__no_init volatile long int EIC_SIR13 @ EIC_BASE + 0x94;
__no_init volatile long int EIC_SIR14 @ EIC_BASE + 0x98;
__no_init volatile long int EIC_SIR15 @ EIC_BASE + 0x9C;
__no_init volatile long int EIC_SIR16 @ EIC_BASE + 0xA0;
__no_init volatile long int EIC_SIR17 @ EIC_BASE + 0xA4;
__no_init volatile long int EIC_SIR18 @ EIC_BASE + 0xA8;
__no_init volatile long int EIC_SIR19 @ EIC_BASE + 0xAC;
__no_init volatile long int EIC_SIR20 @ EIC_BASE + 0xB0;
__no_init volatile long int EIC_SIR21 @ EIC_BASE + 0xB4;
__no_init volatile long int EIC_SIR22 @ EIC_BASE + 0xB8;
__no_init volatile long int EIC_SIR23 @ EIC_BASE + 0xBC;
__no_init volatile long int EIC_SIR24 @ EIC_BASE + 0xC0;
__no_init volatile long int EIC_SIR25 @ EIC_BASE + 0xC4;
__no_init volatile long int EIC_SIR26 @ EIC_BASE + 0xC8;
__no_init volatile long int EIC_SIR27 @ EIC_BASE + 0xCC;
__no_init volatile long int EIC_SIR28 @ EIC_BASE + 0xD0;
__no_init volatile long int EIC_SIR29 @ EIC_BASE + 0xD4;
__no_init volatile long int EIC_SIR30 @ EIC_BASE + 0xD8;
__no_init volatile long int EIC_SIR31 @ EIC_BASE + 0xDC;

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores do módulo de interrupção externa - XTI

********************************************************************************
********************************************************************************
*******************************************************************************/

union uxti_sr
{
  unsigned int full;
  struct
  {
    int XTIS0 : 1;
    int XTIS1 : 1;
    int XTIS2 : 1;
    int XTIS3 : 1;
    int XTIS4 : 1;
    int XTIS5 : 1;
    int XTIS6 : 1;
    int XTIS7 : 1;
  };
};

__no_init volatile union uxti_sr XTI_SR_bit @ XTI_BASE + 0x1C;
#define XTI_SR XTI_SR_bit.full

union uxti_ctrl
{
  unsigned char full;
  struct
  {
    int WKUP_INT : 1;
    int ID1S : 1;
    int STOP : 1;
  };
};

__no_init volatile union uxti_ctrl XTI_CTRL_bit @ XTI_BASE + 0x24;
#define XTI_CTRL XTI_CTRL_bit.full

union uxti_mrh
{
  unsigned int full;
  struct
  {
    int XTIM8  : 1;
    int XTIM9  : 1;
    int XTIM10 : 1;
    int XTIM11 : 1;
    int XTIM12 : 1;
    int XTIM13 : 1;
    int XTIM14 : 1;
    int XTIM15 : 1;
  };
};

__no_init volatile union uxti_mrh XTI_MRH_bit @ XTI_BASE + 0x28;
#define XTI_MRH XTI_MRH_bit.full

union uxti_mrl
{
  unsigned int full;
  struct
  {
    int XTIM0 : 1;
    int XTIM1 : 1;
    int XTIM2 : 1;
    int XTIM3 : 1;
    int XTIM4 : 1;
    int XTIM5 : 1;
    int XTIM6 : 1;
    int XTIM7 : 1;
  };
};

__no_init volatile union uxti_mrl XTI_MRL_bit @ XTI_BASE + 0x28;
#define XTI_MRL XTI_MRL_bit.full

union uxti_trh
{
  unsigned int full;
  struct
  {
    int XTIT8  : 1;
    int XTIT9  : 1;
    int XTIT10 : 1;
    int XTIT11 : 1;
    int XTIT12 : 1;
    int XTIT13 : 1;
    int XTIT14 : 1;
    int XTIT15 : 1;
  };
};

__no_init volatile union uxti_trh XTI_TRH_bit @ XTI_BASE + 0x30;
#define XTI_TRH XTI_TRH_bit.full

union uxti_trl
{
  unsigned int full;
  struct
  {
    int XTIT0 : 1;
    int XTIT1 : 1;
    int XTIT2 : 1;
    int XTIT3 : 1;
    int XTIT4 : 1;
    int XTIT5 : 1;
    int XTIT6 : 1;
    int XTIT7 : 1;
  };
};

__no_init volatile union uxti_trl XTI_TRL_bit @ XTI_BASE + 0x34;
#define XTI_TRL XTI_TRL_bit.full

union uxti_prh
{
  unsigned int full;
  struct
  {
    int XTIP8  : 1;
    int XTIP9  : 1;
    int XTIP10 : 1;
    int XTIP11 : 1;
    int XTIP12 : 1;
    int XTIP13 : 1;
    int XTIP14 : 1;
    int XTIP15 : 1;
  };
};

__no_init volatile union uxti_prh XTI_PRH_bit @ XTI_BASE + 0x38;
#define XTI_PRH XTI_PRH_bit.full

union uxti_prl
{
  unsigned int full;
  struct
  {
    int XTIP0 : 1;
    int XTIP1 : 1;
    int XTIP2 : 1;
    int XTIP3 : 1;
    int XTIP4 : 1;
    int XTIP5 : 1;
    int XTIP6 : 1;
    int XTIP7 : 1;
  };
};

__no_init volatile union uxti_prl XTI_PRL_bit @ XTI_BASE + 0x3C;
#define XTI_PRL XTI_PRL_bit.full

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de controle das pontes APB1 e APB2

********************************************************************************
********************************************************************************
*******************************************************************************/

union uapb1_res
{
  unsigned int full;
  struct
  {
    int I2C0_RES  : 1;
    int I2C1_RES  : 1;
    int           : 1;
    int UART0_RES : 1;
    int UART1_RES : 1;
    int UART2_RES : 1;
    int UART3_RES : 1;
    int USB_RES   : 1;
    int CAN_RES   : 1;
    int SPI0_RES  : 1;
    int SPI1_RES  : 1;
    int           : 1;
    int           : 1;
    int HDLC_RES  : 1;
  };
};

union uapb1_ckdis
{
  unsigned int full;
  struct
  {
    int I2C0_CKDIS  : 1;
    int I2C1_CKDIS  : 1;
    int             : 1;
    int UART0_CKDIS : 1;
    int UART1_CKDIS : 1;
    int UART2_CKDIS : 1;
    int UART3_CKDIS : 1;
    int USB_CKDIS   : 1;
    int CAN_CKDIS   : 1;
    int SPI0_CKDIS  : 1;
    int SPI1_CKDIS  : 1;
    int             : 1;
    int             : 1;
    int HDLC_CKDIS  : 1;
  };
};

__no_init volatile union uapb1_ckdis APB1_CKDIS_bit @ APB1_BASE + 0x10;
#define APB1_CKDIS APB1_CKDIS_bit.full

__no_init volatile union uapb1_res APB1_SWRES_bit @ APB1_BASE + 0x14;
#define APB1_SWRES APB1_SWRES_bit.full

union uapb2_res
{
  unsigned int full;
  struct
  {
    int XTI_RES   : 1;
    int           : 1;
    int PORT0_RES : 1;
    int PORT1_RES : 1;
    int PORT2_RES : 1;
    int           : 1;
    int ADC_RES   : 1;
    int CKOUT_RES : 1;
    int TIMER0_RES: 1;
    int TIMER1_RES: 1;
    int TIMER2_RES: 1;
    int TIMER3_RES: 1;
    int RTC_RES   : 1;
    int WDG_RES   : 1;
    int EIC_RES   : 1;
  };
};

union uapb2_ckdis
{
  unsigned int full;
  struct
  {
    int XTI_CKDIS   : 1;
    int             : 1;
    int PORT0_CKDIS : 1;
    int PORT1_CKDIS : 1;
    int PORT2_CKDIS : 1;
    int             : 1;
    int ADC_CKDIS   : 1;
    int CKOUT_CKDIS : 1;
    int TIMER0_CKDIS: 1;
    int TIMER1_CKDIS: 1;
    int TIMER2_CKDIS: 1;
    int TIMER3_CKDIS: 1;
    int RTC_CKDIS   : 1;
    int WDG_CKDIS   : 1;
    int EIC_CKDIS   : 1;
  };
};

__no_init volatile union uapb2_ckdis APB2_CKDIS_bit @ APB2_BASE + 0x10;
#define APB2_CKDIS APB2_CKDIS_bit.full

__no_init volatile union uapb2_res APB2_SWRES_bit @ APB2_BASE + 0x14;
#define APB2_SWRES APB2_SWRES_bit.full

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de controle do RTC

********************************************************************************
********************************************************************************
*******************************************************************************/

union urtc_crh
{
  unsigned int full;
  struct
  {
    int SEN         : 1;
    int AEN         : 1;
    int OWEN        : 1;
    int GEN         : 1;
  };
};

__no_init volatile union urtc_crh RTC_CRH_bit @ RTC_BASE;
#define RTC_CRH RTC_CRH_bit.full

union urtc_crl
{
  unsigned int full;
  struct
  {
    int SIR         : 1;
    int AIR         : 1;
    int OWIR        : 1;
    int GIR         : 1;
    int CNF         : 1;
    int RTOFF       : 1;
  };
};

__no_init volatile union urtc_crl RTC_CRL_bit @ RTC_BASE + 4;
#define RTC_CRL RTC_CRL_bit.full

__no_init volatile int RTC_PRLH @ RTC_BASE + 0x08;
__no_init volatile int RTC_PRLL @ RTC_BASE + 0x0C;
__no_init volatile int RTC_DIVH @ RTC_BASE + 0x10;
__no_init volatile int RTC_DIVL @ RTC_BASE + 0x14;
__no_init volatile int RTC_CNTH @ RTC_BASE + 0x18;
__no_init volatile int RTC_CNTL @ RTC_BASE + 0x1C;
__no_init volatile int RTC_ALRH @ RTC_BASE + 0x20;
__no_init volatile int RTC_ALRL @ RTC_BASE + 0x24;

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de controle dos Timers 0, 1, 2 e 3

********************************************************************************
********************************************************************************
*******************************************************************************/

union utim_cr1
{
  unsigned int full;
  struct
  {
    int ECKEN       : 1;
    int EXEDG       : 1;
    int IEDGA       : 1;
    int IEDGB       : 1;
    int PWM         : 1;
    int OPM         : 1;
    int OCAE        : 1;
    int OCBE        : 1;
    int OLVLA       : 1;
    int OLVLB       : 1;
    int FOLVA       : 1;
    int FOLVB       : 1;
    int             : 2;
    int PWMI        : 1;
    int EN          : 1;
  };
};

union utim_cr2
{
  unsigned int full;
  struct
  {
    int CC          : 8;
    int             : 2;
    int OCBIE       : 1;
    int ICBIE       : 1;
    int TOIE        : 1;
    int OCAIE       : 1;
    int ICAIE       : 1;
  };
};

union utim_sr
{
  unsigned int full;
  struct
  {
    int             : 11;
    int OCFB        : 1;
    int ICFB        : 1;
    int TOF         : 1;
    int OCFA        : 1;
    int ICFA        : 1;
  };
};

// Timer 0

__no_init volatile int TIM0_ICAR @ TIM0_BASE;
__no_init volatile int TIM0_ICBR @ TIM0_BASE + 0x04;
__no_init volatile int TIM0_OCAR @ TIM0_BASE + 0x08;
__no_init volatile int TIM0_OCBR @ TIM0_BASE + 0x0C;
__no_init volatile int TIM0_CNTR @ TIM0_BASE + 0x10;
__no_init volatile union utim_cr1 TIM0_CR1_bit @ TIM0_BASE + 0x14;
#define TIM0_CR1 TIM0_CR1_bit.full
__no_init volatile union utim_cr2 TIM0_CR2_bit @ TIM0_BASE + 0x18;
#define TIM0_CR2 TIM0_CR2_bit.full
__no_init volatile union utim_sr TIM0_SR_bit @ TIM0_BASE + 0x1C;
#define TIM0_SR TIM0_SR_bit.full

// Timer 1

__no_init volatile int TIM1_ICAR @ TIM1_BASE;
__no_init volatile int TIM1_ICBR @ TIM1_BASE + 0x04;
__no_init volatile int TIM1_OCAR @ TIM1_BASE + 0x08;
__no_init volatile int TIM1_OCBR @ TIM1_BASE + 0x0C;
__no_init volatile int TIM1_CNTR @ TIM1_BASE + 0x10;
__no_init volatile union utim_cr1 TIM1_CR1_bit @ TIM1_BASE + 0x14;
#define TIM1_CR1 TIM1_CR1_bit.full
__no_init volatile union utim_cr2 TIM1_CR2_bit @ TIM1_BASE + 0x18;
#define TIM1_CR2 TIM1_CR2_bit.full
__no_init volatile union utim_sr TIM1_SR_bit @ TIM1_BASE + 0x1C;
#define TIM1_SR TIM1_SR_bit.full

// Timer 2

__no_init volatile int TIM2_ICAR @ TIM2_BASE;
__no_init volatile int TIM2_ICBR @ TIM2_BASE + 0x04;
__no_init volatile int TIM2_OCAR @ TIM2_BASE + 0x08;
__no_init volatile int TIM2_OCBR @ TIM2_BASE + 0x0C;
__no_init volatile int TIM2_CNTR @ TIM2_BASE + 0x10;
__no_init volatile union utim_cr1 TIM2_CR1_bit @ TIM2_BASE + 0x14;
#define TIM2_CR1 TIM2_CR1_bit.full
__no_init volatile union utim_cr2 TIM2_CR2_bit @ TIM2_BASE + 0x18;
#define TIM2_CR2 TIM2_CR2_bit.full
__no_init volatile union utim_sr TIM2_SR_bit @ TIM2_BASE + 0x1C;
#define TIM2_SR TIM2_SR_bit.full

// Timer 3

__no_init volatile int TIM3_ICAR @ TIM3_BASE;
__no_init volatile int TIM3_ICBR @ TIM3_BASE + 0x04;
__no_init volatile int TIM3_OCAR @ TIM3_BASE + 0x08;
__no_init volatile int TIM3_OCBR @ TIM3_BASE + 0x0C;
__no_init volatile int TIM3_CNTR @ TIM3_BASE + 0x10;
__no_init volatile union utim_cr1 TIM3_CR1_bit @ TIM3_BASE + 0x14;
#define TIM3_CR1 TIM3_CR1_bit.full
__no_init volatile union utim_cr2 TIM3_CR2_bit @ TIM3_BASE + 0x18;
#define TIM3_CR2 TIM3_CR2_bit.full
__no_init volatile union utim_sr TIM3_SR_bit @ TIM3_BASE + 0x1C;
#define TIM3_SR TIM3_SR_bit.full

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de controle das UARTs 0, 1, 2 e 3

********************************************************************************
********************************************************************************
*******************************************************************************/
union uuart_cr
{
  unsigned int full;
  struct
  {
    int MODE    : 3;
    int STOPB   : 2;
    int PARITY  : 1;
    int LOOP    : 1;
    int RUN     : 1;
    int RXEN    : 1;
    int SCEN    : 1;
    int FIFOEN  : 1;
  };
};

union uuart_ier
{
  unsigned int full;
  struct
  {
    int RXBNEIE : 1;
    int TXBEIE  : 1;
    int TXBHEIE : 1;
    int PEIE    : 1;
    int FEIE    : 1;
    int OEIE    : 1;
    int TONEIE  : 1;
    int TOIDLEIE: 1;
    int RXBHFIE : 1;
  };
};

union uuart_sr
{
  unsigned int full;
  struct
  {
    int RXBNE   : 1;
    int TXBE    : 1;
    int TXBHE   : 1;
    int PARERR  : 1;
    int FRERR   : 1;
    int OERR    : 1;
    int TONE    : 1;
    int TOIDLE  : 1;
    int RXBHF   : 1;
    int TXBF    : 1;
  };
};

__no_init volatile union uuart_cr UART0_CR_bit @ UART0_BASE + 0x0C;
#define UART0_CR UART0_CR_bit.full
__no_init volatile union uuart_ier UART0_IER_bit @ UART0_BASE + 0x10;
#define UART0_IER UART0_IER_bit.full
__no_init volatile union uuart_sr UART0_SR_bit @ UART0_BASE + 0x14;
#define UART0_SR UART0_SR_bit.full
__no_init volatile int UART0_BR @ UART0_BASE;
__no_init volatile int UART0_GTR @ UART0_BASE + 0x18;
__no_init volatile int UART0_TOR @ UART0_BASE + 0x1C;
__no_init volatile int UART0_TXBUFR @ UART0_BASE + 0x4;
__no_init volatile int UART0_RXBUFR @ UART0_BASE + 0x8;
__no_init volatile int UART0_TXRSTR @ UART0_BASE + 0x20;
__no_init volatile int UART0_RXRSTR @ UART0_BASE + 0x24;

__no_init volatile union uuart_cr UART1_CR_bit @ UART1_BASE + 0x0C;
#define UART1_CR UART1_CR_bit.full
__no_init volatile union uuart_ier UART1_IER_bit @ UART1_BASE + 0x10;
#define UART1_IER UART1_IER_bit.full
__no_init volatile union uuart_sr UART1_SR_bit @ UART1_BASE + 0x14;
#define UART1_SR UART1_SR_bit.full
__no_init volatile int UART1_BR @ UART1_BASE;
__no_init volatile int UART1_GTR @ UART1_BASE + 0x18;
__no_init volatile int UART1_TOR @ UART1_BASE + 0x1C;
__no_init volatile int UART1_TXBUFR @ UART1_BASE + 0x4;
__no_init volatile int UART1_RXBUFR @ UART1_BASE + 0x8;
__no_init volatile int UART1_TXRSTR @ UART1_BASE + 0x20;
__no_init volatile int UART1_RXRSTR @ UART1_BASE + 0x24;

__no_init volatile union uuart_cr UART2_CR_bit @ UART2_BASE + 0x0C;
#define UART2_CR UART2_CR_bit.full
__no_init volatile union uuart_ier UART2_IER_bit @ UART2_BASE + 0x10;
#define UART2_IER UART2_IER_bit.full
__no_init volatile union uuart_sr UART2_SR_bit @ UART2_BASE + 0x14;
#define UART2_SR UART2_SR_bit.full
__no_init volatile int UART2_BR @ UART2_BASE;
__no_init volatile int UART2_GTR @ UART2_BASE + 0x18;
__no_init volatile int UART2_TOR @ UART2_BASE + 0x1C;
__no_init volatile int UART2_TXBUFR @ UART2_BASE + 0x4;
__no_init volatile int UART2_RXBUFR @ UART2_BASE + 0x8;
__no_init volatile int UART2_TXRSTR @ UART2_BASE + 0x20;
__no_init volatile int UART2_RXRSTR @ UART2_BASE + 0x24;

__no_init volatile union uuart_cr UART3_CR_bit @ UART3_BASE + 0x0C;
#define UART3_CR UART3_CR_bit.full
__no_init volatile union uuart_ier UART3_IER_bit @ UART3_BASE + 0x10;
#define UART3_IER UART3_IER_bit.full
__no_init volatile union uuart_sr UART3_SR_bit @ UART3_BASE + 0x14;
#define UART3_SR UART3_SR_bit.full
__no_init volatile int UART3_BR @ UART3_BASE;
__no_init volatile int UART3_GTR @ UART3_BASE + 0x18;
__no_init volatile int UART3_TOR @ UART3_BASE + 0x1C;
__no_init volatile int UART3_TXBUFR @ UART3_BASE + 0x4;
__no_init volatile int UART3_RXBUFR @ UART3_BASE + 0x8;
__no_init volatile int UART3_TXRSTR @ UART3_BASE + 0x20;
__no_init volatile int UART3_RXRSTR @ UART3_BASE + 0x24;

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores dos controladores BSPI0 e BSPI1

********************************************************************************
********************************************************************************
*******************************************************************************/

union ubspi_csr1
{
  unsigned int full;
  struct
  {
    int BSPE  : 1;
    int MSTR  : 1;
    int RIE   : 2;
    int REIE  : 1;
    int       : 2;
    int BEIE  : 1;
    int CPOL  : 1;
    int CPHA  : 1;
    int WL    : 2;
    int RFE   : 4;
  };
};
union ubspi_csr2
{
  unsigned int full;
  struct
  {
    int DFIFO : 1;
    int       : 1;
    int BERR  : 1;
    int RFNE  : 1;
    int RFF   : 1;
    int ROFL  : 1;
    int TFE   : 1;
    int TUFL  : 1;
    int TFF   : 1;
    int TFNE  : 1;
    int _TFE  : 4;
    int TIE   : 2;
  };
};

__no_init volatile union ubspi_csr1 BSPI0_CSR1_bit @ BSPI0_BASE + 0x08;
#define BSPI0_CSR1 BSPI0_CSR1_bit.full
__no_init volatile union ubspi_csr2 BSPI0_CSR2_bit @ BSPI0_BASE + 0x0C;
#define BSPI0_CSR2 BSPI0_CSR2_bit.full
__no_init volatile int BSPI0_CLK @ BSPI0_BASE + 0x10;
__no_init volatile int BSPI0_RXR @ BSPI0_BASE;
__no_init volatile int BSPI0_TXR @ BSPI0_BASE + 0x04;

__no_init volatile union ubspi_csr1 BSPI1_CSR1_bit @ BSPI1_BASE + 0x08;
#define BSPI1_CSR1 BSPI1_CSR1_bit.full
__no_init volatile union ubspi_csr2 BSPI1_CSR2_bit @ BSPI1_BASE + 0x0C;
#define BSPI1_CSR2 BSPI1_CSR2_bit.full
__no_init volatile int BSPI1_CLK @ BSPI1_BASE + 0x10;
__no_init volatile int BSPI1_RXR @ BSPI1_BASE;
__no_init volatile int BSPI1_TXR @ BSPI1_BASE + 0x04;

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de controle das interfaces I2C0 e I2C1

********************************************************************************
********************************************************************************
*******************************************************************************/
union ui2c_cr
{
  unsigned int full;
  struct
  {
    int ITE   : 1;
    int STOP  : 1;
    int ACK   : 1;
    int START : 1;
    int ENGC  : 1;
    int PE    : 1;
  };
};

union ui2c_sr1
{
  unsigned int full;
  struct
  {
    int SB      : 1;
    int MSL     : 1;
    int ADSL    : 1;
    int BTF     : 1;
    int I2CBUSY : 1;
    int TRA     : 1;
    int ADD10   : 1;
    int EVF     : 1;
  };
};

union ui2c_sr2
{
  unsigned int full;
  struct
  {
    int GCAL  : 1;
    int BERR  : 1;
    int ARLO  : 1;
    int STOPF : 1;
    int AF    : 1;
    int ENDAF : 1;
  };
};
__no_init volatile union ui2c_cr I2C0_CR_bit @ I2C0_BASE;
#define  I2C0_CR  I2C0_CR_bit.full
__no_init volatile union ui2c_sr1 I2C0_SR1_bit @ I2C0_BASE + 0x04;
#define  I2C0_SR1  I2C0_SR1_bit.full
__no_init volatile union ui2c_sr2 I2C0_SR2_bit @ I2C0_BASE + 0x08;
#define  I2C0_SR2  I2C0_SR2_bit.full
__no_init volatile int I2C0_CCR @ I2C0_BASE + 0x0C;
__no_init volatile int I2C0_ECCR @ I2C0_BASE + 0x1C;
__no_init volatile int I2C0_OAR1 @ I2C0_BASE + 0x10;
__no_init volatile int I2C0_OAR2 @ I2C0_BASE + 0x14;
__no_init volatile int I2C0_DR @ I2C0_BASE + 0x18;

__no_init volatile union ui2c_cr I2C1_CR_bit @ I2C1_BASE;
#define  I2C1_CR  I2C1_CR_bit.full
__no_init volatile union ui2c_sr1 I2C1_SR1_bit @ I2C1_BASE + 0x04;
#define  I2C1_SR1  I2C1_SR1_bit.full
__no_init volatile union ui2c_sr2 I2C1_SR2_bit @ I2C1_BASE + 0x08;
#define  I2C1_SR2  I2C1_SR2_bit.full
__no_init volatile int I2C1_CCR @ I2C1_BASE + 0x0C;
__no_init volatile int I2C1_ECCR @ I2C1_BASE + 0x1C;
__no_init volatile int I2C1_OAR1 @ I2C1_BASE + 0x10;
__no_init volatile int I2C1_OAR2 @ I2C1_BASE + 0x14;
__no_init volatile int I2C1_DR @ I2C1_BASE + 0x18;

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores de controle do ADC12

********************************************************************************
********************************************************************************
*******************************************************************************/
union uadc_csr
{
  unsigned int full;
  struct
  {
    int DA0 : 1;
    int DA1 : 1;
    int DA2 : 1;
    int DA3 : 1;
    int A0  : 1;
    int A1  : 1;
    int AXT : 1;
    int     : 1;
    int IE0 : 1;
    int IE1 : 1;
    int IE2 : 1;
    int IE3 : 1;
    int     : 1;
    int OR  : 1;
  };
};

__no_init volatile union uadc_csr ADC_CSR_bit @ ADC12_BASE + 0x20;
#define  ADC_CSR  ADC_CSR_bit.full
__no_init volatile int ADC_CPR @ ADC12_BASE + 0x30;
__no_init volatile int ADC_DATA0 @ ADC12_BASE;
__no_init volatile int ADC_DATA1 @ ADC12_BASE + 0x08;
__no_init volatile int ADC_DATA2 @ ADC12_BASE + 0x10;
__no_init volatile int ADC_DATA3 @ ADC12_BASE + 0x18;

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores do controlador da FLASH

********************************************************************************
********************************************************************************
*******************************************************************************/
union uflash_cr0
{
  unsigned int full;
  struct
  {
    int       : 1;
    int BSY0  : 1;
    int BSY1  : 1;
    int       : 1;
    int LOCK  : 1;
    int       : 10;
    int PWD   : 1;
    int       : 4;
    int INTP  : 1;
    int INTM  : 1;
    int       : 2;
    int SPR   : 1;
    int       : 2;
    int SER   : 1;    
  };
};
union uflash_cr1
{
  unsigned int full;
  struct
  {
    int B0F0  : 1;
    int B0F1  : 1;
    int B0F2  : 1;
    int B0F3  : 1;
    int B0F4  : 1;
    int B0F5  : 1;
    int B0F6  : 1;
    int B0F7  : 1;
    int       : 8;
    int B1F0  : 1;
    int B1F1  : 1;
    int       : 6;
    int B0S   : 1;
    int B1S   : 1;    
  };
};
union uflash_er
{
  unsigned int full;
  struct
  {
    int ERR   : 1;
    int ERER  : 1;
    int PGER  : 1;
    int _10ER : 1;
    int       : 2;
    int SEQER : 1;
    int RESER : 1;
  };
};

__no_init volatile union uflash_cr0 FLASH_CR0_bit @ FLASHR_BASE;
#define  FLASH_CR0  FLASH_CR0_bit.full
__no_init volatile union uflash_cr1 FLASH_CR1_bit @ FLASHR_BASE + 0x04;
#define  FLASH_CR1  FLASH_CR1_bit.full
__no_init volatile union uflash_er FLASH_ER_bit @ FLASHR_BASE + 0x14;
#define  FLASH_ER  FLASH_ER_bit.full
__no_init volatile int FLASH_DR0 @ FLASHR_BASE + 0x08;
__no_init volatile int FLASH_DR1 @ FLASHR_BASE + 0x0C;
__no_init volatile int FLASH_AR @ FLASHR_BASE + 0x10;

union uflash_nvwpar
{
  unsigned int full;
  struct
  {
    int W0P0  : 1;
    int W0P1  : 1;
    int W0P2  : 1;
    int W0P3  : 1;
    int W0P4  : 1;
    int W0P5  : 1;
    int W0P6  : 1;
    int W0P7  : 1;
    int       : 8;
    int W1P0  : 1;
    int W1P1  : 1;
  };
};
union uflash_nvapr0
{
  unsigned int full;
  struct
  {
    int READOUT : 1;
    int DBGP    : 1;
  };
};
union uflash_nvapr1
{
  unsigned int full;
  struct
  {
    int PDS0  : 1;
    int PDS1  : 1;
    int PDS2  : 1;
    int PDS3  : 1;
    int PDS4  : 1;
    int PDS5  : 1;
    int PDS6  : 1;
    int PDS7  : 1;
    int PDS8  : 1;
    int PDS9  : 1;
    int PDS10 : 1;
    int PDS11 : 1;
    int PDS12 : 1;
    int PDS13 : 1;
    int PDS14 : 1;
    int PDS15 : 1;
    int PEN0  : 1;
    int PEN1  : 1;
    int PEN2  : 1;
    int PEN3  : 1;
    int PEN4  : 1;
    int PEN5  : 1;
    int PEN6  : 1;
    int PEN7  : 1;
    int PEN8  : 1;
    int PEN9  : 1;
    int PEN10 : 1;
    int PEN11 : 1;
    int PEN12 : 1;
    int PEN13 : 1;
    int PEN14 : 1;
    int PEN15 : 1;
  };
};

__no_init volatile union uflash_nvwpar FLASH_NVWPAR_bit @ FLASHPR_BASE;
#define  FLASH_NVWPAR  FLASH_NVWPAR_bit.full
__no_init volatile union uflash_nvapr0 FLASH_NVAPR0_bit @ FLASHPR_BASE + 0x08;
#define  FLASH_NVAPR0  FLASH_NVAPR0_bit.full
__no_init volatile union uflash_nvapr1 FLASH_NVAPR1_bit @ FLASHPR_BASE + 0x0C;
#define  FLASH_NVAPR1  FLASH_NVAPR1_bit.full

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores da interface USB

********************************************************************************
********************************************************************************
*******************************************************************************/

union uusb_cntr
{
  unsigned int full;
  struct
  {
    int FRES    : 1;
    int PDWN    : 1;
    int LPMODE  : 1;
    int FSUSP   : 1;
    int RESUME  : 1;
    int         : 3;
    int ESOFM   : 1;
    int SOFM    : 1;
    int RESETM  : 1;
    int SUSPM   : 1;
    int WKUPM   : 1;
    int ERRM    : 1;
    int DOVRM   : 1;
    int CTRM    : 1;
  };
};

__no_init volatile union uusb_cntr USB_CNTR_bit @ USB_BASE + 0x40;
#define  USB_CNTR  USB_CNTR_bit.full

union uusb_istr
{
  unsigned int full;
  struct
  {
    int EP_ID   : 4;
    int DIR     : 1;
    int         : 3;
    int ESOF    : 1;
    int SOF     : 1;
    int RESET   : 1;
    int SUSP    : 1;
    int WKUP    : 1;
    int ERR     : 1;
    int DOVR    : 1;
    int CTR     : 1;
  };
};

__no_init volatile union uusb_istr USB_ISTR_bit @ USB_BASE + 0x44;
#define  USB_ISTR  USB_ISTR_bit.full

union uusb_fnr
{
  unsigned int full;
  struct
  {
    int FN      : 11;
    int LSOF    : 2;
    int LCK     : 1;
    int RXDM    : 1;
    int RXDP    : 1;
  };
};

__no_init volatile union uusb_fnr USB_FNR_bit @ USB_BASE + 0x48;
#define  USB_FNR  USB_FNR_bit.full

union uusb_daddr
{
  unsigned int full;
  struct
  {
    int ADDR  : 7;
    int EF    : 1;
    int       : 8;
  };
};

__no_init volatile union uusb_daddr USB_DADDR_bit @ USB_BASE + 0x4C;
#define  USB_DADDR  USB_DADDR_bit.full

union uusb_epr
{
  unsigned int full;
  struct
  {
    int EA      : 4;
    int STAT_TX : 2;
    int DTOG_TX : 1;
    int CTR_TX  : 1;
    int EP_KIND : 1;
    int EP_TYPE : 2;
    int SETUP   : 1;
    int STAT_RX : 2;
    int DTOG_RX : 1;
    int CTR_RX  : 1;
  };
};

__no_init volatile union uusb_epr USB_EP0R_bit @ USB_BASE;
#define USB_EP0R USB_EP0R_bit.full
__no_init volatile union uusb_epr USB_EP1R_bit @ USB_BASE + 0x04;
#define USB_EP1R USB_EP1R_bit.full
__no_init volatile union uusb_epr USB_EP2R_bit @ USB_BASE + 0x08;
#define USB_EP2R USB_EP2R_bit.full
__no_init volatile union uusb_epr USB_EP3R_bit @ USB_BASE + 0x0C;
#define USB_EP3R USB_EP3R_bit.full
__no_init volatile union uusb_epr USB_EP4R_bit @ USB_BASE + 0x10;
#define USB_EP4R USB_EP4R_bit.full

__no_init volatile union uusb_epr USB_EP5R_bit @ USB_BASE + 0x14;
#define USB_EP5R USB_EP5R_bit.full
__no_init volatile union uusb_epr USB_EP6R_bit @ USB_BASE + 0x18;
#define USB_EP6R USB_EP6R_bit.full
__no_init volatile union uusb_epr USB_EP7R_bit @ USB_BASE + 0x1C;
#define USB_EP7R USB_EP7R_bit.full
__no_init volatile union uusb_epr USB_EP8R_bit @ USB_BASE + 0x20;
#define USB_EP8R USB_EP8R_bit.full

__no_init volatile union uusb_epr USB_EP9R_bit @ USB_BASE + 0x24;
#define USB_EP9R USB_EP9R_bit.full
__no_init volatile union uusb_epr USB_EP10R_bit @ USB_BASE + 0x28;
#define USB_EP10R USB_EP10R_bit.full
__no_init volatile union uusb_epr USB_EP11R_bit @ USB_BASE + 0x2C;
#define USB_EP11R USB_EP11R_bit.full
__no_init volatile union uusb_epr USB_EP12R_bit @ USB_BASE + 0x30;
#define USB_EP12R USB_EP12R_bit.full

__no_init volatile union uusb_epr USB_EP13R_bit @ USB_BASE + 0x34;
#define USB_EP1R USB_EP1R_bit.full
__no_init volatile union uusb_epr USB_EP14R_bit @ USB_BASE + 0x38;
#define USB_EP14R USB_EP14R_bit.full
__no_init volatile union uusb_epr USB_EP15R_bit @ USB_BASE + 0x3C;
#define USB_EP15R USB_EP15R_bit.full

__no_init volatile int USB_BTABLE @ USB_BASE + 0x50;

struct sBUFFER_DESCRIPTOR
{
  int USB_ADDR_TX;
  int USB_COUNT_TX;
  int USB_ADDR_RX;
  int USB_COUNT_RX;
};

union uUSB_BUFFER
{
  struct sBUFFER_DESCRIPTOR BDT_EP[16];
  unsigned int DATA[256];
};

__no_init volatile union uUSB_BUFFER USB_BUFFER @  0xC0008000;

/*******************************************************************************
********************************************************************************
********************************************************************************

  Registradores do Watchdog

********************************************************************************
********************************************************************************
*******************************************************************************/

union uwdg_cr
{
  unsigned int full;
  struct
  {
    int WE    : 1;
    int SC    : 1;
  };
};

union uwdg_sr
{
  unsigned int full;
  struct
  {
    int EC    : 1;
  };
};

union uwdg_mr
{
  unsigned int full;
  struct
  {
    int ECM   : 1;
  };
};

__no_init volatile union uwdg_cr WDG_CR_bit @ WDG_BASE;
#define  WDG_CR  WDG_CR_bit.full
__no_init volatile int WDG_PR @ WDG_BASE + 0x04;
__no_init volatile int WDG_VR @ WDG_BASE + 0x08;
__no_init volatile int WDG_CNT @ WDG_BASE + 0x0C;
__no_init volatile union uwdg_sr WDG_SR_bit @ WDG_BASE + 0x10;
#define  WDG_SR  WDG_SR_bit.full
__no_init volatile union uwdg_mr WDG_MR_bit @ WDG_BASE + 0x14;
#define  WDG_MR  WDG_MR_bit.full
__no_init volatile int WDG_KR @ WDG_BASE + 0x18;

// 2007 - Fábio Pereira
