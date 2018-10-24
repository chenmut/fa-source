#include "led.h"

#ifndef	HIGH
#  define	HIGH	1
#  define	LOW		0
#endif

void ledOn( int pin)
{
	digitalWrite ( pin, HIGH );
}

void ledOff( int pin)
{
	digitalWrite ( pin, LOW );
}