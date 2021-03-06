#include "STR71x.h"
#include "simb_STR71x.h"

void atraso(unsigned int aux)
{
  unsigned char cont;
  for(;aux;aux--) for (cont=0xff; cont;cont--);
}

void main (void)
{
  CONFIG_PORT_OUT(0,BIT12+BIT13); // pinos P0.12 e P0.13 como sa�das push-pull
  while(1)
  {
    GPIO0->PD = BIT13;  // ativa sa�da P0.13 (desliga as demais)
    atraso(0xFF);       // atraso
    GPIO0->PD = BIT12;  // ativa a sa�da P0.12 (desliga as demais)
    atraso(0xFF);       // atraso
  }
}
