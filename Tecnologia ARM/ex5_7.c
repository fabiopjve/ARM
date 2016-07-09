#include "MEU_STR71x.h"

volatile unsigned int tempo_atraso = 4800;

__irq __arm void trata_clock(void)
{
  RCCU_CFR |= bLOCK_I;  // apaga o flag LOCK_I
  // verifica se o PLL está travado (LOCK = 1) e ajusta o tempo de atraso do loop
  // principal em função do PLL
  if (RCCU_CFR & bLOCK)
  {
    // se LOCK=1 o PLL está travado e o chip está operando a 48 MHz
    RCCU_CFR = RCLK_PLL1;// Seleciona o PLL1 como fonte do RCLK
    tempo_atraso = 4800; // constante de atraso para 48 MHz
    GPIO0PD &= ~BIT12;   // ativa a saída P0.12
  } else
  {  
    // se LOCK=0 o PLL não está travado e o chip está operando a 500 kHz
    // Configura os barramentos APB1 e APB2 para operar em RCLK/1
    PCU_PDIVR = PCLK2_RCLK_DIV_1 + PCLK1_RCLK_DIV_1;
    // Configura o PLL1 para o modo free running a 500 kHz:
    // FREEN = 1, FREF_RANGE = 1, DX = 1 1 1 e MX = 0 0 ou 1 0
    RCCU_PLL1CR = PLL1_FREE_RUNNING_500K;
    RCCU_CFR = RCLK_PLL1;  // Seleciona o PLL1 como fonte do RCLK
    tempo_atraso = 50;     //constante de atraso para 500 kHz
    GPIO0PD |= BIT12;      // desativa a saída P0.12
  }
  EIC_IPR = bIRQ2;         // apaga o flag de interrupção do EIC
}

void atraso(unsigned int aux)
{
  unsigned int cont;
  for(;aux;aux--) for (cont=0xff; cont;cont--);
}

void main (void)
{
  CONFIG_PORT_OUT(0,BIT12+BIT13); // pinos P0.12 e P0.13 como saídas push-pull
  GPIO0PD = 0;  // desliga todas as saídas
  // Configura o EIC:
  // armazena a parte alta do endereço de trata_clock no registrador EIC_IVR
  EIC_IVR = (long)trata_clock;
  // armazena a parte baixa do endereço de trata_clock no registrador EIC_SIR2
  EIC_SIR2 = ((long)trata_clock<<16);
  EIC_SIR2 |= 1;          // prioridade 1 para a IRQ2
  EIC_IER = bIRQ2;        // habilita a IRQ2
  RCCU_CFR &= ~bDIV2;     // Desliga o divisor por 2 (DIV2) na entrada CK
  // Configura os barramentos APB1 e APB2 para operar em RCLK/2
  PCU_PDIVR = PCLK2_RCLK_DIV_2 + PCLK1_RCLK_DIV_2;
  // Agora iremos configurar o PLL1 para gerar um sinal RCLK = 48 MHz:
  // 48 / 4 = 12 --> M = 12 e D = 1
  // Configura o PLL1 para operar a partir do clock externo (CK):
  // FREF_RANGE ativado pois o sinal CK é igual a 4 MHz
  // CLOCK2x12 - configura o fator M para 12
  // PLLCLOCK_DIV_1 - configura o fator D para 1
  // RCLK = 4 MHZ * 12 / 1 = 48 MHz
  RCCU_PLL1CR = bFREF_RANGE + CLOCK2x12 + PLLCLOCK_DIV_1;
  while (!(RCCU_CFR & bLOCK));  // Aguarda do PLL1 travar na referência externa
  // Seleciona o PLL1 como fonte do RCLK
  RCCU_CFR = RCLK_PLL1;
  // habilita a interrupção de LOCK do PLL1
  RCCU_CCR = bEN_LOCK;
  // ativa as interrupções IRQ no EIC
  EIC_ICR = bIRQ_EN;
  while (1)
  {
      GPIO0PD |= BIT13;       // ativa a saída P0.13
      atraso(tempo_atraso);   // atraso
      GPIO0PD &= ~BIT13;      // desativa a saída P0.13
      atraso(tempo_atraso);   // atraso
  }
}







