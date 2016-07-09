/*****************************************************************************
  Arquivo com as funções de comunicação e suporte USB utilizadas nos exemplos 
  do livro: 

  Tecnologia ARM: Microcontroladores de 32 bits
  Autor: Fábio Pereira

******************************************************************************/

// Função de processamento das requisições USB
void processa_requisicao(unsigned char *req)
{
  unsigned char bmRequestType, bRequest;
  unsigned char request_dir, request_type, request_recipient, tamanho;
  unsigned short int wValue, wIndex, wLength;
  unsigned char ok;
  // extrai os campos da requisição do buffer na memória
  bmRequestType = req[0];
  bRequest = req[1];
  wValue = req[3]*256 + req[2];
  wIndex = req[5]*256 + req[4];
  wLength = req[7]*256 + req[6];
  request_dir = bmRequestType & 0x80;
  request_type = (bmRequestType & 0x60) >> 5;
  request_recipient = bmRequestType & 0x1f;
  ok = 1; // indicador de transação ocorrida com sucesso
  switch (request_type)
  {
    case 0: /************ requisições padrão *********************************/
      switch (bRequest)
      {
        case 0 :  /************ GET_STATUS ***********************************/
          if (request_recipient == 2)
          {
            // se o destino é um endpoint, envia o status de halt do mesmo
            USB_BUFFER.DATA[EP0_TXBUFINDEX] = 0x0000;
            if (ep1_halt) USB_BUFFER.DATA[EP0_TXBUFINDEX] = 0x0100;
          } else
          {
            // se o destino é o dispositivo ou uma interface, retorna 0
            USB_BUFFER.DATA[EP0_TXBUFINDEX] = 0x0000;
          }
          USB_BUFFER.BDT_EP[0].USB_COUNT_TX = 2;  // dois bytes de resposta
          USB_EP0R = USB_EP_CTRL | USB_RX_NAK_TO_VALID | USB_EP_STATUS_OUT 
            | USB_TX_NAK_TO_VALID;
          break;
        case 1 :  /************ CLEAR_FEATURE ********************************/
          if (request_recipient == 2)
          {
            ep1_halt = 0;
            // gera ACK -> transmite pacote DATA com zero bytes
            USB_BUFFER.BDT_EP[0].USB_COUNT_TX = 0;
            USB_EP0R = USB_EP_CTRL | USB_RX_NAK_TO_VALID | USB_EP_STATUS_OUT 
              | USB_TX_NAK_TO_VALID;
          } else ok = 0;  // transação inválida
          break;
        case 3 :  /************ SET_FEATURE **********************************/
          if (request_recipient == 2)
          {
            ep1_halt = 1;
            // gera ACK -> transmite pacote DATA com zero bytes
            USB_BUFFER.BDT_EP[0].USB_COUNT_TX = 0;
            USB_EP0R = USB_EP_CTRL | USB_RX_NAK_TO_VALID | USB_EP_STATUS_OUT 
              | USB_TX_NAK_TO_VALID;
          } else ok = 0;  // transação inválida
          break;
        case 5 :  /************ SET_ADDRESS **********************************/
          usb_addr = wValue;
          // gera ACK -> transmite pacote DATA com zero bytes
          USB_BUFFER.BDT_EP[0].USB_COUNT_TX = 0;
          USB_EP0R = bCTR_TX | USB_EP_CTRL | USB_TX_NAK_TO_VALID;
          muda_estado_usb(USB_STATE_ADDRESS);
          break;
        case 6 :  /************ GET_DESCRIPTOR *******************************/
          tamanho = wLength;
          // Envia o descritor especificado em wValue
          switch (req[3]) // verifica os bits 15-8 do campo wValue
          {
            case 1 :  /************ descritor de dispositivo *****************/
              if (tamanho>TAMANHO_DESCRITOR_DISPOSITIVO) 
                tamanho = TAMANHO_DESCRITOR_DISPOSITIVO;
              // copia o descritor para o buffer de pacotes
              cbytebuffer_to_USB_buffer(descritor_dispositivo, tamanho , 
                                        EP0_TXBUFINDEX);
              break;
            case 2 :  /************ descritor de configuração ****************/
              if (tamanho>TAMANHO_TOTAL_DESCRITORES) 
                tamanho = TAMANHO_TOTAL_DESCRITORES;
              // copia o descritor para o buffer de pacotes
              cbytebuffer_to_USB_buffer(descritor_config, tamanho , 
                                        EP0_TXBUFINDEX);
              break;
            case 3 :  /************ descritores de string ********************/
              switch (req[2])
              {
                case 0: // descritor de string índice zero
                  if (tamanho>TAMANHO_DESCRITOR_STRING) 
                    tamanho = TAMANHO_DESCRITOR_STRING;
                  // copia o descritor para o buffer de pacotes
                  cbytebuffer_to_USB_buffer(descritor_string, tamanho , 
                                            EP0_TXBUFINDEX);
                  break;
                case 1: // string com o nome do fabricante
                  // copia o descritor para o buffer de pacotes
                  tamanho = cstring_to_USB_buffer(string_fabricante,
                                                  EP0_TXBUFINDEX);
                  break;
                case 2: // string com o nome do produto
                  // copia o descritor para o buffer de pacotes
                  tamanho=cstring_to_USB_buffer(string_produto,EP0_TXBUFINDEX);
                  break;
                case 3: // string com o número serial
                  // copia o descritor para o buffer de pacotes
                  tamanho=cstring_to_USB_buffer(string_serial,EP0_TXBUFINDEX);
                  break;
                default:
                  ok = 0; // não implementado
                  break;
              }
              break;
            case 0x22 : /************ descritor de report ********************/
              if (tamanho>TAMANHO_DESCRITOR_REPORT) 
                tamanho = TAMANHO_DESCRITOR_REPORT;
              // copia o descritor para o buffer de pacotes
              cbytebuffer_to_USB_buffer(descritor_report, tamanho,
                                        EP0_TXBUFINDEX);
              break;            
            default :
              ok = 0; // não implementado
              break;
          }
          // se a transação GET_DESCRIPTOR ocorreu com sucesso, retorna ACK 
          // e envia os dados
          if (ok)
          {
            // configura o número de bytes a serem transmitidos
            USB_BUFFER.BDT_EP[0].USB_COUNT_TX = tamanho;
            // configura o status de tx e rx do endpoint para VALID ( trans-
            // mite os dados e buffer na próxima transação IN) e recebe novos
            // dados na próxima transação OUT ou SETUP
            USB_EP0R = USB_EP_CTRL | USB_EP_STATUS_OUT | USB_RX_NAK_TO_VALID 
              | USB_TX_NAK_TO_VALID;
          }
          break;
        case 9 :  /************ SET_CONFIGURATION ****************************/
          // gera ACK -> pacote com zero bytes de resposta
          USB_BUFFER.BDT_EP[0].USB_COUNT_TX = 0;
          muda_estado_usb(USB_STATE_CONFIGURED);
          USB_EP0R = bCTR_TX | USB_EP_CTRL | USB_TX_NAK_TO_VALID;
          break;
        case 7 :  /************ SET_DESCRIPTOR *******************************/
        case 8 :  /************ GET_CONFIGURATION ****************************/
        case 10 : /************ GET_INTERFACE ********************************/
        case 11 : /************ SET_INTERFACE ********************************/
        default : /************ outros valores inválidos *********************/
          ok = 0;  // transação inválida
          break;
      }
      break;
    case 1: /************ requisições de classe ******************************/
      switch (bRequest)
      {
        case 1  : /************ GET_REPORT ***********************************/
          tamanho = wLength;
          switch (req[3])
          {
            case 1: // report de entrada
              if (tamanho>TAMANHO_DESCRITOR_REPORT) 
                tamanho = TAMANHO_DESCRITOR_REPORT;
              // copia o descritor para o buffer de pacotes
              cbytebuffer_to_USB_buffer(descritor_report, tamanho,
                                        EP0_TXBUFINDEX);
              // configura o número de bytes a serem transmitidos
              USB_BUFFER.BDT_EP[0].USB_COUNT_TX = tamanho;
              // configura o status de tx e rx do endpoint para VALID ( trans-
              // mite os dados e buffer na próxima transação IN) e recebe novos
              // dados na próxima transação OUT ou SETUP
              USB_EP0R = USB_EP_CTRL | USB_EP_STATUS_OUT | USB_RX_NAK_TO_VALID 
                | USB_TX_NAK_TO_VALID;
              break;              
            case 2: // report de saída
            case 3: // report de feature
              ok = 0;  // transação inválida
              break;
          }
        break;
        default:  /************** Outras requisições *************************/
          ok = 0;  // transação inválida
          break;
      }
      break;
    case 2: /************ requisições do fabricante **************************/
    case 3: /************ reservadas *****************************************/
    default:  /************ valores inválidos ********************************/
      ok = 0;  // transação inválida  
      break;
  }
  if (!ok)
  {
    // não implementado, responde com STALL
    USB_EP0R = USB_EP_CTRL | USB_RX_NAK_TO_STALL | USB_TX_NAK_TO_STALL;
  }
}

