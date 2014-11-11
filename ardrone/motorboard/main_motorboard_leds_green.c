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
  printf("LEDs off");
	
  mot_Init();

  mot_SetLeds(MOT_LEDGREEN,MOT_LEDGREEN,MOT_LEDGREEN,MOT_LEDGREEN);

  pthread_yield();

  sleep(5);
 
  mot_Close();

  printf("\nDone...\n");
  return 0;
}
