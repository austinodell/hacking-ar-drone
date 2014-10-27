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
  printf("Right motors set to 60% and left motors set to 40%\r\n");
	
  mot_Init();
  
  float throttle1 = .40;
  float throttle2 = .60;
  float throttle3 = .60;
  float throttle4 = .40;

  mot_Run(throttle1,throttle2,throttle3,throttle4);

  //yield to other threads
  pthread_yield();

  sleep(5);
 
  mot_Close();

  printf("\nDone...\n");
  return 0;
}