// Função de mudança de estado USB do dispositivo
// Os estados possíveis estão definidos no arquivo usb.h
void muda_estado_usb(unsigned char novo_estado)
{
  unsigned int temp;
  switch (novo_estado)
  {
    case 0: 
      // estado 0, apenas aguarda um reset
    case USB_STATE_POWERED: 
      // estado energizado, aguarda um reset
      USB_CNTR = bRESETM + bSUSPM + bWKUPM;
      break;
    case USB_STATE_DEFAULT: 
      // estado padrão, habilita a interface e configura os endpoints
      USB_DADDR = bEF;  // habilita a interface e inicializa o endereço em zero
      usb_addr = 0;
      // desativa o endpoint 1
      USB_EP1R = 0; // isto não apaga os bits STAT_RX e STAT_TX
      // a linha a seguir escreve no registrador o mesmo valor que ele continha
      // previamente. Isto provoca o toggle apenas dos bits STAT_RX e STAT_TX
      // que estavam setados, fazendo com que ambos voltem ao estado 00
      USB_EP1R = USB_EP1R;
      // ativa e configura o endpoint 0
      // primeiro apagamos todo o registrador do endpoint 0
      USB_EP0R = 0;
      USB_EP0R = USB_EP0R;
      // agora vamos configurar o buffer de recepção
      USB_BTABLE = 0;
      // o buffer de TX do EP0 inicia-se logo após o descritor de buffer do EP1
      // o buffer de TX tem 64 bytes
      USB_BUFFER.BDT_EP[0].USB_ADDR_TX = EP0_TXBUFADDR;
      // o buffer de RX do EP0 inicia-se após o buffer de TX
      USB_BUFFER.BDT_EP[0].USB_ADDR_RX = EP0_RXBUFADDR;
      // o tamanho do buffer de RX é de 64 bytes
      USB_BUFFER.BDT_EP[0].USB_COUNT_RX = BLSIZE32 | 1<<10;
      // habilita a recepção e a transmissão do EP0
      USB_EP0R = USB_EP_CTRL | USB_RX_VALID | USB_TX_VALID;
      break;
    case USB_STATE_ADDRESS: 
      // estado endereçado, o dispositivo responde aos comandos endereçados 
      // a ele
      for (temp=100000; temp; temp--);
      //while (debug);
      USB_DADDR = bEF | usb_addr;
      break;
    case USB_STATE_CONFIGURED:  
      // estado configurado, operação normal
      // configura o EP1
      // o buffer de TX do EP1 inicia-se logo após o buffer de RX do EP0
      USB_BUFFER.BDT_EP[1].USB_ADDR_TX = EP1_TXBUFADDR;
      // habilita a recepção e a transmissão do EP1
      USB_EP1R = USB_EP_INT | USB_TX_NAK | 1;
      break;
  }
  usb_state = novo_estado;  // seta usb_state para o novo estado
}

