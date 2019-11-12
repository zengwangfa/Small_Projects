#include "c8051F020.h"
#include "uart.h"
#include "delay.h"
#include "intrins.h"
/************************************************************************************/

/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/


/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/
//#define INPUTSIZE  256	// 输入缓冲区256字节
//#define OUTPUTSIZE 256	// 输出缓冲区256字节
		
	unsigned char m_InputBuf[INPUTSIZE];  /* 接收缓冲区Comm_SendFinish:21*/
	unsigned char m_OutputBuf[OUTPUTSIZE];/* 发送缓冲区*/
	unsigned char m_SendFirstPos;	  	  /* 发送缓冲区首索引*/
	unsigned char m_SendLastPos;	  	  /* 发送缓冲区尾索引*/
	unsigned char m_ReceiveFirstPos;	  /* 接收缓冲区首索引*/
	unsigned char m_ReceiveLastPos;	  	  /* 接收缓冲区尾索引*/
	volatile unsigned char m_SendOver;

/************************************************************************************
*  Uart0子程序
*************************************************************************************/
/***********************************************************************************
* 函数名称：Uart0_Init;
*
* 函数功能描述：Uart0初始化;
*              
* 输入参数：unsigned char类型，发送数据波特率;
*
* 返回数据：none；
*
* 注意：    none;
************************************************************************************/

void Uart0_Init(unsigned char BaudRate) //Uart0初始化        
{                                    
	TR1=0;                              // 关闭定时器Timer1
	ET1=0;                              // 关闭定时器Timer1中断 
	PT1=0;                              // 关闭定时器Timer1中断优先权
	TMOD&= 0x0f;                        // TMOD: 定时器1, 模式2, 8位重载 
	TMOD|= 0x20;                        // TMOD: 定时器1, 模式2, 8位重载 
  SCON0  = 0x50;                      // SCON0: 模式1, 8位UART, 使能RX
  PCON  |= 0x80;                      // SMOD00 = 1
	if (BaudRate>=BaudRate_4800)
	{
	 	CKCON |= 0x10;                             // 定时器Timer1使用系统时钟作为时间基准
	 	TH1    = -(SYSCLK/1200/(BaudRate*16));     // 设置定时器Timer1重载值
	}
	else
	{
		CKCON &= ~0x10;                               // 定时器Timer1使用系统时钟作为时间基准
	 	TH1    = -(SYSCLK/1200/(BaudRate*16*12));     // 设置定时器Timer1重载值
	}
		ES0=0;             				 // 关闭串口Uart0中断
		PS=0;             				 // 关闭串口Uart0中断优先权
	  TI0  = 1;                  // Indicate TX0 ready
    RI0  = 0;                  // Indicate RX0 ready
    TR1=1;							 // 打开串口Uart0
    RI0=0;
		TI0=0;
    ES0=1;
    m_ReceiveLastPos=m_ReceiveFirstPos=0;
		m_SendFirstPos=m_SendLastPos=0;	  	  /* 发送缓冲区首索引*/	
}

/***********************************************************************************
* 函数名称：Uart0_Enable;
*
* 函数功能描述：Uart0初始化;
*              
* 输入参数：bool类型，打开输入1；关闭输入0;
*
* 返回数据：none；
*
* 注意：    none;
************************************************************************************/

void Uart0_Enable(bool Flag)
{
    PS=1;
	//PT0=0;
	if (Flag)
		TR1=1;   // 打开串口Uart0
	else
        TR1=0;   // 关闭串口Uart0
}



/***********************************************************************************
* 函数名称：GetReciLen;
*
* 函数功能描述：Uart0接收串行数据长度计算;
*              
* 输入参数：none;
*
* 返回数据：unsigned char类型，串行口接收数据长度为m_ReceiveLastPos-m_ReceiveFirstPos；
*
* 注意：    none;
************************************************************************************/

unsigned char GetReciLen(void)
{
//	WDTCN=0xA5;
	return(m_ReceiveLastPos-m_ReceiveFirstPos);
}

/***********************************************************************************
* 函数名称：ReadString;
*
* 函数功能描述：Uart0接收串行数据;
*              
* 输入参数：unsigned char* str接收数据返回目的数组，unsigned char len接收数据长度;
*
* 返回数据：unsigned char类型，实际上接收到的数据个数；
*
* 注意：    none;
************************************************************************************/
unsigned char ReadString(unsigned char* str, unsigned char len)
{
	register unsigned char i, j;
	j=GetReciLen();
	if(j>len)
		j=len;
	for(i=0; i<j; i++)
	{
		str[i]=m_InputBuf[m_ReceiveFirstPos++];
	//	WDTCN=0xA5;
	}
	return i;
}


void Uart0Send(unsigned char ch)
{
	SBUF0=ch;							//送入缓冲区
	while (TI0 == 0);     //等待发送完毕
  TI0=0;                // 清零
}

void Uart0Sends(unsigned char *str)
{
	while(*str!='\0')
	{
		SBUF0=*str;
		str++;
		while (TI0 == 0);     // Wait for the transmit to complete
    TI0=0;                // Clear TI1
	}
}

void Uart0_ISR(void) interrupt 4 using 1
{
	if(RI0)
	{
		RI0=0;   // 清除RI0标志位
	  m_InputBuf[m_ReceiveLastPos++]=SBUF0;
	}
	else 
	{
		TI0=0;	
		if(m_SendFirstPos!=m_SendLastPos)
		{
	 		SBUF0=m_OutputBuf[m_SendFirstPos];
			m_SendFirstPos++;
		}
		else
		{
			m_SendOver = 1;
		}
	}
}


