/************************************************************************************
*  Copyright (c) 2004,西安铭朗电子科技有限责任公司
*            All rights reserved.
*
* 文件名称： I2C.C
* 文件标识： none
* 适用器件： c8051f0f0、PCF8563
* 
* 摘 要： 本文件是I2C总线子程序；将跳线器JP5短接; 使用外部22.1184MHz晶振.
* 
* 当前版本：1.0
* 作 者：卢 阳
* 完成日期：2004年11月14日
*
* 历史版本：0.9 
* 原作者 ： 卢阳、张宁强
* 完成日期：2004年1月1日
*************************************************************************************/

/************************************************************************************/
// 引用外部头文件

#include "c8051f020.h"
#include "I2C.h"
//#include "gpsone.h"
#include "delay.h"

/************************************************************************************/

/************************************************************************************/
// 全局变量
/************************************************************************************/

unsigned char Command;//命令缓存
int *I2CDataBuff;//待法发数据、接收数据指针
unsigned char ByteNumber;  //发送字节数
unsigned char ByteReadBytes;//读字节数
int *ByteReadAddress;//读缓冲区指针
unsigned char ChipChoice;//芯片选择，0选择RTC、1选择24C256							

bit BusBusy;//总线忙
bit NoStop;//发送完一组数据后不发送停止位

/***********************************************************************************
* 函数名称：SMBusInit;
*
* 函数功能描述：SMBus初始化;
*              
* 输入参数：none;
*
* 返回数据：none；
*
* 注意：    none;
************************************************************************************/

void SMBusInit(void)//SMBus初始化
{
	SMB0CN=0x44;//SMBus控制寄存器
	SMB0CR=0xee;//SCL速率设置l_0xed--0xf0
	EIE1=EIE1|0x02;//开启中断
	EIP1=EIP1|0x02;//设置IIC中断优先级
	//NoStop=0;
	NoStop=1;
	
}

/***********************************************************************************
* 函数名称：SMBusService;
*
* 函数功能描述：SMBus中断响应服务程序，判断状态码进行下步操作;
*              
* 输入参数：none;
*
* 返回数据：none；
*
* 注意：    none;
************************************************************************************/

void SMBusService (void) interrupt 7
{
	switch (SMB0STA)
		{
		case 0x08: //0x08起始条件已发送
			SMB0DAT=Command;
			STA=0; 
			break;

		case 0x10://0x10 重复起始条件已发送
			SMB0DAT=Command;
			STA=0;
			break;
			
		case 0x18://0x18 地址+W已发送收到ACK
			if (ByteNumber>0)
			{
				SMB0DAT=*I2CDataBuff;
				I2CDataBuff++;
				ByteNumber--;			
			}
			else
			{
				STO=1;
				BusBusy=0;
			}
			break;

		case 0x20://0x20 地址+W 已发送收到NACK,从器件不应答发送STOP + START 重试
			STO=1;
			STA=1;
			break;

		case 0x28://0x28 数据字节已发送收到ACK
			if (ByteNumber>0)
			{
				SMB0DAT=*I2CDataBuff;
				I2CDataBuff++;
				ByteNumber--;			
			}
           /*else
			{
				STO=1;
				BusBusy=0;
			}*/
			 else
			{
				if(NoStop)
					{
						STO=1;
						BusBusy=0;
					}
				else 
					{
						//STO=0;
						//AA=1;
						if(ChipChoice)
							Command=I2C24AddressR;
						else
							Command=I2CPcfAddressR;
						I2CDataBuff=ByteReadAddress;
						ByteNumber=ByteReadBytes;
						STA=1;
						NoStop=1;
					 }				
			}

			break;

		case 0x30://0x30 数据字节已发送收到NACK,从器件不应答发送STOP + START 重试
			STO=1;
			STA=1;
			break;

		case 0x38://0x38 竞争失败
			STO=1;
			STA=1;
			break;

		case 0x40://0x40 地址+R 已发送,收到ACK
			if(ByteNumber>1) 
				AA=1; // 在应答周期ACK
			else 
				AA=0; 

			if (ByteNumber==0)
			{	
				STO=1;
				BusBusy=0; // 释放SMBus
			}
			break;

		case 0x48://0x48 地址+R 已发送收到NACK,从器件不应答发送重复起始条件重试
			STA=1;
			break;

		case 0x50://0x50 收到数据字节ACK 已发送
			if (ByteNumber>0)
			{
				*I2CDataBuff=SMB0DAT;
				I2CDataBuff++;
				ByteNumber--;			
			}
			if (ByteNumber==1) AA=0;
			break;

		case 0x58://0x58 收到数据字节NACK 已发送
			*I2CDataBuff=SMB0DAT;
			STO=1;
			BusBusy=0; // 释放SMBus
			NoStop=1;

			break;
			
		default:// 其它状态码没有意义,复位SMBus
			STO=1;
			BusBusy=0;
			break;
		}
	SI=0; // 清除中断标志
}




/***********************************************************************************
* 函数名称：ReadPcf;
*
* 函数功能描述：读PCF8563;
*              
* 输入参数：unsigned char类型指针BytesAddress，读出数据存储的头地址;
*	    unsigned char 类型RomAddress，片内地址;
*	    unsigned char 类型Count，读数据个数;
*
* 返回数据：none；
*
* 注意：    none;
************************************************************************************/

void ReadPcf( int *BytesAddress,int RomAddress,unsigned char Count)//读PCF8563
{
/*
	while (BusBusy);
	I2CDataBuff=&RomAddress;
	BusBusy=1;
	AA=1;
	NoStop=0;
	ByteNumber=1;
	Command=I2CPcfAddressW;
	STA=1;
	while (BusBusy);
    NoStop=1;
	I2CDataBuff=BytesAddress;
	BusBusy=1;
	AA=1;
	ByteNumber=Count;
	Command=I2CPcfAddressR;
	STA=1;
	while (BusBusy);*/


	ChipChoice=0;
	ByteReadAddress=BytesAddress;
	ByteReadBytes=Count;    
  while (BusBusy);
	I2CDataBuff=&RomAddress;//存储空间地址
	BusBusy=1;
	AA=1;
	//NoStop=1;
	NoStop=0;
	ByteNumber=1;
	Command=I2CPcfAddressW;//设备写地址
	STA=1;
	while (BusBusy);
}

/***********************************************************************************
* 函数名称：WritePcf;
*
* 函数功能描述：写PCF8563;
*              
* 输入参数：unsigned char类型指针BytesAddress，写入数据的头地址;
*	    unsigned char 类型RomAddress，片内地址;
*	    unsigned char 类型Count，写数据个数;
*
* 返回数据：none；
*
* 注意：    none;
************************************************************************************/
/*
void WritePcf(unsigned char *BytesAddress,unsigned char RomAddress,unsigned char Count)//写PCF8563
{
	int xdata TempBuff[17],n;
	ChipChoice=0;
	TempBuff[0]=RomAddress;
	for(n=1;n<(Count+1);n++)
	{
		TempBuff[n]=*BytesAddress++;
	}
	while (BusBusy);
	NoStop=1;
	I2CDataBuff=&TempBuff[0];
	BusBusy=1;
	AA=1;
	ByteNumber=Count+1;
	Command=I2CPcfAddressW;
	STA=1;
	while (BusBusy);
}*/

/***********************************************************************************/
// 文件结束
/***********************************************************************************/
