#include "MEU_STR71x.h"

void atraso(unsigned int aux)
{
  unsigned int cont;
  for(;aux;aux--) for (cont=0xff; cont;cont--);
}

void main (void)
{
  CONFIG_PORT_OUT(0,BIT12+BIT13); // pinos P0.12 e P0.13 como saídas push-pull
  CONFIG_PORT_PULLIN(0,BIT14);    // pino P0.14 como entrada CMOS
  GPIO0PD = BIT14;                // ativa o pullup do pino P0.14
  while(1)
  {
    while (!(GPIO0PD & BIT14))
    {
      GPIO0PD = BIT13;    // ativa o P0.13 e desliga o P0.12
      atraso(0xFF);       // atraso
      GPIO0PD = BIT12;	  // ativa o P0.12 e desliga o P0.13
      atraso(0xFF);       // atraso
    }
  }
}


