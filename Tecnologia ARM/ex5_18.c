#include "MEU_STR71x.h"

unsigned char flag = 0;

void uart0_write_string(unsigned char *dado);

// Função de tratamento da interrupção de recepção da UART0
__irq __arm void trata_rx_uart0(void)
{
  unsigned char rxchar;
  // lê o caractere recebido e guarda em rxchar
  rxchar = UART0_RXBUFR;
  // caso o caractere recebido seja o ponto de interrogação
  if (rxchar=='?')
  {
    flag = 1; // seta o flag
  } else
  {
    // caso contrário, devolve o caractere pela serial
    UART0_TXBUFR = rxchar;
  }
  GPIO0PD ^= BIT13;       // inverte o estado de P0.13
  EIC_IPR = bIRQ9;        // apaga o flag do EIC
}

// Escreve uma string terminada por nulo na UART
void uart0_write_string(unsigned char *dado)
{
  // enquanto o caractere atual não for nulo
  while (*dado)
  {
    // caso o buffer de transmissão não esteja cheio
    if (!(UART0_SR & bTXBF))
    {
      // escreve o caractere atual da string no buffer
      UART0_TXBUFR = *dado;
      // incrementa o apontador da string para o próximo caractere
      dado++;
    }
  }
}

void main (void)
{
  // Desliga o divisor por 2 (DIV2) na entrada CK:
  RCCU_CFR &= ~bDIV2;
  // Os clocks MCLK, PCLK1 e PCLK2 apartir de agora operam a 4MHz
  CONFIG_PORT_OUT(0,BIT13);    // pino P0.13 como saída push-pull
  CONFIG_PORT_OUTALT(0,BIT9);  // pino P0.9 como saída de periférico
  // Configura a UART0
  UART0_BR = 26;    // Baud rate = 9600 bps @ 4 MHz
  UART0_TXRSTR = 1; // apaga a FIFO de TX
  UART0_RXRSTR = 1; // apaga a FIFO de RX
  // Configura a UART para o modo 8N1
  UART0_CR = bFIFOEN + bRXEN + bRUN + bUART_1STOP + bUART_8BIT;
  // habilita a interrupção de buffer de recepção não vazio
  UART0_IER = bRXBNEIE;
  // Configura o EIC:
  // armazena a parte alta do endereço de trata_rx_uart0 no registrador 
  // EIC_IVR
  EIC_IVR = (long)trata_rx_uart0;
  // armazena a parte baixa do endereço de trata_rx_uart0 no registrador 
  // EIC_SIR9
  EIC_SIR9 = ((long)trata_rx_uart0<<16);
  EIC_SIR9 |= 1;       // prioridade 1 para a IRQ9
  EIC_IER = bIRQ9;     // habilita a IRQ9  
  EIC_ICR = bIRQ_EN;   // habilita IRQ no EIC
  // aguarda uma interrupção
  while (1)
  {
    // caso o flag seja setado pela interrupção
    if (flag)
    {
      flag = 0; // apaga o flag
      // imprime a frase no terminal
      uart0_write_string(" Ola mundo ! ");
    }
  }
}




















