/*
 *  main.c:
 *	IIC 24c16  test
 */
#include "main.h"

//要写入到24c16的字符串数组
const uint8_t TEXT_Buffer[] = { "tian" };

#define SIZE sizeof(TEXT_Buffer)	

int main( void )
{
	printf( "-----testing-----\n" );
	
	uint8_t datatemp[SIZE];
	
	wiringPiSetupPhys();
	
	while( 0 )	//  AT24CXX_Check()  检测不到24c02
	{
		printf( "24c16 Check Failed!" );
		delay( 1000 );
	}
	
	while ( 1 )
	{
		AT24CXX_Init();			//IIC初始化
		
		AT24CXX_Write( 0, ( uint8_t *)TEXT_Buffer, SIZE );
		
		AT24CXX_Read( 0, datatemp, SIZE );
		
		printf("The data is: %s \n", datatemp );
		delay( 1000 );
	}	
	
	return 0;
}
