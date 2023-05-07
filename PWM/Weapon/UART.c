#include "UART.h"
void uart_init( u32 bound )
{
	/* GPIO???? */
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE );         /* ??USART1,GPIOA?? */

	/* USART1_TX   GPIOA.9 */
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_9;                                           /* PA.9 */
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;                                      /*?????? */
	GPIO_Init( GPIOA, &GPIO_InitStructure );                                                /* ???GPIOA.9 */

	/* USART1_RX	  GPIOA.10??? */
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_10;                                          /* PA10 */
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN_FLOATING;                                /* ???? */
	GPIO_Init( GPIOA, &GPIO_InitStructure );                                                /* ???GPIOA.10 */

	/* Usart1 NVIC ?? */
	NVIC_InitStructure.NVIC_IRQChannel			= USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 3;                            /* ?????3 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 3;                            /* ????3 */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;                       /* IRQ???? */
	NVIC_Init( &NVIC_InitStructure );                                                       /* ??????????VIC??? */

	/* USART ????? */
	USART_InitStructure.USART_BaudRate		= bound;                                /* ????? */
	USART_InitStructure.USART_WordLength		= USART_WordLength_8b;                  /* ???8????? */
	USART_InitStructure.USART_StopBits		= USART_StopBits_1;                     /* ????? */
	USART_InitStructure.USART_Parity		= USART_Parity_No;                      /* ?????? */
	USART_InitStructure.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;       /* ???????? */
	USART_InitStructure.USART_Mode			= USART_Mode_Rx | USART_Mode_Tx;        /* ???? */

	USART_Init( USART1, &USART_InitStructure );                                             /* ?????1 */
	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );                                        /* ???????? */
	USART_Cmd( USART1, ENABLE );                                                            /* ????1 */
}

u8 res;
void USART1_IRQHandler( void )                                                                        /* ??1?????? */
{
	if ( USART_GetITStatus( USART1, USART_IT_RXNE ) != RESET )                                      /* ????(?????????0x0d 0x0a??) */
	{
		res = USART_ReceiveData( USART1 );                                                      /* ???????? */
		USART_SendData(USART1, res);
	}

}




