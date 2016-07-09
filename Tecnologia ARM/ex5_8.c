#include "MEU_STR71x.h"

void main (void)
{
  RCCU_CFR &= ~bDIV2; // Desliga o divisor por 2 (DIV2) na entrada CK
  // Configura o PLL1 para operar a partir do clock externo (CK):
  // FREF_RANGE ativado pois o sinal CK é igual a 4 MHz
  // CLOCK2x12 - configura o fator M para 16
  // PLLCLOCK_DIV_2 - configura o fator D para 2
  // RCLK = 4 MHZ * 16 / 2 = 32MHz
  RCCU_PLL1CR = bFREF_RANGE + CLOCK2x16 + PLLCLOCK_DIV_2;
  while (!(RCCU_CFR & bLOCK));  // Aguarda do PLL1 travar na referência externa
  // Seleciona o PLL1 como fonte do RCLK
  RCCU_CFR = RCLK_PLL1;
  // O MCLK após o reset é igual ao RCLK/1 = RCLK = 32 MHz
  CONFIG_PORT_OUT(0,0xFFFF); // todos os pinos da porta 0 como saídas push-pull
  while(1)
  {
    GPIO0PD = BIT13; // ativa saída P0.13 (desliga as demais)
    GPIO0PD = 0;     // desliga todos os pinos da porta 0
    GPIO0PD = BIT13; // ativa saída P0.13 (desliga as demais)
    GPIO0PD = 0;     // desliga todos os pinos da porta 0
    GPIO0PD = BIT13; // ativa saída P0.13 (desliga as demais)
    GPIO0PD = 0; // desliga todos os pinos da porta 0
  }
}








