#include <stdio.h>   /* Standard input/output definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <pthread.h>
#include <ctype.h>    /* For tolower() function */
#include <math.h>

#include "../util/type.h"
#include "../util/util.h"
#include "mot.h"


int main()
{
  printf("All motors at 10% for 5 seconds.\r\n");
	
  mot_Init();
  
  float throttle1 = .1;
  float throttle2 = .1;
  float throttle3 = .1;
  float throttle4 = .1;

  mot_Run(throttle1,throttle2,throttle3,throttle4);

  int count = 5;
  while(count>0) {
	printf("%i...",count--);
	fflush(stdout);
	sleep(1);
  }  

  printf("%i...Done!\n",count);
 
  mot_Close();

  return 0;
}
