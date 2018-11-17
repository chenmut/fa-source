#include "myiic.h"
#include "mydelay.h"

//产生IIC开始信号
uint8_t IIC_Start( void )
{   
	pinMode( SDAPIN, OUTPUT );     //sda线输出
	pinMode( SCLPIN, OUTPUT );     //sda线输出
	
	digitalWrite( SDAPIN, HIGH );	  	  
	digitalWrite( SCLPIN, HIGH );
	delayMicroseconds( 4 );           
	
	digitalWrite( SDAPIN, LOW );
	delayMicroseconds( 4 );
	
	digitalWrite( SCLPIN,LOW );                        //钳住I2C总线，准备发送或接收数据 
	
	return 0; 
}	  

//产生IIC停止信号 scl高电平时 sda由低电平向高电平跳变
uint8_t IIC_Stop( void )
{
	pinMode( SDAPIN, OUTPUT );		//sda线输出
	
	digitalWrite( SCLPIN, LOW );
	digitalWrite( SDAPIN, LOW );	//STOP:when CLK is high DATA change form low to high
 	delayMicroseconds(4);
	
	digitalWrite( SCLPIN, HIGH ); 
	digitalWrite( SDAPIN, HIGH );	//2C总线结束信号
	
	delayMicroseconds(4);         

	return 0; 	
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack( void )
{
	uint8_t u8ErrTime=0;
	
	pinMode( SDAPIN, INPUT );      //SDA设置为输入  
	
	digitalWrite( SDAPIN, HIGH );
	delayMicroseconds( 1 );
	
	digitalWrite( SCLPIN, HIGH );
	delayMicroseconds( 1 );	
    
	//等待sda低电平	
	while ( digitalRead( SDAPIN ) == HIGH )
	{
		u8ErrTime++;
		
		if( u8ErrTime > 250 )
		{
			IIC_Stop();
			return 1;
		}
	}
	
	digitalWrite( SCLPIN,LOW );		//时钟输出0 
	
	return 0;  
} 

//产生ACK应答
uint8_t IIC_Ack( void )
{
	digitalWrite( SCLPIN, LOW );
	pinMode( SDAPIN, OUTPUT );
	
	digitalWrite( SDAPIN, LOW );
	delayMicroseconds(2);         
	
	digitalWrite( SCLPIN, HIGH );
	delayMicroseconds(2);        
	
	digitalWrite( SCLPIN, LOW );
	
	return 0; 
}

//不产生ACK应答		    
uint8_t IIC_NAck( void )
{
	digitalWrite( SCLPIN, LOW );
	pinMode( SDAPIN, OUTPUT );
	
	digitalWrite( SDAPIN, HIGH );
	delayMicroseconds(2);
	
	digitalWrite( SCLPIN, HIGH );
	delayMicroseconds(2);
	
	digitalWrite( SCLPIN, LOW );
	
	return 0; 
}		
			 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
uint8_t IIC_Send_Byte( uint8_t txd )
{                        
    uint8_t t;   
	
	pinMode( SDAPIN, OUTPUT ); 	    
    digitalWrite( SCLPIN, LOW );		//拉低时钟开始数据传输
	
    for ( t = 0; t < 8; t++)
    {              
		if ((txd & 0x80) >> 7 )
		{
			digitalWrite( SDAPIN, HIGH );
		}
		else
		{
			digitalWrite( SDAPIN, LOW );
		}
		
		txd <<= 1; 	  
		delayMicroseconds(2);   	//对TEA5767这三个延时都是必须的
		
		digitalWrite( SCLPIN, HIGH );
		delayMicroseconds(2); 
		
		digitalWrite( SCLPIN, LOW );	
		delayMicroseconds(2);
    }	

	return 0; 	
} 	
    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t IIC_Read_Byte( unsigned char ack )
{
	unsigned char i, receive=0;
	
	pinMode( SDAPIN, INPUT );			//SDA设置为输入
	
    for ( i = 0; i < 8; i++ )
	{
        digitalWrite( SCLPIN, LOW ); 
        delayMicroseconds(2);
		
		digitalWrite( SCLPIN, HIGH );
        receive <<= 1;
		
        if( digitalRead( SDAPIN ))
		{
			receive++;   
		}
		
		delayMicroseconds( 1 ); 
    }					 
    if ( !ack )
	{
        IIC_NAck();//发送nACK
	}
    else
	{
        IIC_Ack(); //发送ACK   
	}
	
    return receive;
}







