#include "c8051f020.h"
#include "delay.h"
#include "I2C.h"
#include "PCF8563.h"

struct Time
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


	struct Time TIME={0x01,0x22,0x15,0x01,0x01,0x01,0x18};//ÉèÖÃÊ±¼ä
	struct Reg REG={0x00,0x00,0x83,0x82,0x00};//ÉèÖÃ¼Ä´æÆ÷
	struct Alarm ALARM={0x00,0x00,0x00,0x00};//ÉèÖÃ±¨Ê±¿ØÖÆ¼Ä´æÆ÷
	unsigned char xdata Time[16]; //¶Á¼Ä´æÆ÷pecf8563  buffer
	unsigned char set[16];//Ğ´¼Ä´æÆ÷buffer
	
	set[0]=REG.reg1;			//¿ØÖÆ×´Ì¬¼Ä´æÆ÷1  00H
	set[1]=REG.reg2;			//¿ØÖÆ×´Ì¬¼Ä´æÆ÷1  01H
	set[2]=TIME.second;
	set[3]=TIME.minite;
	set[4]=TIME.hour;
	set[5]=TIME.day;
	set[6]=TIME.week;
	set[7]=TIME.month;
	set[8]=TIME.year;
	set[9]=ALARM.minite;
	set[10]=ALARM.hour;
	set[11]=ALARM.day;
	set[12]=ALARM.week;
	set[13]=REG.clk;		//CLKOUTÊä³ö¼Ä´æÆ÷	 0DH
	set[14]=REG.count1;	//¶¨Ê±Æ÷¿ØÖÆ¼Ä´æÆ÷	 0EH
	set[15]=REG.count2; //¶¨Ê±Æ÷µ¹¼ÆÊı¼Ä´æÆ÷ 0FH