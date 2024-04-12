#ifndef __DHT11_H__
#define __DHT11_H__
#include"delay.h" 

sbit DHT11_DQ2 = P3^7;
sbit DHT11_DQ1 = P3^7;

uchar U8count,U8temp,U8FLAG,U8comdata;

void Delay_10us(void)
{
	uchar i;
	i--;
	i--;
	i--;
	i--;
	i--;
	i--;
} 
void COM(uchar n)
{    
 	uchar i;
    for(i=0;i<8;i++)    
    {
    	U8FLAG=2;  
    	if(n){while((!DHT11_DQ1)&&U8FLAG++);}
		else {while((!DHT11_DQ2)&&U8FLAG++);}
    	Delay_10us();
    	Delay_10us();
      	U8temp=0;
      	if(n){if(DHT11_DQ1)U8temp=1;}
		else {if(DHT11_DQ2)U8temp=1;}
      	U8FLAG=2;
   		if(n){while((DHT11_DQ1)&&U8FLAG++);}
		else {while((DHT11_DQ2)&&U8FLAG++);}        
    	if(U8FLAG==1)break; 
     	U8comdata<<=1;
        U8comdata|=U8temp;        
	}
}
uchar Read_TRH(uchar ch,uchar n)
{
	uchar TRH_data=0;
	static uchar U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
	static uchar U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
    if(n)DHT11_DQ1=0;
	else DHT11_DQ2=0;
    Delay(24);
    if(n)DHT11_DQ1=1;
	else DHT11_DQ2=1;
    Delay_10us();
    Delay_10us();
    Delay_10us();
    Delay_10us();
    if(n)DHT11_DQ1=1;
	else DHT11_DQ2=1; 
    if(!DHT11_DQ1 || !DHT11_DQ2)   
    {
    	U8FLAG=2;
    	if(n){while((!DHT11_DQ1)&&U8FLAG++);}
		else {while((!DHT11_DQ2)&&U8FLAG++);}
    	U8FLAG=2;
    	if(n){while((DHT11_DQ1)&&U8FLAG++);}
		else {while((DHT11_DQ2)&&U8FLAG++);}
    	COM(n);U8RH_data_H_temp=U8comdata;
    	COM(n);U8RH_data_L_temp=U8comdata;
    	COM(n);U8T_data_H_temp=U8comdata;
    	COM(n);U8T_data_L_temp=U8comdata;
    	COM(n);U8checkdata_temp=U8comdata;
    	if(n)DHT11_DQ1=1;
		else DHT11_DQ2=1;
    	U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
    	if(U8temp==U8checkdata_temp)
    	{
       		U8RH_data_H=U8RH_data_H_temp;
       		U8RH_data_L=U8RH_data_L_temp;
    		U8T_data_H=U8T_data_H_temp;
       		U8T_data_L=U8T_data_L_temp;
       		U8checkdata=U8checkdata_temp;
    	}
    }
	if(ch)TRH_data=U8RH_data_H;
	else TRH_data=U8T_data_H;
	return TRH_data;
}
#endif


