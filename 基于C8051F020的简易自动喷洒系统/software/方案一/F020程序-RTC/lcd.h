
#include <intrins.h>   
#include <Ctype.h>  

#define uchar unsigned char    
#define uint unsigned  int   
#define ulong unsigned long

typedef unsigned char  INT8U; 
sbit sclk=P3^1;           //接口定义:lcd_sclk 就是LCD的sclk   
sbit sda=P3^2;            //接口定义:lcd_sid 就是LCD的sid   
sbit rs=P3^3;             //接口定义:lcd_rs 就是LCD的rs   
sbit reset=P3^4;          //接口定义:lcd_reset 就是LCD的reset   
sbit cs1=P3^5;            //接口定义:lcd_cs1 就是LCD的cs1  
//sbit CLCD=P3^0; 
//sbit key=P2^0;          //定义一个按键 

//void SYSCLK_Init (void); 
void Initial_Lcd();
void lcd_address(uchar page,uchar column);
void clear_screen();
void display_graphic_8x16(uchar page,uchar column,uchar *dp);
void display_graphic_16x16(uchar page,uchar column,uchar *dp); 
//void display_graphic_32x32(uchar page,uchar column,uchar *dp);  
void delay(int i) ;
void lcddelay_us(int i);
void transfer_command(int data1);
void transfer_data(int data1);
//void zifukong();
void Time_Watch();
void Time_Display();
