#include <stdio.h>
#include "wiringPi.h"

#define	BUTTON			2
#define	LED				9

#define	LEDON			HIGH
#define	LEDOFF			LOW

//-------------------------------------

int main(int argc, char **argv)
{
	wiringPiSetup();
	
	pinMode(LED,OUTPUT);
	pinMode(BUTTON,INPUT);
	
	pullUpDnControl (BUTTON, PUD_UP);
	
	digitalWrite (LED, LEDOFF);
	
	//------------------------------------
	while(1)
	{
		if ( digitalRead (BUTTON) == LOW )
		{
			delay(1);
			digitalWrite ( LED, LEDON );
		}
		//digitalWrite ( LED, LOW );
	}
	
	return 0;
}