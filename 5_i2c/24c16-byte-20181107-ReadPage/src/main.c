/*
 *  main.c:
 *	IIC 24c16  test
 */
#include "main.h"

//要写入到24c16的字符串数组
const uint8_t TEXT_Buffer[] = { 'a', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'G', 
								'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T' };

//#define WORDSIZE sizeof( TEXT_Buffer )	
#define WORDSIZE 16
#define PAGESIZE 16

#define READPAGE 1 		//0->读全部2048地址；1->读页


int main( void )
{
	printf( "-----testing-----\n" );
	
	uint8_t datatemp[ WORDSIZE ] = { 0 };
	
	wiringPiSetupPhys();
	
	while ( 1 )
	{
		int i = 0;
		
		memset( datatemp, 0, sizeof( datatemp ));
		
		for ( i = 0; i < 2048; i += PAGESIZE )
		{
			AT24CXX_Write( i, ( uint8_t *)TEXT_Buffer, WORDSIZE );
			delay ( 5 );  
		}

		AT24CXX_Read( 0, datatemp, 2048 );
		
		printf("The data is: %s \n", datatemp );

		delay( 500 );
	}	
	
	return 0;
}
