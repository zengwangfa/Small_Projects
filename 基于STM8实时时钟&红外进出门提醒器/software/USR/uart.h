
#ifndef __UART_H
#define __UART_H
#include "stm8s_uart1.h"

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
#define RxBufferSize 64

void Uart_Init(void);
void UART1_SendByte(u8 data);
void UART1_SendString(u8* Data,u16 len);
u8 UART1_ReceiveByte(void);

#endif