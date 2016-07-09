#include "MEU_STR71x.h"
unsigned short int periodo = 100000;

__fiq __arm void trata_fiq(void)
{
  TIM0_SR_bit.TOF = 0;    // apaga o flag de interrupção do TIMER0
  EIC_FIR |= bFIP0;       // apaga o flag FIP0
  GPIO0PD ^= BIT13;       // inverte o estado de P0.13
}

// A interrupção de comparação do canal A irá alterar o estado do pino P0.12 a 
// cada comparação, ou seja, a cada 100ms. O sinal de saída terá um período de 
// 200ms e uma freqüência de 5 Hz
__irq __arm void trata_timer1_comp_a(void)
{
  GPIO0PD ^= BIT12;      // inverte o estado de P0.12
  TIM1_OCAR += periodo;  // soma o período atual ao registrador de comparação
  TIM1_SR_bit.OCFA = 0;  // apaga o flag de interrupção do TIMER1
  EIC_IPR = bIRQ19;      // apaga o flag de interrupção do EIC
}

// Inicialização dos periféricos utilizados
void inicializa(void)
{
  CONFIG_PORT_OUT(0,BIT12+BIT13); // pinos P0.12 e P0.13 como saídas push-pull
  RCCU_CFR_bit.DIV2 = 0; // Desliga o divisor por 2 (DIV2) na entrada CK
  // A partir deste ponto, MCLK = PCLK1 = PCLK2 = 4 MHz
  // Configura o EIC: armazena a parte alta do endereço de trata_timer1_comp_a
  // no registrador EIC_IVR
  EIC_IVR = (long)trata_timer1_comp_a;
  // armazena a parte baixa do endereço de trata_timer1_comp_a no registrador 
  // EIC_SIR19
  EIC_SIR19 = ((long)trata_timer1_comp_a<<16);
  EIC_SIR19 |= 1;       // prioridade 1 para a IRQ19
  EIC_IER = bIRQ19;     // habilita a IRQ19
  EIC_FIR = bFIE0;      // habilita a interrupção FIQ to timer 0
  GPIO0PD = BIT12;      // aciona o led ligado em P0.12
  // configura o timer 0
  TIM0_CR1 = bEN;       // habilita o timer 0
  TIM0_SR = 0;          // apaga todos os flags do timer 0
  // habilita interrupção de estouro de contagem e configura o prescaler
  // para dividir por 31 (30 + 1). Ftim0 = 4 MHz / 31 = 129032,3 Hz
  // Fint = 129032,3 Hz / 65536 = 1,97 Hz
  TIM0_CR2 = bTOIE + 30;
  // configura o timer1
  TIM1_CR1 = bEN; // habilita o timer 1
  TIM1_SR = 0;    // apaga todos os flags do timer 1
  // habilita interrupção de comparação do canal A e configura o prescaler
  // para dividir por 4 (3 + 1)
  // Ftim1 = 4 MHz / 4 = 1 MHz e Ttim1 = 1 / Ftim1 = 1 us
  TIM1_CR2 = bOCAIE + 3;
  // carrega o registrador de comparação com o período atual (1000)
  // o período de interrupção é igual a FTIM * 100000 = 100.000 us ou 100 ms
  TIM1_OCAR = periodo;
  EIC_ICR = bFIQ_EN + bIRQ_EN;       // habilita IRQ e FIQ
}
void main (void)
{
  inicializa(); // inicializa os periféricos
  while (1) {}  // aguarda uma interrupção
}
















