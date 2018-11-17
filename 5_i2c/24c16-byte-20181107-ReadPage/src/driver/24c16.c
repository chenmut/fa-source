#include "24c16.h"


//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
uint8_t AT24CXX_WriteOneByte( uint16_t WriteAddr, uint8_t DataToWrite )
{				   	  	    																 
    IIC_Start(); 
	
	IIC_Send_Byte( 0XA0 + (( WriteAddr / 256 ) << 1 ));   //发送器件地址0XA0,写数据
	IIC_Wait_Ack();	
	
    IIC_Send_Byte( WriteAddr % 256 );   //发送低地址
	IIC_Wait_Ack(); 
	
	IIC_Send_Byte( DataToWrite );     //发送字节							   
	IIC_Wait_Ack();  
	
    IIC_Stop();		//产生一个停止条件 
	
	delay( 10 ); 

	return 0;	
}


//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值     :读到的数据
uint8_t AT24CXX_ReadOneByte( uint16_t ReadAddr )
{				  
	uint8_t u8Temp=0;
	
    IIC_Start(); 
	
	IIC_Send_Byte( 0XA0 + (( ReadAddr / 256 ) << 1 ));   //发送器件地址0XA0,写数据 	 
	IIC_Wait_Ack(); 
	
    IIC_Send_Byte( ReadAddr % 256 );  //发送低地址
	IIC_Wait_Ack();
	
	IIC_Start();  
	
	IIC_Send_Byte( 0XA1 + (( ReadAddr / 256 ) << 1 ));          	 //进入接收模式			   
	IIC_Wait_Ack();	
	
    u8Temp = IIC_Read_Byte( 0 );
	
    IIC_Stop();		//产生一个停止条件
	
	return u8Temp;
}


//在AT24CXX里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
uint8_t AT24CXX_WriteLenByte( uint16_t WriteAddr, uint32_t DataToWrite, uint8_t Len)
{  	
	uint8_t t;
	
	for ( t = 0; t < Len; t++ )
	{
		AT24CXX_WriteOneByte( WriteAddr + t, ( DataToWrite >> ( 8 * t )) & 0xff );
	}	

	return 0;	
}


//在AT24CXX里面的指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
//Len        :要读出数据的长度2,4
uint32_t AT24CXX_ReadLenByte( uint16_t ReadAddr, uint8_t Len )
{  	
	uint8_t t;
	uint32_t u32Temp=0;
	
	for ( t = 0; t < Len; t++ )
	{
		u32Temp <<= 8;
		u32Temp += AT24CXX_ReadOneByte( ReadAddr + Len - t - 1 ); 	 				   
	}
	
	return u32Temp;												    
}


//检查AT24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
uint8_t AT24CXX_Check( void )
{
	uint8_t temp;
	
	temp = AT24CXX_ReadOneByte( 255 );	//避免每次开机都写AT24CXX
	
	if ( temp == 0X55 )
	{
		return 0;		   
	}
	else//排除第一次初始化的情况
	{
		AT24CXX_WriteOneByte( 255,0X55 );
	    temp = AT24CXX_ReadOneByte(255);
		
		if ( temp == 0X55 )
		{
			return 0;
		}
	}
	
	return 1;											  
}


//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
uint8_t AT24CXX_Read( uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead )
{
	while ( NumToRead )
	{
		*pBuffer++ = AT24CXX_ReadOneByte( ReadAddr++ );	
		NumToRead--;
	}
	
	return 0;
} 
 
 
//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
uint8_t AT24CXX_Write( uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite )
{
	while ( NumToWrite-- )
	{
		AT24CXX_WriteOneByte( WriteAddr, *pBuffer );
		WriteAddr++;
		pBuffer++;
	}
	
	return 0;
}

 
