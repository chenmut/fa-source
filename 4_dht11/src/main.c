/*
 *  main.c:
 *	Simple test program to test the wiringPi functions
 *	DHT11 test
 */
#include "main.h"

#define DHTPIN		3

//dht11 test
int main( void )
{
	printf( " RasPi  DHT11 Temperature test program\n" );
	
	if ( wiringPiSetupPhys() == -1 )
		exit( 1 );
 
	while ( 1 )
	{
		read_dht11_dat( DHTPIN );
		delay( 1000 ); /* wait 1sec to refresh */
	}
 
	return(0);
}
