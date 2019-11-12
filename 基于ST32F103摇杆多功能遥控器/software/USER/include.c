#include "include.h"



void Perpheral_Init(void)                         //蜂箱控制外围初始化
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为115200
	KEY_Init();          	//初始化与按键连接的硬件接口
	LED_Init();		  		//初始化与LED连接的硬件接口

 	Adc_Init(GPIO_Pin_0);		  		//ADC初始化	  
 	Adc_Init(GPIO_Pin_1);		  		//ADC初始化	
 	Adc_Init(GPIO_Pin_2);		  		//ADC初始化	  
 	Adc_Init(GPIO_Pin_3);		  		//ADC初始化		 
	TIM3_Int_Init(1000,7199);                       //10Khz的计数频率，计数到5000为500ms
	OLED_Init();
	
}