// Copia "num" bytes do buffer de bytes para o buffer USB na posição "indice"
void bytebuffer_to_USB_buffer(unsigned char *buffer, unsigned int num, 
                              unsigned int indice)
{
  unsigned int str_pos;
  str_pos = 0;  // zera o apontador do buffer de byte
  while (num)   // enquanto houverem caracteres no buffer
  {
    USB_BUFFER.DATA[indice] = 0;  // apaga a posição do buffer de pacotes
    // escreve o byte no LSB no buffer de pacotes
    USB_BUFFER.DATA[indice] = buffer[str_pos++];
    num--;  // decrementa um do número de bytes restantes
    if (!num) break;  // se não houverem mais bytes no buffer, retorna
    // escreve o byte no MSB no buffer de pacotes
    USB_BUFFER.DATA[indice++] += buffer[str_pos++]*256;
    num--;  // decrementa um do número de bytes restantes
  }
}

// Copia "num" bytes do buffer de bytes constante para o buffer USB
void cbytebuffer_to_USB_buffer(unsigned const char *buffer, unsigned int num, 
                               unsigned int indice)
{
  unsigned int str_pos;
  str_pos = 0;  // zera o apontador do buffer de byte
  while (num)   // enquanto houverem caracteres no buffer
  {
    USB_BUFFER.DATA[indice] = 0;  // apaga a posição do buffer de pacotes
    // escreve o byte no LSB no buffer de pacotes
    USB_BUFFER.DATA[indice] = buffer[str_pos++];
    num--;  // decrementa um do número de bytes restantes
    if (!num) break;  // se não houverem mais bytes no buffer, retorna
    // escreve o byte no MSB no buffer de pacotes
    USB_BUFFER.DATA[indice++] += buffer[str_pos++]*256;
    num--;  // decrementa um do número de bytes restantes
  }
}

