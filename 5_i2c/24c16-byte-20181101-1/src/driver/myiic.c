#include "myiic.h"
#include "mydelay.h"

//初始化IIC
void IIC_Init(void)
{
	SCL_OUT();
	SDA_OUT();
	
	IIC_SDA( HIGH );	  	  
	IIC_SCL( HIGH );
}

//产生IIC起始信号
void IIC_Start( void )
{
	SDA_OUT();  //sda线输出
	
	IIC_SDA( HIGH );	  	  
	IIC_SCL( HIGH );
	delayMicroseconds( 4 );
	
 	IIC_SDA( LOW );		 //START:when CLK is high,DATA change form high to low 
	delayMicroseconds( 4 );
	
	IIC_SCL( LOW );		//钳住I2C总线，准备发送或接收数据 
}
	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT() ;			//sda线输出
	
	IIC_SCL( LOW );
	IIC_SDA( LOW );		//STOP:when CLK is high DATA change form low to high
 	delayMicroseconds( 4 );
	
	IIC_SDA( HIGH );	  	  
	IIC_SCL( HIGH );	//发送I2C总线结束信号
 	delayMicroseconds( 4 );
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack ( void )
{
	uint8_t ErrTime=0;
	
	SDA_IN();      //SDA设置为输入  
	IIC_SDA( HIGH );
	delayMicroseconds( 1 );
	
	IIC_SCL( HIGH );
	delayMicroseconds( 1 );
	
	while( READ_SDA )
	{
		ErrTime++;
		if( ErrTime > 250 )
		{
			IIC_Stop();
			return 1;
		}
	}
	
	IIC_SCL( LOW ); 	//时钟输出0   
	return 0;  
} 

//产生ACK应答
void IIC_Ack( void )
{
	IIC_SCL( LOW ); 
	
	SDA_OUT();
	IIC_SDA( LOW );	
	delayMicroseconds( 2 );
	
	IIC_SCL( HIGH );
	delayMicroseconds( 2 );
	
	IIC_SCL( LOW );
}

//不产生ACK应答		    
void IIC_NAck( void )
{
	IIC_SCL( LOW ); 
	
	SDA_OUT();
	IIC_SDA( HIGH );
	delayMicroseconds( 2 );
	
	IIC_SCL( HIGH );
	delayMicroseconds( 2 );
	
	IIC_SCL( LOW );
}
					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte ( uint8_t TextData )
{                        
    uint8_t t; 
	
	SDA_OUT(); 	    
    IIC_SCL( LOW );		//拉低时钟开始数据传输
	
    for( t = 0; t < 8; t++ )
    {   
		if(( TextData & 0x80 ) >> 7)
		{
			IIC_SDA( HIGH );
		}
		else
		{
			IIC_SDA( LOW );	
		}
		
		TextData <<= 1;
		delayMicroseconds( 2 );  	
		
		IIC_SCL( HIGH );
		delayMicroseconds( 2 );
		
		IIC_SCL( LOW );
		delayMicroseconds( 2 );
    }	 
} 	
    
//读1个字节，u8Ack=1时，发送ACK，u8Ack=0，发送nACK   
uint8_t IIC_Read_Byte ( uint8_t Ack )
{
	uint8_t i, Receive = 0;
	
	SDA_IN();		//SDA设置为输入
	
    for( i = 0; i < 8; i++ )
	{
        IIC_SCL( LOW );
        delayMicroseconds( 2 );
		
		IIC_SCL( HIGH );
        Receive <<= 1;
		
        if( READ_SDA )
		{
			Receive++;   
		}
		
		delayMicroseconds( 1 );
    }
	
    if ( !Ack )
	{
        IIC_NAck();		//发送nACK
	}
    else
	{
        IIC_Ack(); 		//发送ACK  
	}
	
    return Receive;
}



























