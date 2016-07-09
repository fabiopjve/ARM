/*****************************************************************************
  Arquivo com os descritores USB utilizados nos exemplos 
  do livro: 

  Tecnologia ARM: Microcontroladores de 32 bits
  Autor: F�bio Pereira

******************************************************************************/

#define TAMANHO_DESCRITOR_REPORT        27
#define TAMANHO_DESCRITOR_DISPOSITIVO   18
#define TAMANHO_TOTAL_DESCRITORES       34
#define TAMANHO_DESCRITOR_STRING        4

// Descritor de Report do dispositivo HID (gerado com a ferramenta HID 
// Descriptor Tool)
const unsigned char descritor_report [TAMANHO_DESCRITOR_REPORT] = 
{
  0x05, 0x0c,    // USAGE_PAGE (Consumer Devices)
  0x09, 0x01,    // USAGE (Consumer Control)
  0xa1, 0x01,    // COLLECTION (Application)
  0x15, 0x00,    //   LOGICAL_MINIMUM (0)
  0x25, 0x01,    //   LOGICAL_MAXIMUM (1)
  0x09, 0xe9,    //   USAGE (Volume Up)
  0x09, 0xea,    //   USAGE (Volume Down)
  0x75, 0x01,    //   REPORT_SIZE (1)
  0x95, 0x02,    //   REPORT_COUNT (2)
  0x81, 0x02,    //   INPUT (Data,Var,Abs)
  0x75, 0x01,    //   REPORT_SIZE (1)
  0x95, 0x06,    //   REPORT_COUNT (6)
  0x81, 0x03,    //   INPUT (Cnst,Var,Abs)
  0xc0           // END_COLLECTION
};

const unsigned char descritor_dispositivo [TAMANHO_DESCRITOR_DISPOSITIVO] = 
{
	0x12,	        // bLength - tamanho do descritor = 18 bytes
	0x01,	        // bDescriptorType - tipo do descritor = 0x01
	0x00,	0x02,   // bcdUSB - vers�o da USB = 2.0
	0x00,	        // bDeviceClass
	0x00,	        // bDeviceSubClass
	0x00,	        // bDeviceProtocol
	0x40,	        // bMaxPacketSize0 - tamanho m�ximo do pacote do EP0 = 64 bytes
	0x83,	0x04,   // idVendor	(0x0483) -> 0x0483 = ST
	0x25,	0x00,   // idProduct = 0x0001
	0x00,	0x01,   // bcdDevice -> revis�o 1.00
	1,		        // �ndice da string com o nome do fabricante
	2,		        // �ndice da string com o nome do produto
	3,            // �ndice da string com o n�mero serial
	0x01	        // bNumConfigurations -> n�mero de configura��es = 1
};

const unsigned char descritor_config [TAMANHO_TOTAL_DESCRITORES] = 
{
	0x09,	        // bLength - tamanho do descritor = 9 bytes
	0x02,	        // bDescriptorType - tipo do descritor = 0x02
	TAMANHO_TOTAL_DESCRITORES, 	0x00,   // wTotalLength - tamanho total dos 
                                      // descritores
	0x01,	        // bNumInterfaces - n�mero de interfaces = 1
	0x01,	        // bConfigurationValue - n�mero da configura��o atual = 1
	0x00,	        // iConfiguration - �ndice da string que descreve esta config.
	0x00,	        // bmAttributes - atributos:  self-powered = n�o
                //                            remote wakeup = n�o
	0x32,	        // bMaxPower - consumo m�ximo = 50 mA
  // descritor de interface
  0x09,	        // bLength - tamanho do descritor = 9 bytes
	0x04,	        // bDescriptorType - tipo do descritor = 4
	0x00,	        // bInterfaceNumber - n�mero da interface = 0
	0x00,	        // bAlternateSetting - configura��o alternativa = 0
	0x01,	        // bNumEndpoints - n�mero de endpoints = 1 (al�m do EP0)
	0x03,	        // bInterfaceClass - classe da interface = 3 = HID
	0x00,	        // bInterfaceSubClass - subclasse: 0 = n�o � dispositivo de boot
	0x00,	        // nInterfaceProtocol - protocolo = 0 = nenhum
	0,            // iInterface - �ndice da string que descreve a interface
  // descritor de HID
	0x09,	        // bLength - tamanho do descritor = 9 bytes
	0x21,	        // bDescriptorType - tipo do descritor = 21
	0x10, 0x01,	  // bcdHID - vers�o HID = 1.1
	0x00,	        // bCountryCode - c�digo do pa�s = 0
	0x01,	        // bNumDescriptors - n�mero de descritores HID = 1
	0x22,	        // bDescriptorType - tipo do descritor = 0x22 (report)
	TAMANHO_DESCRITOR_REPORT, 0x00,// wDescriptorLength - tamanho total do
                                 // descritor de report
  // descritor de endpoint
	0x07,	        // bLength - tamanho do descritor = 7 bytes
	0x05,	        // bDescriptorType - tipo do descritor = 5
	0x81,	        // bEndpointAddress - endere�o do endpoint = EP1 IN
	0x03,	        // bmAttributes - atributos = interrup��o
	0x01,	0x00,   // wMaxPacketSize - tamanho do pacote = 1 byte
	0x20	        // bInterval - intervalo de leitura = 32 ms
};

const unsigned char descritor_string[TAMANHO_DESCRITOR_STRING] = 
{
	0x04,         // bLength - tamanho do descritor = 4 bytes
	0x03,         // bDescriptorType - tipo do descritor = 3
	0x09, 0x04		// wLANGID = 0x0416 = Portugu�s
};

const unsigned char string_fabricante [] =
{
  "ST Microelectronics / ScTec"
};

const unsigned char string_produto [] =
{
	"Controle de Volume com STR711"  
};

const unsigned char string_serial [] =
{
	"0001-2007"  
};