// Copia uma string constante para o buffer USB(converte a string para UNICODE)
unsigned char cstring_to_USB_buffer(unsigned const char *buffer, 
                                    unsigned int indice)
{
  unsigned int str_pos, indice_inicial;
  indice_inicial = indice;  // memoriza a posição inicial do índice
  // os dois primeiros bytes fazem parte do descritor 
  USB_BUFFER.DATA[indice++] = 0x0300;
  str_pos = 0;  // zera o apontador do buffer de byte
  while (buffer[str_pos]) // enquanto houverem caracteres na string
  {
    USB_BUFFER.DATA[indice++] = buffer[str_pos++];  // escreve na buffer USB
  }
  // ajusta o apontador para ser igual ao dobro do número de caracteres, já
  // que cada caractere ocupa dois bytes e soma dois (cabeçalho do descritor)
  str_pos = (str_pos << 1) +  2;
  // escreve o tamanho total de bytes no primeiro byte do buffer
  USB_BUFFER.DATA[indice_inicial] |= str_pos;
  return (str_pos); // retorna o número total de bytes escritos no buffer USB
}

// Copia "num" bytes do buffer USB para um buffer de bytes
void USB_buffer_to_bytebuffer(unsigned char *buffer, unsigned int num, 
                              unsigned int indice)
{
  unsigned int str_pos;
  str_pos = 0;  // zera o apontador do buffer de byte
  while (num)   // enquanto houverem caracteres no buffer USB
  {
    // lê o LSB do buffer USB e guarda no buffer de bytes
    buffer[str_pos++] = USB_BUFFER.DATA[indice];
    num--;  // decrementa um do número de bytes restantes
    if (!num) break;  // se não houverem mais bytes no buffer, retorna
    // lê o MSB, rotaciona 8 bits à direita e guarda no buffer de bytes
    buffer[str_pos++] = USB_BUFFER.DATA[indice++] >> 8;
    num--;  // decrementa um do número de bytes restantes
  }
}

