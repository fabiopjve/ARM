#include "MEU_STR71x.h"

void atraso(unsigned int aux)
{
  unsigned int cont;
  for(;aux;aux--) for (cont=0xff; cont;cont--);
}

void main (void)
{
  unsigned int ciclos;
  CONFIG_PORT_OUT(0,BIT12+BIT13); // pinos P0.12 e P0.13 como saídas push-pull
  CONFIG_PORT_CMOSIN(0,BIT15);    // pino P0.15 como entrada CMOS
  XTI_MRH = BIT7; // configura o canal 15 do XTI (equivale ao pino 0.15)
  while(1)
  {
    ciclos = 5; // ciclos de repetição do pisca
    while (ciclos)
    {
      GPIO0PD = BIT13;  // ativa saída P0.13 (desliga as demais)
      atraso(0xFF);     // atraso
      GPIO0PD = BIT12;  // ativa a saída P0.12 (desliga as demais)
      atraso(0xFF);     // atraso
      ciclos--;         // decrementa um ciclo
    }
    GPIO0PD = 0;        // desativa todas as saídas
    // agora entra no modo STOP e aguarda uma interrupção
    XTI_CTRL = bID1S + bWKUP_INT; // habilita o wakeup através do XTI
    XTI_CTRL |= bSTOP;    // seta o bit STOP
    XTI_CTRL &= ~bSTOP;   // apaga o bit STOP
    XTI_CTRL |= bSTOP;    // seta o bit STOP
    // o chip entra em modo STOP daqui em diante
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
  }
}









