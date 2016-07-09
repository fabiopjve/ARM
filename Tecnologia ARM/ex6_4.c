/*****************************************************************************
  Exemplo de comunicação SPI com memória M25P10A para o livro: 

  Tecnologia ARM: Microcontroladores de 32 bits
  Autor: Fábio Pereira

******************************************************************************/

#include "MEU_STR71x.h"
#include "m25p10a.c"

volatile unsigned char aux;
unsigned char buffer1[]={0,1,2,3,4,5,6,7,8,9};
unsigned char buffer2[10];

// Inicializa os periféricos do chip
void inicializa()
{
  CONFIG_PORT_OUTALT(0,BIT0+BIT1+BIT2+BIT3);
  CONFIG_PORT_OUT(0,BIT4);
  RCCU_CFR_bit.DIV2 = 0;    // Desliga o divisor por 2 (DIV2) na entrada CK
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
  while (!RCCU_CFR_bit.LOCK);
  // Seleciona o PLL1 como fonte do RCLK (agora o RCLK = 48 MHz)
  RCCU_CFR = RCLK_PLL1;
  // Configuração da interface BSPI0:
  // Buffer de transmissão e de recepção = 1 byte
  // BSPI0 no modo mestre de 8 bits CPOL=0, CPHA=0
  // Clock = 48 MHz / 2 / 6 = 4 MHz
  BSPI0_CSR1 = SPI_RXFIFO_1W + SPI_8BITS + bMSTR + bBSPE;
  BSPI0_CSR2 = SPI_TXFIFO_1W;
  BSPI0_CLK = 6; // Velocidade da SPI = PCLK1 / 6 = 4 MHz
  PCU_BOOTCR = bSPI0EN; // habilita a interface BSPI0
}

void main (void)
{
  inicializa();                 // iniciliaza o chip e os periféricos
  M25P10A_write_enable();       // ativa o bit WEL na memória
  M25P10A_sector_erase(0x1000); // apaga o setor do endereço 0x1000
  // aguarda a operação ser concluído (WIP = 0)
  do
    aux = M25P10A_read_SR();  
  while (aux & SR_WIP);
  M25P10A_write_enable();       // ativa o bit WEL na memória
  // Escreve 10 bytes do buffer1 no endereço 0x1000
  M25P10A_write_bytes(0x1000,10,buffer1);
  // aguarda a operação ser concluído (WIP = 0)  
  do
    aux = M25P10A_read_SR();
  while (aux & SR_WIP);
  // Lê 10 bytes a partir do endereço 0x1000 e escreve em buffer2
  M25P10A_read_bytes(0x1000,10,buffer2);
  while (1)
  {
    aux = M25P10A_read_id(); // lê o código de identificação da memória
  }
}



























