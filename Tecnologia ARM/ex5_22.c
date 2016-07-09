#include "MEU_STR71x.h"
#include "stdio.h"

unsigned char flag = 0;
unsigned int result;

void uart0_write_string(unsigned char *dado);

// Fun��o de tratamento da interrup��o de recep��o da UART0
__irq __arm void trata_rx_uart0(void)
{
  // caso o caractere recebido seja o CR (c�digo 13)
  if (UART0_RXBUFR==13)
  {
    flag = 1; // seta o flag
  }
  EIC_IPR = bIRQ9;        // apaga o flag do EIC
}

// Fun��o de tratamento da interrup��o de convers�o pronta do ADC12
__irq __arm void trata_adc(void)
{
  result = ADC_DATA0 >> 4; // l� o resultado da convers�o
  ADC_CSR_bit.DA0 = 0;     // apaga o flag DA0
  EIC_IPR = bIRQ18;        // apaga o flag do EIC
}

// Escreve uma string terminada por nulo na UART
void uart0_write_string(unsigned char *dado)
{
  // enquanto o caractere atual n�o for nulo
  while (*dado)
  {
    // caso o buffer de transmiss�o n�o esteja cheio
    if (!(UART0_SR & bTXBF))
    {
      // escreve o caractere atual da string no buffer
      UART0_TXBUFR = *dado;
      // incrementa o apontador da string para o pr�ximo caractere
      dado++;
    }
  }
}

void main (void)
{
  unsigned char string[6];
  // Desliga o divisor por 2 (DIV2) na entrada CK:
  RCCU_CFR_bit.DIV2 = 0;
  // Os clocks MCLK, PCLK1 e PCLK2 a partir de agora operam a 4MHz
  CONFIG_PORT_OUTALT(0,BIT9);  // pino P0.9 como sa�da de perif�rico
  CONFIG_PORT_AIN(1,BIT0);     // pino P1.0 na fun��o anal�gica
  // Configura a UART0
  UART0_BR = 26;    // Baud rate = 9600 bps @ 4MHz
  UART0_TXRSTR = 1; // apaga a FIFO de TX
  UART0_RXRSTR = 1; // apaga a FIFO de RX
  // Configura a UART para o modo 8N1
  UART0_CR = bFIFOEN + bRXEN + bRUN + bUART_1STOP + bUART_8BIT;
  // habilita a interrup��o de buffer de recep��o n�o vazio
  UART0_IER = bRXBNEIE;
  // Configura o conversor A/D:
  PCU_BOOTCR = bADCEN;     // habilita o conversor A/D
  ADC_CPR = 2;             // prescaler do ADC = PCLK2 / 4 = 1 MHz
  // modo de canal �nico, canal 0, interrup��o do canal 0 ativada
  ADC_CSR = bSINGLE_CHAN + bADC_CH0 + bADCIE0;
  // Configura o EIC:
  // armazena a parte alta do endere�o de trata_rx_uart0 no registrador 
  // EIC_IVR
  EIC_IVR = (long)trata_rx_uart0;
  // armazena a parte baixa do endere�o de trata_rx_uart0 no registrador 
  // EIC_SIR9
  EIC_SIR9 = ((long)trata_rx_uart0<<16);
  EIC_SIR9 |= 2;       // prioridade 2 para a IRQ9 (UART) 
  // armazena a parte baixa do endere�o de trata_adc no registrador EIC_SIR18
  EIC_SIR18 = ((long)trata_adc<<16);
  EIC_SIR18 |= 1;      // prioridade 1 para a IRQ18 (ADC)
  EIC_IER = bIRQ9 + bIRQ18; // habilita a IRQ9 e IRQ18
  EIC_ICR = bIRQ_EN;        // habilita IRQ no EIC
  // aguarda uma interrup��o
  uart0_write_string("Pressione ENTER para converter\r\n");
  while (1)
  {
    // caso o flag seja setado pela interrup��o
    if (flag)
    {
      flag = 0; // apaga o flag
      // ajusta o resultado
      if ((result & 0x800)==0x800) result = (0x800 - (((~ result)&0xFFF) +1));
        else if ((result & 0x800) == 0) result = (result + 0x800); 
          else result = 0;
      // converte o resultado em uma string
      sprintf(string,"%u\r\n",result);
      // imprime a �ltima convers�o no terminal
      uart0_write_string("AIN.0=");
      uart0_write_string(string);
    }
  }
}
























