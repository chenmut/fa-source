/*
 *  main.c:
 *	SPI NRF24L01  test
 */
#include "main.h"

#define NRF24L01_MODE	 1 		//0->RX模式；1->TX模式

int main( void )
{
	wiringPiSetupPhys();
	
	while ( 1 )
	{
		unsigned char uc_temp_buf[33];
		unsigned char uc_tx_symbol;
		
		printf("----testing----\n");
		
		
		if ( NRF24L01_MODE == 0 )	//RX模式
		{
			memset( uc_temp_buf, 0, sizeof( uc_temp_buf ));
			NRF24L01_RX_Mode();	
			
			while ( 1 )
			{
				if ( NRF24L01_RxPacket( uc_temp_buf ) == 0 )
				{
					uc_temp_buf[32] = 0;
					
					printf( "The data is: %s\n", uc_temp_buf );
				}	
				else
				{
					printf( "Receive Failed!\n" );
				}
				
				delayMicroseconds( 100 );
			}
		}
		else	//TX模式
		{
			uc_tx_symbol = '0';
			
			NRF24L01_TX_Mode();
			
			while ( 1 )
			{
				if ( NRF24L01_TxPacket( uc_temp_buf ) == TX_OK )
				{
					for ( unsigned char nTemp = 0; nTemp < 32; nTemp++ )
					{
						uc_temp_buf[nTemp] = uc_tx_symbol;
						uc_tx_symbol++;
					}
					
					uc_temp_buf[32] = 0;
				}
				else
				{
					printf( "Send Failed!\n" );
				}
				
				delay( 1000 );
			}	
		}	
	}
	
	return 0;
}
