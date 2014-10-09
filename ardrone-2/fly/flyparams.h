#ifndef _FLYPARAMS_H
#define _FLYPARAMS_H

/** parameter handling code
 * the following functions allow the retrieval of parameters from an external source without recompilation
 * currently this external source are environment variables
*/


/** returns the value of the parameter identified by name or default value if parameter not present
* @param name the name of the parameter to request
* @param defaultValue the value to returns if the parameter is not defined
*/
float getFloatParam(char *const name, float defaultValue);

#endif
