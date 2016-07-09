#include "MEU_STR71x.h"

void atraso(unsigned int aux)
{
  unsigned int cont;
  for(;aux;aux--) for (cont=0xff; cont;cont--);
}
void main (void)
{
  RCCU_CFR_bit.DIV2 = 0;   // Desliga o divisor por 2 (DIV2) na entrada CK
  // Configura os barramentos APB1 e APB2 para operar em RCLK/2
  PCU_PDIVR = PCLK2_RCLK_DIV_2 + PCLK1_RCLK_DIV_2;
  // Configura o PLL1 para operar a partir do clock externo (CK):
  // FREF_RANGE ativado pois o sinal CK é igual a 4 MHz
  // CLOCK2x12 - configura o fator M para 12
  // PLLCLOCK_DIV_1 - configura o fator D para 1
  // RCLK = 4 MHZ * 12 / 1 = 48MHz
  RCCU_PLL1CR = bFREF_RANGE + CLOCK2x12 + PLLCLOCK_DIV_1;
  while (!(RCCU_CFR & bLOCK)); // Aguarda do PLL1 travar na referência externa
  RCCU_CFR = RCLK_PLL1;      	 // Seleciona o PLL1 como fonte do RCLK
  // O MCLK é igual a RCLK/1 = RCLK = 48 MHz
  CONFIG_PORT_OUT(0,BIT12+BIT13); // pinos P0.12 e P0.13 como saídas push-pull
  while(1)
  {
    GPIO0PD = BIT13; 	// ativa saída P0.13 (desliga as demais)
    atraso(0xFFF); 	  // atraso
    GPIO0PD = BIT12; 	// ativa a saída P0.12 (desliga as demais)
    atraso(0xFFF); 	  // atraso
  }
}





