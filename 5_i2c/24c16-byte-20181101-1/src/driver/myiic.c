#include "myiic.h"
#include "mydelay.h"

//��ʼ��IIC
void IIC_Init(void)
{
	SCL_OUT();
	SDA_OUT();
	
	IIC_SDA( HIGH );	  	  
	IIC_SCL( HIGH );
}

//����IIC��ʼ�ź�
void IIC_Start( void )
{
	SDA_OUT();  //sda�����
	
	IIC_SDA( HIGH );	  	  
	IIC_SCL( HIGH );
	delayMicroseconds( 4 );
	
 	IIC_SDA( LOW );		 //START:when CLK is high,DATA change form high to low 
	delayMicroseconds( 4 );
	
	IIC_SCL( LOW );		//ǯסI2C���ߣ�׼�����ͻ�������� 
}
	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT() ;			//sda�����
	
	IIC_SCL( LOW );
	IIC_SDA( LOW );		//STOP:when CLK is high DATA change form low to high
 	delayMicroseconds( 4 );
	
	IIC_SDA( HIGH );	  	  
	IIC_SCL( HIGH );	//����I2C���߽����ź�
 	delayMicroseconds( 4 );
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC_Wait_Ack ( void )
{
	uint8_t ErrTime=0;
	
	SDA_IN();      //SDA����Ϊ����  
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
	
	IIC_SCL( LOW ); 	//ʱ�����0   
	return 0;  
} 

//����ACKӦ��
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

//������ACKӦ��		    
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
					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte ( uint8_t TextData )
{                        
    uint8_t t; 
	
	SDA_OUT(); 	    
    IIC_SCL( LOW );		//����ʱ�ӿ�ʼ���ݴ���
	
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
    
//��1���ֽڣ�u8Ack=1ʱ������ACK��u8Ack=0������nACK   
uint8_t IIC_Read_Byte ( uint8_t Ack )
{
	uint8_t i, Receive = 0;
	
	SDA_IN();		//SDA����Ϊ����
	
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
        IIC_NAck();		//����nACK
	}
    else
	{
        IIC_Ack(); 		//����ACK  
	}
	
    return Receive;
}



























