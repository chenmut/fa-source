#include "wiringPi.h"
#include <stdio.h>

#define	BUTTON			 0
//-------------------------------------
int main(int argc, char **argv)
{
	wiringPiSetup();
	
	pinMode(BUTTON,INPUT);
	pullUpDnControl (BUTTON, PUD_UP);
	
	//------------------------------------
	while(1)
	{
		if ( digitalRead (BUTTON) == LOW )
		{
			printf ("BUTTON DETECTED!\n");
			return 0;
		}
		else 
		{
			printf ("NO BUTTON!\n");
			return 0;
		}	
	}
	
	return 0;
}