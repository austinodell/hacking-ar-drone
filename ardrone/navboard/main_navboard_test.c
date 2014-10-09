/*
    main_navboard_test.c - AR.Drone navboard demo program

    Copyright (C) 2011 Hugo Perquin - http://blog.perquin.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
    MA 02110-1301 USA.
*/
#include <stdio.h>   /* Standard input/output definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <pthread.h>
#include <ctype.h>    /* For tolower() function */
#include <math.h>

#include "../util/type.h"
#include "../util/util.h"
#include "navboard.h"

int main()
{
	int rc;
	nav_struct nav;
	
	printf("Nav board test program\r\n");

	//nav board
	printf("Init Navboard ...\r\n");
	sleep(1);
	rc = nav_Init(&nav);
	if(rc) return rc;
	printf("Init Navboard OK\r\n");
	sleep(1);

	//calibrate
	printf("Calibration ...\r\n");
	sleep(1);
	rc=nav_FlatTrim();
	sleep(1);
	if(rc) {printf("Failed: retcode=%d\r\n",rc); return rc;}
	sleep(1);
	printf("Calibration OK\r\n");
	 
	//main loop	
	while(1) { 
		//get sample
		rc = nav_GetSample(&nav);
		if(rc) {
			printf("ERROR: nav_GetSample return code=%d\n",rc); 
		}
		nav_Print(&nav);
	}
	nav_Close();
	printf("\nDone...\n");
	return 0;
}
