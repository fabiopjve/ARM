/*****************************************************************************
  Exemplo de comunicação com módulo LCD 16x2 para o livro: 

  Tecnologia ARM: Microcontroladores de 32 bits
  Autor: Fábio Pereira

******************************************************************************/

#include "MEU_STR71x.h"
void delay_ms(unsigned int tempo);
#include "modlcd_arm.c"

volatile unsigned char flag_tempo=0;

// A interrupção de comparação do canal A do timer 0 ocorre a cada 1ms
__irq __arm void trata_timer0_comp_a(void)
{
  TIM0_OCAR += 1000;    // soma 1000 ao registrador de comparação (+ 1ms)
  TIM0_SR &= ~bOCFA;    // apaga o flag de interrupção do TIMER0
  flag_tempo = 0;       // apaga o flag de tempo
  EIC_IPR = bIRQ30;     // apaga o flag de interrupção do EIC
}

// Função de atraso de tempo (x ms)
void delay_ms(unsigned int tempo)
{
  TIM0_OCAR += 1000;  // soma 1ms ao registrador de comparação
  for (;tempo;tempo--)  // aguarda "tempo" ms
  {
    flag_tempo=1;       // seta o flag_tempo
    while (flag_tempo); // aguarda o flag ser apagado
  }
}

// Inicializa os periféricos do chip
void inicializa()
{
  // todos os pinos da porta GPIO0 como saídas
  CONFIG_PORT_OUT(0,0xFFFF);
  GPIO0PD = 0;
  // Configura o EIC: armazena a parte alta do endereço de trata_timer0_comp_a 
  // no registrador EIC_IVR
  EIC_IVR = (long)trata_timer0_comp_a;
  // armazena a parte baixa do endereço de trata_timer0_tof no registrador 
  // EIC_SIR30
  EIC_SIR30 = ((long)trata_timer0_comp_a<<16);
  EIC_SIR30 |= 2;         // prioridade 2 para a IRQ30
  EIC_IER = bIRQ30;       // habilita a IRQ30
  // Configura o timer 0 e o canal A
  TIM0_CR1 = bEN;         // habilita o timer 0
  TIM0_SR = 0;            // apaga flags
  // Habilita a interrupção de comparação do canal A e configura o prescaler
  // para dividir por 4 (3 + 1)
  TIM0_CR2 = bOCAIE + 3;
  EIC_ICR = bIRQ_EN;      // habilita as IRQs
}

void main (void)
{
  inicializa(); // inicializa os periféricos do chip
  // Inicializa o display
  lcd_ini(display_8x5|_2_linhas,display_ligado|cursor_desligado|cursor_fixo);
  lcd_escreve_char('\f'); // apaga o conteúdo do display
  lcd_pos_xy(4,1);  // posiciona o cursor na quarta coluna da primeira linha 
  lcd_escreve_string("ARM STR711");
  while (1) {}
}

























