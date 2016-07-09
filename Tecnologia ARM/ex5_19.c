#include "MEU_STR71x.h"

// Inicializa os periféricos do chip
void inicializa()
{
  CONFIG_PORT_OUTALT(0,BIT1+BIT2);
  RCCU_CFR &= ~bDIV2;    // Desliga o divisor por 2 (DIV2) na entrada CK
  // PCLK1 = PCLK2 = RCLK/2
  PCU_PDIVR = PCLK2_RCLK_DIV_2 + PCLK1_RCLK_DIV_2;
  // Configuração do PLL1 para gerar um sinal RCLK = 48 MHz:
  // 48 / 4 = 12 --> M = 12 e D = 1
  // Para configurar o PLL1 para operar a partir do clock externo (CK):
  // FREF_RANGE ativado pois o sinal CK é igual a 4 MHz
  // CLOCK2x12 - configura o fator M para 12
  // PLLCLOCK_DIV_1 - configura o fator D para 1
  // RCLK = 4 MHZ * 12 / 1 = 48 MHz
  RCCU_PLL1CR = bFREF_RANGE + CLOCK2x12 + PLLCLOCK_DIV_1;
  // Aguarda do PLL1 travar na referência externa
  while (!(RCCU_CFR & bLOCK));
  // Seleciona o PLL1 como fonte do RCLK (agora o RCLK = 48 MHz)
  RCCU_CFR = RCLK_PLL1;
  // Configuração da interface BSPI0:
  // Buffer de transmissão e de recepção = 1 byte
  // BSPI0 no modo mestre de 8 bits CPOL=0, CPHA=0
  // Clock = 48 MHz / 2 / 8 = 3 MHz
  BSPI0_CSR1 = SPI_RXFIFO_1W + SPI_8BITS + bMSTR + bBSPE;
  BSPI0_CSR2 = SPI_TXFIFO_1W;
  BSPI0_CLK = 8; // Velocidade da SPI = PCLK1 / 8
  PCU_BOOTCR = bSPI0EN; // habilita a interface BSPI0
}
void main (void)
{
  volatile unsigned int temp;
  unsigned char dado;
  inicializa(); // inicializa o chip
  while (1)
  {
    for (dado=1;dado;dado=dado<<1)
    {
      BSPI0_TXR = dado << 8; // armazena o dado na parte alta de BSPI0_TXR
      for (temp=1000000;temp;temp--); // atraso
    }
  }
}





















