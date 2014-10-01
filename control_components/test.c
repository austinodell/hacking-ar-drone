#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MOT_LEDOFF 0
#define MOT_LEDRED 1
#define MOT_LEDGREEN 2
#define MOT_LEDORANGE 3

#define MOT_PWM_max 0x1ff
#define MOT_PWM_min 0x00

int mot_fd;

void motorboard_SetLeds(uint8_t,uint8_t,uint8_t,uint8_t);
void motorboard_SetPWM(uint16_t,uint16_t,uint16_t,uint16_t);

int main(int argc, char *argv[]) {
	motorboard_SetLeds(MOT_LEDOFF,MOT_LEDGREEN,MOT_LEDRED,MOT_LEDORANGE);
	uint16_t mot_pwm = (uint16_t) MOT_PWM_max/2;
	motorboard_SetPWM(mot_pwm,mot_pwm,mot_pwm,mot_pwm);
	
	mot_fd = open("/dev/ttyPA1", O_RDWR | O_NOCTTY | O_NDELAY);
	if (mot_fd == -1)
	{
		perror("open_port: Unable to open /dev/ttyPA1 - ");
	}
}

void motorboard_SetLeds(uint8_t led0, uint8_t led1, uint8_t led2, uint8_t led3)
{
	int a;
	uint8_t cmd[2];
	cmd[0]=0x60 | ((led0&3)<<3)  | ((led1&3)<<1)   | ((led2&3)>>1);
	cmd[1]=((led2&3)<<7)  | ((led3&3)<<5);
	//write(mot_fd, cmd, 2);
	for(a=0;a<2;a++) {
		printf("LED %i: %x\n",a+1,cmd[a]);
	}
}

void motorboard_SetPWM(uint16_t pwm0, uint16_t pwm1, uint16_t pwm2, uint16_t pwm3)
{
	int a;
	uint8_t cmd[5];
	cmd[0] = 0x20 | ((pwm0&0x1ff)>>4);
	cmd[1] = ((pwm0&0x1ff)<<4) | ((pwm1&0x1ff)>>5);
	cmd[2] = ((pwm1&0x1ff)<<3) | ((pwm2&0x1ff)>>6);
	cmd[3] = ((pwm2&0x1ff)<<2) | ((pwm3&0x1ff)>>7);
	cmd[4] = ((pwm3&0x1ff)<<1);
	//write(mot_fd, cmd, 5);
	for(a=0;a<5;a++) {
		printf("Motor %i: %x\n",a+1,cmd[a]);
	}
}
