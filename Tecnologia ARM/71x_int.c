/*******************************************************************************

 Funções de Tratamento de Interrupção do STR711

*******************************************************************************/

void Undefined_Handler   (void);
void FIQ_Handler         (void);
void SWI_Handler         (void);
void Prefetch_Handler    (void);
void Abort_Handler       (void);
void T0TIMI_IRQHandler   (void);
void FLASH_IRQHandler    (void);
void RCCU_IRQHandler     (void);
void RTC_IRQHandler      (void);
void WDG_IRQHandler      (void);
void XTI_IRQHandler      (void);
void USBHP_IRQHandler    (void);
void I2C0ITERR_IRQHandler(void);
void I2C1ITERR_IRQHandler(void);
void UART0_IRQHandler    (void);
void UART1_IRQHandler    (void);
void UART2_IRQHandler    (void);
void UART3_IRQHandler    (void);
void BSPI0_IRQHandler    (void);
void BSPI1_IRQHandler    (void);
void I2C0_IRQHandler     (void);
void I2C1_IRQHandler     (void);
void CAN_IRQHandler      (void);
void ADC12_IRQHandler    (void);
void T1TIMI_IRQHandler   (void);
void T2TIMI_IRQHandler   (void);
void T3TIMI_IRQHandler   (void);
void HDLC_IRQHandler     (void);
void USBLP_IRQHandler    (void);
void T0TOI_IRQHandler    (void);
void T0OC1_IRQHandler    (void);
void T0OC2_IRQHandler    (void);

/******************************************************************************
* Nome da Função  : Undefined_Handler
* Descrição       : Tratamento da exceção Undefined
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void Undefined_Handler(void)
{
}

/*******************************************************************************
* Nome da Função  : FIQ_Handler
* Descrição       : Tratamento da interrupção FIQ
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void FIQ_Handler(void)
{
}

/*******************************************************************************
* Nome da Função  : SWI_Handler
* Descrição       : Tratamento da exceção de interrupção por software (SWI)
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void SWI_Handler(void)
{
}

/*******************************************************************************
* Nome da Função  : Prefetch_Handler
* Descrição       : Tratamento da exceção de aborto de prefetch
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void Prefetch_Handler(void)
{
}

/*******************************************************************************
* Nome da Função  : Abort_Handler
* Descrição       : Tratamento da exceção de aborto de dados (data abort)
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void Abort_Handler(void)
{
}

/*******************************************************************************
* Nome da Função  : T0TIMI_IRQHandler
* Descrição       : Tratamento global das interrupções do timer 0
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void T0TIMI_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : FLASH_IRQHandler
* Descrição       : Tratamento global das interrupções do controlador da FLASH
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void FLASH_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : RCCU_IRQHandler
* Descrição       : Tratamento global das interrupções do RCCU
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void RCCU_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : RTC_IRQHandler
* Descrição       : Tratamento global das interrupções do RTC
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void RTC_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : WDG_IRQHandler
* Descrição       : Tratamento da interrupção do Watchdog
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void WDG_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : XTI_IRQHandler
* Descrição       : Tratamento das interrupções externas (XTI)
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void XTI_IRQHandler(void)
{
  piscando = !piscando;
  XTI_PRH = 0;
}

/*******************************************************************************
* Nome da Função  : USBHP_IRQHandler
* Descrição       : Tratamento das interrupções de alta prioridade da USB
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void USBHP_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : I2C0ITERR_IRQHandler
* Descrição       : Tratamento da interrupção de erro da I2C 0
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void I2C0ITERR_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : I2C1ITERR_IRQHandler
* Descrição       : Tratamento da interrupção de erro da I2C 1
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void I2C1ITERR_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : UART0_IRQHandler
* Descrição       : Tratamento global das interrupções da UART 0
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void UART0_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : UART1_IRQHandler
* Descrição       : Tratamento global das interrupções da UART 1
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void UART1_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : UART2_IRQHandler
* Descrição       : Tratamento global das interrupções da UART 2
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void UART2_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : UART3_IRQHandler
* Descrição       : Tratamento global das interrupções da UART 3
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void UART3_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : BSPI0_IRQHandler
* Descrição       : Tratamento global das interrupções da SPI 0
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void BSPI0_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : BSPI1_IRQHandler
* Descrição       : Tratamento global das interrupções da SPI 1
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void BSPI1_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : I2C0_IRQHandler
* Descrição       : Tratamento global das interrupções da I2C 0
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void I2C0_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : I2C1_IRQHandler
* Descrição       : Tratamento global das interrupções da I2C 1
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void I2C1_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : CAN_IRQHandler
* Descrição       : Tratamento global das interrupções da interface CAN
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void CAN_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : ADC12_IRQHandler
* Descrição       : Tratamento da interrupção do ADC12
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void ADC12_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : T1TIMI_IRQHandler
* Descrição       : Tratamento global das interrupções do timer 1
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void T1TIMI_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : T2TIMI_IRQHandler
* Descrição       : Tratamento global das interrupções do timer 2
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void T2TIMI_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : T3TIMI_IRQHandler
* Descrição       : Tratamento global das interrupções do timer 3
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void T3TIMI_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : HDLC_IRQHandler
* Descrição       : Tratamento global das interrupções da interface HDLC
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void HDLC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USBLP_IRQHandler
* Description    : This function handles USB low priority event interrupt.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBLP_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : T0TOI_IRQHandler
* Descrição       : Tratamento da interrupção de transbordo do timer 0
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void T0TOI_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Função  : T0OC1_IRQHandler
* Descrição       : Tratamento da interrupção de comparação do canal 1 do timer 0
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void T0OC1_IRQHandler(void)
{
}


/*******************************************************************************
* Nome da Função  : T0OC2_IRQHandler
* Descrição       : Tratamento da interrupção de comparação do canal 2 do timer 0
* Entrada         : Nada
* Saída           : Nada
* Retorna         : Nada
*******************************************************************************/
void T0OC2_IRQHandler(void)
{
}
