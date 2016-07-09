/*****************************************************************************
 Biblioteca de comunica��o com a mem�ria M25P10A, produzida para o livro: 

  Tecnologia ARM: Microcontroladores de 32 bits
  Autor: F�bio Pereira

******************************************************************************/

#define WREN_cmd      0x06
#define WRDI_cmd      0x04
#define RDSR_cmd      0x05
#define WRSR_cmd      0x01
#define READ_cmd      0x03
#define FAST_READ_cmd 0x0B
#define PP_cmd        0x02
#define SE_cmd        0xD8
#define BE_cmd        0xC7
#define DP_cmd        0xB9
#define RES_cmd       0xAB
#define SR_WIP        BIT0
#define SR_WEL        BIT1
#define SR_BP0        BIT2
#define SR_BP1        BIT3
#define SR_SRWD       BIT7

#define DUMMY         0xFA

// O pino de habilita��o da mem�ria � o P0.4
#define MEM_ENABLE()  GPIO0PD &= ~BIT4
#define MEM_DISABLE() GPIO0PD |= BIT4

//****************************************************************************
// Transfere um byte pelo pino MOSI e recebe outro pelo MISO
//****************************************************************************
unsigned char spi_transfere(unsigned char dado)
{
  unsigned char temp;
  while (BSPI0_CSR2 & bRFNE)
    temp = BSPI0_RXR;         // esvazia o buffer de recep��o
  while (BSPI0_CSR2 & bTFF);  // espera espa�o no buffer de transmiss�o
  BSPI0_TXR = dado << 8;      // transmite o dado
  while (!(BSPI0_CSR2 & bRFNE));  // aguarda o dado ser recebido
  while (BSPI0_CSR2 & bRFNE)
    temp = BSPI0_RXR>>8;      // le o dado recebido
  return (temp);  
}


//****************************************************************************
// L� um byte da mem�ria M25P10A
//****************************************************************************
char M25P10A_read_byte (unsigned int endereco)
{
  unsigned char temp;
  MEM_ENABLE();                   // habilita a mem�ria
  spi_transfere(READ_cmd);        // envia o comando
  spi_transfere(endereco >> 16);  // envia o primeiro byte do endere�o
  spi_transfere(endereco >> 8);   // envia o segundo byte do endere�o
  spi_transfere(endereco);        // envia o terceiro byte do endere�o
  temp = spi_transfere(DUMMY);    // l� o byte da mem�ria
  MEM_DISABLE();                  // desabilita a mem�ria
  return (temp);                  // retorna o dado livro
}


//****************************************************************************
// L� "num_byte" bytes da mem�ria M25P10A
//****************************************************************************
void M25P10A_read_bytes (unsigned int endereco, unsigned int num_byte, 
                           unsigned char *end_destino)
{
  MEM_ENABLE();                   // habilita a mem�ria
  spi_transfere(READ_cmd);        // envia o comando
  spi_transfere(endereco >> 16);  // envia o primeiro byte do endere�o
  spi_transfere(endereco >> 8);   // envia o segundo byte do endere�o
  spi_transfere(endereco);        // envia o terceiro byte do endere�o
  for(;num_byte;num_byte--)       // repete "num_byte" vezes
    *end_destino++ = spi_transfere(DUMMY); // l� byte da mem�ria
  MEM_DISABLE();                  // desabilita a mem�ria
}


//****************************************************************************
// Escreve "num_byte" bytes na mem�ria M25P10A
//****************************************************************************
void M25P10A_write_bytes (unsigned int endereco, unsigned int num_byte,
                            unsigned char *end_destino)
{
  MEM_ENABLE();                   // habilita a mem�ria
  spi_transfere(PP_cmd);          // envia o comando
  spi_transfere(endereco >> 16);  // envia o primeiro byte do endere�o
  spi_transfere(endereco >> 8);   // envia o segundo byte do endere�o
  spi_transfere(endereco);        // envia o terceiro byte do endere�o
  // envia os bytes a serem programados
  for(;num_byte;num_byte--)
    spi_transfere(*end_destino++);
  // A programa��o � iniciada somente quando a mem�ria � desabilitada
  MEM_DISABLE();                  // desabilita a mem�ria
}


//****************************************************************************
// L� o ID da mem�ria M25P10A
//****************************************************************************
unsigned char M25P10A_read_id(void)
{
  unsigned char temp;
  MEM_ENABLE();                   // habilita a mem�ria
  spi_transfere(RES_cmd);         // envia o comando
  spi_transfere(DUMMY);           // envia byte dummy (qualquer valor)
  spi_transfere(DUMMY);           // envia byte dummy (qualquer valor)
  spi_transfere(DUMMY);           // envia byte dummy (qualquer valor)
  temp = spi_transfere(DUMMY);    // l� o ID da mem�ria
  MEM_DISABLE();                  // desabilita a mem�ria
  return(temp);                   // retorna o ID
}


//****************************************************************************
// Seta bit WEL no registrador SR da mem�ria M25P10A, habilita escritas na
// mem�ria
//****************************************************************************
void M25P10A_write_enable(void)
{
  MEM_ENABLE();                   // habilita a mem�ria
  spi_transfere(WREN_cmd);        // envia o comando
  MEM_DISABLE();                  // desabilita a mem�ria
}


//****************************************************************************
// Apaga o bit WEL no registrador SR da mem�ria M25P10A, desabilita escritas 
// na mem�ria
//****************************************************************************
void M25P10A_write_disable(void)
{
  MEM_ENABLE();                   // habilita a mem�ria
  spi_transfere(WRDI_cmd);        // envia o comando
  MEM_DISABLE();                  // desabilita a mem�ria
}


//****************************************************************************
// L� o registrador SR da mem�ria M25P10A
//****************************************************************************
unsigned char M25P10A_read_SR(void)
{
  unsigned char temp;
  MEM_ENABLE();                   // habilita a mem�ria
  spi_transfere(RDSR_cmd);        // envia o comando
  temp = spi_transfere(DUMMY);    // l� o registrador
  MEM_DISABLE();                  // desabilita a mem�ria
  return(temp);                   // retorna o dado
}


//****************************************************************************
// Escreve no registrador SR da mem�ria M25P10A
//****************************************************************************
void M25P10A_write_SR(unsigned char dado)
{
  MEM_ENABLE();                   // habilita a mem�ria
  spi_transfere(WRSR_cmd);        // envia o comando
  spi_transfere(dado);            // envia o dado
  MEM_DISABLE();                  // desabilita a mem�ria
}


//****************************************************************************
// Apaga um setor da mem�ria M25P10A
//****************************************************************************
void M25P10A_sector_erase(unsigned int endereco)
{
  MEM_ENABLE();                   // habilita a mem�ria
  spi_transfere(SE_cmd);          // envia o comando
  spi_transfere(endereco >> 16);  // envia o primeiro byte do endere�o
  spi_transfere(endereco >> 8);   // envia o segundo byte do endere�o
  spi_transfere(endereco);        // envia o terceiro byte do endere�o
  MEM_DISABLE();                  // desabilita a mem�ria
}


//****************************************************************************
// Apaga todo o conte�do da mem�ria M25P10A
//****************************************************************************
void M25P10A_bulk_erase(void)
{
  MEM_ENABLE();                   // habilita a mem�ria
  spi_transfere(BE_cmd);          // envia o comando
  MEM_DISABLE();                  // desabilita a mem�ria
}


























