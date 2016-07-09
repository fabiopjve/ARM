/*****************************************************************************
 Biblioteca de comunicação com a memória M25P10A, produzida para o livro: 

  Tecnologia ARM: Microcontroladores de 32 bits
  Autor: Fábio Pereira

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

// O pino de habilitação da memória é o P0.4
#define MEM_ENABLE()  GPIO0PD &= ~BIT4
#define MEM_DISABLE() GPIO0PD |= BIT4

//****************************************************************************
// Transfere um byte pelo pino MOSI e recebe outro pelo MISO
//****************************************************************************
unsigned char spi_transfere(unsigned char dado)
{
  unsigned char temp;
  while (BSPI0_CSR2 & bRFNE)
    temp = BSPI0_RXR;         // esvazia o buffer de recepção
  while (BSPI0_CSR2 & bTFF);  // espera espaço no buffer de transmissão
  BSPI0_TXR = dado << 8;      // transmite o dado
  while (!(BSPI0_CSR2 & bRFNE));  // aguarda o dado ser recebido
  while (BSPI0_CSR2 & bRFNE)
    temp = BSPI0_RXR>>8;      // le o dado recebido
  return (temp);  
}


//****************************************************************************
// Lê um byte da memória M25P10A
//****************************************************************************
char M25P10A_read_byte (unsigned int endereco)
{
  unsigned char temp;
  MEM_ENABLE();                   // habilita a memória
  spi_transfere(READ_cmd);        // envia o comando
  spi_transfere(endereco >> 16);  // envia o primeiro byte do endereço
  spi_transfere(endereco >> 8);   // envia o segundo byte do endereço
  spi_transfere(endereco);        // envia o terceiro byte do endereço
  temp = spi_transfere(DUMMY);    // lê o byte da memória
  MEM_DISABLE();                  // desabilita a memória
  return (temp);                  // retorna o dado livro
}


//****************************************************************************
// Lê "num_byte" bytes da memória M25P10A
//****************************************************************************
void M25P10A_read_bytes (unsigned int endereco, unsigned int num_byte, 
                           unsigned char *end_destino)
{
  MEM_ENABLE();                   // habilita a memória
  spi_transfere(READ_cmd);        // envia o comando
  spi_transfere(endereco >> 16);  // envia o primeiro byte do endereço
  spi_transfere(endereco >> 8);   // envia o segundo byte do endereço
  spi_transfere(endereco);        // envia o terceiro byte do endereço
  for(;num_byte;num_byte--)       // repete "num_byte" vezes
    *end_destino++ = spi_transfere(DUMMY); // lê byte da memória
  MEM_DISABLE();                  // desabilita a memória
}


//****************************************************************************
// Escreve "num_byte" bytes na memória M25P10A
//****************************************************************************
void M25P10A_write_bytes (unsigned int endereco, unsigned int num_byte,
                            unsigned char *end_destino)
{
  MEM_ENABLE();                   // habilita a memória
  spi_transfere(PP_cmd);          // envia o comando
  spi_transfere(endereco >> 16);  // envia o primeiro byte do endereço
  spi_transfere(endereco >> 8);   // envia o segundo byte do endereço
  spi_transfere(endereco);        // envia o terceiro byte do endereço
  // envia os bytes a serem programados
  for(;num_byte;num_byte--)
    spi_transfere(*end_destino++);
  // A programação é iniciada somente quando a memória é desabilitada
  MEM_DISABLE();                  // desabilita a memória
}


//****************************************************************************
// Lê o ID da memória M25P10A
//****************************************************************************
unsigned char M25P10A_read_id(void)
{
  unsigned char temp;
  MEM_ENABLE();                   // habilita a memória
  spi_transfere(RES_cmd);         // envia o comando
  spi_transfere(DUMMY);           // envia byte dummy (qualquer valor)
  spi_transfere(DUMMY);           // envia byte dummy (qualquer valor)
  spi_transfere(DUMMY);           // envia byte dummy (qualquer valor)
  temp = spi_transfere(DUMMY);    // lê o ID da memória
  MEM_DISABLE();                  // desabilita a memória
  return(temp);                   // retorna o ID
}


//****************************************************************************
// Seta bit WEL no registrador SR da memória M25P10A, habilita escritas na
// memória
//****************************************************************************
void M25P10A_write_enable(void)
{
  MEM_ENABLE();                   // habilita a memória
  spi_transfere(WREN_cmd);        // envia o comando
  MEM_DISABLE();                  // desabilita a memória
}


//****************************************************************************
// Apaga o bit WEL no registrador SR da memória M25P10A, desabilita escritas 
// na memória
//****************************************************************************
void M25P10A_write_disable(void)
{
  MEM_ENABLE();                   // habilita a memória
  spi_transfere(WRDI_cmd);        // envia o comando
  MEM_DISABLE();                  // desabilita a memória
}


//****************************************************************************
// Lê o registrador SR da memória M25P10A
//****************************************************************************
unsigned char M25P10A_read_SR(void)
{
  unsigned char temp;
  MEM_ENABLE();                   // habilita a memória
  spi_transfere(RDSR_cmd);        // envia o comando
  temp = spi_transfere(DUMMY);    // lê o registrador
  MEM_DISABLE();                  // desabilita a memória
  return(temp);                   // retorna o dado
}


//****************************************************************************
// Escreve no registrador SR da memória M25P10A
//****************************************************************************
void M25P10A_write_SR(unsigned char dado)
{
  MEM_ENABLE();                   // habilita a memória
  spi_transfere(WRSR_cmd);        // envia o comando
  spi_transfere(dado);            // envia o dado
  MEM_DISABLE();                  // desabilita a memória
}


//****************************************************************************
// Apaga um setor da memória M25P10A
//****************************************************************************
void M25P10A_sector_erase(unsigned int endereco)
{
  MEM_ENABLE();                   // habilita a memória
  spi_transfere(SE_cmd);          // envia o comando
  spi_transfere(endereco >> 16);  // envia o primeiro byte do endereço
  spi_transfere(endereco >> 8);   // envia o segundo byte do endereço
  spi_transfere(endereco);        // envia o terceiro byte do endereço
  MEM_DISABLE();                  // desabilita a memória
}


//****************************************************************************
// Apaga todo o conteúdo da memória M25P10A
//****************************************************************************
void M25P10A_bulk_erase(void)
{
  MEM_ENABLE();                   // habilita a memória
  spi_transfere(BE_cmd);          // envia o comando
  MEM_DISABLE();                  // desabilita a memória
}


























