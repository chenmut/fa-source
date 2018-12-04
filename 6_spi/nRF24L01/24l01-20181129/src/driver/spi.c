#include "spi.h"

//软件spi 1；硬件spi 0

unsigned char SPI_ReadWriteByte( unsigned char u8Data )
{
	if( SPIEMULATE == 1 )
	{
		digitalWrite( SCL_PIN, LOW );     //先将时钟线拉低
	
		for( int i = 0; i < 8; i++ )
		{   
			if(( u8Data & 0x80 ) == 0x80 )  //从高位发送
			{
				digitalWrite( MOSI_PIN, HIGH );
			}
			else
			{
				digitalWrite( MOSI_PIN, LOW );
			}
	
			digitalWrite( SCL_PIN, HIGH );  //将时钟线拉高，在时钟上升沿，数据发送到从设备
	
			u8Data <<= 1;
	
			if( digitalRead( MISO_PIN ) == 1 )   //读取从设备发射的数据
			{
				u8Data |= 0x01;     
			}
			
			digitalWrite( SCL_PIN, LOW );      //在下降沿数据被读取到主机
		}
	
		return u8Data;         //返回读取到的数据
	}
	else
	{
		unsigned char aByte[1] = { 0 };
		
		aByte[0] = u8Data;
	
		wiringPiSPIDataRW( 0, aByte, 1 );
		u8Data = aByte[0];		//调用该函数后从SPI bus上读取到的数据已经存放在aByte中
		
		return u8Data;			//返回读取到的数据
		//return wiringPiSPIDataRW( 0, (unsigned char*)u8Data, 1 );
	}   
	
}
