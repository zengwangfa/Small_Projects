/********************  ********************
 * 文件名  ：main.c
 * 描述    ：RC522(RFID）模块  
 * 实验平台：STM8S103F3P6核心板
 * 库版本  ：V1.0.0
 * 作者    ：
 * 博客    ：
*修改时间 ：
    |--------------------|
    |  USART1_RX-PD4     |
    |  USART1_TX-PD5     |
    |--------------------|
**********************************************************************************/

#include "uart.h"
#include "stm8s_uart1.h"
#include "stm8s_clk.h"

/* ********************************************
UART1  configured as follow:
  - BaudRate = 115200 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Receive and transmit enabled
 -  Receive interrupt
  - UART1 Clock disabled
*********************************************/
void Uart_Init(void)
{
    UART1_DeInit();
    UART1_Init((u32)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO , UART1_SYNCMODE_CLOCK_DISABLE , UART1_MODE_TXRX_ENABLE);
    UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE  );
    UART1_Cmd(ENABLE);
  
}

void UART1_SendByte(u8 data)
{
    UART1_SendData8((unsigned char)data);
  /* Loop until the end of transmission */
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
}


void UART1_SendString(u8* Data,u16 len)
{
  u16 i=0;
  for(;i<len;i++)
    UART1_SendByte(Data[i]);
  
}

u8 UART1_ReceiveByte(void)
{
     u8 USART1_RX_BUF; 
     while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
     USART1_RX_BUF=UART1_ReceiveData8();
     return  USART1_RX_BUF;
    
}

