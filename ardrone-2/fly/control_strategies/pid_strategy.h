#ifndef _PID_STRATEGY
#define _PID_STRATEGY

#include "../controls.h"
#include "../../attitude/attitude.h"

/** the pid strategy tries to stabilize the drone using three independent control loops featuring one/two pid controllers each
* it is tunable using external paramters
* for details, see source code
*/


void pid_strategy_init();
void pid_strategy_calculateMotorSpeeds(struct drone_state_struct *cs, float motorOut[4]);

/** puts interesting logging information into buffer, returning the number of bytes written, format is csv */
unsigned int pid_strategy_getLogText(char *buf,unsigned int maxLen);
/* put a list of headings for the log columns into buffer, returning the number of bytes written, format is csv */
unsigned int pid_strategy_getLogHeadings(char *buf, unsigned int maxLen);

#endif
