#include "MEU_STR71x.h"
volatile unsigned int piscando=0;

__irq __arm void trata_XTI(void)
{
  piscando = !piscando; // inverte o estado da variável
  XTI_PRH = 0;          // apaga os flags do XTI
  EIC_IPR = bIRQ5;      // apaga o flag de interrupção no EIC
}

void atraso(unsigned int aux)
{
  unsigned int cont;
  for(;aux;aux--) for (cont=0xff; cont;cont--);
}

void main (void)
{
  CONFIG_PORT_OUT(0,BIT12+BIT13); // pinos P0.12 e P0.13 como saídas push-pull
  CONFIG_PORT_CMOSIN(0,BIT15); // pino P0.15 como entrada CMOS
  XTI_MRH = BIT7;       // configura o canal 15 do XTI (equivale ao pino 0.15)
  XTI_CTRL = bID1S;     // habilita a interrupção do XTI
  EIC_IVR = (long)trata_XTI; // armazena a parte alta do endereço de trata_XTI
  // armazena a parte baixa do endereço de trata_XTI
  EIC_SIR5 = ((long)trata_XTI<<16);
  EIC_SIR5 |= 1;      // prioridade 1 para a IRQ5
  EIC_IER = bIRQ5;    // habilita a IRQ5
  EIC_ICR = bIRQ_EN;  // habilita as IRQs no EIC
  while(1) {
    while (piscando) {
      GPIO0PD = BIT13;  // ativa saída P0.13 (desliga as demais)
      atraso(0xFF);     // atraso
      GPIO0PD = BIT12;  // ativa a saída P0.12 (desliga as demais)
      atraso(0xFF);     // atraso
    }
  }
}




