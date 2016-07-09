#include "MEU_STR71x.h"

__irq __arm void trata_rtc(void)
{
  // verifica se foi o flag de alarme
  if (RTC_CRL & bAIR)
  {
    // se foi o alarme, acende o LED P0.12
    GPIO0PD_bit.bit12 = 1;
  }
  // verifica se foi o flag de segundos
  if (RTC_CRL & bSIR)
  {
    // foi a interrupção de segundo, inverte o estado do led P0.13
    GPIO0PD ^= BIT13;
  }
  RTC_CRL = 0;          // apaga os flags de interrupção do RTC
  EIC_IPR = bIRQ3;      // apaga o flag de interrupção do EIC
}

void main (void)
{
  CONFIG_PORT_OUT(0,BIT12+BIT13); // pinos P0.12 e P0.13 como saídas push-pull
  // Configura o EIC:
  // armazena a parte alta do endereço de trata_rtc no registrador EIC_IVR
  EIC_IVR = (long)trata_rtc;
  // armazena a parte baixa do endereço de trata_rtc no registrador EIC_SIR3
  EIC_SIR3 = ((long)trata_rtc<<16);
  EIC_SIR3 |= 1;          // prioridade 1 para a IRQ3
  EIC_IER = bIRQ3;        // habilita a IRQ3
  EIC_ICR = bIRQ_EN;      // habilita as IRQs
  while (!(RTC_CRL & bRTOFF)); // aguarda o RTOFF ir a 1
  RTC_CRL |= bCNF;  // entra no modo de configuração
  RTC_CNTH = 0;     // apaga a contagem do RTC
  RTC_CNTL = 0;     // apaga a contagem do RTC
  RTC_ALRH = 0;     // configura o alarme
  RTC_ALRL = 15;    // para 15 segundos
  RTC_CRL_bit.CNF = 0;  // sai do modo de configuração
  while (!(RTC_CRL & bRTOFF)); // aguarda o RTOFF ir a 1
  // Após um reset POR, o prescaler do RTC é programado para dividir por 32768
  RTC_CRH = bGEN + bSEN;  // habilita a interrupção global e de segundos no RTC
  while (1)
  {
  }
}










