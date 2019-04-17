#include <stdlib.h>
#include <wiringPi.h>
#include <stdio.h>


#define button_pin 18 // pin 12

int main(void) 
{
	printf("test start\n");
	//system("omxplayer /home/pi/Downloads/samples/808_kick.wav");
	
	if (wiringPiSetupGpio() == -1)
		return 1;
	
	pinMode(button_pin, INPUT);
	pullUpDnControl(button_pin, PUD_UP);
	
		
	while(1){
		if(digitalRead(button_pin) == 0){
			system("aplay /home/pi/Downloads/samples/808_kick.wav");
			delay(10);
		}
		delay(1);
	}
		
	
		
	return 0;
}
