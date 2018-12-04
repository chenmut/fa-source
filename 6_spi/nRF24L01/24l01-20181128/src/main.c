/*
 *  main.c:
 *	SPI NRF24L01  test
 */
#include "main.h"

#define NRF24L01_MODE	1		//0->RX模式；1->TX模式
#define RXSIZE			11
#define TXSIZE			11

#define CSPINNUM		10
#define CEPINNUM        8 


int main( void )
{
	printf("----nRF24L01 SPI TEST PROG!----\r\n");
	
	unsigned char u8RxBuf[RXSIZE];
	unsigned char u8TxBuf[TXSIZE];
	unsigned char u8TxSymbol;
	
	//NRF24L01_Init();
	
	wiringPiSetupPhys();
	
    delay(1);

	while ( 0 )
	{
		printf("  Command Data\r\n");
		
		unsigned char data[33];
		
		wiringPiSPISetup( 0, 1000000 );    //1Mb/s
		pinMode( CEPINNUM, OUTPUT );
		digitalWrite( CEPINNUM, LOW );
		
		NRF24L01_Command( 0, NRF_WRITE_REG | CONFIG, ( 1 << EN_CRC ) | ( 1 << PWR_UP ));
		
		data[0]	= WR_TX_PLOAD;
		data[1]	= 0xfe;
		data[2]	= 0xdc;
		data[3]	= 0xba;
		data[4]	= 0x98; 
		
		wiringPiSPIDataRW( 0, data, 5 );
	
		digitalWrite( CEPINNUM, HIGH );
		
		NRF24L01_Command( 0, NRF_READ_REG | NRF_FIFO_STATUS, 0 );
		
		delay( 1*1000 );
	}
	
	//测试硬件spi
	while ( 0 )
	{
		unsigned char buf[20] = { 0x9F,0x55 };
		int ret000 = 0;
		
		ret000 = wiringPiSPISetup( 0, 1000*1000);
		while (ret000!=-1)
		{
			buf[0]=0x01;	//寄存器地址
			buf[1]=0x02;	//要写的数据
			buf[2]=0x03;	//寄存器地址
			buf[3]=0x04;	//要写的数据
			buf[4]=0x05;	//寄存器地址
			buf[5]=0x06;	//要写的数据
			buf[6]=0x07;	//寄存器地址
			buf[7]=0x08;	//要写的数据
			buf[8]=0x09;	//寄存器地址
			buf[9]=0x0a;	//要写的数据
			buf[10]=0x10;	//寄存器地址
			buf[11]=0x11;	//要写的数据
			buf[12]=0x12;	//寄存器地址
			buf[13]=0x13;	//要写的数据
			buf[14]=0x14;	//寄存器地址
			buf[15]=0x15;	//要写的数据
			buf[16]=0x16;	//要写的数据
			buf[17]=0x17;	//要写的数据
			buf[18]=0x18;	//要写的数据
			buf[19]=0x19;	//要写的数据
			
			if( 1 ) 
			{
				ret000 = wiringPiSPIDataRW(0, buf, 20); 					
			}
			else
			{
				digitalWrite( CSPINNUM, LOW );
				
				ret000 = wiringPiSPIDataRW1( 0, buf, 20, 1 );	//cs_change
				
				digitalWrite( CSPINNUM, HIGH );
			}
			
			if( ret000 < 0 )
			{
				printf("spi error\n");
			}
			else
			{
				printf("spi rx data : %d\n", buf[0]);
			}
			
			delay( 2*1000);
		}
	}
	
	//测试硬件spi，读写5字节
	while ( 0 )
	{
		printf("Starting SPI Test\n");
		
		unsigned char u8SPIBufSize = 2;
		unsigned char u8SPITxBuf[2] = { 0X21, 0X01 };
		unsigned char u8SPIRxBuf[2] = { 0X01, 0XFF };
		//unsigned char u8SPIRxBuf[2] = { 0X01, 0X00 };
		unsigned int ret111 = 0;
		unsigned int i;
		
		wiringPiSPISetup( 0, 1000*1000 );
			
		ret111 = wiringPiSPIDataRW( 0, u8SPITxBuf, u8SPIBufSize );
		
		delay(1);
		
		ret111 = wiringPiSPIDataRW( 0, u8SPIRxBuf, 1 );
		
		//printf("-ret-: %8d -rx-: %8d\n", ret111, u8SPIRxBuf[1] );
		
		if( u8SPITxBuf[1] != u8SPIRxBuf[1] )
		{
			printf("spi error\n");
		}
		else
		{
			printf("spi rx data: %d\n", u8SPIRxBuf[1] );		
		}
		
 		delay(1000);
	}
	
	
	NRF24L01_Init();
	
	//测试读取状态寄存器
	while ( 0 )
	{
		unsigned char nTemp = 1;
		
		NRF24L01_WriteReg( NRF_WRITE_REG + EN_AA, 0x01 );
		nTemp = NRF24L01_ReadReg( EN_AA );
		
		//nTemp = NRF24L01_ReadReg( STATUS );  	//读取状态寄存器的值	   
		//NRF24L01_WriteReg( NRF_WRITE_REG + STATUS, nTemp ); //清除TX_DS或MAX_RT中断标志
	
		printf( "Data is: %x \n", nTemp );
		
 		delay(1000);
	}
	
	//接收或发送
	while (1)
	{
		printf("----testing----\r\n");
		
		if ( NRF24L01_MODE == 0 )	//RX模式
		{
			memset( u8RxBuf, 0, sizeof( u8RxBuf ));
			
			NRF24L01_RXMode();	
			
			while ( 1 )
			{
				if ( NRF24L01_RxPacket( u8RxBuf ) == 0 )
				{
					u8RxBuf[RXSIZE-1] = 0;
					printf( "The received data are: %s\n", u8RxBuf );
				}	
				else
				{
					printf( "Receive Failed!\r\n" );
				}
				
				delay( 500 );
			}
		}
		else	//TX模式
		{
			unsigned char nTxStatus = 1;
			memset( u8TxBuf, 0, TXSIZE);
			
			u8TxSymbol = '0';
			for ( unsigned char k = 0; k < (TXSIZE-1) ; k++)
			{
				u8TxBuf[ k ] = u8TxSymbol;
				u8TxSymbol++;
			}
			u8TxBuf[TXSIZE-1] = 0;
			printf( "The send data are: %s\n", u8TxBuf );
			
			NRF24L01_TXMode();
			
			while ( 1 )
			{
				nTxStatus = NRF24L01_TxPacket( u8TxBuf );
				
				if ( nTxStatus == TX_OK )
				{
					printf( "Send succeed!\r\n" );
				}
				else if( nTxStatus == MAX_TX )
				{
					printf( "MAX is up----%d\n", MAX_TX );
				}
				else
				{
					printf( "Send Failed!\r\n" );
				}
				
				delay( 500 );
			}	
		}	
	}
	
	return 0;
}
