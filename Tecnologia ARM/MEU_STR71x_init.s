; Arquivo de inicializa��o da CPU STR711, baseado no arquivo de inicializa��o
; fornecido pela ST

; defini��o dos modos da CPU

Modo_USR      EQU   0x10
Modo_FIQ      EQU   0x11
Modo_IRQ      EQU   0x12
Modo_SVC      EQU   0x13
Modo_ABT      EQU   0x17
Modo_UNDEF    EQU   0x1B
Modo_SYS      EQU   0x1F

; flags de interrup��o da CPU

bitI          EQU   0x80
bitF          EQU   0x40

;******************************************************************************
; Inicio do Programa
;******************************************************************************
		MODULE	?program_start
		RSEG	  IRQ_STACK:DATA(2)
		RSEG	  FIQ_STACK:DATA(2)
		RSEG	  UNDEF_STACK:DATA(2)
		RSEG	  ABT_STACK:DATA(2)		
		RSEG	  SVC_STACK:DATA(2)
		RSEG	  CSTACK:DATA(2)
		RSEG	  ICODE:CODE(2)
		PUBLIC	__program_start
		EXTERN	?main
               CODE32

;******************************************************************************
; Vetores de Exce��o
;******************************************************************************
    LDR     PC, =__program_start	; vetor de reset
    LDR     PC, =__program_start	; vetor de exce��o undefined
    LDR     PC, =__program_start	; vetor de exce��o supervisor
    LDR     PC, =__program_start	; vetor de exce��o prefetch abort
    LDR     PC, =__program_start	; vetor de exce��o data abort
    NOP                           ; Vetor reservado (n�o utilizado nos ARM7)
    LDR     PC, [PC,#-0x808]      ; IRQ - Carrega o valor do EIC_IVR no PC
    LDR     PC, =__program_start	; vetor de exce��o fiq
__program_start
    ;LDR     PC, =proxima
proxima
    NOP		;Aguarda estabiliza��o do oscilador
    ; inicializa��o das pilhas dos diversos modos
    MSR     CPSR_c, #Modo_ABT|bitF|bitI
    LDR     SP,=SFE(ABT_STACK) & 0xFFFFFFF8     ; fim da pilha do modo abt
    MSR     CPSR_c, #Modo_UNDEF|bitF|bitI
    LDR     SP,=SFE(UNDEF_STACK) & 0xFFFFFFF8   ; fim da pilha do modo und
    MSR     CPSR_c, #Modo_SVC|bitF|bitI
    LDR     SP,=SFE(SVC_STACK) & 0xFFFFFFF8     ; fim da pilha do modo svc
    MSR     CPSR_c, #Modo_FIQ|bitI              ; muda para o modo fiqQ
    LDR     SP,=SFE(FIQ_STACK) & 0xFFFFFFF8     ; fim da pilha do modo fiq
    MSR     CPSR_c, #Modo_IRQ|bitI              ; muda para o modo irq
    LDR     SP,=SFE(IRQ_STACK) & 0xFFFFFFF8     ; fim da pilha do modo irq
    MSR     CPSR_c, #Modo_USR              ; muda para modo usr, habilita I e F
    LDR     SP,=SFE(CSTACK) & 0xFFFFFFF8   ; fim da pilha CSTACK do usu�rio
    ; Coloca em reset todos os perif�ricos
    LDR     R3,=65535
    MOV     R1,#0xC0000014  ; endere�o do registrador APB1_SWRES 
    LDR     R2,=0xE0000014  ; endere�o do registrador APB2_SWRES
    STR     R3,[R1]         ; carrega APB1_SWRES com 0xFFFF
    STR     R3,[R2]         ; carrega APB2_SWRES com 0xFFFF
    ; Loop para aguardar uma eventual conex�o do JTAG
    MOV     R0,#32768       ; carrega R0 com 32768 decimal
loop
    SUBS    R0,R0,#1        ; decrementa o R0
    BNE     loop            ; desvia para loop de R0<>0
    STR     R0,[R1]         ; apaga APB1_SWRES
    STR     R0,[R2]         ; apaga APB2_SWRES
    B       ?main           ; desvia para o programa principal
    LTORG

    END

