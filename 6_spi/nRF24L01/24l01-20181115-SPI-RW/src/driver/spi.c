#include "spi.h"

unsigned char SPI_ReadWriteByte( unsigned char uc_data )
{
	unsigned char i;
	
    digitalWrite( SCL_PIN, LOW );     //先将时钟线拉低

    for( i = 0; i < 8; i++ )
    {   
        if(( uc_data & 0x80 ) == 0x80 )  //从高位发送
        {
            digitalWrite( MOSI_PIN, HIGH );
        }
        else
        {
            digitalWrite( MOSI_PIN, LOW );
        }

        digitalWrite( SCL_PIN, HIGH );  //将时钟线拉高，在时钟上升沿，数据发送到从设备

        uc_data <<= 1;

        if( digitalRead( MISO_PIN ) == 1 )   //读取从设备发射的数据
        {
            uc_data |= 0x01;     
        }
		
        digitalWrite( SCL_PIN, LOW );      //在下降沿数据被读取到主机
    }

    return uc_data;         //返回读取到的数据
}
	




