/************************************************
*   程序功能： LCD1602头文件			   			            
*   使用说明： 在需要使用LCD1602显示时添加此头文件“LCD1602.h”
************************************************/
#ifndef __LCD1602_H__
#define __LCD1602_H__
#include "delay.h"  		  //添加延时函数头文件
#define LCD_PINDATA P0	  //数据端口定义 
sbit RS  =  P1^4;		  //RS 
sbit RW  =  P1^5;		  //RW 
sbit E   =  P1^6;		  //E  
/************************************************
** 函数名称 ： WriteCOMDATA(uchar LCD_DATA,uchar N)
** 函数功能 ： LCD1602写指令、数据函数
** 输    入 ： LCD_DATA:指令或者数据
               N：指令方式还是数据方式 
	       N=0时，LCD_DATA为指令，N=1时，LCD_DATA为数据
** 输    出	： 无
** 说    明 ： 
************************************************/
void WriteCOMDATA(uchar LCD_DATA, uchar N)
{
	Delay(5);
	E=1;
	RW=0;
	RS=N;
	LCD_PINDATA=LCD_DATA;
	E=0;
}
/************************************************
** 函数名称 ： void LCD_init(void)
** 函数功能 ： LCD1602初始化操作
** 输    入 ： 无
** 输    出 ： 无
** 说    明 ：
************************************************/
void LCD_Init(void)
{
	WriteCOMDATA(0x01,0);
	Delay(500);
	WriteCOMDATA(0x38,0);
	Delay(10);
	WriteCOMDATA(0x06,0);
	Delay(10);
	WriteCOMDATA(0x0C,0);
	Delay(10);
}
/************************************************
** 函数名称 ：void WriteChar(uchar Row,uchar Col,uchar Num,uchar *pBuffer)
** 函数功能 ：在任意位置写指定个字符
** 输    入 ：Row : 要写的字符所在的行，只能为1或2；
              Col : 要写的字符所在的列，只能为0---15
              Num : 要写字符的个数
              pbuffer : 要写字符的首地址
** 输    出 ：无
** 说    明 ：
************************************************/
void WriteChar(uchar Row, uchar Col, uchar Num, uchar *pBuffer)
{
	uchar i;
	if(Row==1)Row=0x80+Col;
	else Row=0xC0+Col;
	WriteCOMDATA(Row,0);
	for(i=Num;i!=0;i--)
	{	
		WriteCOMDATA(*pBuffer,1);	
		pBuffer++;
	}
}

#endif
