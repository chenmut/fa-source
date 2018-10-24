//button test
#include "butTest.h"

int main (void)
{
	//int value=10;
	// Enable the on-goard GPIO

	wiringPiSetup () ;
	
	printf ("Raspberry Pi - Quick2Wire Mainboard Button  Test\n") ;
	
	pinMode (BUTTON, INPUT) ;
	pullUpDnControl(BUTTON,PUD_UP);
	printf ("button  test! \n");
//-------------------------------------
//	value = digitalRead(BUTTON);
//	printf ("--value: %d--", value);
//----------------------------
//	volatile int i = 0;
// for (i=0;i<100;i++)
// {
// 	while(digitalRead (BUTTON) == HIGH)	// Swap LED states
// 	{
// 		int value=10;
// 		printf("value initial --%d--\n", value);
// 		value=digitalRead(BUTTON);
// 		printf ("button detect! --%d--LEVEL: %d\n", i,value);
// 		delay(10);
// 	}
// 	delay (1000) ;
// }

//------------------------------------
		if(digitalRead (BUTTON) == LOW)
		{
			printf ("KEY PRESS!");
			delay(500);
		}

  return 0 ;
}