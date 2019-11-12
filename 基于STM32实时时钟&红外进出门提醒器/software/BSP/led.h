/***********************************************************************
*    剑齿虎STM8开发板硬件连接
*    LED1-PE0          
*    LED2-PA3          
*    LED3-PA6          
************************************************************************/

#ifndef _LED_H  //宏定义，定义文件名称
#define _LED_H

/*---------------------------头文件引用--------------------------------------*/
#include "stm8s.h"//引用STM8头文件

/*---------------------------宏定义声明--------------------------------------*/
#define LED1_PIN GPIO_PIN_0  //定义GPIO_PIN_0引脚为LED1_PIN，相当于重新命名。
#define LED2_PIN GPIO_PIN_3  //定义GPIO_PIN_3引脚为LED2_PIN，相当于重新命名。
#define LED3_PIN GPIO_PIN_6  //定义GPIO_PIN_6引脚为LED3_PIN，相当于重新命名。

#define LED1_PORT GPIOE  //定义GPIOE端口为LED1_PORT，相当于重新命名。
#define LED2_PORT GPIOA  //定义GPIOA端口为LED2_PORT，相当于重新命名。
#define LED3_PORT GPIOA  //定义GPIOA端口为LED3_PORT，相当于重新命名。

//如果想用其他管脚控制LED,那么只需更改上面对应的端口与引脚编号即可

#define LED1_L GPIO_WriteLow(LED1_PORT,LED1_PIN);       //定义LED1_L,调用LED1_L命令，PE0引脚输出低电平
#define LED1_H GPIO_WriteHigh(LED1_PORT,LED1_PIN);      //定义LED1_H,调用LED1_H命令，PE0引脚输出低高平
#define LED1_R GPIO_WriteReverse(LED1_PORT,LED1_PIN);   //定义LED1_R,调用LED1_R命令，PE0引脚输出电平状态取反

#define LED2_L GPIO_WriteLow(LED2_PORT,LED2_PIN);       //定义LED2_L,调用LED2_L命令，PA3引脚输出低电平
#define LED2_H GPIO_WriteHigh(LED2_PORT,LED2_PIN);      //定义LED2_H,调用LED2_H命令，PA3引脚输出低高平
#define LED2_R GPIO_WriteReverse(LED2_PORT,LED2_PIN);   //定义LED2_R,调用LED2_R命令，PA3引脚输出电平状态取反

#define LED3_L GPIO_WriteLow(LED3_PORT,LED3_PIN);       //定义LED3_L,调用LED2_L命令，PA6引脚输出低电平
#define LED3_H GPIO_WriteHigh(LED3_PORT,LED3_PIN);      //定义LED3_H,调用LED2_H命令，PA6引脚输出低高平
#define LED3_R GPIO_WriteReverse(LED3_PORT,LED3_PIN);   //定义LED3_R,调用LED2_R命令，PA6引脚输出电平状态取反

/*---------------------------函数声明--------------------------------------*/
void LED_Init(void);  //LED初始化函数
void LED_Demo1(void); //闪烁例程1，间隔时间为1秒
void LED_Demo2(void); //闪烁例程2，间隔时间为1秒

#endif //定义文件名称结束


/************************ 论坛地址 www.zxkjmcu.com ******************************/