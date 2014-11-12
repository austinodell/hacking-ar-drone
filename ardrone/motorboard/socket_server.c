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
#include <sys/uio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

size_t getFilesize(const char* filename);

int main( int argc, char *argv[] )
{
	int sockfd, newsockfd, portno;
	unsigned int clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int  n;
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
		
		char c=tolower(buffer[0]);
		if(c=='z') {
			write(newsockfd,"Front Camera Saved",18);
			printf("\rFront Camera Saved");
			//system("rm -f front.bin");
			//system("yavta -c1 --file=front.bin -f UYVY -s 1280x720 /dev/video1");
			
			char imgBuffer[1843200];
			bzero(imgBuffer,1843200);
			
			int camera = open("front.bin",O_RDONLY);
			read(camera,imgBuffer,1843200);
			close(camera);
			write(newsockfd,imgBuffer,1843200);
			printf("\rFront Camera Sent");
		}
		
		printf("\n");
		fflush(stdout);
		close(newsockfd);
	  }
	return 0; 
}

size_t getFilesize(const char* filename) {
	struct stat st;
	stat(filename, &st);
	return st.st_size; 
}