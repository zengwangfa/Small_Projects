#include "pbdata.h"
/*********************************************************************************
*   函 数 名: UART1_Congfiguration
*   功能说明: UART1 配置函数
*   形    参：无
*   返 回 值: 无
*********************************************************************************/
void UART1_Congfiguration(void)
{
    //配置串口参数为：波特率115200，8位数据位，1位停止位，无校验，禁止同步传输，允许接收发送
    UART1_Init((u32)115200,UART1_WORDLENGTH_8D,UART1_STOPBITS_1,UART1_PARITY_NO,UART1_SYNCMODE_CLOCK_DISABLE,UART1_MODE_TXRX_ENABLE);
    UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);//使能接收中断
    UART1_Cmd(ENABLE);//使能UART1
}
/*********************************************************************************
*   函 数 名: UART1_Send_Byte
*   功能说明: UART1发送数据函数
*   形    参：u8 byte  一次发送一个字节
*   返 回 值: 无
*********************************************************************************/
void UART1_Send_Byte(u8 byte)
{
    UART1_SendData8(byte);//UART1发送8位数据
    while(UART1_GetFlagStatus(UART1_FLAG_TXE)==RESET);//等待发送完成
}

void UART1_Printf_Demo(void)
{
    //u16 d2=123;
    //u32 d1=12345678;
    //u8 d3='a';
    //u8 d5[5];
  double d4=(double)145.23412;
    
    
  printf("%d.%d\r\n",(u16)d4,Get_decimal(d4,4));
  
  printf("%d.%d\r\n",(u16)d4,Get_decimal(d4,2));
  
    //printf("%ld\r\n",d1);
    
    
    //printf("%6.4d\r\n",d2);
    //printf("%8x\r\n",d2);
    //printf("%X\r\n",d2);
    
    //printf("%c\r\n",d3);
    
    /*d5[0]='a';
    d5[1]='b';
    d5[2]='c';
    d5[3]='d';
    d5[4]='\0';
    
    printf("%s\r\n",d5);*/
    
    while(1);
}


//printf函数
#ifdef __GNUC__
    #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
    #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE //发送一个字符协议
{
/* 将Printf内容发往串口 */
  UART1_SendData8((unsigned char) ch);
  while (!(UART1->SR & UART1_FLAG_TXE));//如果发送未完成， //标志位未置位，则循环等待
  return (ch);
}


/************************ 论坛地址 www.zxkjmcu.com ******************************/