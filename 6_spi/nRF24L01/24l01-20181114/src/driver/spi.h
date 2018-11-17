#ifndef _SPI_H
#define _SPI_H
	#include "common/common.h"
	
	#define CS_PIN 		3
	#define SCL_PIN 	5
	#define MOSI_PIN 	11
	#define MISO_PIN 	13
	
	int SPI_Init( void );			//初始化SPI口
	int SPI_SetSpeed( unsigned char uc_speedSet ); 	//设置SPI速度   
	unsigned char SPI_ReadWriteByte( unsigned char uc_txData );	//SPI总线读写一个字节
	  
#endif	//_SPI_H
















