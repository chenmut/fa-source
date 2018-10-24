#include "main.h"


#define  	BUTTON		5
#define 	LED			10
#define 	BEEP		13

//初始化设置
void setup()
{
	//定义为物理管脚
	wiringPiSetupPhys();
	
	pinMode( LED,OUTPUT );
	pinMode( BEEP,OUTPUT );
	pinMode( BUTTON,INPUT );
	
	pullUpDnControl ( BUTTON, PUD_UP );	//按键引脚设置为上拉模式
	
	ledOff (LED );			//设置LED引脚状态为灭
	beepOff ( BEEP );		//设置BEEP引脚状态为不响
}

//-------------------------------------

int main(int argc, char **argv)
{
	volatile int flag = 1;			//标记两次不同的按键
	int time = 5;			//每次按键后维持的时间
	int freq[2] = {2, 5};	//两次频率
	
	setup();
	
	//------------------------------------
	
	while(1)
	{
		if( getButtonStatus( BUTTON ) == LOW )
		{
			
			//第一次响应按键
			if ( flag == 1 )
			{
				for (int i = 0; i < time * freq[0]; i++ )
				{
					ledOn ( LED );
					beepOn ( BEEP );
					delay( 500/freq[0] );
					ledOff (LED );
					beepOff ( BEEP );
					delay( 500/freq[0] );
					
					//将flag 减去1
					flag = 0;
				}
			}
			
			//第二次响应按键
			else if ( flag == 0 )		
			{
				for (int i = 0; i < time * freq[1]; i++ )
				{
					ledOn ( LED );
					beepOn ( BEEP );
					delay( 500/freq[1] );
					ledOff (LED );
					beepOff ( BEEP );
					delay( 500/freq[1] );
					
					flag = -1;
				}
			}
			
			
			//第三次响应按键
			else
			{
			ledOff (LED );
			beepOff ( BEEP );
			
			break;
			}
		}   
	}
	
	return 0;
}
