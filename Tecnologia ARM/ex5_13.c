#include "MEU_STR71x.h"

__fiq __arm void trata_fiq(void)
{
  TIM0_SR_bit.TOF = 0;  // apaga o flag de interrupção do TIMER0
  EIC_FIR |= bFIP0;     // apaga o flag FIP0
  GPIO0PD ^= BIT12 + BIT13; // inverte o estado de P0.12 e P0.13
}

// Inicialização dos periféricos utilizados
void inicializa(void)
{
  CONFIG_PORT_OUT(0,BIT12+BIT13); // pinos P0.12 e P0.13 como saídas push-pull
  // Configura o EIC:
  EIC_FIR = bFIE0;
  EIC_ICR = bFIQ_EN;    // habilita as interrupções FIQ no EIC
  GPIO0PD = BIT12;      // aciona o LED ligado em P0.12
  // configura o timer 0
  TIM0_CR1 = bEN;       // habilita o timer 0
  TIM0_SR = 0;          // apaga todos os flags do TIMER 0
  // Habilita interrupção de estouro de contagem e configura o prescaler
  // para dividir por 30 (29 + 1). A freqüência de interrupção será aproxima-
  // damente igual a 2 MHz / 30 / 65536 = 1,02 Hz
  TIM0_CR2 = bTOIE + 29;
}

void main (void)
{
  inicializa(); // inicializa os periféricos
  while (1) {}  // aguarda uma interrupção
}













