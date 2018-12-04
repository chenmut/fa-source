#ifndef _SPI_H_
#define _SPI_H_
	#include <linux/types.h>
	#include "common/common.h"
	
	#define SCL_PIN 	23
	#define MOSI_PIN 	19
	#define MISO_PIN 	21
	
	#define  SPIEMULATE 	1      //软件->1；硬件->0
	
	unsigned char SPI_ReadWriteByte( unsigned char u8Data );
	
#endif	//_SPI_H_
