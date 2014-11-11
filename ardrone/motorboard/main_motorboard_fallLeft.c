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
  printf("Motors 2 and 3 set to 60% and Motors 1 and 4 set to 40% for 5 seconds.\r\n");
	
  mot_Init();
  
  float throttle1 = .40;
  float throttle2 = .60;
  float throttle3 = .60;
  float throttle4 = .40;

  mot_Run(throttle1,throttle2,throttle3,throttle4);

  int count = 5;
  while(count>0) {
	printf("%i...",count--);
	fflush(stdout);
	sleep(1);
  }  

  printf("%i...Done!\n",count);
 
  mot_Close();

  printf("\nDone...\n");
  return 0;
}
