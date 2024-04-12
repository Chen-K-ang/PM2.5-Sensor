#ifndef __24C02_H__
#define __24C02_H__

#include "delay.h"

sbit scl=P3^4;
sbit sda=P3^5;

//********24c02启动子函数********
void start(void)
{
	sda=1;
	scl=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	sda=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	scl=0;
}
//********24c02停止子函数********
void stop(void)
{
	sda=0;
	scl=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	sda=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	scl=0;
}
//********24c02写一字节子函数********
void writebyte(uchar j)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		j=j<<1;
		sda=CY;
		scl=1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		scl=0;
	}
	scl=0;
	sda=1;
}
//********24c02读一字节子函数********
uchar readbyte()
{
	uchar i,j,k=0;
	for(i=0;i<8;i++)
	{
		scl=1;
		sda=1;
		if(sda==1)j=1;
		else j=0;
		k=(k<<1)|j;
		scl=0;
	}
	return(k);
}
//********24c02应答子函数********
void clock()
{
	sda=0;
	_nop_();
	scl=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	scl=0;
}
//********24c02非应答子函数********
void nclock(void)
{
	sda=1;
	_nop_();
	_nop_();
	scl=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	scl=0;
	_nop_();
}
//********24c02写子函数********
void x24c02write(uchar dizhi,uchar shuju)
{
	start();
	writebyte(0xa0);
	clock();
	writebyte(dizhi);
	clock();
	writebyte(shuju);
	clock();
	stop();
	Delay11(500);
}
//********24c02读子函数********
uchar x24c02read(uchar dizhi)
{
	uchar n;
	start();
	writebyte(0xa0);
	clock();
	writebyte(dizhi);
	clock();
	start();
	writebyte(0xa1);
	clock();
	n=readbyte();
	nclock();
	stop();
	return(n);
}

#endif
