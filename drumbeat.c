#include <stdlib.h>
#include <wiringPi.h>
#include <stdio.h>
#include <alsa/asoundlib.h>


#define button_pin 18 // pin 12
#define button2_pin 23 // pin 16
#define button3_pin 24 // pin 18
#define button4_pin 25 // pin 22
#define button5_pin 17 // pin 11
#define button6_pin 27 // pin 13

static char *device = "default";                        /* playback device */
snd_output_t *output = NULL;

int play_sound(unsigned char buffer[], size_t buffer_size, snd_pcm_t *handle)
{
		unsigned int i;
		snd_pcm_sframes_t frames;
        for (i = 0; i < 16; i++) {
                frames = snd_pcm_writei(handle, buffer, buffer_size);
                if (frames < 0)
                        frames = snd_pcm_recover(handle, frames, 0);
                if (frames < 0) {
                        printf("snd_pcm_writei failed: %s\n", snd_strerror(frames));
                        break;
                }
                if (frames > 0 && frames < (long)buffer_size)
                        printf("Short write (expected %li, wrote %li)\n", (long)buffer_size, frames);
        }
       // snd_pcm_close(handle);
        return 0;
}

void init_sound_engine(snd_pcm_t *handle) 
{
	    int err;
        if ((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
                printf("Playback open error: %s\n", snd_strerror(err));
                exit(EXIT_FAILURE);
        }
        if ((err = snd_pcm_set_params(handle,
                                      SND_PCM_FORMAT_U8,
                                      SND_PCM_ACCESS_RW_INTERLEAVED,
                                      1,
                                      48000,
                                      1,
                                      500000)) < 0) {   /* 0.5sec */
                printf("Playback open error: %s\n", snd_strerror(err));
                exit(EXIT_FAILURE);
        }
}

int main(void) 
{
	/*unsigned char buffer[16*1024];                     
	unsigned int i;
	snd_pcm_t *handle;
	init_sound_engine(handle);
    for (i = 0; i < sizeof(buffer); i++)
        buffer[i] = random() & 0xff;
        
    play_sound(buffer, sizeof(buffer), handle);
	*/
	printf("test start\n");
	//system("omxplayer /home/pi/Downloads/samples/808_kick.wav");
	
	if (wiringPiSetupGpio() == -1)
		return 1;
	
	pinMode(button_pin, INPUT);
	pullUpDnControl(button_pin, PUD_UP);
	
	pinMode(button2_pin, INPUT);
	pullUpDnControl(button2_pin, PUD_UP);
	
	pinMode(button3_pin, INPUT);
	pullUpDnControl(button3_pin, PUD_UP);
	
	pinMode(button4_pin, INPUT);
	pullUpDnControl(button4_pin, PUD_UP);
	
	pinMode(button5_pin, INPUT);
	pullUpDnControl(button5_pin, PUD_UP);
	
	pinMode(button6_pin, INPUT);
	pullUpDnControl(button6_pin, PUD_UP);
	
	
	
	int prev_b1_state = 1;
	int prev_b2_state = 1;
	int prev_b3_state = 1;
	int prev_b4_state = 1;
	int prev_b5_state = 1;
	int prev_b6_state = 1;
		
	while(1){
		if(digitalRead(button_pin) == 0 && prev_b1_state == 1){
			system("aplay -d 1 -c 32 /home/pi/Downloads/samples/kick.wav &");
			prev_b1_state = 0;
		}
		else if (digitalRead(button_pin) == 1)
			prev_b1_state = 1;
			
		if(digitalRead(button2_pin) == 0 && prev_b2_state == 1){
			system("aplay -d 1 -c 32 /home/pi/Downloads/samples/snare.wav &");
			prev_b2_state = 0;
		}
		else if (digitalRead(button2_pin) == 1)
			prev_b2_state = 1;
			
		if(digitalRead(button3_pin) == 0 && prev_b3_state == 1){
			system("aplay -d 1 -c 32 /home/pi/Downloads/samples/hat.wav &");
			prev_b3_state = 0;
		}
		else if (digitalRead(button3_pin) == 1)
			prev_b3_state = 1;
			
		if(digitalRead(button4_pin) == 0 && prev_b4_state == 1){
			system("aplay -d 1 -c 32 /home/pi/Downloads/samples/crash.wav &");
			prev_b4_state = 0;
		}
		else if (digitalRead(button4_pin) == 1)
			prev_b4_state = 1;
			
		if(digitalRead(button5_pin) == 0 && prev_b5_state == 1){
			system("aplay -d 1 -c 32 /home/pi/Downloads/samples/perc.wav &");
			prev_b5_state = 0;
		}
		else if (digitalRead(button5_pin) == 1)
			prev_b5_state = 1;
			
		if(digitalRead(button6_pin) == 0 && prev_b6_state == 1){
			system("aplay -c 32 /home/pi/Downloads/samples/melody.wav &");
			prev_b6_state = 0;
		}
		else if (digitalRead(button6_pin) == 1)
			prev_b6_state = 1;

		delay(1);
	}
		
	
		
	return 0;
}
