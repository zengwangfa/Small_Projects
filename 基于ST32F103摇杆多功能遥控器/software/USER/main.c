/**
   初始化为 停止状态；右摇杆为上下模式
	 2018.6.10
	 摇杆操纵方向与 引脚标的Vx,Vy相反
**/

#include "include.h"



int main(void)
{ 
	
  Perpheral_Init();      //外部初始化
	Begin_Show();          //开机界面
	TIM_Cmd(TIM3, ENABLE); //使能TIMx外设
	my_OLED();
	while(1)
	{ 
			CMD_Send();
			My_Show_OLED();
	}											    
}	




