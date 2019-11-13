#include "pbdata.h"   //引入自定义公共头文件

/*********************************************************************************
*   函 数 名: delay_us
*   功能说明: 微秒延时程序，注意此函数的运行环境为(16M时钟速度)
*   形    参：nCount要延时的微秒数，输入nCount=1微妙
*   返 回 值: 无
*********************************************************************************/
void delay_us(u16 nCount)   //16M 晶振时  延时 1个微妙
{
    nCount*=3;//等同于 nCount=nCount*3  相当于把nCount变量扩大3倍
    while(--nCount);//nCount变量数值先减一，再判断nCount的数值是否大于0，大于0循环减一，等于0退出循环。
}

/*********************************************************************************
*   函 数 名: delay_ms
*   功能说明: 毫秒延时程序，注意此函数的运行环境为(16M时钟速度)
*   形    参：nCount要延时的毫秒数，输入nCount=1毫秒
*   返 回 值: 无
*********************************************************************************/
void delay_ms(u16 nCount)  //16M 晶振时  延时 1个毫秒
{
    while(nCount--)//先判断while()循环体里的nCount数值是否大于0，大于0循环，减一执行循环体，等于0退出循环。
    {
        delay_us(1000);//调用微妙延时函数，输入1000等译演示1毫秒。
    }
}



void Configuration_Init(void)//硬件配置初始化
{  
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//时钟速度为内部16M，1分频，

  GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_OUT_PP_HIGH_SLOW);//红外对管1
  GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_SLOW);//红外对管1
  GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_SLOW);//LED
  
  GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_OUT_PP_HIGH_SLOW);//KEY1
  I2C_Configuration();
  PCF8563_Init();
  
  OLED_Init();
  OLED_Clear();
  Uart_Init();
  
  TIM1_TimeBaseInit(16,TIM1_COUNTERMODE_UP,1000,0);//16分频    1M/1000=1000
  TIM1_ARRPreloadConfig(ENABLE);
  TIM1_ITConfig(TIM1_IT_UPDATE , ENABLE);
  TIM1_Cmd(ENABLE);
  __enable_interrupt();//打开总中断
  
  for(u8 i=0;i<5;i++)//OLED显示当前人数
  {
      OLED_ShowCHinese(0+16*i,6,8+i);
  }
  OLED_ShowString(80,6,":");
}


