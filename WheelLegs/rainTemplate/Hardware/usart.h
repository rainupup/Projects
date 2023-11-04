
#ifndef STM32_USART1_H
#define STM32_USART1_H
/******************************************************************************/
#include "stdio.h"
#include "stm32f10x.h"

/******************************************************************************/
#define USART_REC_LEN 256
/******************************************************************************/
extern unsigned char USART_RX_BUF[USART_REC_LEN];
extern unsigned short USART_RX_STA;
/******************************************************************************/
void uart_init(unsigned long bound);
/******************************************************************************/

uint16_t Usart_GetData(void);
#endif
