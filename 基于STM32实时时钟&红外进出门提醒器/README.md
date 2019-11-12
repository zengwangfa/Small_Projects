
>**最后有代码与原理图PCB分享**

<kbd>**用到的工具有**：</kbd>
 - [x] 程序 IAR编译器环境
 - [x] altium designer 原理图
 - [x] altium designer PCB

==实现的小功能有：==
==①能通过外部两个红外对管记人数并在OLED上显示 粗略计数人数==
==②能通过外部两个红外对 判断人进入或出去，并发出语音提示    
 ag:人进门：[语音]欢迎光临；人出门：[语音]谢谢惠顾==
==③语音整点报时==
==④OLED上显示实时时间包括：年-月-日-星期-时-分-秒==
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181126220421429.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)
# 总体设计
1.基础硬件DIY设计
2.单片机程序设计
3.效果展示

## 1.基础硬件DIY设计
**电路硬件：**
[MCU]STM8S003P
[外部RTC]PCF8563
[语音模块]MY2490
[屏幕]0.96寸12864 OLED

###  1）整体原理图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181126212334509.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)


### 2）外部RTC[PCF8563]电路

> **PCF8563芯片为IIC通信，SDA[5]与SCL[6]引脚需要上拉**
> 
**RTC模块 多接一纽扣电池[3.0V]，当整机断电时，纽扣电池为其提供电源，保证时钟还在运行。当单片机供上电时，读取数据为实时的时间，==保证了断电时间还在继续运行。==**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181126213701891.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)

### 3）PCB电路
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181126215840883.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)
### 4）3D_PCB
- TOP层![在这里插入图片描述](https://img-blog.csdnimg.cn/20181126220336380.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)
- BOTTOM层![在这里插入图片描述](https://img-blog.csdnimg.cn/20181126220421429.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)

## 2.单片机程序设计
###  1）PCF8563  I2C通信程序
```javascript
//pcf8563.c       [PCF8563 I2C通信]
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
    I2C_Start();//启动信号
    I2C_Send_Byte(PCF8563_ADDRESS);
    I2C_Wait_Ack();
    I2C_Send_Byte((u8)(addr));
    I2C_Wait_Ack();
    I2C_Send_Byte(dt);
    I2C_Wait_Ack();
    I2C_Stop();    
}

void PCF8563_SetTime(void)//PCF8563初始化设定初始时间
{   
    struct Time TIME={0x18,0x10,0x06,0x21,0x21,0x53,0x30};//设置时间： 年->月->周->日->时->分->秒
    //定义时间寄存器地址
    PCF8563_WriteByte(0x02,TIME.second);
    PCF8563_WriteByte(0x03,TIME.minite);
    PCF8563_WriteByte(0x04,TIME.hour);
    PCF8563_WriteByte(0x05,TIME.day);
    PCF8563_WriteByte(0x06,TIME.week);
    PCF8563_WriteByte(0x07,TIME.month);
    PCF8563_WriteByte(0x08,TIME.year);
}

void PCF8563_GetTime(u8 *buf)//得到时间数据包
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
    
    buf[0]=HexToBcd(buf[0]);  //秒 
    buf[1]=HexToBcd(buf[1]);  //分
    buf[2]=HexToBcd(buf[2]);  //时
    buf[3]=HexToBcd(buf[3]);  //日
    buf[5]=HexToBcd(buf[5]);  //月
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
    if(last_sec != time_buf[sec]){//产生“：”闪烁效果
      if(time_buf[sec]%2 == 0){//偶数显示“：”  奇数显示“ ”  
        OLED_ShowString(96,2,":");
      }
      else{OLED_ShowString(96,2," ");}
    }
    
    OLED_ShowNum(112,2,time_buf[0],2,16);
}

```


###  2）main函数逻辑  [OLED的显示/红外对管的逻辑监测/语音模块的控制]
```javascript
// main.c   [main函数]
#include "pbdata.h"  //引入自定义公共头文件

u8 Time_Remind_CMD[]={0x7E,0x05,0x41,0x00,0x01,0x45,0xEF};//整点报时
u8 IN_CMD[]={0x7E,0x05,0x41,0x00,0x19,0x5D,0xEF}; //进门声   0x19 -> 0025   
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
  OLED_ShowNum(96,6,People_num,2,16);//显示人数
  
}
```

## 3.效果展示        
        DESIGN

```mermaid
gantt
	dateFormat  YYYY-MM-DD
        title 设计制作步骤
        section 现有任务
        部分功能验证               :done,    des1, 2017-05-5,2d
        原理图              	     :done,  des2, 2017-05-5, 1d
        PCB          	           : done ,       des3, after des2, 1d
       程序设计                 :   done ,     des4, after des3, 3d
        外盒包装设计                 :   done ,     des5, after des3, 1d
```
### 1）实物电路顶层图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181126221450497.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)

### 2）实物电路底层图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181126221419589.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)

### 3）.防水盒内部图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181126223853988.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)

###  4）整体效果图
<kbd>**防误关闭设计**</kbd>
屏幕旁的小孔为电源开关【用一个小棍[例如小螺丝刀]伸入即可做到开关总电源】

<kbd>**可玩性**</kbd>
预留五个调试按键，可改装为音乐播放器【已成功】
改装功能为：==①可上下切歌 /②可调节音量大小/③在屏幕显示音量与当前歌名==
>不过音质较差需要优化音频运放电路
>
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181126222305160.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)

附：
程序：
[程序（模拟I2C通信PCF8563 + 红外对管逻辑判断进出门+语音报时等）](https://download.csdn.net/download/qq_39492932/10809332)
硬件（原理图+PCB）：
[[DIY]STM8S003的实时时钟[PCF8563]与红外进出门提醒器](https://download.csdn.net/download/qq_39492932/10809326)
==若想直接获得下载文件，留言留下邮箱即可，我看到就会发==
