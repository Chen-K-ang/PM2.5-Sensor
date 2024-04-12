/************************************************
*   �����ܣ� LCD1602ͷ�ļ�			   			            
*   ʹ��˵���� ����Ҫʹ��LCD1602��ʾʱ���Ӵ�ͷ�ļ���LCD1602.h��
************************************************/
#ifndef __LCD1602_H__
#define __LCD1602_H__
#include "delay.h"  		  //������ʱ����ͷ�ļ�
#define LCD_PINDATA P0	  //���ݶ˿ڶ��� 
sbit RS  =  P1^4;		  //RS 
sbit RW  =  P1^5;		  //RW 
sbit E   =  P1^6;		  //E  
/************************************************
** �������� �� WriteCOMDATA(uchar LCD_DATA,uchar N)
** �������� �� LCD1602дָ����ݺ���
** ��    �� �� LCD_DATA:ָ���������
               N��ָ�ʽ�������ݷ�ʽ 
	       N=0ʱ��LCD_DATAΪָ�N=1ʱ��LCD_DATAΪ����
** ��    ��	�� ��
** ˵    �� �� 
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
** �������� �� void LCD_init(void)
** �������� �� LCD1602��ʼ������
** ��    �� �� ��
** ��    �� �� ��
** ˵    �� ��
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
** �������� ��void WriteChar(uchar Row,uchar Col,uchar Num,uchar *pBuffer)
** �������� ��������λ��дָ�����ַ�
** ��    �� ��Row : Ҫд���ַ����ڵ��У�ֻ��Ϊ1��2��
              Col : Ҫд���ַ����ڵ��У�ֻ��Ϊ0---15
              Num : Ҫд�ַ��ĸ���
              pbuffer : Ҫд�ַ����׵�ַ
** ��    �� ����
** ˵    �� ��
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