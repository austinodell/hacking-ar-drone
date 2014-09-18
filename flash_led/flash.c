#include <stdio.h>

int main(int argc, char *argv[]) {
	int a;
	/*for(a=0; a<10; a++) {
		system("/usr/sbin/gpio 63 -d ho 0");system("/usr/sbin/gpio 64 -d ho 0"); // Both LEDs off
		printf("Hello world!");
		sleep(1); // wait 1 second
		system("/usr/sbin/gpio 64 -d ho 1"); // Green LED on
		printf("I'm green!");
		sleep (1); // wait 1 second
		system("/usr/sbin/gpio 64 -d ho 0"); // Green LED off
		sleep(1); // wait 1 second
		system("/usr/sbin/gpio 63 -d ho 1"); // Red LED on
		printf("I'm red!");
		sleep(1); // wait 1 second
	}*/
	//system("/usr/sbin/gpio 64 -d ho 1");
	printf("Test");
	return 0;
}
