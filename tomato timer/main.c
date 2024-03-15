//����������us 1908 1706 1520 1436 1276 1136 1012 956 854 760 718 638 568 506 478 426 380 358 320 284 254
#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char
#define uint  unsigned int

sbit k1=P1^0;//��ť����
sbit k2=P1^1;
sbit k3=P1^2;

sbit beep=P2^7;//������

sbit smg1=P2^0;//�����
sbit smg2=P2^1;
sbit smg3=P2^2;
sbit smg4=P2^3;
sbit smg5=P2^4;

uchar code smgduan0[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//��ʾ0~9,��С����
uchar code smgduan1[10]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};//��ʾ0~9,��С����
uchar fen=0,miao=0,sec=0;
uchar cishu=0;//��������

uchar ge_num=1;//�������
//����������us 1908 1706 1520 1436 1276 1136 1012 956 854 760 718 638 568 506 478 426 380 358 320 284 254
//������
uint code music[22]={0x0fff,1908,1706,1520,1436,1276,1136,1012,956,854,760,718,638,568,506,478, 426, 380, 358, 320, 284, 254};
//���ı���,һ��16�İ�������
uint code pai16[22]={1,80, 88, 99, 105, 117, 132,148, 157,175,196,208,234,264,295,313, 351, 394, 418, 471, 528, 589};

//���ף�������us+����ʱ�䣨16���ı�����
uchar code gequ1[]={ //�������룬����
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

uint times=0;//������
uint num=0;//����
uchar a=0xfc,b=0x18;//��ʱ����ֵ
uint first=1;//��������

uint time=0; //��ʱ
uchar shunxu=0;//��ʾ����

void delay_us(uint i)//��ʱus
{
	while(i--);
}

void delay_ms(uint i)//��ʱms
{
   uchar k;
   while(i--)
   	for(k=0;k<110;k++);
}
//��ʾ
void disp()
{
	P0=smgduan0[fen/10];smg1=0;delay_us(50);smg1=1;
	P0=smgduan1[fen%10];smg2=0;delay_us(50);smg2=1;
	P0=smgduan0[miao/10];smg3=0;delay_us(50);smg3=1;
	P0=smgduan0[miao%10];smg4=0;delay_us(50);smg4=1;
	P0=smgduan0[cishu];smg5=0;delay_us(50);smg5=1;
}
//������
void main()
{
	uint i=0;
	TMOD=0X11;//��ʱ��0��������ʽ1��
	TH0=0XFC;	//��ʱ1ms
	TL0=0X18;
	TH1=0X3C;	//��ʱ50ms
	TL1=0XB0;	
	ET0=1;//�򿪶�ʱ��0�ж�����
	ET1=1;
	EA=1;//�����ж�
while(1)
{
	disp();
	//�������
	if(!k1)//ʱ������
	{
		delay_ms(10);//��ʱ����
		if(!k1)
		{
			while(!k1)//��һ�ΰ���
			{
				disp();
			}
			for(i=0;i<150;i++)//�ڶ��ΰ���
			{
				disp();
				if(!k1)
					break;
			}
			if(i==150)//����
			{
				fen=45;miao=0;
				if(cishu<4)
					cishu++;
				else
					cishu=1;
			}
			else //˫��
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
			TR1=1;//����
			
		}
		while(!k1);
	}
	if(!k2)//���ſ���
	{
		delay_ms(10);//��ʱ����
		if(!k2)
		{
			while(!k2)//��һ�ΰ���
			{
				disp();
			}
			for(i=0;i<150;i++)//�ڶ��ΰ���
			{
				disp();
				if(!k2)
					break;
			}
			if(i==150)//����
			{
				TR0=1;
			}
			else //˫��
			{
				TR0=0;beep=1;
				num=0;
			}
		}
		while(!k2);
	}
	if(!k3)//��λ
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
//��ʱ��0�ж�
void Timer0() interrupt 1
{
	TH0=a;	//����ʱ������ֵ
	TL0=b;
	if(gequ1[num]!=0)
		beep=!beep;
	if(times<first)//������δ��������+1
	  	times++;   //��ʱ
	else
	{
		times=0;	   //��������
		num+=2;		   //��һ������
		if(gequ1[num]==0xff)	  //����
		{
			num=0;
			TR0=0;//�رն�ʱ��
			beep=1;
		}
		a=(65536-music[gequ1[num]])/256;	//���ó�ֵ
		b=(65536-music[gequ1[num]])%256;
		first=gequ1[num+1]*pai16[gequ1[num]];
	}
		  	
}
//��ʱ��1�ж�
void Timer1() interrupt 3
{
	if(sec<20) //1s
	{
		sec++;
	}
	else
	{
		sec=0;
		if(miao>0)//����ʱ
			miao--;
		else
		{
			if(fen>0)
			{
				fen--;
				miao=59;
			}
			else//����
			{
				TR1=0;
				TR0=1;
			}
		}
	}
	TH1=0X3C;	//��ʱ50ms
	TL1=0XB0;
}