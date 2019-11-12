/************************ 自定义公共头文件 **************************************/

#ifndef _PBDATA_H//宏定义，定义文件名称
#define _PBDATA_H
#include "stm8s.h"//引入STM8的头文件
#include <stdio.h>//需要引用这个头文件才能实现
#include "math.h"//需要引用这个头文件才能实现
#include "stm8s_tim1.h"

#include "led.h"  //引用LED头文件
#include "uart.h"
#include "i2c.h"
#include "pcf8563.h"
#include "oled.h"



typedef enum {//时间定义枚举
  sec,
  min,
  hour,
  day,
  week,
  moon,
  year
}RTC_INDEX_e;

typedef enum{
  NONE ,
  OUT , 
  IN ,
}IrDA_STATUS_e;//红外对管状态
void delay_us(u16 nCount); //微秒延时程序
void delay_ms(u16 nCount); //毫秒延时程序
u16 Get_decimal(double dt,u8 deci);   //获得数值小数部分
void Configuration_Init(void); //硬件配置初始化
#endif //定义文件名称结束


/************************ 论坛地址 www.zxkjmcu.com ******************************/