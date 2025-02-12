#include "delay.h"  		  //添加延时函数头文件
#include <intrins.h>
sbit CS   = P1^2;
sbit Clk  = P1^1;
sbit DATI = P1^0;
sbit DATO = P1^0;
/****************************************************************************
函数功能:AD转换子程序
入口参数:CH
出口参数:dat
****************************************************************************/
unsigned char adc0832(unsigned char CH)
{
	unsigned char dat = 0x00;      //AD值
	unsigned char i,test,adval;
	adval = 0x00;
	test = 0x00;
	Clk = 0;       //初始化
	DATI = 1;
	_nop_();
	CS = 0;
	_nop_();
	Clk = 1;
	_nop_();
	if ( CH == 0x00 ) {     //通道选择
   	
		Clk = 0;
		DATI = 1;      //通道0的第一位
		_nop_();
		Clk = 1;
		_nop_();
		Clk = 0;
		DATI = 0;      //通道0的第二位
		_nop_();
		Clk = 1;
		_nop_();
	} else {
		Clk = 0;
		DATI = 1;      //通道1的第一位
		_nop_();
		Clk = 1;
		_nop_();
		Clk = 0;
		DATI = 1;      //通道1的第二位
		_nop_();
		Clk = 1;
		_nop_();
	}
	Clk = 0;
	DATI = 1;
	for (i = 0; i < 8; i++ ) {     //读取前8位的值
	
		_nop_();
		adval <<= 1;
		Clk = 1;
		_nop_();
		Clk = 0;
		if (DATO)
			adval |= 0x01;
		else
			adval |= 0x00;
	}
	for (i = 0; i < 8; i++) {      //读取后8位的值
	
		test >>= 1;
		if (DATO)
		test |= 0x80;
		else 
		test |= 0x00;
		_nop_();
		Clk = 1;
		_nop_();
		Clk = 0;
	}
	if (adval == test)      //比较前8位与后8位的值，如果不相同舍去。若一直出现显示为零，请将该行去掉
		dat = test;
	_nop_();
	CS = 1;        //释放ADC0832
	DATO = 1;
	Clk = 1;
	return dat;
}
//sbit vled  = P1^7;

void Delay1us(uint t)		//@12MHz
{
	while(t--)_nop_();
}
uint read_data(uchar N)
{
	uint val=0;
//	vled=0;
	Delay1us(20);
	val=adc0832(N);
//	vled=1;
	Delay1us(400);	
	return val;
}

