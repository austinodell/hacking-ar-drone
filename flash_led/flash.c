#include <stdio.h>

int main(int argc, char *argv[]) {
	int a;
	for(a=0; a<10; a++) {
		system("gpio 181 -d lo 0");system("gpio 180 -d lo 0"); // Both LEDs off
		sleep(1); // wait 1 second
		system("gpio 180 -d lo 1"); // Green LED on
		sleep (1); // wait 1 second
		system("gpio 181 -d lo 1"); // Red LED on
		sleep(1); // wait 1 second
	}
	return 0;
}
