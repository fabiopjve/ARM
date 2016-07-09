#include "MEU_STR71x.h"

unsigned int result;

void main (void)
{
  CONFIG_PORT_OUT(0,BIT12+BIT13); // pinos P0.12 e P0.13 como saídas push-pull
  CONFIG_PORT_AIN(1,BIT0); // configura o pino P1.0 para a função analógica
  PCU_BOOTCR = bADCEN;     // habilita o conversor A/D
  ADC_CPR = 2;             // prescaler do ADC = PCLK2 / 4 = 500 kHz
  ADC_CSR = bSINGLE_CHAN + bADC_CH0;  // modo de canal único, canal 0
  while (1)
  {
    // se o bit DA0 estiver setado
    if (ADC_CSR & bADC_DA0)
    {
      // uma nova conversão está disponível
      result = ADC_DATA0 >> 4;  // lê o resultado e desloca 4 bits
      // se o resultado estiver entre 0xFF0 (-16) e 0x00F (+15), acende o led
      // em P0.13
      if ((result>=0xFF0 && result <=0xFFF) || (result<=0x00F)) GPIO0PD=BIT13;
        else GPIO0PD = 0;
      ADC_CSR_bit.DA0 = 0;  // apaga o flag DA0
    }
  }
}























