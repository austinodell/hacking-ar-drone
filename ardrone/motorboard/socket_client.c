#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>

#define FRONTIMGSIZE 1843200
#define INPUTSIZE 2500

void readIn(char input[INPUTSIZE]);
size_t getFilesize(const char* filename);

int main(int argc, char *argv[])
{
	char input[INPUTSIZE];
	
	while(strcmp(".quit",input) != 0 && strcmp("q",input) != 0)
	{
		int sockfd = 0, n = 0;
		char recvBuff[1024];
		char buffer[256];
		struct sockaddr_in serv_addr; 

		if(argc != 3)
		{
			printf("\n Usage: %s <ip of server> <port> \n",argv[0]);
			return 1;
		}

		memset(recvBuff, '0',sizeof(recvBuff));
		if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			printf("\n Error : Could not create socket \n");
			return 1;
		}

		memset(&serv_addr, '0', sizeof(serv_addr)); 

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(atoi(argv[2])); 

		if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
		{
			printf("\n inet_pton error occured\n");
			return 1;
		}
	
		if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		{
		   printf("\n Error : Connect Failed \n");
		   return 1;
		}
		
		printf ("Message for server: ");
		readIn(input);
		
		write(sockfd,&input,strlen(input));
		
		bzero(buffer,256);
		read(sockfd,buffer,255);
		printf("%s\n",buffer);
		
		if(strcmp(input,"z") == 0) {
			system("curl -O ftp://192.168.1.1/bin/motorboard/front.bin");
			system("curl -X 'DELE front.bin' ftp://192.168.1.1/bin/motorboard/");
			system("curl -T front.bin -o front.bmp http://api.odell.cc/uyvy.php");
			system("rm front.bin ; open front.bmp");
		}/* else if(strcmp(input,"x") == 0) {
			system("curl -O ftp://192.168.1.1/bin/motorboard/bottom.bin");
			system("curl -T bottom.bin -o bottom.bmp http://api.odell.cc/uyvy.php");
		}*/
		
		shutdown(sockfd,SHUT_RDWR);
		close(sockfd);
	}

	return 0;
}

void readIn(char input[INPUTSIZE])
{
	int a = 0;
	
	while(a<INPUTSIZE)
	{
		input[a++] = fgetc(stdin);
		
		if(a>1 && (input[a-1] == '\n'))
		{
			input[a-1]='\0';
			break;
		}
	}
}

size_t getFilesize(const char* filename) {
	struct stat st;
	stat(filename, &st);
	return st.st_size; 
}