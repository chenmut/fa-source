/*
 *  main.c:
 *	IIC 24c16  test
 */
#include "main.h"

//要写入到24c16的字符串数组
const uint8_t TEXT_Buffer[] = {'0','1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };

//#define WORDSIZE sizeof( TEXT_Buffer )	

#define WORDSIZE 10

int main( void )
{

    uint8_t datatemp[WORDSIZE];
	
	wiringPiSetupPhys();
	
	while ( 1 )
	{
		int i = 0;
		
		memset( datatemp, 0, sizeof( datatemp ));
		
		printf( "------writing begin------\n" );
	
		for ( i = 0; i < 10; i += WORDSIZE )
		{
			AT24CXX_Write( i, ( uint8_t *)TEXT_Buffer, WORDSIZE ); 
		}
        
		delay ( 10 );
		
		for ( i = 0; i < 10; i += WORDSIZE )
		{
			AT24CXX_Read( i, datatemp, WORDSIZE );
			printf("The data is: %s \n", datatemp );
			delay ( 1 );  
		}
	
		printf( "------reading end ------\n" );
		
		delay( 2000 );
	}	
	
	return 0;
}
