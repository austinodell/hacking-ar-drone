#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdlib.h>  //exit()
#include <math.h>

int main() {
	int nav_fd = open("/dev/ttyO1", O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
	int a,n,c;
	char nav[46];
	if (nav_fd == -1)
	{
		perror("nav_Init: Unable to open /dev/ttyO1 - ");
		return 101;
	} else {
		printf("Successfully opened file descriptor: nav_fd code = %d\r\n\n",nav_fd);
		n = read(nav_fd, nav, 46);
		if(n == -1) {
			perror("error reading file descriptor");
			return 101;
		} else {
			for(a=0;a<46;a++) {
				printf("%c",nav[a]);
			}
		}
		
		c = close(nav_fd);
		if(c == -1) {
			perror("error closing file descriptor");
			return 101;
		} else {
			printf("Successfully closed file descriptor");
		}
	}
	return 1;
}