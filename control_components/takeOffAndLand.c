#include <stdio.h>

int main(int argc, char *argv[]) {
	system("./atcomproxy_arm -v -d /dev/tty");
	sleep(2);
	system("AT*REF=1,512");
	sleep(2);
	system("AT(REF=2,1024");
}