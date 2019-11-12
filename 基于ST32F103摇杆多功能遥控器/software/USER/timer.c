#include "include.h"

extern u8 Remote1_X,Remote1_Y;
extern u8 Remote2_X,Remote2_Y;

extern u8 run_flag;  //1为正常模式
extern u8 mode_flag;  //
extern u8 Remote1_X,Remote1_Y;
extern u8 Remote2_X,Remote2_Y;
extern u8 CMD[6];
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
			TIM3, //TIM2
			TIM_IT_Update ,
			ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, DISABLE);          //禁止TIMx外设
							 
}
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{

			KYE1_SHOW();
			KYE2_SHOW();
	
			Remote1_X = Get_Adc_Value(ADC_Channel_10);  //①Y   --->A4 /  通道4   
			Remote1_Y = Get_Adc_Value(ADC_Channel_11);  //①X   --->A5 /  通道5   	
			Remote2_X = Get_Adc_Value(ADC_Channel_13);  //②X   --->A7 /  通道7  
			Remote2_Y = Get_Adc_Value(ADC_Channel_12);  //②Y   --->A6 /  通道6  
			CMD[0]=run_flag;    //开启标志位
			CMD[1]=Remote1_Y;   //前后
			//CMD[2]=mode_flag;		//状态标志位
			if(mode_flag==0){CMD[3]=Remote2_X;}//上下
			else{CMD[3]=Remote2_Y;}//左右
			CMD[4]=Remote1_X;   //抓取释放
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );   //清除TIMx的中断待处理位:TIM 中断源

	}
}
