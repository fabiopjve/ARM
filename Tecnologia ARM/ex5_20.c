#include "MEU_STR71x.h"

unsigned char endereco_escravo = 0x50;
volatile unsigned char dado;
volatile unsigned int temp;

void main (void)
{
  RCCU_CFR &= ~bDIV2;   // Desliga o divisor por 2 (DIV2) na entrada CK
  // Configura os barramentos APB1 e APB2 para operar em RCLK/2
  PCU_PDIVR = PCLK2_RCLK_DIV_2 + PCLK1_RCLK_DIV_2;
  // Configura o PLL1 para operar a partir do clock externo (CK):
  // FREF_RANGE ativado pois o sinal CK é igual a 4 MHz
  // CLOCK2x12 - configura o fator M para 12
  // PLLCLOCK_DIV_1 - configura o fator D para 1
  // RCLK = 4 MHZ * 12 / 1 = 48MHz
  RCCU_PLL1CR = bFREF_RANGE + CLOCK2x12 + PLLCLOCK_DIV_1;
  // Aguarda do PLL1 travar na referência externa
  while (!(RCCU_CFR & bLOCK));
  RCCU_CFR = RCLK_PLL1;    // Seleciona o PLL1 como fonte do RCLK
  // O MCLK é igual a RCLK/1 = RCLK = 48 MHz, PCLK1 = PCLK2 = 24 MHz
  // Agora configuramos os dois pinos da I2C1 para o modo de saída alternativa
  // no modo dreno aberto:
  CONFIG_PORT_ODALT(0,BIT2+BIT3);
  // Configura a velocidade da I2C1 para operar com PCLK1 = 24 MHz:
  I2C1_OAR2 = bFR1;
  // Para obtermos uma velocidade de comunicação de 100 kbps (modo padrão) a 
  // partir de um PCLK1 = 24 MHz, temos de configurar o divisor de clock da
  // interface I2C1 de acordo com a seguinte fórmula:
  // 100k = 24 MHz / (2*(DIVISOR+7)) = 113
  I2C1_CCR = 113;
  I2C1_CR = bPE;  // habilita a interface I2C1
  I2C1_CR |= bSENDSTART;  // envia uma condição de START (ativa o modo mestre)
  while (!(I2C1_SR1 & bSB)); // aguarda a transmissão do START
  // Envia o endereço do dispositivo escravo. A rotação de 1 bit à esquerda de-
  // corre do fato de que o endereço do dispositivo escravo (7 bits) ocupa os 7
  // bits mais significativos do byte. O bit menos significativo é a seleção de
  // leitura/escrita (R/W) que é mantido em zero, selecionando uma operação de
  // escrita
  I2C1_DR = endereco_escravo<<1;
  while (!(I2C1_SR2 & bENDAD)); // aguarda a transmissão do endereço
  I2C1_CR |= bPE;  // escreve no registrador I2C1_CR (seqüência obrigatória)
  I2C1_DR = 0x00;  // transmite o primeiro byte do endereço da EEPROM (0x00)
  while (!(I2C1_SR1 & bBTF)); // aguarda a transmissão do dado
  I2C1_DR = 0x01;  // transmite o segundo byte do endereço da EEPROM (0x01)
  while (!(I2C1_SR1 & bBTF)); // aguarda a transmissão do dado
  I2C1_DR = 0x12;  // escreve o valor 0x12 no endereço 0x0001 da memória
  while (!(I2C1_SR1 & bBTF)); // aguarda a transmissão do dado
  I2C1_CR |= bSENDSTOP;  // envia uma condição de STOP, encerrando a operação
  while (I2C1_SR1 & bI2CBUSY); // aguarda o barramento I2C estar livre
  // atraso entre operações, necessário para a memória EEPROM 
  for (temp=10000; temp; temp--);

  do
  {
    I2C1_CR |= bSENDSTART;  // envia uma condição de START
    while (!(I2C1_SR1 & bSB)); // aguarda a transmissão do START
    I2C1_DR = endereco_escravo<<1;  // Envia o endereço do dispositivo escravo
    while (!(I2C1_SR2 & bENDAD)); // aguarda a transmissão do endereço
  } while (I2C1_SR2 & bAF);
  I2C1_CR |= bSENDSTOP;  // envia uma condição de STOP, encerrando a operação
  // atraso entre operações, necessário para a memória EEPROM 
  for (temp=10000; temp; temp--);
  /* 
     Agora iremos realizar a leitura do endereço 0x0001, de forma a confirmar 
     que a operação de escrita foi realizada com sucesso
  */
  while (I2C1_SR1 & bI2CBUSY); // aguarda o barramento I2C estar livre
  I2C1_CR |= bSENDSTART;  // envia uma condição de START
  while (!(I2C1_SR1 & bSB)); // aguarda a transmissão do START
  I2C1_DR = endereco_escravo<<1;  // Envia o endereço do dispositivo escravo
  while (!(I2C1_SR2 & bENDAD)); // aguarda a transmissão do endereço
  I2C1_CR |= bPE;  // escreve no registrador I2C1_CR (seqüência obrigatória)
  I2C1_DR = 0;  // transmite o primeiro byte do endereço da EEPROM
  while (!(I2C1_SR1 & bBTF)); // aguarda a transmissão do dado
  I2C1_DR = 1;  // transmite o segundo byte do endereço da EEPROM
  while (!(I2C1_SR1 & bBTF)); // aguarda a transmissão do dado
  I2C1_CR |= bSENDSTART;  // envia uma condição de RESTART
  while (!(I2C1_SR1 & bSB)); // aguarda a transmissão do START
  // Envia o endereço do dispositivo escravo. A rotação de 1 bit à esquerda de-
  // corre do fato de que o endereço do dispositivo escravo (7 bits) ocupa os 7
  // bits mais significativos do byte. O bit menos significativo é a seleção de
  // leitura/escrita (R/W) que, neste caso é mantido em zero, selecionando uma
  // operação de leitura
  I2C1_DR = endereco_escravo<<1 | 1;
  while (!(I2C1_SR2 & bENDAD)); // aguarda a transmissão do endereço
  I2C1_CR |= bPE;  // escreve no registrador I2C1_CR (seqüência obrigatória) 
  while (!(I2C1_SR1 & bBTF)); // aguarda a recepção do dado
  I2C1_CR |= bSENDSTOP;  // envia uma condição de parada
  dado = I2C1_DR;  // lê o dado recebido e armazena na variável "dado"
  while (1);
}






















