#include <stdio.h>

int main(int argc, char *argv[]) {
	system("gpio 181 -d lo 0");
	system("gpio 180 -d lo 1");
	return 0;
}
