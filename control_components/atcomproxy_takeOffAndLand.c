/*
 * Based on project by nosaari with ARDroneTools.
 */

#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> /* close() */
#include <string.h> /* memset() */

// Set up the serial port
#define DEFAULT_SERIAL_DEVICE   "/dev/tty"

// Address of control server on drone
#define REMOTE_SERVER_ADDRESS   "192.168.1.1"

// Port of control server for AT commands
#define REMOTE_SERVER_PORT      5556

// Buffer size for AT commands
#define MAX_MESSAGE_LENGTH      100


int main(int argc, char* argv[])
{
    int flags               = 0;
    int verbose             = 0;
    int connectionSocket    = 0;
    int returnNo            = 0;    
    uint addressLength      = 0;
    
    char message[MAX_MESSAGE_LENGTH];
    char* serialDevice      = NULL;
    char* remoteIpAddress   = NULL;
    FILE* inputFile;

    struct sockaddr_in remoteAddress;
    
    serialDevice = DEFAULT_SERIAL_DEVICE;
    remoteIpAddress = REMOTE_SERVER_ADDRESS;
    
    // Create socket with UDP setting (SOCK_DGRAM)
    connectionSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (connectionSocket < 0)
    {
        fprintf(stderr, "%s > ERROR: Cannot open socket!\n", argv[0]);
        exit(1);
    }
    
    // Open serial device
    if ((inputFile = fopen(serialDevice, "r")) == 0)
    {
        fprintf(stderr, "%s > ERROR: Cannot open file %s!\n",
                argv[0],
                serialDevice);
        
        exit(1);
    }
    
    // Initialise remote server address
    memset(&remoteAddress, 0, sizeof(struct sockaddr_in));
    remoteAddress.sin_family = AF_INET;
    remoteAddress.sin_addr.s_addr = inet_addr(remoteIpAddress);
    remoteAddress.sin_port = htons(REMOTE_SERVER_PORT);
    addressLength = sizeof(remoteAddress);
    
    // Init/clear buffer
    memset(message, 0x0, MAX_MESSAGE_LENGTH);
    
    sprintf(message,"AT*REF=1,290718208\r"); // take-off
    
    // Send message to remote server
	returnNo = sendto(connectionSocket,
		message,
		strlen(message),
		flags,
		(struct sockaddr *)&remoteAddress,
		addressLength);
		
	if (returnNo < 0)
    {
    	fprintf(stderr, "%s > ERROR: Cannot send data!\n", argv[0]);
    }
    
    // Init/clear buffer
    memset(message, 0x0, MAX_MESSAGE_LENGTH);
    
    sleep(3);
    
    sprintf(message,"AT*REF=2,290717696\r"); // land
    
    // Send message to remote server
	returnNo = sendto(connectionSocket,
		message,
		strlen(message),
		flags,
		(struct sockaddr *)&remoteAddress,
		addressLength);
		
	if (returnNo < 0)
    {
    	fprintf(stderr, "%s > ERROR: Cannot send data!\n", argv[0]);
    }
    
    return 0;
}
