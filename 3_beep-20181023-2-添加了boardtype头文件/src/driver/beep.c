#include "beep.h"

void beepOn( int pin)
{
	digitalWrite ( pin, HIGH );
}

void beepOff( int pin)
{
	digitalWrite ( pin, LOW );
}

