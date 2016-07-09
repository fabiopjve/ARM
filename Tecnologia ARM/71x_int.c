/*******************************************************************************

 Fun��es de Tratamento de Interrup��o do STR711

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
* Nome da Fun��o  : Undefined_Handler
* Descri��o       : Tratamento da exce��o Undefined
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void Undefined_Handler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : FIQ_Handler
* Descri��o       : Tratamento da interrup��o FIQ
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void FIQ_Handler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : SWI_Handler
* Descri��o       : Tratamento da exce��o de interrup��o por software (SWI)
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void SWI_Handler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : Prefetch_Handler
* Descri��o       : Tratamento da exce��o de aborto de prefetch
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void Prefetch_Handler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : Abort_Handler
* Descri��o       : Tratamento da exce��o de aborto de dados (data abort)
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void Abort_Handler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : T0TIMI_IRQHandler
* Descri��o       : Tratamento global das interrup��es do timer 0
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void T0TIMI_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : FLASH_IRQHandler
* Descri��o       : Tratamento global das interrup��es do controlador da FLASH
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void FLASH_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : RCCU_IRQHandler
* Descri��o       : Tratamento global das interrup��es do RCCU
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void RCCU_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : RTC_IRQHandler
* Descri��o       : Tratamento global das interrup��es do RTC
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void RTC_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : WDG_IRQHandler
* Descri��o       : Tratamento da interrup��o do Watchdog
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void WDG_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : XTI_IRQHandler
* Descri��o       : Tratamento das interrup��es externas (XTI)
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void XTI_IRQHandler(void)
{
  piscando = !piscando;
  XTI_PRH = 0;
}

/*******************************************************************************
* Nome da Fun��o  : USBHP_IRQHandler
* Descri��o       : Tratamento das interrup��es de alta prioridade da USB
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void USBHP_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : I2C0ITERR_IRQHandler
* Descri��o       : Tratamento da interrup��o de erro da I2C 0
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void I2C0ITERR_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : I2C1ITERR_IRQHandler
* Descri��o       : Tratamento da interrup��o de erro da I2C 1
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void I2C1ITERR_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : UART0_IRQHandler
* Descri��o       : Tratamento global das interrup��es da UART 0
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void UART0_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : UART1_IRQHandler
* Descri��o       : Tratamento global das interrup��es da UART 1
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void UART1_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : UART2_IRQHandler
* Descri��o       : Tratamento global das interrup��es da UART 2
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void UART2_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : UART3_IRQHandler
* Descri��o       : Tratamento global das interrup��es da UART 3
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void UART3_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : BSPI0_IRQHandler
* Descri��o       : Tratamento global das interrup��es da SPI 0
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void BSPI0_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : BSPI1_IRQHandler
* Descri��o       : Tratamento global das interrup��es da SPI 1
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void BSPI1_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : I2C0_IRQHandler
* Descri��o       : Tratamento global das interrup��es da I2C 0
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void I2C0_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : I2C1_IRQHandler
* Descri��o       : Tratamento global das interrup��es da I2C 1
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void I2C1_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : CAN_IRQHandler
* Descri��o       : Tratamento global das interrup��es da interface CAN
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void CAN_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : ADC12_IRQHandler
* Descri��o       : Tratamento da interrup��o do ADC12
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void ADC12_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : T1TIMI_IRQHandler
* Descri��o       : Tratamento global das interrup��es do timer 1
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void T1TIMI_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : T2TIMI_IRQHandler
* Descri��o       : Tratamento global das interrup��es do timer 2
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void T2TIMI_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : T3TIMI_IRQHandler
* Descri��o       : Tratamento global das interrup��es do timer 3
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void T3TIMI_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : HDLC_IRQHandler
* Descri��o       : Tratamento global das interrup��es da interface HDLC
* Entrada         : Nada
* Sa�da           : Nada
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
* Nome da Fun��o  : T0TOI_IRQHandler
* Descri��o       : Tratamento da interrup��o de transbordo do timer 0
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void T0TOI_IRQHandler(void)
{
}

/*******************************************************************************
* Nome da Fun��o  : T0OC1_IRQHandler
* Descri��o       : Tratamento da interrup��o de compara��o do canal 1 do timer 0
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void T0OC1_IRQHandler(void)
{
}


/*******************************************************************************
* Nome da Fun��o  : T0OC2_IRQHandler
* Descri��o       : Tratamento da interrup��o de compara��o do canal 2 do timer 0
* Entrada         : Nada
* Sa�da           : Nada
* Retorna         : Nada
*******************************************************************************/
void T0OC2_IRQHandler(void)
{
}
