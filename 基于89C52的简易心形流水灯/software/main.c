/**************************************************************************************
*		              点亮第一个LED实验												  *
实现现象：下载程序后D1指示灯点亮
注意事项：无																				  
***************************************************************************************/


#include "reg52.h"			 //′????t?D?¨ò?á?μ￥???úμ?ò?D?ì?êa1|?ü??′??÷



typedef unsigned int uint;	  //??êy?YààDí??DDéù?÷?¨ò?
typedef unsigned char uchar;
sbit k1=P3^0;
sbit k2=P3^1;
sbit k3=P3^2;
sbit beepIO=P3^7;
uchar code table0[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//LED从低位往高位移
uchar code table1[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//LED从高位往低位移
uchar code table2[]={0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00};//LED从1个亮到8个都点亮(从低位往高位)
uchar code table3[]={0x7f,0x3f,0x1f,0x0f,0x07,0x03,0x01,0x00};//LED从1个亮到8个都点亮(从高位往低位)
uchar code table4[]={0x00,0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};//LED从8个全亮到一个都不亮(从低位往高位)
uchar code table5[]={0x00,0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff};//LED从8个全亮到一个都不亮(从高位往低位)
uchar code table6[]={0xfe,0xfc,0xfa,0xf6,0xee,0xde,0xbe,0x7e};//LED从低位往高位移(最低位始终为0)
uchar code table7[]={0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e};//LED从高位往低位移(最高位始终为0)
uchar code table8[]={0x7e,0xbd,0xdb,0xe7}; //两边往中间一个一个亮
uchar code table9[]={0x7e,0x3c,0x1e,0x00};  //两边往中间逐渐都点亮
uchar code table10[]={0xe7,0xc3,0x81,0x00};  //中间往两边逐渐都点亮
uchar code table11[]={0x18,0x3c,0x7e,0xff};  //中间往两边从全亮逐渐都不亮
uchar code table12[]={0xe0,0xc0,0x80,0x00};  //P1左边全亮，右边从底部开始一个一个亮直到全亮
uchar code table13[]={0x07,0x03,0x01,0x00};  //P1右边全亮，左边从底部开始一个一个亮直到全亮
uchar code table14[]={0x80,0xc0,0xe0,0xf0};  //P1左边全亮，从右边开始全亮直到全灭
uchar code table15[]={0xef,0xcf,0x8f,0x0f};  //P1左边全灭，右边从底部开始一个一个亮直到全亮
uchar code table16[]={0x0e,0x0c,0x08,0x00};  //P1右边全亮，从左边开始到底部一个一个亮直到全亮
uchar code table17[]={0x10,0x30,0x70,0xf0};  //P1左边全亮，从右边开始全亮直到全灭
uchar code table18[]={0x1f,0x3f,0x7f,0xff};  //P1右边全灭，左边从开始一个一个灭直到全灭 
uchar i,j;		//定义循环变量
uchar m,n; 
uint cycle=500,high,low;
uchar code T[49][2]={{0,0},
{0xF8,0x8B},{0xF8,0xF2},{0xF9,0x5B},{0xF9,0xB7},{0xFA,0x14},{0xFA,0x66},{0xFA,0xB9},{0xFB,0x03},{0xFB,0x4A},{0xFB,0x8F},{0xFB,0xCF},{0xFC,0x0B},
{0xFC,0x43},{0xFC,0x78},{0xFC,0xAB},{0xFC,0xDB},{0xFD,0x08},{0xFD,0x33},{0xFD,0x5B},{0xFD,0x81},{0xFD,0xA5},{0xFD,0xC7},{0xFD,0xE7},{0xFE,0x05},
{0xFE,0x21},{0xFE,0x3C},{0xFE,0x55},{0xFE,0x6D},{0xFE,0x84},{0xFE,0x99},{0xFE,0xAD},{0xFE,0xC0},{0xFE,0x02},{0xFE,0xE3},{0xFE,0xF3},{0xFF,0x02},
{0xFF,0x10},{0xFF,0x1D},{0xFF,0x2A},{0xFF,0x36},{0xFF,0x42},{0xFF,0x4C},{0xFF,0x56},{0xFF,0x60},{0xFF,0x69},{0xFF,0x71},{0xFF,0x79},{0xFF,0x81}
};
uchar code music[][2]={{0,4},
{0,4},{24,4},{24,4},{21,4},{19,4},{21,4},{14,8},{19,4},{21,4},{24,4},{21,4},{19,16},{0,4},{24,4},{24,4},{21,4},{19,4},{21,4},{12,8},{19,4},{21,4},{24,4},{19,4},{17,16},{0,4},{17,4},{19,4},{21,4},
{24,4},{26,4},{24,4},{22,4},{24,4},{21,4},{21,4},{19,4},{19,16},{0,4},
{17,4},{19,4},{17,4},{17,4},{19,4},{17,4},{19,4},{19,4},{21,8},{24,4},{21,4},{21,12},{0,4},{24,4},{24,4},{21,4},{19,4},{21,4},{14,8},{19,4},{21,4},{24,4},{21,4},{19,16},{0,4},{24,4},{24,4},{21,4},
{19,4},{21,4},{12,8},{19,4},{21,4},{24,4},{19,4},{17,16},{0,4},{17,4},{19,4},{21,4},{24,4},{26,4},{24,4},{22,4},{24,4},{21,4},{21,4},{19,4},{19,12},{12,4},{21,8},{19,4},{19,8},{17,16},
{0xFF,0xFF}};


void delay1(uchar p)
{
uchar i,j; 
for(;p>0;p--)
for(i=181;i>0;i--)
for(j=181;j>0;j--);
}
void delay2(uint i)
{
	while(i--);
}

void pause()
{
uchar i,j;
for(i=150;i>0;i--)
for(j=150;j>0;j--);
}


void T0_int() interrupt 1
{
P0=P2=0Xc3;
P1=0X81;
beepIO=!beepIO;
TH0=T[m][0]; TL0=T[m][1];
P2=P1=P0=0XFF;
}






void delay(uint time)	//延时函数
{
	uint x,y;
	for(x=time;x>0;x--)
	for(y=110;y>0;y--);
}
void disp0()			//状态0 所有LED闪烁3次
{
	for(i=0;i<3;i++)
	{
		P2=0x00; P1=0x00; P0=0x00; 
		delay(300);
		P0=0xff; P2=0xff; P1=0xff;
		delay(300);
	}
}

void disp1()			//状态1 LED顺时针转一圈
{
	for(i=0;i<8;i++)
	{
		P2=table1[i];
		delay(50);
	}
	P2=0xff;
	for(i=0;i<8;i++)
	{
		P1=table1[i];
		delay(50);
	}
	P1=0xff;
	for(i=0;i<8;i++)
	{
		P0=table0[i];
		delay(50);
	}
	P0=0xff;
}

void disp2()			//状态2 LED逆时针转一圈
{
	for(i=0;i<8;i++)
	{
		P0=table1[i];
		delay(50);
	}
	P0=0xff;
	for(i=0;i<8;i++)
	{
		P1=table0[i];
		delay(50);
	}
	P1=0xff;
	for(i=0;i<8;i++)
	{
		P2=table0[i];
		delay(50);
	}
	P2=0xff;
}

void disp3()			//状态3 3个LED同时顺时、逆时针移动1/3圈
{
	for(i=0;i<8;i++)
	{
		P0=table1[i];
		P1=table0[i];
		P2=table0[i];		
		delay(100);
	}
	for(i=0;i<8;i++)
	{
		P0=table0[i];
		P1=table1[i];
		P2=table1[i];
		delay(100);
	}
	P0=0xff;P1=0xff; P2=0xff; 
}

void disp4()			//状态4  
{
	for(i=0;i<12;i++)
	{
		if(i<8)
		{
			P0=table1[i];
			P2=table1[i];
		}
		else
		{
			P0=0xff; P2=0xff;
		 	P1=table8[i];
		}	
		delay(100);
	}
		P1=0xff;	
}
void disp5()			//状态5 
{
	for(i=0;i<12;i++)
	{
		if(i<4)
		{
			P1=table8[3-i];	
		}
		else
		{
			P1=0xff;
			P0=table0[i];
			P2=table0[i];
		}	
		delay(100);
	}
		P0=0xff; P2=0xff;	
}
void disp6()			//状态6 LED自上而下逐渐点亮(一半点亮一半不亮)
{
	for(i=0;i<8;i++)
	{
		P0=table3[i];
		P2=table3[i];
		delay(100);
	}
	P0=0xff; P2=0xff;
	for(i=0;i<4;i++)
	{
		P1=table9[i];		
		delay(100);
	}
	P1=0xff;
}

void disp7()			//状态7 LED自下而上逐渐点亮(直到全部点亮)
{
	for(i=0;i<4;i++)
	{
		P1=table9[i];
		delay(100);
	}
	for(i=0;i<8;i++)
	{
		P0=table2[i];
		P2=table2[i];
		delay(100);
	}
}

void disp10()			//状态10 从LED全部亮到全不亮(间断8格的3个LED开始逆时针熄灭)
{
	for(i=0;i<9;i++)
	{
		P0=table5[i];
		P2=table4[i];
		P1=table4[i];
		delay(100);
	}
	delay(300);
}

void disp11()			//状态11 间断8格的3个LED亮并顺时针旋转
{
	for(j=0;j<2;j++)
	{
		for(i=0;i<8;i++)
		{
			P0=table0[i];
			P2=table1[i];
			P1=table1[i];
			delay(100);
		}
		P0=0xff; P2=0xff; P1=0xff;
		for(i=0;i<8;i++)
		{
			P0=table0[i];
			P2=table1[i];
			P1=table1[i];
			delay(100);
		}
		P0=0xff; P2=0xff; P1=0xff; 
	}
}

void disp12()			//间断8格的3个LED亮，然后顺时针逐渐点亮(直到全部点亮)
{
	for(i=0;i<8;i++)
	{
		P0=table2[i];
		P2=table3[i];
		P1=table3[i];
		delay(100);
	}
	delay(1000);
}

void disp13()			//状态13 从LED全部亮到全不亮(间断8格的3个LED开始顺时针熄灭)
{
	for(i=0;i<8;i++)
	{
		P0=table4[i];
		P2=table5[i];
		P1=table5[i];
		delay(100);
	}
	delay(300);
}

void disp14()			//状态14 从LED不亮到全亮(从P0.0、P1.0、P1.7、P2.0开始逐步点亮)
{
	for(i=0;i<8;i++)
	{
		P0=table2[i];
		P2=table2[i];
		if(i<4)
		{
			P1=table8[i];
		}		
		delay(100);
	}
}

void disp15()			//状态15 从LED全亮到全不亮(从P0.7、P1.3、P1.4、P2.7开始逐步熄灭)
{
	for(i=0;i<8;i++)
	{
		P0=table5[i];
		P2=table5[i];
		if(i<4)
		{
			P1=table11[i];
		}		
		delay(100);
	}
}

void disp16()			//状态16 LED灯交替闪烁(频率有慢变快)
{
	for(i=0;i<5;i++)
	{
		P0=0xaa; P1=0x55; P2=0xaa;
		delay(100);
		P0=~P0; P1=~P1; P2=~P2; 
		delay(100);
	}
	for(i=0;i<5;i++)
	{
		P0=0xaa; P1=0x55; P2=0xaa;
		delay(200);
		P0=~P0; P1=~P1; P2=~P2;
		delay(200);
	}
	for(i=0;i<5;i++)
	{
		P0=0xaa; P1=0x55; P2=0xaa;
		delay(300);
		P0=~P0; P1=~P1; P2=~P2;
		delay(300);
	}
	P0=0xff; P2=0xff; P1=0xff; 
	delay(300);
}

void disp17()  //状态17 LED从P0.7开始逆时针逐步点亮,并且速度会逐步提高
{
	for(i=0;i<4;i++)
	{
		P1=table3[3-i];	
		delay(100);
	}
	for(i=0;i<8;i++)
	{
		P0=table2[i];
		delay(100);
	}
	for(i=0;i<4;i++)
	{
		P1=table12[i];	
		delay(100);	
	}
	for(i=0;i<8;i++)
	{
		P2=table2[i];
		delay(100);
	}
	P0=0xff; P1=0xff; P2=0xff;
/************再循环一次****************/
for(i=0;i<4;i++)
	{
		P1=table3[3-i];	
		delay(50);
	}
	for(i=0;i<8;i++)
	{
		P0=table2[i];
		delay(50);
	}
	for(i=0;i<4;i++)
	{
		P1=table12[i];	
		delay(50);	
	}
	for(i=0;i<8;i++)
	{
		P2=table2[i];
		delay(50);
	}
	P0=0xff; P1=0xff;P2=0xff;
			
}

void disp19()			//状态19 LED从P2.7开始顺时针逐步点亮,(循环2次)并且速度会逐步提高
{
	for(i=0;i<8;i++)
	{
		P2=table3[i];
		delay(100);
	}
	for(i=0;i<4;i++)
	{
		P1=table3[i];
		delay(100);
	}	
	for(i=0;i<8;i++)
	{
		P0=table3[i];
		delay(100);
	}	
	for(i=0;i<4;i++)
	{
		P0=table13[i];
		delay(100);
	}
	P0=0xff; P1=0xff;P2=0xff;
/*******************************/
	for(i=0;i<8;i++)
	{
		P2=table3[i];
		delay(50);
	}
	for(i=0;i<4;i++)
	{
		P1=table3[i];
		delay(50);
	}	
	for(i=0;i<8;i++)
	{
		P0=table3[i];
		delay(50);
	}	
	for(i=0;i<4;i++)
	{
		P0=table13[i];
		delay(50);
	}
	P0=0xff; P1=0xff; P2=0xff;
}

void disp23()			//状态23 LED上下交替闪烁
{

	for(i=0;i<2;i++)
	{
		P0=0x00; P2=0x00;
		delay(1000);
		P0=0xff; P2=0xff;
		P1=0x00;
		delay(1000);
		P1=0xff;
	}
}

void disp39()			//状态39 P1一直亮,上半部分LED向外扩张亮,然后闪烁3次
{
	P1=0x00;
	for(i=0;i<8;i++)
	{
		P0=table3[i];
		P2=table3[i];
		delay(50);
	}
	for(i=0;i<8;i++)
	{
		P0=table3[i];
		P2=table3[i];
		delay(100);
	}
	for(i=0;i<4;i++)
	{
		P0=~P0; P2=~P2;
		delay(80);
	}
	delay(200);
	P1=0xff; P2=0xff;P0=0xff;
} 

void disp32()			//状态32 LED自上而下逐步点亮，然后从下往上逐步熄灭
{
	for(i=0;i<8;i++)
	{
		P0=table3[i];
		P2=table3[i];
		delay(100);
	}
	for(i=0;i<4;i++)
	{
		P1=table8[i];
		delay(100);
	}
	for(i=0;i<4;i++)
	{
		P1=table11[i];
		delay(100);
	}
	for(i=0;i<8;i++)
	{
		P0=table4[i];
		P2=table4[i];
		delay(100);
	}
}

void disp33()			//状态33 LED从左往右开始点亮(直到全亮)，然后从左右两边开始熄灭(直到全部熄灭)
{
	for(i=0;i<8;i++)
	{
		P0=table2[i];		
		if(i<4)
		{
			P1=table2[i];
		}		
		delay(100);
	}
	for(i=0;i<8;i++)
	{		
		P2=table3[i];
		if(i<4)
		{
			P1=table12[i];
		}		
		delay(100);
	}
/****************************/
	for(i=0;i<8;i++)
	{
		P2=table4[i];		
		if(i<4)
		{
			P1=table14[i];
		}		
		delay(100);
	}
	for(i=0;i<8;i++)
	{
		P0=table5[i];		
		if(i<4)
		{
			P1=table5[i+5];
		}		
		delay(100);
	}
}

void disp36()			//状态36  从P0.7、P1.4开始同时逆时针旋转，直到LED全亮
{
	for(i=0;i<8;i++)
	{
	 	if(i<4)	 P1=table15[i];
	 	if(i<8)	 P0=table3[i];	  
		delay(100);
	}
	for(i=0;i<8;i++)
	{
		if(i<4)	 P1=table16[i];
	 	if(i<8)	 P2=table2[i];
		delay(100);
	}
}

void disp40()			//状态40 LED从P1.4、P0.7开始逆时针同时熄灭，直到LED全部熄灭
{
	for(i=0;i<8;i++)
	{
		if(i<4)	 P1=table17[i];
	 	if(i<8)	 P0=table3[i];
		delay(100);
	}
	for(i=0;i<8;i++)
	{
		if(i<4)	 P1=table18[i];
	 	if(i<8)	 P2=table2[i];
		delay(100);
	}
	delay(300);	
}

void disp28()			//状态28 P1、P2和P0交替闪烁
{	
	for(i=0;i<2;i++)
	{
		P1=0x0f; P2=0x00;  
		delay(1000);
		P1=0xf0; P2=0xff; P0=0x00; 
		delay(1000);
	}
	P1=0xff; P2=0xff; P0=0xff;
}

void disp66()
{
	for(i=0;i<10;i++)
	{
		P0=0xff;
		P2=0x00;
		P1=0x0f;
		delay(80);
		P1=0xf0;
		P2=0xff;
		P0=0x00;		
		delay(80);
	}
	P1=P0=P2=0X00;
}




			

void main()
{
	uchar i=0; 
	TMOD=0x01; EA=1; ET0=1;
	while(1)
	{
	if(k1==0)
	{
	   delay(100);
	   if(k1==0)
	   {  
		disp0();	//状态0 所有LED闪烁3次
		disp1();	//状态1 LED顺时针转一圈
		disp2();	//状态2 LED逆时针转一圈	
		disp3();	//状态3 3个LED同时顺时、逆时针移动1/3圈
		disp4();	//状态4  2个LED同时从顶部中间开始往两边到底部移动半圈
		disp5();	//状态5  2个LED同时从底部中间开始往两边到顶部移动半圈
		disp6();	//状态6 LED自上而下逐渐点亮(一半点亮一半不亮)
		disp7();	//状态7 LED自下而上逐渐点亮(直到全部点亮)
		disp0();	//状态0 所有LED闪烁3次
		disp10();	//状态10 从LED全部亮到全不亮
		disp11();	//状态11 间断8格的3个LED亮并顺时针旋转
		disp12();	//状态12 间断8格的3个LED亮，然后顺时针逐渐点亮(直到全部点亮)
		disp13();	//状态13 从LED全部亮到全不亮(间断8格的3个LED开始顺时针熄灭)
		disp14();	//状态14 从LED不亮到全亮(从P0.0、P1.0、P1.7、P2.0开始逐布点亮)
		disp15();	//状态15 从LED全亮到全不亮(从P0.7、P1.3、P1.4、P2.7开始逐步熄灭)
		disp16();	//状态16 LED灯交替闪烁(频率有慢变快)
		disp17();	//状态17 LED从P0.7开始逆时针逐步点亮,并且速度会逐步提高
		disp19();	//状态19 LED从P2.7开始顺时针逐步点亮,(循环2次)并且速度会逐步提高
		disp23();	//状态23 LED上下交替闪烁
		disp39();	//状态39 P1(下半部分)一直亮,上半部分LED向外扩张亮,然后闪烁3次
		disp32();	//状态32 LED自上而下逐步点亮，然后从下往上逐步熄灭
		disp33();	//状态33 LED从左往右开始点亮(直到全亮)，然后从左右两边开始熄灭(直到全部熄灭)
		disp36();	//状态36  从P0.7、P1.4开始同时逆时针旋转，直到LED全亮
		disp40();	//状态40 从P0.7、P1.4开始逆时针同时熄灭，直到LED全部熄灭
		disp28();	//状态28 P1、P2和P0交替闪烁
		disp66();	//状态66 左右边交叉闪
		}
		while(!k1);
	}
	if(k2==0)
	{
		delay(100);
		if(k2==0)
		{
		while(1)
		{		
		for(high=1;high<cycle;high++)
		{
			P2=P1=P0=0XFF;
			delay2(high);
			P2=P1=P0=0X00;
			low=cycle-high;
			delay2(low);
		}			
		for(low=1;low<cycle;low++)
		{
			
			P2=P1=P0=0XFF;;
			high=cycle-low;
			delay2(high);
			P2=P1=P0=0X00;
			delay2(low);
		}
     	}
	}
		while(!k2);
		}
	if(k3==0)
	{	
		delay(100);
		if(k3==0)
		{
		while(1)
		{		
			m=music[i][0];n=music[i][1]; 
		if(m==0x00)
		{TR0=0;delay1(n);i++;} 
		else if(m==0xFF)
		{TR0=0;delay1(30);i=0;} 
		else if(m==music[i+1][0]) 
		{TR0=1;delay1(n);TR0=0;pause();i++;}
		else
		{TR0=1;delay1(n);i++;}
		}
		}
	}
	}
	while(!k3);		
}