#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

#include "../util/type.h"
#include "../util/util.h"
#include "mot.h"
#include "../vbat/vbat.h"

size_t getFilesize(const char* filename);

int main( int argc, char *argv[] )
{
	system("kk");
	sleep(1);
	int sockfd, newsockfd, portno;
	unsigned int clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int  n;
	vbat_struct vbat;
	struct stat stat_buf;

	/* First call to socket() function */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	{
		perror("ERROR opening socket");
		exit(1);
	}
	/* Initialize socket structure */
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = argv[1] ? atoi(argv[1]) : 6000;
	
	printf("Opening socket on port %i\n",portno);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	/* Now bind the host address using bind() call.*/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("ERROR on binding");
		exit(1);
	}
	
	/* Start motors */
	mot_Init();

	/* Now start listening for the clients, here process will
	* go in sleep mode and will wait for the incoming connection
	*/
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	
	
	float throttle1 = 0;
	float throttle2 = 0;
	float throttle3 = 0;
	float throttle4 = 0;
	float step=0.01;
	
	while(1) { 
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, 
									&clilen);
		if (newsockfd < 0) 
		{
			perror("ERROR on accept");
			exit(1);
		}
		else
		{
			printf("Connected to client!\n");
		}
		
		/* If connection is established then start communicating */
		bzero(buffer,256);
		n = read( newsockfd,buffer,255 );
		if (n < 0)
		{
			perror("ERROR reading from socket");
			exit(1);
			break;
		}
		
		char help[] = "1..4: Motor 1..4 at .5\n5: All Motors at .5\n+/-: Throttle up/down .01\n0: Stop All Motors\na: LEDs off\nd: LEDs on\nz: Take picture\nc: Flash bottom LED\np: Presentation Mode";
		
		char c=tolower(buffer[0]);
		if(c=='h') {
			write(newsockfd,&help,sizeof(help));
			printf("Help\n");
		}
		if(c=='q') {
			write(newsockfd,"Quit",4);
			printf("Quit\n");
			mot_Close();
			break;
		}
		if(c=='1') {
			write(newsockfd,"Run motor 1 at 25%",18);
			printf("Run Motor1 25\n");
			throttle1 = .25;
			throttle2 = 0;
			throttle3 = 0;
			throttle4 = 0;
			mot_Run(throttle1,throttle2,throttle3,throttle4);
		}
		if(c=='2') {
			write(newsockfd,"Run motor 2 at 25%",18);
			printf("Run Motor2 25\n");
			throttle1 = 0;
			throttle2 = .25;
			throttle3 = 0;
			throttle4 = 0;
			mot_Run(throttle1,throttle2,throttle3,throttle4);
		}
		if(c=='3') {
			write(newsockfd,"Run motor 3 at 25%",18);
			printf("Run Motor3 25\n");
			throttle1 = 0;
			throttle2 = 0;
			throttle3 = .25;
			throttle4 = 0;
			mot_Run(throttle1,throttle2,throttle3,throttle4);
		}
		if(c=='4') {
			write(newsockfd,"Run motor 4 at 25%",18);
			printf("Run Motor4 25\n");
			throttle1 = 0;
			throttle2 = 0;
			throttle3 = 0;
			throttle4 = .25;
			mot_Run(throttle1,throttle2,throttle3,throttle4);
		}
		if(c=='5') {
			write(newsockfd,"Run all motors at 25%",21);
			printf("Run All Motors 25\n");
			throttle1 = .25;
			throttle2 = .25;
			throttle3 = .25;
			throttle4 = .25;
			mot_Run(throttle1,throttle2,throttle3,throttle4);
		}
		if(c=='6') {
			write(newsockfd,"Taking off",10);
			printf("Taking off\n");
			float throttle14 = .25;
			float throttle23 = .25;
			mot_Run(throttle14,throttle23,throttle23,throttle14);
			usleep(500000);
			int a = 0;
			while(a<50) {
				throttle14 += .01;
				throttle23 += .01;
				mot_Run(throttle14,throttle23,throttle23,throttle14);
				usleep(100000);
				a++;
			}
			while(a>0) {
				throttle14 -= .01;
				throttle23 -= .01;
				mot_Run(throttle14,throttle23,throttle23,throttle14);
				usleep(150000);
				a--;
			}
			mot_Stop();
		}
		if(c=='-') {
			float val;
			if(throttle1>step) { throttle1 -= step; val = throttle1; }
			if(throttle2>step) { throttle2 -= step; val = throttle2; }
			if(throttle3>step) { throttle3 -= step; val = throttle3; }
			if(throttle4>step) { throttle4 -= step; val = throttle4; }
			mot_Run(throttle1,throttle2,throttle3,throttle4);
			char output[100];
			sprintf(output,"Throttle down: %.0f%%",val*100);
			write(newsockfd,&output,sizeof(output));
			printf("Throttle down\n");
		}
		if(c=='+' || c=='=') {
			float val;
			if(throttle1>0) { throttle1 += step; val = throttle1; }
			if(throttle2>0) { throttle2 += step; val = throttle2; }
			if(throttle3>0) { throttle3 += step; val = throttle3; }
			if(throttle4>0) { throttle4 += step; val = throttle4; }
			mot_Run(throttle1,throttle2,throttle3,throttle4);
			char output[100];
			sprintf(output,"Throttle up: %.0f%%",val*100);
			write(newsockfd,&output,sizeof(output));
			printf("Throttle up\n");
		}
		if(c=='0') {
			write(newsockfd,"Stop",4);
			printf("\rStop");
			mot_Stop();
		}
		if(c=='a') {
			write(newsockfd,"LEDs off",8);
			printf("\rLeds off");
			mot_SetLeds(MOT_LEDOFF,MOT_LEDOFF,MOT_LEDOFF,MOT_LEDOFF);
		}
		if(c=='s') {
			write(newsockfd,"LEDs green",10);
			printf("\rLeds green");
			mot_SetLeds(MOT_LEDGREEN,MOT_LEDGREEN,MOT_LEDGREEN,MOT_LEDGREEN);
		}
		if(c=='d') {
			write(newsockfd,"LEDs orange",11);
			printf("\rLeds orange");
			mot_SetLeds(MOT_LEDORANGE,MOT_LEDORANGE,MOT_LEDORANGE,MOT_LEDORANGE);
		}
		if(c=='f') {
			write(newsockfd,"LEDs red",8);
			printf("\rLeds red");
			mot_SetLeds(MOT_LEDRED,MOT_LEDRED,MOT_LEDRED,MOT_LEDRED);
		}
		if(c=='z') {
			system("rm -f front.bin");
			system("yavta -c1 --file=front.bin -f UYVY -s 1280x720 /dev/video1");
			write(newsockfd,"Front Camera Saved",18);
			printf("\rFront Camera Saved");
		}
		if(c=='p') {
			write(newsockfd,"in presentation mode",20);
			printf("\rPresentation mode");
			while(1) {
				bzero(buffer,256);
				read(newsockfd,buffer,255);
				char cc=tolower(buffer[0]);
				if(cc=='q') {
					write(newsockfd,"Exiting presentation mode...",28);
					break;
				} else {
					write(newsockfd,"Not a valid command! (q)uit",27);
				}
			}
		}
		/*if(c=='x') {
			system("rm -f bottom.bin");
			system("yavta -c1 --file=bottom.bin -f UYVY -s 320x240 /dev/video2");
			write(newsockfd,"Bottom Camera Saved",19);
			printf("\rBottom Camera Saved");
		}*/
		if(c=='c') {
			int a;
			write(newsockfd,"Flashing bottom LED",19);
			printf("\rFlashing bottom LED");
			for(a=0; a<3; a++) {
				system("gpio 181 -d lo 0");system("gpio 180 -d lo 0"); // Both LEDs off
				usleep(250000); // wait 1 second
				system("gpio 180 -d lo 1"); // Green LED on
				usleep(250000); // wait 1 second
				system("gpio 181 -d lo 1"); // Red LED on
				usleep(250000); // wait 1 second
			}
		}
		if(c=='v') {
			char tmp[100];
			vbat_read(&vbat);
			sprintf(tmp,"Voltage: %5.2fV\0",vbat.vbat);
			write(newsockfd,&tmp,strlen(tmp));
			printf("\rVoltage: %s",tmp);
		}
		
		printf("\n");
		fflush(stdout);
		close(newsockfd);
	  }

	/* Write a response to the client */
	n = write(newsockfd,"I got your message",18);
	if (n < 0)
	{
		perror("ERROR writing to socket");
		exit(1);
	}
	return 0; 
}

size_t getFilesize(const char* filename) {
	struct stat st;
	stat(filename, &st);
	return st.st_size; 
}