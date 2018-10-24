#include "main.h"

#define  	BUTTON		2
#define 	LED			9

#define 	LEDON		HIGH
#define 	LEDOFF		LOW

//-------------------------------------
int main(int argc, char **argv)
{
	wiringPiSetup();
	
	pinMode(LED,OUTPUT);
	pinMode(BUTTON,INPUT);
	
	pullUpDnControl (BUTTON, PUD_UP);	//设置引脚的上拉或下拉功能
	
	digitalWrite (LED, LEDOFF);	//低电平时led灭
	
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
