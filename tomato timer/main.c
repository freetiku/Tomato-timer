//音符半周期us 1908 1706 1520 1436 1276 1136 1012 956 854 760 718 638 568 506 478 426 380 358 320 284 254
#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char
#define uint  unsigned int

sbit k1=P1^0;//按钮定义
sbit k2=P1^1;
sbit k3=P1^2;

sbit beep=P2^7;//蜂鸣器

sbit smg1=P2^0;//数码管
sbit smg2=P2^1;
sbit smg3=P2^2;
sbit smg4=P2^3;
sbit smg5=P2^4;

uchar code smgduan0[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//显示0~9,无小数点
uchar code smgduan1[10]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};//显示0~9,有小数点
uchar fen=0,miao=0,sec=0;
uchar cishu=0;//工作次数

uchar ge_num=1;//歌曲编号
//音符半周期us 1908 1706 1520 1436 1276 1136 1012 956 854 760 718 638 568 506 478 426 380 358 320 284 254
//半周期
uint code music[22]={0x0fff,1908,1706,1520,1436,1276,1136,1012,956,854,760,718,638,568,506,478, 426, 380, 358, 320, 284, 254};
//节拍编码,一个16拍半周期数
uint code pai16[22]={1,80, 88, 99, 105, 117, 132,148, 157,175,196,208,234,264,295,313, 351, 394, 418, 471, 528, 589};

//简谱，半周期us+节拍时间（16分拍倍数）
uchar code gequ1[]={ //歌曲编码，花心
10,2, 12,2, 0,1, 12,12, 0,1, 12,2, 13,2,  12,2,  10,8,  9,2,  10,2,  0,1,  9,12,  6,4,  8,10,
0,1,  5,4,  0,1,  5,4,  6,4, 0,2,  8,2,   9,2,   10,4,  8,4,  9,2,   0,1,  9,1,   
10,1,  9,2,  8,2,  7,4,  8,4,  0,1,  8,10,  0,2,  12,2,  0,1,  12,4,  13,4,
0,1,  15,2, 0,1, 15,2,  0,1, 15,4, 12,4,  13,2,  0,1,   13,1, 15,1,  13,2,  12,2, 10,4, 12,4,  
0,1,  12,10,0,1,  5,2,  0,1,   5,2,  6,2,   8,2,   0,1,   8,2,  9,2,   10,4,   8,4,
9,2, 10,2, 15,4,  13,2,  12,2,  0,1,  12,8,  10,4,12,4,0,1,10,2,0,1,10,2,0,1,10,2,9,2,10,2,
9,2,8,2,0,1,9,2,0,1,9,2,0,1,9,2,10,2,9,4,8,2,7,2,
7,2,0,1,7,2,0,1,7,2,0,1,7,2,0,1,7,2,8,2,9,2,8,2,0,1,8,10,0,1,12,2,13,2,15,2,0,1,
15,2,16,2,15,4,13,2,12,2,0,1,12,6,13,2,12,2,10,4,12,4,0,1,10,2,0,1,10,2,0,1,10,2,0,1,10,4,9,2,
8,2,0,1,9,2,0,1,9,2,0,1,9,2,10,2,9,4,8,2,7,2,0,1,7,2,0,1,7,2,
0xff
};

uint times=0;//节拍数
uint num=0;//计数
uchar a=0xfc,b=0x18;//定时器初值
uint first=1;//公共变量

uint time=0; //计时
uchar shunxu=0;//显示控制

void delay_us(uint i)//延时us
{
	while(i--);
}

void delay_ms(uint i)//延时ms
{
   uchar k;
   while(i--)
   	for(k=0;k<110;k++);
}
//显示
void disp()
{
	P0=smgduan0[fen/10];smg1=0;delay_us(50);smg1=1;
	P0=smgduan1[fen%10];smg2=0;delay_us(50);smg2=1;
	P0=smgduan0[miao/10];smg3=0;delay_us(50);smg3=1;
	P0=smgduan0[miao%10];smg4=0;delay_us(50);smg4=1;
	P0=smgduan0[cishu];smg5=0;delay_us(50);smg5=1;
}
//主函数
void main()
{
	uint i=0;
	TMOD=0X11;//定时器0，工作方式1。
	TH0=0XFC;	//定时1ms
	TL0=0X18;
	TH1=0X3C;	//定时50ms
	TL1=0XB0;	
	ET0=1;//打开定时器0中断允许
	ET1=1;
	EA=1;//打开总中断
while(1)
{
	disp();
	//按键检测
	if(!k1)//时间设置
	{
		delay_ms(10);//延时防抖
		if(!k1)
		{
			while(!k1)//第一次按下
			{
				disp();
			}
			for(i=0;i<150;i++)//第二次按下
			{
				disp();
				if(!k1)
					break;
			}
			if(i==150)//单击
			{
				fen=45;miao=0;
				if(cishu<4)
					cishu++;
				else
					cishu=1;
			}
			else //双击
			{
				if(cishu==4)
				{
					fen=10;miao=0;
				}
				else
				{
					fen=5;miao=0;
				}
			}
			TR1=1;//启动
			
		}
		while(!k1);
	}
	if(!k2)//播放控制
	{
		delay_ms(10);//延时防抖
		if(!k2)
		{
			while(!k2)//第一次按下
			{
				disp();
			}
			for(i=0;i<150;i++)//第二次按下
			{
				disp();
				if(!k2)
					break;
			}
			if(i==150)//单击
			{
				TR0=1;
			}
			else //双击
			{
				TR0=0;beep=1;
				num=0;
			}
		}
		while(!k2);
	}
	if(!k3)//复位
	{
		TR0=0;beep=1;
		num=0;
		fen=0;
		miao=0;
		TR1=0;
		cishu=0;
	}	
}
}
//定时器0中断
void Timer0() interrupt 1
{
	TH0=a;	//给定时器赋初值
	TL0=b;
	if(gequ1[num]!=0)
		beep=!beep;
	if(times<first)//节拍数未到，计数+1
	  	times++;   //计时
	else
	{
		times=0;	   //节拍清零
		num+=2;		   //下一个音符
		if(gequ1[num]==0xff)	  //结束
		{
			num=0;
			TR0=0;//关闭定时器
			beep=1;
		}
		a=(65536-music[gequ1[num]])/256;	//设置初值
		b=(65536-music[gequ1[num]])%256;
		first=gequ1[num+1]*pai16[gequ1[num]];
	}
		  	
}
//定时器1中断
void Timer1() interrupt 3
{
	if(sec<20) //1s
	{
		sec++;
	}
	else
	{
		sec=0;
		if(miao>0)//倒计时
			miao--;
		else
		{
			if(fen>0)
			{
				fen--;
				miao=59;
			}
			else//结束
			{
				TR1=0;
				TR0=1;
			}
		}
	}
	TH1=0X3C;	//定时50ms
	TL1=0XB0;
}