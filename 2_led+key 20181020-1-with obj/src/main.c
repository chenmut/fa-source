#include "main.h"

#define  	BUTTON		2
#define 	LED			9

//-------------------------------------
int main(int argc, char **argv)
{
	
	wiringPiSetup();
	
	pinMode(LED,OUTPUT);
	pinMode(BUTTON,INPUT);
	
	pullUpDnControl (BUTTON, PUD_UP);
	
	digitalWrite (LED, LOW);
	//------------------------------------
	while(1)
	{
		if ( getButtonStatus ( BUTTON ) == LOW )
		{
			delay(5);
			ledOn( LED );
		}
		else
		{
			delay(5);
			ledOff( LED );
		}
		delay(50);
	}
	
	return 0;
}
