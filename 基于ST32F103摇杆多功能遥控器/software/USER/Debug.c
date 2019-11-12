#include "include.h"

extern u8 run_flag;  //1为正常模式
extern u8 mode_flag;  //
extern u8 Remote1_X,Remote1_Y;
extern u8 Remote2_X,Remote2_Y;
extern u8 CMD[6];
extern u8 check_byte;
extern u8 temp;
extern float AD_temp;
extern unsigned char JMU_LOGO[];
extern u8 page_num;
extern int recv_buffer[(MAX_DATA_LENS+4)]; //串口1接收数据缓冲变量,
extern u8 page_num;
extern u8 recv1_data_ok;
extern u8 speed;
void Display_page0(void);

u8 tFlag=1;
extern unsigned int tempDepth;

void Begin_Show()
{
	
		OLED_ShowCHinese1(32,2,16);//模式
		OLED_ShowCHinese1(48,2,17);
		OLED_ShowCHinese1(64,2,18);//模式
		OLED_ShowCHinese1(80,2,19);
		//OLED_ShowString1(38,6,"iROBOT");
		delay_ms(500);
  	OLED_Clear1(); 
		OLED_DrawBMP(3,0,123,7,JMU_LOGO);
		delay_ms(500);
	  OLED_Clear1(); 

}

void My_Show_OLED(void)           //一些固定显示
{
	temp=KEY_Scan(0);
	OLED_3num(16,1,tempDepth);
	Display_page0();

	switch(KEY_Scan(1))
  {
		case 1:
			{
				CMD[5]=0x23;
				break;
			}
		case 3:
			{
				CMD[5]=0x55;
				break;
			}
		case 5:  
			{
				
				
				break;
			}
		case 6: 
			{
				if(tFlag==1)CMD[2]=1;
				else CMD[2]=2;
				tFlag = ~tFlag;
				break;     
			}
		}
		if(page_num>2)page_num=0;
		if(page_num<1)page_num=0;
}

void Display_page0()
{
	if(page_num==0)
	{

			if(run_flag==1)		      { OLED_ShowString1(48,0,"RUN ");	}	
			else if(run_flag==0)		{ OLED_ShowString1(48,0,"STOP");		}
			Dis_Num(6,12,Remote2_X,3);//Remote1_Y

		if(mode_flag==1)
		{
			Dis_Num(4,12,Remote2_Y,3);
		}
		if(mode_flag==0)
		{
			Dis_Num(4,12,Remote1_X,3);//Remote2_X
		}

	}
}

void my_OLED()
{
			OLED_ShowCHinese1(0,0,8);//模式
			OLED_ShowCHinese1(16,0,9);
			Dis_String(32,0,":");
			OLED_ShowCHinese1(0,2,10);//前后 A4
			OLED_ShowCHinese1(16,2,11);
			Dis_String(32,2,":");
			OLED_ShowString1(0,6,"turn:");//抓取 A5  左右移动摇杆
			Dis_Num(2,12,Remote1_Y,3);  //Remote2_X
	
			OLED_ShowCHinese1(0,4,12);//上下 A6
			OLED_ShowCHinese1(16,4,13);
			Dis_String(32,4,":");
	
			OLED_ShowCHinese1(0,4,14);//左右 A7
			OLED_ShowCHinese1(16,4,15);
			Dis_String(32,4,":");
}

