/************************************************************************************
*  Copyright (c) 2004,西安铭朗电子科技有限责任公司
*            All rights reserved.
*
* 文件名称： I2C.h
* 文件标识： none
* 适用器件： C8051F020
* 
* 摘 要： 本文件是I2C总线子程序头文件；将跳线器JP5短接; 使用外部22.1184MHz晶振.
* 
* 当前版本：1.0
* 作 者：卢 阳
* 完成日期：2004年11月14日
*
* 历史版本：0.9 
* 原作者 ： 卢 阳、张宁强
* 完成日期：2004年1月1日
*************************************************************************************/
//extern struct	Time	PKTimeNow;
/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/

#define I2C24AddressW 0xa0		//24C硬件地址_写
#define I2C24AddressR 0xa1		//24C硬件地址_读

#define I2CPcfAddressW 0xa2		//PCF8563硬件地址_写
#define I2CPcfAddressR 0xa3		//PCF8563硬件地址_读

#define TRUE 0xFF
#define FALSE 0x00
#define ONEPAGE 0x08
/************************************************************************************/
// 函数外部引用声明

void SMBusInit(void);//SMBus初始化

//unsigned char VWriteI2C(unsigned char *BytesAddress,unsigned int RomAddress,unsigned char Count);

//void WriteI2C(unsigned char *BytesAddress,unsigned int  RomAddress,unsigned char Count);

//void ReadI2C(unsigned char *BytesAddress,unsigned int  RomAddress,unsigned char Count);

void SMBusService();
void ReadPcf( int *BytesAddress,int RomAddress,unsigned char Count);
//void WritePcf(unsigned char *BytesAddress,unsigned char RomAddress,unsigned char Count);//写入时钟

void WriteI2CPages(unsigned char *BytesAddress,unsigned int  RomAddress,unsigned char Count);
void ReadI2CPages(unsigned char *BytesAddress,unsigned int  RomAddress,unsigned char Count);
/*
unsigned char RTCRead(unsigned char *RTCTime);
void WritePcf(unsigned char *BytesAddress,unsigned char RomAddress,unsigned char Count);

void ReadPcf(unsigned char *BytesAddress,unsigned char RomAddress,unsigned char Count);
*/
/************************************************************************************/

