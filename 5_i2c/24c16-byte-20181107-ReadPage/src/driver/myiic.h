#ifndef _MYIIC_H
#define _MYIIC_H
	#include "common/common.h"
	
	#define SDAPIN 	8
	#define SCLPIN 	10
	
	uint8_t IIC_Start ( void );						//����IIC��ʼ�ź�
	uint8_t IIC_Stop ( void );	  					//����IICֹͣ�ź�
	uint8_t IIC_Send_Byte ( uint8_t TextData );	//IIC����һ���ֽ�
	uint8_t IIC_Read_Byte ( uint8_t Ack );		//IIC��ȡһ���ֽ�
	uint8_t IIC_Wait_Ack ( void ); 					//IIC�ȴ�ACK�ź�
	uint8_t IIC_Ack (void);							//IIC����ACK�ź�
	uint8_t IIC_NAck (void);						//IIC������ACK�ź�
	
	uint8_t IIC_Write_One_Byte ( uint8_t DataAddr, uint8_t Addr, uint8_t Data);
	uint8_t IIC_Read_One_Byte ( uint8_t DataAddr, uint8_t Addr);	  
#endif	//_MYIIC_H
















