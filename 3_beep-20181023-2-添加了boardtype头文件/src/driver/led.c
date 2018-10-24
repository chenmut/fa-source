#include "led.h"

#ifndef	HIGH
	#define	HIGH	1
	#define	LOW		0
#endif

void ledOn( int pin)
{
	digitalWrite ( pin, HIGH );
}

void ledOff( int pin)
{
	digitalWrite ( pin, LOW );
}

/*
void ledBlink(int pin, int freq)
{
	digitalWrite( pin, HIGH );
	delay(500/freq);
	digitalWrite( pin, LOW );
	delay(500/freq);
}
*/