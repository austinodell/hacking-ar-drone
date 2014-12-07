#include <stdio.h>   /* Standard input/output definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <pthread.h>
#include <ctype.h>    /* For tolower() function */
#include <math.h>

#include "../util/type.h"
#include "../util/util.h"
#include "navboard.h"

int rc;
struct nav_struct nav;

int setup()
{
	rc = nav_Init(&nav);
	if(rc) { return rc; }

	rc=nav_FlatTrim();
	if(rc) { return rc;}
	
	return 0;
}

int close() {
	nav_Close();
	
	return 0;
}

int getSample() {
	rc = nav_GetSample(&nav);
	nav_Print(&nav);
	
	return 0;
}

int main()
{
	setup();
	getSample();
	close();
	
	return 0;
}
