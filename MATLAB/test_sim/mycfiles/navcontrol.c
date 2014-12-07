#include <stdio.h>   /* Standard input/output definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <pthread.h>
#include <ctype.h>    /* For tolower() function */
#include <math.h>

#include "/Users/aodell/Google Drive/Documents/MATLAB/test_sim/mycfiles/navcontrol.h"
#include "type.h"
#include "util.h"
#include "navboard.h"

int rc;
static struct nav_struct nav;

int navSetup()
{
	rc = nav_Init(&nav);
	if(rc) { return rc; }

	rc=nav_FlatTrim();
	if(rc) { return rc;}
	
	return 0;
}

int navClose() {
	nav_Close();
	
	return 0;
}

int navGetSample() {
	rc = nav_GetSample(&nav);
	nav_Print(&nav);
	
	return 0;
}

float navGetGX() {
	return nav_Get_gx(&nav);
}

float navGetGY() {
	return nav_Get_gy(&nav);
}

float navGetGZ() {
	return nav_Get_gz(&nav);
}

float navGetAX() {
	return nav_Get_ax(&nav);
}

float navGetAY() {
	return nav_Get_ay(&nav);
}

float navGetAZ() {
	return nav_Get_az(&nav);
}

float navGetMX() {
	return nav_Get_mx(&nav);
}

float navGetMY() {
	return nav_Get_my(&nav);
}

float navGetMZ() {
	return nav_Get_mz(&nav);
}

float navGetHeight() {
	return nav_Get_height(&nav);
}