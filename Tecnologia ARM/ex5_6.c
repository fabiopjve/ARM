#include "MEU_STR71x.h"

void atraso(unsigned int aux)
{
  unsigned int cont;
  for(;aux;aux--) for (cont=0xff; cont;cont--);
}
void main (void)
{
  unsigned int contador;
  CONFIG_PORT_OUT(0,BIT12+BIT13); // pinos P0.12 e P0.13 como saídas push-pull
  GPIO0PD = 0; // desliga todas as saídas
  while (1)
  {
    // Primeiro iniciamos operando a CPU a aproximadamente 500 kHz, utilizando
    // o PLL1 no modo Free Running
    // Configura os barramentos APB1 e APB2 para operar em RCLK/1
    PCU_PDIVR = PCLK2_RCLK_DIV_1 + PCLK1_RCLK_DIV_1;
    // Configura o PLL1 para o modo free running a 500 kHz:
    // FREEN = 1
    // FREF_RANGE = 1
    // DX = 1 1 1
    // MX = 0 0 ou 1 0
    RCCU_PLL1CR = PLL1_FREE_RUNNING_500K;
    // Seleciona o PLL1 como fonte do RCLK
    RCCU_CFR = RCLK_PLL1;
    // Pisca 5 vezes o led conectado ao pino P0.13
    // Neste momento: RCLK = MCLK = PCLK1 = PCLK2 = 500 kHz
    for (contador = 5; contador; contador--)
    {
      GPIO0PD |= BIT13;      // ativa a saída P0.13
      atraso(0xFF);          // atraso
      GPIO0PD &= ~BIT13;     // desativa a saída P0.13
      atraso(0xFF);          // atraso
    }
    // Agora iremos operar diretamente a partir do clock de 4 MHz externo e
    // sem o PLL
    RCCU_PLL1CR = PLLOFF;
    // Seleciona o sinal CLK2 como fonte do RCLK, desliga o DIV2
    RCCU_CFR = bCK2_16;
    // Pisca 25 vezes o led conectado ao pino P0.12
    // Neste momento: RCLK = MCLK = PCLK1 = PCLK2 = 4 MHz
    for (contador = 25; contador; contador--)
    {
      GPIO0PD |= BIT12;      // ativa a saída P0.12
      atraso(0xFF);          // atraso
      GPIO0PD &= ~BIT12;     // desativa a saída P0.12
      atraso(0xFF);          // atraso
    }
    // Agora iremos configurar o PLL1 para gerar um sinal RCLK = 32 MHz:
    // 32 / 4 = 8 --> M = 16 e D = 2
    // Desliga o divisor por 2 (DIV2) na entrada CK:
    RCCU_CFR &= ~bDIV2;
    // Configura o PLL1:
    // FREF_RANGE ativado pois o sinal CK é igual a 4 MHz
    // CLOCK2x16 - configura o fator M para 16
    // PLLCLOCK_DIV_2 - configura o fator D para 2
    // RCLK = 4 MHZ * 16 / 2 = 32MHz
    RCCU_PLL1CR = bFREF_RANGE + CLOCK2x16 + PLLCLOCK_DIV_2;
    // Aguarda do PLL1 travar na referência externa
    while (!(RCCU_CFR & bLOCK)); // Aguarda do PLL1 travar na referência externa
    RCCU_CFR = RCLK_PLL1;  // Seleciona o PLL1 como fonte do RCLK
    // Pisca 100 vezes o led conectado ao pino P0.13
    // Neste momento: RCLK = MCLK = PCLK1 = PCLK2 = 32 MHz
    for (contador = 100; contador; contador--)
    {
      GPIO0PD |= BIT13;      // ativa a saída P0.13
      atraso(0x2FF);         // atraso
      GPIO0PD &= ~BIT13;     // desativa a saída P0.13
      atraso(0x2FF);         // atraso
    }
  }
}






