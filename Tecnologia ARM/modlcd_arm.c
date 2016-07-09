/*****************************************************************************
    MODLCD_ARM.C - Biblioteca de manipula��o de m�dulo LCD para MCUs ARM

    Autor: F�bio Pereira

******************************************************************************/

/*****************************************************************************
    MODLCD_ARM.C - Biblioteca de manipula��o de m�dulo LCD para MCUs ARM

    Autor: F�bio Pereira

******************************************************************************/

// As defini��es a seguir s�o utilizadas para acesso aos pinos do display
#ifndef lcd_enable
#define lcd_enable() 	  GPIO0PD |= BIT0   // habilita o m�dulo LCD
#define lcd_disable()   GPIO0PD &= ~BIT0  // desabilita o m�dulo LCD
#define lcd_set_rs()    GPIO0PD |= BIT1   // ativa o pino RS do LCD
#define lcd_reset_rs()  GPIO0PD &= ~BIT1  // desativa o pino RS do LCD
#define lcd_port        GPIO0PD
#endif

#define lcd_seg_lin 0x40    // Endere�o da segunda linha na RAM do LCD

// Defini��es utilizadas para configura��o do display
#define cursor_ligado     2
#define cursor_desligado  0
#define cursor_piscante   1
#define cursor_fixo       0
#define display_ligado    4
#define display_desligado 0
#define display_8x5       0
#define display_10x5      4
#define _2_linhas         8
#define _1_linha          0

// vari�vel global que armazena o configura��o do display
static char modo_lcd2;	

void lcd_envia_nibble(char dado);
void lcd_envia_byte(char endereco, char dado);
void lcd_ini(char modo1, char modo2);
void lcd_pos_xy(char x, char y);
void lcd_escreve_char(char dado);
void lcd_escreve_string (char *dado);
void lcd_liga_display(void);
void lcd_desliga_display(void);
void lcd_liga_cursor(void);
void lcd_desliga_cursor(void);
void lcd_liga_cursor_piscante(void);
void lcd_desliga_cursor_piscante(void);

//**************************************************************************
//* Fun��o de envio de um nibble para o display
//**************************************************************************
//* Argumentos de chamada:
//* char dado : dado a ser enviado para o display (somente o nibble inferior)
//**************************************************************************
//* Retorno : nada
//**************************************************************************
void lcd_envia_nibble(char dado)
{
  // coloca os quatro bits nas saidas
  lcd_port &= 0xFF0F;
  lcd_port |= dado << 4;
  // pulsa a linha enable
  lcd_enable();
  lcd_disable();
}
//**************************************************************************
//* Fun��o de escrita de 1 byte no display
//**************************************************************************
//* Argumentos de chamada:
//* char endereco : 0 se instru��o, 1 se dado
//* char dado : dado ou comando a ser escrito
//**************************************************************************
//* Retorno : nada
//**************************************************************************
void lcd_envia_byte(char endereco, char dado )
{
  // configura a linha rs dependendo do modo selecionado
  if (endereco) lcd_set_rs(); else lcd_reset_rs();
  delay_ms(1);
  // desativa linha enable
  lcd_disable();
  // envia a primeira parte do byte
  lcd_envia_nibble(dado >> 4);
  // envia a segunda parte do byte
  lcd_envia_nibble(dado & 0x0F);
}

//**************************************************************************
//* Fun��o de inicializa��o do display
//**************************************************************************
//* Argumentos de chamada:
//* char modo1 : modo do display (n�mero de linhas e tamanho dos caracteres
//* char modo2 : modo do display (estado do cursor e do display)
//**************************************************************************
//* Retorno : nada
//**************************************************************************
void lcd_ini(char modo1, char modo2 )
{
  char conta;
  // coloca os pinos em n�vel l�gico 0
  lcd_port &= 0xFF0F; 
  lcd_reset_rs();
  lcd_disable();
  delay_ms(15);
  // envia uma seq��ncia de 3 vezes 0x03 e depois 0x02 para configurar o 
  // m�dulo para modo de 4 bits
  for(conta=1;conta<=3;++conta)
  {
    lcd_envia_nibble(3);
    delay_ms(5);
  }
  lcd_envia_nibble(2);
  // envia c�digos de inicializa��o do display
  lcd_envia_byte(0,0x20 | modo1);
  lcd_envia_byte(0,0x08 | modo2);
  modo_lcd2 = 0x08 | modo2;
  lcd_envia_byte(0,1);
  lcd_envia_byte(0,6);
}


