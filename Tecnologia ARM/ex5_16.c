#include "MEU_STR71x.h"

void main (void)
{
  // Desliga o divisor por 2 (DIV2) na entrada CK:
  RCCU_CFR &= ~bDIV2;
  // pinos P0.12 e P0.13 como saídas push-pull
  CONFIG_PORT_OUT(0,BIT13);
  CONFIG_PORT_OUTALT(0,BIT9);
  // Configura a UART0
  UART0_BR = 26;    // Baud rate = 9600 bps @ 4MHz
  UART0_TXRSTR = 1; // apaga FIFO de TX
  UART0_RXRSTR = 1; // apaga FIFO de RX
  // Configura a UART para o modo 8N1
  UART0_CR = bFIFOEN + bRXEN + bRUN + bUART_1STOP + bUART_8BIT;
  while (1)
  {
    // aguarda um caractere ser recebido pela UART0: quando um novo
    // caractere for recebido, o bit RXBNE será setado
    while (UART0_SR & bRXBNE)
    {
      // lê o caractere recebido e o envia de volta
      UART0_TXBUFR = UART0_RXBUFR;
      GPIO0PD ^= BIT13; // inverte o estado de P0.13
    }
  }
}


















