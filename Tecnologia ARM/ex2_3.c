#include "MEU_STR71x.h"

unsigned int contador;

void atraso(unsigned int aux)
{
  unsigned char cont;
  for(;aux;aux--) for (cont=0xff; cont;cont--);
}

void main (void)
{
  CONFIG_PORT_OUT(0,BIT12+BIT13); // pinos P0.12 e P0.13 como saídas push-pull
  contador = 0; // zera o contador
  while(1)
  {
    GPIO0PD = BIT13; // ativa saída P0.13 (desliga as demais)
    atraso(0xFF); // atraso
    GPIO0PD = BIT12; // ativa a saída P0.12 (desliga as demais)
    atraso(0xFF); // atraso
    contador++;   // incrementa o contador
  }
}
