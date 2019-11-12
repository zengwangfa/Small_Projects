#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"


//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)	 
 

#define KEY1_HW    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)  //  摇杆按键1
#define KEY2_HW    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) //  摇杆按键2

#define KEY1    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//读取按键0
#define KEY2    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键1
#define KEY3    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)//读取按键0
#define KEY4    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//读取按键1

#define KEY5    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//读取按键0
#define KEY6    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//读取按键1

#define KEY7    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)//读取按键0
#define KEY8    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)//读取按键1
#define KEY9    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//读取按键0
#define KEY10    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)//读取按键1

#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键2 
 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define WKUP_PRES	3		//WK_UP  

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数		

void KYE1_SHOW(void);
void KYE2_SHOW(void);

#endif