//**************************************************************************
//* Fun��o de posicionamento do cursor do display
//**************************************************************************
//* Argumentos de chamada:
//* char x : coluna a ser posicionado o cursor (iniciando de 1)
//* char y : linha a ser posicionado o cursor (1 ou 2)
//**************************************************************************
//* Retorno : nada
//**************************************************************************
void lcd_pos_xy(char x, char y)
{
   char endereco;
   if (y!=1)	endereco = lcd_seg_lin; else endereco = 0;
   endereco += x-1;
   lcd_envia_byte(0, 0x80 | endereco);
}

//**************************************************************************
//* Fun��o de escrita de um caractere no display
//**************************************************************************
//* Argumentos de chamada :
//* char c : caractere a ser escrito
//**************************************************************************
//* Retorno : nada
//**************************************************************************
//* Observa��es :
//* \f apaga o conte�do do display
//* \n e \r retornam o cursor para a primeira coluna da segunda linha
//**************************************************************************
void lcd_escreve_char(char dado)
// envia um caractere para o display
{
  switch (dado)
  {
    case '\f':	
      lcd_envia_byte(0,1);
      delay_ms(5);
      break;
    case '\n':
    case '\r':	
      lcd_pos_xy(1,2);
      break;
    default	:	
      lcd_envia_byte(1,dado);
  }
}

//**************************************************************************
//* Fun��o de escrita de uma string no display
//**************************************************************************
//* Argumentos de chamada:
//* char *c : um ponteiro para um caractere
//**************************************************************************
//* Retorno : nada
//**************************************************************************
void lcd_escreve_string (char *dado)
{
  while (*dado) lcd_escreve_char(*dado++);
}

//**************************************************************************
//* Fun��o para ativar o display
//**************************************************************************
//* Argumentos de chamada : nenhum
//* Retorno : nada
//**************************************************************************
void lcd_liga_display(void)
{
  modo_lcd2 |= display_ligado;
  lcd_envia_byte (0,modo_lcd2);
}

//**************************************************************************
//* Fun��o para desativar o display
//**************************************************************************
//* Argumentos de chamada : nenhum
//* Retorno : nada
//**************************************************************************
void lcd_desliga_display(void)
{
  modo_lcd2 &= ~display_ligado;
  lcd_envia_byte (0,modo_lcd2);
}

//**************************************************************************
//* Fun��o para ativar o cursor
//**************************************************************************
//* Argumentos de chamada : nenhum
//* Retorno : nada
//**************************************************************************
void lcd_liga_cursor(void)
{
  modo_lcd2 |= cursor_ligado;
  lcd_envia_byte (0,modo_lcd2);
}

//**************************************************************************
//* Fun��o para desativar o cursor
//**************************************************************************
//* Argumentos de chamada : nenhum
//* Retorno : nada
//**************************************************************************
void lcd_desliga_cursor(void)
{
  modo_lcd2 &= ~cursor_ligado;
  lcd_envia_byte (0,modo_lcd2);
}

//**************************************************************************
//* Fun��o para ativar o cursor piscante
//**************************************************************************
//* Argumentos de chamada : nenhum
//* Retorno : nada
//**************************************************************************
void lcd_liga_cursor_piscante(void)
{
  modo_lcd2 |= cursor_piscante;
  lcd_envia_byte (0,modo_lcd2);
}

//**************************************************************************
//* Fun��o para desativar o cursor piscante
//**************************************************************************
//* Argumentos de chamada : nenhum
//* Retorno : nada
//**************************************************************************
void lcd_desliga_cursor_piscante(void)
{
  modo_lcd2 &= ~cursor_piscante;
  lcd_envia_byte (0,modo_lcd2);
}

























