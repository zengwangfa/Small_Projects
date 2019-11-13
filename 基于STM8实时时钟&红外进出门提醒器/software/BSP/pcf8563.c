#include "pbdata.h"

u8 time_buf[7];

typedef struct Time //时间信息 结构体全局变量
{
  u8 year;
    u8 month;
      u8 week;
        u8 day;
          u8 hour;
            u8 minite;
              u8 second;
};
void PCF8563_WriteByte(u8 addr,u8 dt)
{
    I2C_Start();
    
    I2C_Send_Byte(PCF8563_ADDRESS);
    I2C_Wait_Ack();
    
    I2C_Send_Byte((u8)(addr));
    I2C_Wait_Ack();
    
    I2C_Send_Byte(dt);
    I2C_Wait_Ack();
    
    I2C_Stop();    
}

void PCF8563_SetTime(void)
{

    struct Time TIME={0x18,0x10,0x06,0x21,0x21,0x53,0x30};//设置时间： 年->月->周->日->时->分->秒
//    sec=BcdToHex(50);
//    min=BcdToHex(34);
//    hour=BcdToHex(2);
//    day=BcdToHex(18);
//    week=3;
//    moon=BcdToHex(10);
//    year=BcdToHex(18);
    
    PCF8563_WriteByte(0x02,TIME.second);
    PCF8563_WriteByte(0x03,TIME.minite);
    PCF8563_WriteByte(0x04,TIME.hour);
    PCF8563_WriteByte(0x05,TIME.day);
    PCF8563_WriteByte(0x06,TIME.week);
    PCF8563_WriteByte(0x07,TIME.month);
    PCF8563_WriteByte(0x08,TIME.year);
}

void PCF8563_GetTime(u8 *buf)
{
    I2C_Start();
    
    I2C_Send_Byte(PCF8563_ADDRESS);
    I2C_Wait_Ack();
    
    I2C_Send_Byte(0x02);
    I2C_Wait_Ack();
    
    I2C_Start();    
    
    I2C_Send_Byte(PCF8563_ADDRESS+1);//A3
    I2C_Wait_Ack();
    
    buf[0]=I2C_Read_Byte(1);
    buf[1]=I2C_Read_Byte(1);
    buf[2]=I2C_Read_Byte(1);
    buf[3]=I2C_Read_Byte(1);
    buf[4]=I2C_Read_Byte(1);
    buf[5]=I2C_Read_Byte(1);
    buf[6]=I2C_Read_Byte(0);
    
    I2C_Stop();
    
    buf[0]=buf[0]&0x7F;//秒
    buf[1]=buf[1]&0x7F;//分
    buf[2]=buf[2]&0x3F;//时
    buf[3]=buf[3]&0x3F;//日
    buf[4]=buf[4]&0x07;//星期
    buf[5]=buf[5]&0x1F;//月
    
    buf[0]=HexToBcd(buf[0]);
    buf[1]=HexToBcd(buf[1]);
    buf[2]=HexToBcd(buf[2]);
    buf[3]=HexToBcd(buf[3]);
    buf[5]=HexToBcd(buf[5]);
    buf[6]=HexToBcd(buf[6]);  //年  
}

void PCF8563_Init(void)
{
    PCF8563_WriteByte(0x00,0);
    PCF8563_WriteByte(0x01,0);
    //PCF8563_SetTime();  //当设定好时间，关闭初始化设定时间
}

void PCF8563_ShowTime(void)
{
    static u8 last_sec=0;
    //void OLED_ShowNum(u8 x,u8 y,u8 num,u8 len,u8 size2);
    //void OLED_ShowString(u8 x,u8 y, u8 *p);	
    last_sec=time_buf[0];
    PCF8563_GetTime(time_buf);

    OLED_ShowNum(0,0,20,2,16);
    OLED_ShowNum(16,0,time_buf[6],2,16);
    OLED_ShowString(32,0,"-");
    OLED_ShowNum(40,0,time_buf[5],2,16);
    OLED_ShowString(56,0,"-");
    OLED_ShowNum(64,0,time_buf[3],2,16);
            
    OLED_ShowCHinese(96,0,0);//星期 
    OLED_ShowCHinese(112,0,time_buf[4]+1);//2 
    
    OLED_ShowNum(48,2,time_buf[2],2,16);
    OLED_ShowString(64,2,":");
    OLED_ShowNum(80,2,time_buf[1],2,16);
    if(last_sec != time_buf[sec]){
      if(time_buf[sec]%2 == 0){//偶数显示“：”  奇数显示“ ”
        OLED_ShowString(96,2,":");
      }
      else{OLED_ShowString(96,2," ");}
    }
    
    OLED_ShowNum(112,2,time_buf[0],2,16);
}




