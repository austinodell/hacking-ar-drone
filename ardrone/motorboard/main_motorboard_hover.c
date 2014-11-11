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
  printf("All motors at 35% for 5 seconds.\r\n");
	
  mot_Init();
  
  float throttle = .35;

  mot_Run(throttle,throttle,throttle,throttle);

  sleep(5);
 
  mot_Close();

  printf("\nDone...\n");
  return 0;
}
