#ifndef _MYIIC_H
#define _MYIIC_H
	#include "common/common.h"
	
	#define SDAPIN 	8
	#define SCLPIN 	10
	
	uint8_t IIC_Start ( void );						//发送IIC开始信号
	uint8_t IIC_Stop ( void );	  					//发送IIC停止信号
	uint8_t IIC_Send_Byte ( uint8_t TextData );	//IIC发送一个字节
	uint8_t IIC_Read_Byte ( uint8_t Ack );		//IIC读取一个字节
	uint8_t IIC_Wait_Ack ( void ); 					//IIC等待ACK信号
	uint8_t IIC_Ack (void);							//IIC发送ACK信号
	uint8_t IIC_NAck (void);						//IIC不发送ACK信号
	
	uint8_t IIC_Write_One_Byte ( uint8_t DataAddr, uint8_t Addr, uint8_t Data);
	uint8_t IIC_Read_One_Byte ( uint8_t DataAddr, uint8_t Addr);	  
#endif	//_MYIIC_H
















