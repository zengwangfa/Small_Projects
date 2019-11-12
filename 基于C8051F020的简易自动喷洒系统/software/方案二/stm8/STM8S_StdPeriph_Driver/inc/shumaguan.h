#include "stm8s.h"

#define BEEP_PORT  (GPIOD)          //蜂鸣器引脚配置
#define BEEP_PINS  (GPIO_PIN_3)

void display(unsigned char i);    //显示数码管函数