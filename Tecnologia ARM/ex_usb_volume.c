/*****************************************************************************
  Arquivo principal do controle USB de volume escrito para o livro: 

  Tecnologia ARM: Microcontroladores de 32 bits
  Autor: Fábio Pereira

******************************************************************************/

#include "MEU_STR71x.h"
#include "usb.h"

unsigned char buffer_tx0[64], buffer_rx0[64];
unsigned char buffer_tx1[4];

void modo_STOP(void)
{
  // entra no modo STOP e aguarda uma interrupção
  XTI_MRL = BIT1; // canal 1 do XTI = wakeup USB
  XTI_TRL = BIT1; // canal 1, borda de subida
  XTI_PRL = 0;
  XTI_CTRL = bID1S + bWKUP_INT; // habilita o wakeup através do XTI
  XTI_CTRL |= bSTOP;    // seta o bit STOP
  XTI_CTRL &= ~bSTOP;   // apaga o bit STOP
  XTI_CTRL |= bSTOP;    // seta o bit STOP
  // o chip entra em modo STOP daqui em diante
  NOP(); NOP(); NOP();
  NOP(); NOP(); NOP();
  NOP(); NOP();  
}

// Função de tratamento da interrupção de baixa prioridade da USB
// Esta ISR é executada quando um dos eventos acontece:
// RESET USB
// Transação de controle
__irq __arm void trata_usb_baixa_prioridade(void)
{
  unsigned char endpoint;
  unsigned int tamanho;
  static unsigned int last_USB_CNTR;
  EIC_IPR = bIRQ26; // apaga flag de interrupção do EIC
  // verifica se foi recebida ou enviada alguma informação pela USB
  if (USB_ISTR & bCTR)
  {
    // uma transferência foi completada corretamente, verifica qual o endpoint
    endpoint = USB_ISTR & 0x000F;
    if (endpoint==0)
    {
      // se for o endpoint 0
      if (USB_ISTR & bDIR)
      {
        // recepção de dados completada no EP0
        tamanho = USB_BUFFER.BDT_EP[0].USB_COUNT_RX & 1023;
        if (USB_EP0R & bSETUP)
        {
          // foi uma transação de SETUP, copia os dados para o buffer_rx0
          USB_buffer_to_bytebuffer(buffer_rx0, tamanho, EP0_RXBUFINDEX);
          processa_requisicao(buffer_rx0);  // processa a requisição
        } else
        {
          USB_EP0R = USB_EP_CTRL | USB_RX_NAK_TO_VALID;
        }
      } else
      {
        // transmissão de dados completada no EP0
        USB_EP0R = bCTR_RX | USB_EP_CTRL ;  // apaga o flag CTR_TX
      }
    } else
    {
      // se não for o EP0, só pode ser o EP1
      USB_EP1R = USB_EP_CTRL; // apaga os flags CTR_TX e CTR_RX
    }
  }
  // se for uma interrupção de reset USB, coloca o dispositivo no modo DEFAULT
  if (USB_ISTR & bUSB_RESET)
  {
    muda_estado_usb(USB_STATE_DEFAULT);
    USB_ISTR = ~bUSB_RESET;
  }
  
  // verifica se foi uma interrupção de wake-up e retira o dispositivo do modo
  // suspenso
  if (USB_ISTR & bUSB_WKUP)
  {
    if (USB_FNR & bRXDP == bRXDP)
    {
      // A inferface recebeu um evento de wakeup
      USB_CNTR = last_USB_CNTR; // a interface retorna ao modo original     
    } else
    {
      // não foi um evento de wakeup, retorna ao modo suspenso
      modo_STOP();
    }
    USB_ISTR = ~bUSB_WKUP;
  }
  // verifica se foi uma interrupção de suspensão e coloca o dispositivo em
  // modo suspenso
  if (USB_CNTR & bSUSPM && USB_ISTR & bUSB_SUSP)
  {
    // desativa a interface USB e habilita o canal 1 do XTI para permitir
    // que o chip seja acordado por qualquer evento no barramento USB
    last_USB_CNTR = USB_CNTR;
    USB_CNTR = bFSUSP + bPDWN;
    modo_STOP();
    USB_ISTR = ~bUSB_SUSP;
  }
}

// Função de tratamento da interrupção de alta prioridade da USB
// Não é utilizada neste exemplo
__irq __arm void trata_usb_alta_prioridade(void)
{
  EIC_IPR = bIRQ6;  // apaga flag de interrupção do EIC
}

