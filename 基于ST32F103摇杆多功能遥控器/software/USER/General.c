#include "include.h"

u8 run_flag =0;  //1为正常模式
u8 mode_flag=0;  //

u8 Remote1_X=0,Remote1_Y=0;
u8 Remote2_X=0,Remote2_Y=0;

u8 CMD[6]={0};
u8 SBuff[4]={0};
u8 check_byte=0;
u8 temp=0;
float AD_temp=0;

u8 page_num=0;
u8 speed=140;
u8 send_flag=0;





void CMD_Send()
{
	check_byte = 0xaa+0x55+0x07+CMD[0]+CMD[1]+CMD[2]+CMD[3]+CMD[4]+CMD[5];
	USART_SendData(USART1,0xaa);
	USART_SendData(USART1,0x55);
	USART_SendData(USART1,0x07);  //数据长度，单字节扣除起始位和校验位，包含数据长度位
	USART1_Sends(CMD,sizeof(CMD));  //发送控制数据
	USART_SendData(USART1,check_byte);  //发送校验字节
	CMD[5] = 0;
}
