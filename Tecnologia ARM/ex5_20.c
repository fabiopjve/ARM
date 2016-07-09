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
  // FREF_RANGE ativado pois o sinal CK � igual a 4 MHz
  // CLOCK2x12 - configura o fator M para 12
  // PLLCLOCK_DIV_1 - configura o fator D para 1
  // RCLK = 4 MHZ * 12 / 1 = 48MHz
  RCCU_PLL1CR = bFREF_RANGE + CLOCK2x12 + PLLCLOCK_DIV_1;
  // Aguarda do PLL1 travar na refer�ncia externa
  while (!(RCCU_CFR & bLOCK));
  RCCU_CFR = RCLK_PLL1;    // Seleciona o PLL1 como fonte do RCLK
  // O MCLK � igual a RCLK/1 = RCLK = 48 MHz, PCLK1 = PCLK2 = 24 MHz
  // Agora configuramos os dois pinos da I2C1 para o modo de sa�da alternativa
  // no modo dreno aberto:
  CONFIG_PORT_ODALT(0,BIT2+BIT3);
  // Configura a velocidade da I2C1 para operar com PCLK1 = 24 MHz:
  I2C1_OAR2 = bFR1;
  // Para obtermos uma velocidade de comunica��o de 100 kbps (modo padr�o) a 
  // partir de um PCLK1 = 24 MHz, temos de configurar o divisor de clock da
  // interface I2C1 de acordo com a seguinte f�rmula:
  // 100k = 24 MHz / (2*(DIVISOR+7)) = 113
  I2C1_CCR = 113;
  I2C1_CR = bPE;  // habilita a interface I2C1
  I2C1_CR |= bSENDSTART;  // envia uma condi��o de START (ativa o modo mestre)
  while (!(I2C1_SR1 & bSB)); // aguarda a transmiss�o do START
  // Envia o endere�o do dispositivo escravo. A rota��o de 1 bit � esquerda de-
  // corre do fato de que o endere�o do dispositivo escravo (7 bits) ocupa os 7
  // bits mais significativos do byte. O bit menos significativo � a sele��o de
  // leitura/escrita (R/W) que � mantido em zero, selecionando uma opera��o de
  // escrita
  I2C1_DR = endereco_escravo<<1;
  while (!(I2C1_SR2 & bENDAD)); // aguarda a transmiss�o do endere�o
  I2C1_CR |= bPE;  // escreve no registrador I2C1_CR (seq��ncia obrigat�ria)
  I2C1_DR = 0x00;  // transmite o primeiro byte do endere�o da EEPROM (0x00)
  while (!(I2C1_SR1 & bBTF)); // aguarda a transmiss�o do dado
  I2C1_DR = 0x01;  // transmite o segundo byte do endere�o da EEPROM (0x01)
  while (!(I2C1_SR1 & bBTF)); // aguarda a transmiss�o do dado
  I2C1_DR = 0x12;  // escreve o valor 0x12 no endere�o 0x0001 da mem�ria
  while (!(I2C1_SR1 & bBTF)); // aguarda a transmiss�o do dado
  I2C1_CR |= bSENDSTOP;  // envia uma condi��o de STOP, encerrando a opera��o
  while (I2C1_SR1 & bI2CBUSY); // aguarda o barramento I2C estar livre
  // atraso entre opera��es, necess�rio para a mem�ria EEPROM 
  for (temp=10000; temp; temp--);

  do
  {
    I2C1_CR |= bSENDSTART;  // envia uma condi��o de START
    while (!(I2C1_SR1 & bSB)); // aguarda a transmiss�o do START
    I2C1_DR = endereco_escravo<<1;  // Envia o endere�o do dispositivo escravo
    while (!(I2C1_SR2 & bENDAD)); // aguarda a transmiss�o do endere�o
  } while (I2C1_SR2 & bAF);
  I2C1_CR |= bSENDSTOP;  // envia uma condi��o de STOP, encerrando a opera��o
  // atraso entre opera��es, necess�rio para a mem�ria EEPROM 
  for (temp=10000; temp; temp--);
  /* 
     Agora iremos realizar a leitura do endere�o 0x0001, de forma a confirmar 
     que a opera��o de escrita foi realizada com sucesso
  */
  while (I2C1_SR1 & bI2CBUSY); // aguarda o barramento I2C estar livre
  I2C1_CR |= bSENDSTART;  // envia uma condi��o de START
  while (!(I2C1_SR1 & bSB)); // aguarda a transmiss�o do START
  I2C1_DR = endereco_escravo<<1;  // Envia o endere�o do dispositivo escravo
  while (!(I2C1_SR2 & bENDAD)); // aguarda a transmiss�o do endere�o
  I2C1_CR |= bPE;  // escreve no registrador I2C1_CR (seq��ncia obrigat�ria)
  I2C1_DR = 0;  // transmite o primeiro byte do endere�o da EEPROM
  while (!(I2C1_SR1 & bBTF)); // aguarda a transmiss�o do dado
  I2C1_DR = 1;  // transmite o segundo byte do endere�o da EEPROM
  while (!(I2C1_SR1 & bBTF)); // aguarda a transmiss�o do dado
  I2C1_CR |= bSENDSTART;  // envia uma condi��o de RESTART
  while (!(I2C1_SR1 & bSB)); // aguarda a transmiss�o do START
  // Envia o endere�o do dispositivo escravo. A rota��o de 1 bit � esquerda de-
  // corre do fato de que o endere�o do dispositivo escravo (7 bits) ocupa os 7
  // bits mais significativos do byte. O bit menos significativo � a sele��o de
  // leitura/escrita (R/W) que, neste caso � mantido em zero, selecionando uma
  // opera��o de leitura
  I2C1_DR = endereco_escravo<<1 | 1;
  while (!(I2C1_SR2 & bENDAD)); // aguarda a transmiss�o do endere�o
  I2C1_CR |= bPE;  // escreve no registrador I2C1_CR (seq��ncia obrigat�ria) 
  while (!(I2C1_SR1 & bBTF)); // aguarda a recep��o do dado
  I2C1_CR |= bSENDSTOP;  // envia uma condi��o de parada
  dado = I2C1_DR;  // l� o dado recebido e armazena na vari�vel "dado"
  while (1);
}






















