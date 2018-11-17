#ifndef _MYIIC_H
#define _MYIIC_H
	#include "common/common.h"
	
	#define SDAPIN 	8
	#define SCLPIN 	10
	

	//IO��������
	#define SCL_OUT() 	{pullUpDnControl( SCLPIN, PUD_UP );pinMode( SCLPIN, OUTPUT );}
	#define SDA_IN() 	{pullUpDnControl( SDAPIN, PUD_UP );pinMode( SDAPIN, INPUT );}
	#define SDA_OUT() 	{pullUpDnControl( SDAPIN, PUD_UP );pinMode( SDAPIN, OUTPUT );}
	
	//IO��������	 
	#define IIC_SCL( STATUS )  	digitalWrite ( SCLPIN, STATUS )		//SCL
	#define IIC_SDA( STATUS ) 	digitalWrite ( SDAPIN, STATUS ) 	//SDA	 
	#define READ_SDA			digitalRead ( SDAPIN )   			//����SDA 
	
	void IIC_Init(void);                			//��ʼ��IIC��IO��	
	void IIC_Start ( void );						//����IIC��ʼ�ź�
	void IIC_Stop ( void );	  					//����IICֹͣ�ź�
	void IIC_Send_Byte ( uint8_t TextData );	//IIC����һ���ֽ�
	uint8_t IIC_Read_Byte ( uint8_t Ack );		//IIC��ȡһ���ֽ�
	uint8_t IIC_Wait_Ack ( void ); 					//IIC�ȴ�ACK�ź�
	void IIC_Ack (void);							//IIC����ACK�ź�
	void IIC_NAck (void);						//IIC������ACK�ź�
	
	void IIC_Write_One_Byte ( uint8_t DataAddr, uint8_t Addr, uint8_t Data);
	uint8_t IIC_Read_One_Byte ( uint8_t DataAddr, uint8_t Addr);	  
#endif	//_MYIIC_H
















