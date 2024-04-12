#include "LCD1602.h"  //���LCD1602ͷ�ļ�
#include "adc0832.h"
#include <math.h>

#define HPM_LIMIT  500 //PM2.5����ֵ
#define HPM_LV1    300 //LV1ֵ ��
#define HPM_LV2    500 //LV2ֵ ��
#define HPM_LV3    700 //LV3ֵ ��

#define LVx_LEDs P2

uchar disp[16]  = {"PM2.5:     ug/m3"}; //��һ����ʾ�����ݡ�
uchar disp1[16] = {"Limit:     ug/m3"}; //�ڶ�����ʾ�����ݡ�

//ָʾ��
sbit LV1_LED_G = P2^0;
sbit LV2_LED_B = P2^1;
sbit LV3_LED_Y = P2^2;

sbit BUZZER = P1^3;	 //�����������˿�==P1^3
sbit Reduc  = P1^7;	 //����������˿�==P1^7
sbit Add    = P3^0;	 //����������˿�==P3^0
sbit PWR    = P3^1;

void HPM_display(int i); //HPM��ʾ
void PM_display(int i);  //PM��ʾ

void main(void)
{
	//PM2.5��������
	double PM,pm1,pm2;
	int PMVAL = 0, 
	    HPM = HPM_LIMIT, 
	    PM_count = 0, 
	    pm1_count=0;
	
	//��������������
	uchar bueezr_flag = 0, 
	      count = 0, 
	      buzzer_time = 9;

	LCD_Init();
	
	WriteChar(1, 0, 16, disp); //�ڵ�һ����ʾ�����ݡ�
	WriteChar(2, 0, 16, disp1); //�ڵڶ�����ʾ�����ݡ�
	HPM_display(HPM);
	
	while(1)
	{
		while (PWR) {
			PMVAL=PM=pm1=pm2=pm1_count=PM_count=0;
			PM_display(PMVAL);
			HPM = HPM_LIMIT;
			HPM_display(HPM_LIMIT);

			LV1_LED_G = 1;
			LV2_LED_B = 1;
			LV3_LED_Y = 1;
			BUZZER = 1;
			Delay(200);
		}
		//��ȡPM2.5����
		pm1+=read_data(1);
		if(++PM_count>=20)
		{
		  	PM_count=0;
		   	pm1=pm1/20;
			pm2+=pm1;
			pm1=0;
			if(++pm1_count>=5)
			{
				//pm2.5�������
				pm1_count = 0;
				PM = pm2 / 5;
				PM = PM * 50 / 255;
				PM -= 4;
				PM /= 5;
				PM *= 1000;
				PMVAL = PM;
				PMVAL += 235;	
				PMVAL = PMVAL / 9;
				//��ʾ����
				PM_display(PMVAL);
				//�м������������
				PM=pm1=pm2=0;
			}
		}

		//PMֵ�뱨��ֵ�Ƚ�
		if (PMVAL > HPM)
		{	
			bueezr_flag = 1;
		} else {
			bueezr_flag = 0;
			BUZZER = 1;
		}
		/*******����������********/
		count++;
		if (count > buzzer_time * 10)
			count = buzzer_time + 1;
		if(count % buzzer_time == 0 && bueezr_flag)
			BUZZER = ~BUZZER;//������ȡ��  ����������ʾ

		/*******���ñ�������********/ 
		if (Add == 0) {
			Delay(200);	 
			HPM += 50;
			HPM_display(HPM);
		}
		//��
		if (Reduc == 0) {
			Delay(200);
			HPM -= 50;	
			HPM_display(HPM);
		}

		/*******Ũ��ָʾ��********/
		if (PMVAL > HPM_LV1) {
			LV1_LED_G = 0;
		} else {
			LV1_LED_G = 1;
		}
		if (PMVAL > HPM_LV2) {
			LV2_LED_B = 0;
		} else {
			LV2_LED_B = 1;
		}
		if (PMVAL > HPM_LV3) {
			LV3_LED_Y = 0;
		} else {
			LV3_LED_Y = 1;
		}
	}
}

void HPM_display(int i)
{
	WriteCOMDATA(0xc7,0);
	WriteCOMDATA(i/100%10+0x30,1);
	WriteCOMDATA(i/10%10+0x30,1);
	WriteCOMDATA(i%10+0x30,1);	
}

void PM_display(int i)
{
	WriteCOMDATA(0x86,0);
	if(i<0)//i=0;
	{WriteCOMDATA(0+0x30,1);i=abs(i);}
	else WriteCOMDATA(i/1000+0x30,1);
	WriteCOMDATA(i/100%10+0x30,1);
	WriteCOMDATA(i/10%10+0x30,1);
	WriteCOMDATA(i%10+0x30,1);
}
