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
	        
			sleep(5);
			char imgBuffer[1843200];
			bzero(imgBuffer,1843200);
			
			int offset = 0;
			int fsize = getFilesize("front.bin");
			int camera = open("front.bin",O_RDONLY);
			
			//recv(sockfd, imgBuffer, 1843200, 0);
			//read(sockfd,imgBuffer,1843200);
			FILE * imgFile;
			imgFile = fopen ("front_rec.bin", "w");
			fwrite(imgBuffer, sizeof(char), 1843200, imgFile);
			
			sendfile(imgFile, camera, &offset, fsize);
			
			fclose (imgFile);
			
			
			/*FILE *received_file;
			char imgBuffer[256];
			int file_size;
			int remain_data = 0;
			ssize_t len;
			
			/* Receiving file size 
			recv(sockfd, imgBuffer, 256, 0);
			file_size = atoi(imgBuffer);
			fprintf(stdout, "\nFile size : %d\n", file_size);

			received_file = fopen("front.bin", "w");
			if (received_file == NULL)
			{
				fprintf(stderr, "Failed to open file foo --> %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}

			remain_data = file_size;

			while (((len = recv(sockfd, imgBuffer, BUFSIZ, 0)) > 0) && (remain_data > 0))
			{
				fwrite(imgBuffer, sizeof(char), len, received_file);
				remain_data -= len;
				fprintf(stdout, "Receive %zd bytes and we hope :- %d bytes\n", len, remain_data);
			}
			fclose(received_file);*/
		}
		
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