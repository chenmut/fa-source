/*
 *  main.c:
 *	IIC 24c16  test
 */
#include "main.h"

//要写入到24c16的字符串数组
const uint8_t TEXT_Buffer[] = { "a" };

#define SIZE sizeof(TEXT_Buffer)	

int main( void )
{
	printf( "-----testing-----\n" );
	
	uint8_t datatemp[SIZE] = {0};
	
	wiringPiSetupPhys();
	
	while( AT24CXX_Check() )	//  AT24CXX_Check()  检测不到24c02
	{
		printf( "24c16 Check Failed!" );
		delay( 1000 );
	}
	
	while ( 1 )
	{
		
		AT24CXX_Write( 64, ( uint8_t *)TEXT_Buffer, SIZE );
		
		AT24CXX_Read( 64, datatemp, SIZE );
		
		printf("The data is: %s \n", datatemp );
		delay( 1000 );
	}	
	
	return 0;
}
