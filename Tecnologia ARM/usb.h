/*****************************************************************************
  Arquivo de definições USB utilizadas nos exemplos do livro:

  Tecnologia ARM: Microcontroladores de 32 bits
  Autor: Fábio Pereira

******************************************************************************/

#define USB_STATE_POWERED     1
#define USB_STATE_DEFAULT     2
#define USB_STATE_ADDRESS     3
#define USB_STATE_CONFIGURED  4

#define EP0_TXBUFADDR   0x10  // após a BDT
#define EP0_RXBUFADDR   0x50  // 64 bytes após o buffer de TX do EP0
#define EP1_TXBUFADDR   0x90  // 64 bytes após o buffer de RX do EP0

#define EP0_RXBUFINDEX  EP0_RXBUFADDR>>1
#define EP0_TXBUFINDEX  EP0_TXBUFADDR>>1
#define EP1_TXBUFINDEX  EP1_TXBUFADDR>>1

volatile unsigned char usb_state = 0;
volatile unsigned char usb_addr = 0;
volatile unsigned char ep1_halt = 0;

void processa_requisicao(unsigned char *req);
void muda_estado_usb(unsigned char novo_estado);
void bytebuffer_to_USB_buffer(unsigned char *buffer, unsigned int num, 
                              unsigned int indice);
void cbytebuffer_to_USB_buffer(unsigned const char *buffer, unsigned int num, 
                               unsigned int indice);
void USB_buffer_to_bytebuffer(unsigned char *buffer, unsigned int num, 
                              unsigned int indice);
unsigned char cstring_to_USB_buffer(unsigned const char *buffer, 
                                    unsigned int indice);

#include "desc_volume.h"
#include "usb.c"
