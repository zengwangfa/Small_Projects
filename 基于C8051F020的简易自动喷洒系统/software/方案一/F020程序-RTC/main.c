#include "c8051f020.h"
#include "delay.h"
#include "lcd.h"
#include "I2C.h"
#include "keydown.h"

typedef unsigned int u16;
typedef unsigned char u8;
int Clock[16]; //读寄存器pecf8563  buffer

sbit LED = P1^6;//下载程序指示灯

extern u8 KeyValue;
extern u8 code num[],kong[],kong1[],rain[];
extern int flag_move,flag_set,Time_Count_flag;

struct Time //结构体全局变量
{
	unsigned char second;
	unsigned char minite;
	unsigned char hour;
	unsigned char day;
	unsigned char week;
	unsigned char month;
	unsigned char year;
};
struct Reg
{
	unsigned char reg1;
	unsigned char reg2;
	unsigned char clk;
	unsigned char count1;
	unsigned char count2;
};
struct Alarm
{
	unsigned char minite;
	unsigned char hour;
	unsigned char day;
	unsigned char week;
};
/*----------------函数定义声明-------------------------*/
void PORT_Init();//交叉开关使能
void SYSCLK_Init();
void Disable_Wdog();  //禁止看门狗定时器
void Clock_Setting();
void Init();             //初始化
	

void PORT_Init()//交叉开关使能
{
	XBR0    = 0x07;   // Enable UART0(TXD0-P0.0  RXD-P0.1)  SPI_SCK-P0.2  SPI_MISO-P0.3
										// SPI_MOSI-P0.4  SPI_NSS-P0.5   (SDA-P0.6   SCL-P0.7)
  XBR1    = 0x10;		// INT1使能P1.2
  XBR2    = 0x44;		// TXD1-P1.0  RXD1-P1.1
	P3MDOUT = 0xff;	
	P1MDOUT = 0xff;	
	P2MDOUT = 0xff;	
}
/*void Timer0_Init() 
	{     
		TMOD      = 0x02; //方式2 定时，自动重装载  
		TL0       = 0x06;     
		TH0       = 0x06; 
	}*/
void SYSCLK_Init()
{   
	unsigned int i;
	OSCXCN=0X67;           //0X67=0110,0111
	for(i=0;i<256;i++);    //等待>1ms
	while(!(OSCXCN&0X80)); //等待XTLVLD变为1
	OSCICN=0X88;           //时钟失效监测器，选择外部时钟源作为系统时钟
}

void Disable_Wdog()   //禁止看门狗定时器
{  
	WDTCN=0xDE;  
	WDTCN=0xAD; 
}

void Clock_Setting()
{
	struct Time TIME={0x10,0x49,0x09,0x15,0x00,0x03,0x18};//设置时间： 秒/分/时/日/星期/月/年
	struct Reg REG={0x00,0x00,0x83,0x82,0x00};//设置寄存器
	struct Alarm ALARM={0x00,0x00,0x00,0x00};//设置报时控制寄存器
	unsigned char Set[16];//写寄存器buffer
	Set[0]=REG.reg1;	
	Set[1]=REG.reg2;
	Set[2]=TIME.second;
	Set[3]=TIME.minite;
	Set[4]=TIME.hour;
	Set[5]=TIME.day;
	Set[6]=TIME.week;
	Set[7]=TIME.month;
	Set[8]=TIME.year;
	Set[9]=ALARM.minite;
	Set[10]=ALARM.hour;
	Set[11]=ALARM.day;
	Set[12]=ALARM.week;
	Set[13]=REG.clk;		//CLKOUT输出寄存器	 0DH
	Set[14]=REG.count1;	//定时器控制寄存器	 0EH
	Set[15]=REG.count2; //定时器倒计数寄存器 0FH
	//WritePcf(Set,0,16);//设置时钟
}

void Init()
{
	Disable_Wdog();
	PORT_Init();
	SYSCLK_Init();
  Initial_Lcd();//LCD初始化
	clear_screen();//清屏
	SMBusInit();//SMBus初始化 设置I2C
}
void main()
{	
	u8 i=0;
	LED=0;//下载程序成功指示灯
	Init();
	EA=1;//打开中断
	Clock_Setting();
	//Timer0_Init();//定时器0中断
	//IE = 0x82;//中断初始化
	//TR0=1;
	Delay_ms(200);
	while(1)
	{
		//Clock_Setting();//需设置时间时使用
		ReadPcf(Clock,0,16);//实时时钟显读取
		//display_graphic_8x16(1,(0+8*0),&num[KeyValue*16]);//按键值标志
		Key_setting();
		Time_Watch();
	}
}
