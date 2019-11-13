#include "pbdata.h"  //引入自定义公共头文件

u8 Time_Remind_CMD[]={0x7E,0x05,0x41,0x00,0x01,0x45,0xEF};//整点报时
u8 IN_CMD[]={0x7E,0x05,0x41,0x00,0x19,0x5D,0xEF};//进门声   0x19 -> 0025   
u8 OUT_CMD[]={0x7E,0x05,0x41,0x00,0x1A,0x5E,0xEF};//出门声  0x20 -> 0026

u8 IO_flag = 0;//进出标志位
u8 status = 0;
u8 People_num=0;

BitStatus KEY1;
BitStatus IrDA_OUT;
BitStatus  IrDA_IN;

//volatile RTC_INDEX_e rtc_index; //变量rtc_index为    枚举型RTC_INDEX_e
////volatile表示强调修饰符，则会从内存重新装载内容，而不是直接从寄存器拷贝内容
extern u8 time_buf[];

void On_Time_Alarm(void);    //准点报时
void Detection_Number_Of_People(void);//人数检测


int main(void)
{
  Configuration_Init();//硬件配置初始化

  while(1)
  {
    KEY1 = GPIO_ReadInputPin(GPIOC, GPIO_PIN_7);//播放
    
//    if(KEY1 == 0)
//    {
//        UART1_SendString(IN_CMD,sizeof(IN_CMD));
//    }
    PCF8563_ShowTime();
    On_Time_Alarm();  
    Detection_Number_Of_People();
  }
}

void On_Time_Alarm(void)//准点报时
{
  static u8 once_flag = 0;
  if(time_buf[sec] ==0 && time_buf[min] == 0 )
  {
    if(once_flag == 0)
    {
      Time_Remind_CMD[4]=time_buf[hour]+1;  //时间段选号码
      Time_Remind_CMD[5]=0x05^0x41^0x00^(Time_Remind_CMD[4]);  //生成校验码
      UART1_SendString(Time_Remind_CMD,sizeof(Time_Remind_CMD));
      once_flag=1;
    }
    if(time_buf[day]==0){//午间12点人数清零
      People_num=0;  
    }
  }
  if(time_buf[min] == 1){once_flag = 0; }//只为一次发送
  
}

void Detection_Number_Of_People(void)//人数检测
{
  IrDA_OUT = GPIO_ReadInputPin(GPIOA, GPIO_PIN_1);//外侧红外对管    检测到为0
  IrDA_IN  = GPIO_ReadInputPin(GPIOA, GPIO_PIN_2);//内侧红外对管    检测到为0
  
  if(IO_flag == NONE){ 
    if(IrDA_OUT == 0 && IrDA_IN != 0) { IO_flag = IN; }
    else if(IrDA_OUT != 0 && IrDA_IN == 0) { IO_flag = OUT; }  //进出门 标志位
  }
  
  if(IO_flag == IN){  
    if( (IrDA_OUT != 0 && IrDA_IN == 0 ) ||(IrDA_OUT == 0 && IrDA_IN == 0 )) { status = 2; }
  }
  
  else if(IO_flag == OUT){
    if( (IrDA_OUT == 0 && IrDA_IN != 0 ) ||(IrDA_OUT == 0 && IrDA_IN == 0 )) { status = 4; }
  }
  else {status = 0;}

    
  if(status == 2){
    UART1_SendString(IN_CMD,sizeof(IN_CMD));
    People_num++;
    status=0;
    IO_flag=NONE;
  }
  if(status == 4){
    UART1_SendString(OUT_CMD,sizeof(OUT_CMD));
    if(People_num==0){People_num=0;}
    else{People_num--;}
    status=0;
    IO_flag=NONE;

  }

   
  OLED_ShowNum(96,6,People_num,2,16);
  
}









/*断言函数：它的作用是在编程的过程中为程序提供参数检查*/
#ifdef USE_FULL_ASSERT
void assert_failed(u8* file,u32 line)
{
  while(1)
  {
  }
}
#endif

/************************ 论坛地址 www.zxkjmcu.com ******************************/