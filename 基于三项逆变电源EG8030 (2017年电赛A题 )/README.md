@[TOC](目录：)

>关键词：【电赛】【三相逆变电源】【EG8030】



<kbd>**用到的工具有**：</kbd>
 - [x] Altium Designer 16.0
- [X] 示波器

<font color=#0099ff size=5 face="微软雅黑">EG8030+EG3012+EG1181 三相纯正弦波逆变器典型应用：</font>
- 采用48V 蓄电池为直流母线供电
- 以EG8030 为逆变器主控单元
- 通过半桥驱动芯片EG3012驱动功率MOSFET
- 三相全桥逆变输出三相SPWM 经过三相工频变压器升压滤波。

三相工频升压变压器采用Δ- Y 连接方式，四线输出相电压为220V，线电压为380V 的纯正弦波三相电源。板上所需+15V 驱动电源采用DC-DC 降压型开关电源芯片EG1181 进行48V 降压转换。本应用中EG8030 工作在三相同步闭环稳压模式，电压反馈采用三个小变压器隔离采样。

实现的功能有：
**①实现三相SPWM**
**②实现三相交流电**
# 一、相关简介
逆变：
: - 与整流相对应，将直流电变成交流电；

SPWM (Sinusoidal PWM)：
: - 脉冲宽度按**正弦规律**变化的PWM波；

自举电路：
: - 也叫升压电路，是利用自举升压二极管，自举升压电容等电子元件，使电容放电电压和电源电压叠加，从而使电压升高，有的电路升高的电压能达到数倍电源电压。

死区时间:
: - 每个桥的上半桥和下半桥是绝对不能同时导通的，但高速的PWM驱动信号在达到功率元件的控制端时，往往会由于各种各样的原因产生延迟的效果，造成某个半桥元件在应该关断时没有关断，造成功率元件烧毁。
	PWM死区时间图示，保证两个控制信号的切换之间有一个延迟等待时间（死区时间）：![在这里插入图片描述](https://img-blog.csdnimg.cn/20190301124430468.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)


# 二、专用逆变芯片E8030控制板

 - 以EG8030 为逆变器主控单元产生SPWM波
 - 通过半桥驱动芯片EG3012驱动功率MOSFET
<font color =green size=5> 控制核心原理图 :</font>
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190124201929117.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)
<font color =green size=5> PCB图:</font>
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190124205110186.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)





# 三、驱动板
<font color =green size=5> 总体简图 :</font>
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190124202224292.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)
<font color =green size=5> PCB图:</font>
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190124205126542.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)
<font color =green size=5> 桥臂局部MOS图 :</font>
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190124203455619.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)


<font color =#0099ff size=5> D8二极管的作用是：</font>
**由于MOS的栅极和源极之间存在一个比较大的寄生电容，由于二极管没有限流作用理论上电流峰值可以达到无穷大，在该电路中可起到加速给栅极电容放电的目的——<font color =red size=4> 提高关断速度</font>。**


<font color =#0099ff size=5> R38电阻的作用是：</font>
**①：MOS的栅极和源极之间存在一个比较大的寄生电容，电阻给电容充放电时由于电阻的限流作用电容的电压突变都相对比较平缓。
即：<font color =red size=4> 缓启动作用</font>。**

  **②：若不加R38电阻，高压情况下便会因为mos管开关速率过快而导致周围元器件被击穿。但R38电阻过大则会导致MOS管的开关速率变慢，Rds从无穷大到Rds（on）的需要经过一段时间，高压下Rds会消耗大量的功率，而导致mos管发热异常。**


<font color =#0099ff size=5> R19电阻的作用是：</font>
**①：<font color =red size=4> 作为泄放电阻泄放掉G-S的少量静电</font>，防止mos管产生误动作，甚至击穿mos管（因为只要有少量的静电便会使mos管的G-S极间的等效电容产生很高的电压），起到了保护mos管的作用。**

  **②：为mos管提供偏置电压**

# 四、实物测试：
..调试的时候也是炸了好几次，蹦出了火花，大家做电源类的时候一定小心、细心一些，上电之前先测试电源引脚有无短路之类的。
- <font color=red size=5 face="微软雅黑">实物正面图：</font>
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190124210143561.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)
- <font color=red size=5 face="微软雅黑">实物底部图：</font>![在这里插入图片描述](https://img-blog.csdnimg.cn/20190124210357569.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)
- <font color=red size=5 face="微软雅黑">示波器测试SPWM：</font>![在这里插入图片描述](https://img-blog.csdnimg.cn/20190124210441853.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)
- <font color=red size=5 face="微软雅黑">示波器测试单相交流电：</font>![在这里插入图片描述](https://img-blog.csdnimg.cn/2019012421054021.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)

- <font color=red size=5 face="微软雅黑">示波器测试三相交流电：</font>![在这里插入图片描述](https://img-blog.csdnimg.cn/20190124210616109.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF,t_70)

测得相位差为120°，可能是死区时间未设置好，顶峰有些失真。

<div align=center>
<img src="https://img-blog.csdnimg.cn/20190912225809893.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDkyOTMy,size_16,color_FFFFFF"/>