// Inicializa os periféricos do chip
void inicializa()
{
  unsigned int temp;
  CONFIG_PORT_PULLIN(0,BIT14+BIT15); // pinos P0.14 e P0.15 como entradas
  GPIO0PD = BIT14 + BIT15;  // ativa os pullups nos pinos P0.14 e P0.15
  RCCU_CFR_bit.DIV2 = 0;    // Desliga o divisor por 2 (DIV2) na entrada CK
  // Configuração do PLL1 para gerar um sinal RCLK = 48 MHz:
  // 48 / 4 = 12 --> M = 12 e D = 1
  // Para configurar o PLL1 para operar a partir do clock externo (CK):
  // FREF_RANGE ativado pois o sinal CK é igual a 4 MHz
  // CLOCK2x12 - configura o fator M para 12
  // PLLCLOCK_DIV_1 - configura o fator D para 1
  // RCLK = 4 MHZ * 12 / 1 = 48 MHz
  RCCU_PLL1CR = bFREF_RANGE + CLOCK2x12 + PLLCLOCK_DIV_1;
  // Aguarda do PLL1 travar na referência externa
  while (!RCCU_CFR_bit.LOCK);
  // Seleciona o PLL1 como fonte do RCLK (agora o RCLK = 48 MHz)
  RCCU_CFR = RCLK_PLL1;
  // Configuração do clock da interface USB:
  PCU_PLL2CR = bUSBEN + bPLLEN + bFRQRNG + CLOCK2x12;
  RCCU_PER = bUSBCLKON;
  // Configuração do EIC:
  // Interrupção de baixa prioridade da USB
  // Armazena a parte alta do endereço de trata_usb_baixa_prioridade no 
  // registrador EIC_IVR
  EIC_IVR = (long)trata_usb_baixa_prioridade;
  // Armazena a parte baixa do endereço de trata_usb_baixa_prioridade no 
  // registrador EIC_SIR26
  EIC_SIR26 = ((long)trata_usb_baixa_prioridade<<16);
  EIC_SIR26 |= 1; // prioridade 1 para a interrupção USB de baixa prioridade 
  // armazena a parte baixa do endereço de trata_usb_alta_prioridade no 
  // registrador EIC_SIR6
  EIC_SIR6 = ((long)trata_usb_alta_prioridade<<16);
  EIC_SIR6 |= 2;  // prioridade 2 para a interrupção USB de alta prioridade 
  EIC_IER = bIRQ6 + bIRQ26; // habilita a IRQ6 e IRQ26
  // Configuração da interface USB:
  // Primeiramente vamos ativar a interface (desligar o bit USB_CNTR:PWDN):
  USB_CNTR = bFRES; // apaga PDWN e mantem a interface em reset
  // aguarda um tempo para que o transceiver USB inicialize
  for (temp = 100000; temp; temp--);
  // Retira a interface do reset (apaga o bit USB_CNTR:FRES) e habilita a
  // interrupção de reset da mesma, isto fará com que ocorra uma interrupção
  // logo no início do programa. Esta interrupção irá fazer com que o disposi-
  // tivo entre no estado padrão aguardando que o host realize a enumeração
  USB_CNTR = bRESETM;
  USB_ISTR = 0;
  // Agora habilitamos a interrupção IRQ no EIC
  EIC_ICR = bIRQ_EN;
  // A partir de agora uma interrupção poderá desviar o fluxo do programa
}

void main (void)
{
  inicializa();
  while (1)
  {
    buffer_tx1[0] = 0;
    if (!(GPIO0PD & BIT14)) buffer_tx1[0] |= 1; // aumenta volume
    if (!(GPIO0PD & BIT15)) buffer_tx1[0] |= 2; // diminui volume
    if (buffer_tx1[0] && usb_state == USB_STATE_CONFIGURED && !ep1_halt)
    {
      // se houver uma tecla pressionada, guarda no buffer de TX do EP1 e
      // prepara transmissão
      bytebuffer_to_USB_buffer(buffer_tx1, 1, EP1_TXBUFINDEX);
      USB_BUFFER.BDT_EP[1].USB_COUNT_TX = 1;
      USB_EP1R = USB_EP_INT | USB_TX_NAK_TO_VALID | 1;
    }
  }
}


	
	
	
	
	
	




