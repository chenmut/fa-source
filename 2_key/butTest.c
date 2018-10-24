#include "butTest.h"

int main()
{
	wiringPiSetup(BUTTON)

	printf("test interrput\n");  
	pinMode(BUTTON,INPUT); 
	pullUpDnControl(BUTTON,PUD_UP); 
	
	while(1)
	{
		while(digitalRead(BUTTON)==LOW);  
		printf("key Press\n");  
	}
 	return 0;
}