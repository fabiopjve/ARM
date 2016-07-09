#include "MEU_STR71x.h"

__irq __arm void trata_rx_uart0(void)
{
  // devolve o caractere recebido
  UART0_TXBUFR = UART0_RXBUFR;
  GPIO0PD ^= BIT13;       // inverte o estado de P0.13
  EIC_IPR = bIRQ9;        // apaga o flag do EIC
}

void main (void)
{
  // Desliga o divisor por 2 (DIV2) na entrada CK:
  RCCU_CFR &= ~bDIV2;
  // pino P0.13 como saída push-pull
  CONFIG_PORT_OUT(0,BIT13);
  // pino P0.9 como saída push-pull alternativa
  CONFIG_PORT_OUTALT(0,BIT9);
  // Configura a UART0
  UART0_BR = 26;    // Baud rate = 9600 bps @ 4MHz
  UART0_TXRSTR = 1; // apaga FIFO de TX
  UART0_RXRSTR = 1; // apaga FIFO de RX
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
  while (1){}
}



















