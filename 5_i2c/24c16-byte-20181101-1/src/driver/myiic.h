#ifndef _MYIIC_H
#define _MYIIC_H
	#include "common/common.h"
	
	#define SDAPIN 	8
	#define SCLPIN 	10
	

	//IO方向设置
	#define SCL_OUT() 	{pullUpDnControl( SCLPIN, PUD_UP );pinMode( SCLPIN, OUTPUT );}
	#define SDA_IN() 	{pullUpDnControl( SDAPIN, PUD_UP );pinMode( SDAPIN, INPUT );}
	#define SDA_OUT() 	{pullUpDnControl( SDAPIN, PUD_UP );pinMode( SDAPIN, OUTPUT );}
	
	//IO操作函数	 
	#define IIC_SCL( STATUS )  	digitalWrite ( SCLPIN, STATUS )		//SCL
	#define IIC_SDA( STATUS ) 	digitalWrite ( SDAPIN, STATUS ) 	//SDA	 
	#define READ_SDA			digitalRead ( SDAPIN )   			//输入SDA 
	
	void IIC_Init(void);                			//初始化IIC的IO口	
	void IIC_Start ( void );						//发送IIC开始信号
	void IIC_Stop ( void );	  					//发送IIC停止信号
	void IIC_Send_Byte ( uint8_t TextData );	//IIC发送一个字节
	uint8_t IIC_Read_Byte ( uint8_t Ack );		//IIC读取一个字节
	uint8_t IIC_Wait_Ack ( void ); 					//IIC等待ACK信号
	void IIC_Ack (void);							//IIC发送ACK信号
	void IIC_NAck (void);						//IIC不发送ACK信号
	
	void IIC_Write_One_Byte ( uint8_t DataAddr, uint8_t Addr, uint8_t Data);
	uint8_t IIC_Read_One_Byte ( uint8_t DataAddr, uint8_t Addr);	  
#endif	//_MYIIC_H
















