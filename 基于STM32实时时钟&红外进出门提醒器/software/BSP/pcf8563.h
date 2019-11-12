#ifndef _PCF8563_H  //宏定义，定义文件名称
#define _PCF8563_H

/*---------------------------头文件引用--------------------------------------*/
#include "stm8s.h"//引用STM8头文件

#define PCF8563_ADDRESS 0xA2
#define BcdToHex(dec) ((dec/10)<<4)+(dec%10)
#define HexToBcd(hex) ((hex>>4)*10)+(hex%16)


void PCF8563_WriteByte(u8 addr,u8 dt);
void PCF8563_SetTime(void);
void PCF8563_GetTime(u8 *buf);
void PCF8563_Init(void);
void PCF8563_ShowTime(void);

#endif