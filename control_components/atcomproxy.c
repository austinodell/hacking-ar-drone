/*
 *  ATComSerialProxyServer
 *  v0.2.2
 *  ARDroneTools
 *
 *  Created by nosaari on 25.02.11.
 *
 
 Very basic proxy server that reads any lines in given tty device and sends it
 via UDP to given server.
 Any line thats not starting with 'AT' is considered as debug output and will 
 be ignored!
 
 # Options:
 
 -v
 v[erbose] - Enables output of received strings, for performance reasons only use
 while debugging!
 
 -d DEVICE
 d[evice] - Set device to read values from, eg. '/dev/ttyPA0'. If none is given
 the default (hardcoded) device will be used (can be set below, see SETUP!).
 
 -i IP.ADDRESS
 i[p] - Sets IP address commands are sent to, eg. '192.168.1.2'. If none is given
 the default (hardcoded) ip of the drone (192.168.1.1) will be used (can be set 
 below, see SETUP!).

 
 Based on server code from
 http://www.gamedev.net/topic/310343-udp-client-server-echo-example/
 
 For detailed infos read
 http://www.linuxhowtos.org/C_C++/socket.htm
 
 *
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


// SETUP

// The default serial device to use without options.
// Eg. /dev/ttyPA0 for regular serial port or /dev/ttyUSB0 for USB connection.
#define DEFAULT_SERIAL_DEVICE   "/dev/tty"


// OTHER SETTINGS

// Address of control server on drone, should be 192.168.1.1
// Test the server locally by setting address to "127.0.0.1" and 
// typing "nc -l -u 127.0.0.1 5556" in a terminal window!
#define REMOTE_SERVER_ADDRESS   "192.168.1.1"
// Port of control server for AT commands, leave at 5556
#define REMOTE_SERVER_PORT      5556
// Buffer size for AT comands, increase if needed
#define MAX_MESSAGE_LENGTH      100


int main(int argc, char* argv[])
{
    int flags               = 0;    // Send flags, 0 should be good
    int verbose             = 1;
    int connectionSocket    = 0;
    int returnNo            = 0;    
    uint addressLength      = 0;
    
    char message[MAX_MESSAGE_LENGTH];
    char* serialDevice      = NULL;
    char* remoteIpAddress   = NULL;
    FILE* inputFile;

    struct sockaddr_in remoteAddress;
    
    // Use default device if no device was given
    //if (serialDevice == NULL)
    //{
        serialDevice = DEFAULT_SERIAL_DEVICE;
    //}
    
    // Use default ip address if no ip was given
    //if (remoteIpAddress == NULL)
    //{
        remoteIpAddress = REMOTE_SERVER_ADDRESS;
    //}
    
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
    
    // If we reach this point we are up and running!
    printf("%s > Proxy Ready: Waiting for data in %s to send to %s:%u!\n",
           argv[0],
           serialDevice,
           inet_ntoa(remoteAddress.sin_addr),
           ntohs(remoteAddress.sin_port));
    
    // Server infinite loop, use ctrl+c to kill proc
    while (1)
    {
        // Init/clear buffer
        memset(message, 0x0, MAX_MESSAGE_LENGTH);
        
        // Read line from serial
        returnNo = fscanf(inputFile, "%s", message);
        if (returnNo < 0)
        {
            fprintf(stderr, "%s > ERROR: Cannot read data from device!\n", argv[0]);
            
            continue;
        }
        
        if (verbose)
        {
            // Print received message, only use for debugging!
            printf("%s > %s!\n", argv[0], message);
        }
        
        // CONVENTION: Only send messages that begin with the chars 'AT'!
        // Every AT command must begin with these, everything else is ignored!
        if (message[0] == 'A' && message[1] == 'T')
        {
            // Add line feed to the end
            strncat(message, "\r", 2);
            
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
        }
    }
    // End of server infinite loop
    
    return 0;
}
