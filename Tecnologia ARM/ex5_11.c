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
  while (!(RTC_CRL & bRTOFF));    // aguarda o RTOFF ir a 1
  RTC_CRL |= bCNF;  // entra no modo de configuração
  if (!(RCCU_CFR & bRTC_ALARM))   // verifica a origem do reset
  { // O evento de reset não foi originado pelo RTC
    RTC_CNTH = 0;     // apaga a contagem do RTC
    RTC_CNTL = 0;     // apaga a contagem do RTC
    RTC_ALRH = 0;     // configura o alarme
    RTC_ALRL = 2;     // para 2 segundos
  } else
  { // O evento de reset foi originado pelo RTC
    ciclos = RTC_CNTH<<16 | RTC_CNTL; // ciclos = contagem do RTC
    ciclos += 5;           // adiciona 5 segundos à contagem do RTC
    RTC_ALRL = ciclos;     // parte baixa no registrador RTC_ALRL
    RTC_ALRH = ciclos>>16; // parte alta no registrador RTC_ALRH
  }
  RTC_CRL_bit.CNF = 0;  // sai do modo de configuração
  while (!(RTC_CRL & bRTOFF)); // aguarda o RTOFF ir a 1
  ciclos = 5;     // ciclos de repetição do pisca
  while (ciclos)
  {
    GPIO0PD = BIT13;  // ativa saída P0.13 (desliga as demais)
    atraso(0xFF);     // atraso
    GPIO0PD = BIT12;  // ativa a saída P0.12 (desliga as demais)
    atraso(0xFF);     // atraso
    ciclos--;         // decrementa um ciclo
  }
  GPIO0PD = 0;        // desativa todas as saídas
  // agora entra no modo STANDBY e aguarda o alarme do RTC
  PCU_PWRCR = bWREN;  // habilita a escrita no registrador PCU_PWRCR
  PCU_PWRCR |= bPWRDWN; // ativa o modo STANDBY
}











