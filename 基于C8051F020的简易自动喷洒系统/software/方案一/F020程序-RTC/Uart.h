/************************************************************************************
*  Copyright (c) 2004,西安铭朗电子科技有限责任公司
*            All rights reserved.
*
* 文件名称： Uart.c
* 文件标识： none
* 适用器件： C8051F020
* 
* 摘 要： 本文件是串口0、1子程序头文件；使用外部22.1184MHz晶振. Uart驱动程序，包括初始化、
*	  波特率设置，单字节发送接收、字符串发送接受等。将跳线器JP7、JP11短接。
* 	  使用外部22.1184MHz晶振。
* 当前版本：1.0
* 作 者：卢 阳
* 完成日期：2004年11月14日
*
* 历史版本：0.9 
* 原作者 ： 李林利
* 完成日期：2004年1月1日
*************************************************************************************/

#define INPUTSIZE  256	// 输入缓冲区256字节
#define OUTPUTSIZE 256	// 输出缓冲区256字节
		
extern unsigned char m_InputBuf[INPUTSIZE];  /* 接收缓冲区Comm_SendFinish:21*/
extern unsigned char m_OutputBuf[OUTPUTSIZE];/* 发送缓冲区*/
extern unsigned char m_SendFirstPos;	  	  /* 发送缓冲区首索引*/
extern unsigned char m_SendLastPos;	  	  /* 发送缓冲区尾索引*/
extern unsigned char m_ReceiveFirstPos;	  /* 接收缓冲区首索引*/
extern unsigned char m_ReceiveLastPos;	  	  /* 接收缓冲区尾索引*/
//extern struct	Time	PKTimeNow;

extern unsigned char m_InputBuf11[INPUTSIZE];
extern unsigned char m_ReceiveFirstPos11;
extern	unsigned char m_ReceiveLastPos11;


#define  bool   unsigned char
#define  SYSCLK   22118400      //SYSCLK frequency in Hz
#define DisableUart0	ES0=0
#define EnableUart0		ES0=1
#define BaudRate_1200    1		//1*1200
#define BaudRate_2400    2		//2*1200
#define BaudRate_4800    4		//4*1200
#define BaudRate_9600    8		//8*1200
#define BaudRate_19200   16		//16*1200
#define BaudRate_38400   32		//32*1200
#define BaudRate_57600   48		//48*1200
#define BaudRate_115200  96		//96*1200
#define BaudRate_230400  192		//192*1200

#define RI1  SCON1&0x01
#define TI1  SCON1&0x02

#define WDT_CLOSE   EA=0; WDTCN=0xde; WDTCN=0xad; EA=1;
#define WDT_OPEN    WDTCN = 0xff;
#define WDT_CLR     WDTCN = 0xa5;

/************************************************************************************/
// 函数外部引用声明

void SYSCLK_Init (void);
void PORT_Init (void);

void Uart0_Init(unsigned char BaudRate);
void Uart0_Enable(bool Flag);
unsigned char ReadString(unsigned char* str, unsigned char len);
void Uart0Send(unsigned char ch);
void Uart0Sends(unsigned char *str);
void Uart0_ISR(void);



