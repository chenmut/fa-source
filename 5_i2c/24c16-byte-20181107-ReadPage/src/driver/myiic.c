#include "myiic.h"
#include "mydelay.h"

//����IIC��ʼ�ź�
uint8_t IIC_Start( void )
{   
	pinMode( SDAPIN, OUTPUT );     //sda�����
	pinMode( SCLPIN, OUTPUT );     //sda�����
	
	digitalWrite( SDAPIN, HIGH );	  	  
	digitalWrite( SCLPIN, HIGH );
	delayMicroseconds( 4 );           
	
	digitalWrite( SDAPIN, LOW );
	delayMicroseconds( 4 );
	
	digitalWrite( SCLPIN,LOW );                        //ǯסI2C���ߣ�׼�����ͻ�������� 
	
	return 0; 
}	  

//����IICֹͣ�ź� scl�ߵ�ƽʱ sda�ɵ͵�ƽ��ߵ�ƽ����
uint8_t IIC_Stop( void )
{
	pinMode( SDAPIN, OUTPUT );		//sda�����
	
	digitalWrite( SCLPIN, LOW );
	digitalWrite( SDAPIN, LOW );	//STOP:when CLK is high DATA change form low to high
 	delayMicroseconds(4);
	
	digitalWrite( SCLPIN, HIGH ); 
	digitalWrite( SDAPIN, HIGH );	//2C���߽����ź�
	
	delayMicroseconds(4);         

	return 0; 	
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC_Wait_Ack( void )
{
	uint8_t u8ErrTime=0;
	
	pinMode( SDAPIN, INPUT );      //SDA����Ϊ����  
	
	digitalWrite( SDAPIN, HIGH );
	delayMicroseconds( 1 );
	
	digitalWrite( SCLPIN, HIGH );
	delayMicroseconds( 1 );	
    
	//�ȴ�sda�͵�ƽ	
	while ( digitalRead( SDAPIN ) == HIGH )
	{
		u8ErrTime++;
		
		if( u8ErrTime > 250 )
		{
			IIC_Stop();
			return 1;
		}
	}
	
	digitalWrite( SCLPIN,LOW );		//ʱ�����0 
	
	return 0;  
} 

//����ACKӦ��
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

//������ACKӦ��		    
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
			 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
uint8_t IIC_Send_Byte( uint8_t txd )
{                        
    uint8_t t;   
	
	pinMode( SDAPIN, OUTPUT ); 	    
    digitalWrite( SCLPIN, LOW );		//����ʱ�ӿ�ʼ���ݴ���
	
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
		delayMicroseconds(2);   	//��TEA5767��������ʱ���Ǳ����
		
		digitalWrite( SCLPIN, HIGH );
		delayMicroseconds(2); 
		
		digitalWrite( SCLPIN, LOW );	
		delayMicroseconds(2);
    }	

	return 0; 	
} 	
    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t IIC_Read_Byte( unsigned char ack )
{
	unsigned char i, receive=0;
	
	pinMode( SDAPIN, INPUT );			//SDA����Ϊ����
	
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
        IIC_NAck();//����nACK
	}
    else
	{
        IIC_Ack(); //����ACK   
	}
	
    return receive;
}







