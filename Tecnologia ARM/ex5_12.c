#include "MEU_STR71x.h"

__irq __arm void trata_timer0_tof(void)
{
  GPIO0PD ^= BIT12 + BIT13;   // inverte o estado de P0.12 e P0.13
  TIM0_SR_bit.TOF = 0;        // apaga o flag de interrupção do TIMER0
  EIC_IPR = bIRQ29;           // apaga o flag de interrupção do EIC
}

// Inicialização dos periféricos utilizados
void inicializa(void)
{
  CONFIG_PORT_OUT(0,BIT12+BIT13); // pinos P0.12 e P0.13 como saídas push-pull
  // Configura o EIC: armazena a parte alta do endereço de trata_timer0_tof no
  // registrador EIC_IVR
  EIC_IVR = (long)trata_timer0_tof;
  // armazena a parte baixa do endereço de trata_timer0_tof no registrador 
  // EIC_SIR29
  EIC_SIR29 = ((long)trata_timer0_tof<<16);
  EIC_SIR29 |= 1;          // prioridade 1 para a IRQ29
  EIC_IER = bIRQ29;        // habilita a IRQ29
  EIC_ICR = bIRQ_EN;       // habilita as IRQs
  // aciona o led ligado em P0.12
  GPIO0PD = BIT12;
  // configura o timer 0
  TIM0_CR1 = bEN; // habilita o timer 0
  TIM0_SR = 0;    // apaga todos os flags do TIMER 0
  // Habilita interrupção de estouro de contagem e configura o prescaler
  // para dividir por 30 (29 + 1). A frequencia de interrupção será aproxima-
  // damente igual a 2 MHz / 30 / 65536 = 1,02 Hz
  TIM0_CR2 = bTOIE + 29;
}

void main (void)
{
  inicializa(); // inicializa os periféricos
  while (1) {}  // aguarda uma interrupção
}












