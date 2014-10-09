/*
    main_loopback_test
*/

#define TEST_UART "/dev/ttyO3"

#include <fcntl.h>
#include "../util/util.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
              

int openSerialPort() {
	//open mot port
	int fd = open(TEST_UART, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	{
		perror("open_port: Unable to open "TEST_UART" - ");
		return 201;
	} 
	fcntl(fd, F_SETFL, 0); //read calls are non blocking

	//set port options
	struct termios options;
	//Get the current options for the port
	tcgetattr(fd, &options);
	//Set the baud rates to 115200
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);
/*Control Options  (options.c_cflag)
B0 0 baud (drop DTR) 
B50 50 baud 
B75 75 baud 
B110 110 baud 
B134 134.5 baud 
B150 150 baud 
B200 200 baud 
B300 300 baud 
B600 600 baud 
B1200 1200 baud 
B1800 1800 baud 
B2400 2400 baud 
B4800 4800 baud 
B9600 9600 baud 
B19200 19200 baud 
B38400 38400 baud 
B57600 57,600 baud 
B76800 76,800 baud 
B115200 115,200 baud 
EXTA External rate clock 
EXTB External rate clock 
CSIZE Bit mask for data bits 
CS5 5 data bits 
CS6 6 data bits 
CS7 7 data bits 
CS8 8 data bits 
CSTOPB 2 stop bits (1 otherwise) 
CREAD Enable receiver 
PARENB Enable parity bit 
PARODD Use odd parity instead of even 
HUPCL Hangup (drop DTR) on last close 
CLOCAL Local line - do not change "owner" of port 
LOBLK Block job control output 
CNEW_RTSCTS 
CRTSCTS Enable hardware flow control (not supported on all platforms) 
*/
	options.c_cflag |= (CLOCAL | CREAD); //Enable the receiver and set local mode
/*Input Options (options.c_iflag)
INPCK Enable parity check 
IGNPAR Ignore parity errors 
PARMRK Mark parity errors 
ISTRIP Strip parity bits 
IXON Enable software flow control (outgoing) 
IXOFF Enable software flow control (incoming) 
IXANY Allow any character to start flow again 
IGNBRK Ignore break condition 
BRKINT Send a SIGINT when a break condition is detected 
INLCR Map NL to CR 
IGNCR Ignore CR 
ICRNL Map CR to NL 
IUCLC Map uppercase to lowercase 
IMAXBEL Echo BEL on input line too long 
*/
	options.c_iflag = 0; //clear input options
/*Local Options (options.c_lflag)
ISIG Enable SIGINTR, SIGSUSP, SIGDSUSP, and SIGQUIT signals 
ICANON Enable canonical input (else raw) 
XCASE Map uppercase \lowercase (obsolete) 
ECHO Enable echoing of input characters 
ECHOE Echo erase character as BS-SP-BS 
ECHOK Echo NL after kill character 
ECHONL Echo NL 
NOFLSH Disable flushing of input buffers after interrupt or quit characters 
IEXTEN Enable extended functions 
ECHOCTL Echo control characters as ^char and delete as ~? 
ECHOPRT Echo erased character as character erased 
ECHOKE BS-SP-BS entire line on line kill 
FLUSHO Output being flushed 
PENDIN Retype pending input at next read or input char 
TOSTOP Send SIGTTOU for background output 
*/
	options.c_lflag=0; //clear local options
/*Output Options (options.c_oflag)
OPOST Postprocess output (not set = raw output) 
OLCUC Map lowercase to uppercase 
ONLCR Map NL to CR-NL 
OCRNL Map CR to NL 
NOCR No CR output at column 0 
ONLRET NL performs CR function 
OFILL Use fill characters for delay 
OFDEL Fill character is DEL 
NLDLY Mask for delay time needed between lines 
NL0 No delay for NLs 
NL1 Delay further output after newline for 100 milliseconds 
CRDLY Mask for delay time needed to return carriage to left column 
CR0 No delay for CRs 
CR1 Delay after CRs depending on current column position 
CR2 Delay 100 milliseconds after sending CRs 
CR3 Delay 150 milliseconds after sending CRs 
TABDLY Mask for delay time needed after TABs 
TAB0 No delay for TABs 
TAB1 Delay after TABs depending on current column position 
TAB2 Delay 100 milliseconds after sending TABs 
TAB3 Expand TAB characters to spaces 
BSDLY Mask for delay time needed after BSs 
BS0 No delay for BSs 
BS1 Delay 50 milliseconds after sending BSs 
VTDLY Mask for delay time needed after VTs 
VT0 No delay for VTs 
VT1 Delay 2 seconds after sending VTs 
FFDLY Mask for delay time needed after FFs 
FF0 No delay for FFs 
FF1 Delay 2 seconds after sending FFs 
*/
	options.c_oflag &= ~OPOST; //clear output options (raw output)
	//Set the new options for the port
	tcsetattr(fd, TCSANOW, &options);
	
	return fd;
}


int safe_read(int fd, void *target, int bytesToRead)
{
    int bytesRead=0;
    char * targetC=(char *)target;
    while (bytesRead !=bytesToRead) {
        int bytesRemaining=bytesToRead-bytesRead;
        int n=read(fd,targetC+bytesRead,bytesRemaining);
        if(n < 0) return n;
        bytesRead+=n;
    }
    return bytesRead;
}


int testLoopback(int fd,char testVal)
{
  double t0=util_timestamp();

  int rept=50;
  
  for(int i=0;i<rept;i++) write(fd,&testVal,1);
  double t1=util_timestamp();
  
  char resultData;
  
  for(int i=0;i<rept;i++) {
    int readOk=safe_read(fd,&resultData,1);
    if(readOk!=1) { printf("Unable to read byte\n"); return 2; }
    if(resultData!=testVal) { printf("Read data inconsistent\n"); return 1; }
  }
  
  double t2=util_timestamp();
  
  
  double dt1=t1-t0;
  double dt2=t2-t1;
  double dt3=t2-t0;
  
  printf("DT: %2f ms  %2f ms VAL %d\n",dt1*1000,dt2*1000,resultData);
  return 0;


}


int main()
{
  int fd=openSerialPort();
  

  for(int i=0;i<100;i++) testLoopback(fd,i);
  
  
  close(fd);


  return 0;
}
