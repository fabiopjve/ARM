#include "MEU_STR71x.h"

void atraso(unsigned int aux)
{
  unsigned int cont;
  for(;aux;aux--) for (cont=0xff; cont;cont--);
}

void main (void)
{
  CONFIG_PORT_OUT(0,BIT12+BIT13); // pinos P0.12 e P0.13 como saídas push-pull
  while(1)
  {
    GPIO0PD = BIT13;  // ativa saída P0.13 (desliga as demais)
    atraso(0xFF);     // atraso
    GPIO0PD = BIT12;  // ativa a saída P0.12 (desliga as demais)
    atraso(0xFF);     // atraso
  }
}

