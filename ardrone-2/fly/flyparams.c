#include "flyparams.h"
#include <stdlib.h>
#include <stdio.h>


float getFloatParam(const char *name, float defaultValue)
{
	char *val=getenv(name);
	if(!val) return defaultValue;
	else {
		double parsedVal=strtod(val,NULL);
		printf("Param %s overwritten, new value: %lf\n",name,parsedVal);
		return parsedVal;
	}
}
