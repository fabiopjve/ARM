#include "MEU_STR71x.h"

// Inicialização dos periféricos utilizados
void inicializa(void)
{
  CONFIG_PORT_OUTALT(0,BIT13); // pino P0.13 como saída alternativa push-pull
  RCCU_CFR_bit.DIV2 = 0;       // Desliga o divisor por 2 (DIV2) na entrada CK
  // A partir deste ponto, MCLK = PCLK1 = PCLK2 = 4 MHz
  // configura o timer 2
  TIM2_CR1 = bEN + bOLVLB + bPWM + bOCAE;
  // configura o prescaler para dividir por 4 (3 + 1)
  // Ftim2 = 4 MHz / 1 = 4 MHz e Ttim2 = 1 / Ftim2 = 0,25 us
  TIM2_CR2 = 0;
  TIM2_OCAR = 0;
  // O período do sinal é igual a 80+5 * Ttim2 = 21,25us
  // A frequencia do sinal PWM será igual a 47,05 Hz
  TIM2_OCBR = 80;
}
void main (void)
{
  unsigned int temp1, temp2;
  inicializa(); // inicializa os periféricos
  while (1)
  {
    // aumenta gradativamente o ciclo ativo e por conseguinte, o brilho do LED
    for (temp1=0;temp1<TIM2_OCBR+4;temp1++)
    {
      TIM2_OCAR = temp1-4;
      for (temp2=2000; temp2;temp2--);
    }
    for (temp2=5000; temp2;temp2--);
    // diminui gradativamente o ciclo ativo e o brilho do LED
    for (temp1=TIM2_OCBR+3;temp1+1;temp1--)
    {
      TIM2_OCAR = temp1-4;
      for (temp2=2000; temp2;temp2--);
    }
    TIM2_CR1 = bEN + bPWM + bOCAE; // força o PWM em 0%
    for (temp2=400000; temp2;temp2--); // aguarda um tempo
    TIM2_CR1 = bEN + bOLVLB + bPWM + bOCAE; // PWM no modo normal
  }
}

















