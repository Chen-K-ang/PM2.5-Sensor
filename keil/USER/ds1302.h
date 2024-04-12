
#ifndef __DS1302_H__
#define __DS1302_H__
#include"delay.h" 

sbit RST=P1^0;
sbit IO=P1^1;
sbit CLK=P1^2;

sbit ACC0=ACC^0;
sbit ACC7=ACC^7;
 	
//*******��������********
void rst1(void)
{
	RST=0;
	CLK=0;
	RST=1;
}
//*******ֹͣ����********
void rst0(void)
{
	CLK=1;
	RST=0;
}
//*******ʱ�����庯��********
void dsclk(void)
{
	CLK=1;
	CLK=0;
}
//*******д��һ�ֽں���********
void wrbyte(uchar d)
{
	uchar i;
	ACC=d;
	for(i=8;i>0;i--)
	{
		IO=ACC0;
		dsclk();
		ACC=ACC>>1;
	}
}
//*******����һ�ֽں���********
uchar rebyte(void)
{
	uchar i;
	for(i=8;i>0;i--)
	{
		ACC=ACC>>1;
		ACC7=IO; 
		dsclk();
	}
	return(ACC);
}
//*******���ֽ�д�������Ӻ���********
void setds1302(uchar dizhi,uchar shuju)
{
	rst1();
	wrbyte(0x8e);
	wrbyte(0x00);
	rst0();
	rst1();
	wrbyte(dizhi);
	wrbyte(shuju);
	rst0();
	rst1();
	wrbyte(0x8e);
	wrbyte(0x80);
	rst0();
}
//*******���ֽڶ�ȡ�Ӻ���********
uchar getds1302(uchar dizhi)
{
	uchar shuju;
	rst1();
	wrbyte(dizhi);
	shuju=rebyte();
	rst0();
	return(shuju);
}
#endif