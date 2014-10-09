
#include "lowpass.h"


void lowpass_init(struct lowpass_struct *lp)
{
  int i;
  for(i=0;i<FIR_LENGTH-1;i++) lp->lastValues[i]=0;

}

float lowpass_update(struct lowpass_struct *lp, float newVal)
{
  /**  @todo optimize by using a ring buffer */
  
  float result=lp->lastValues[0]*0.22295145+
               lp->lastValues[1]*0.27704855+
               lp->lastValues[2]*0.27704855+
               newVal*0.22295145;
               
  lp->lastValues[0]=lp->lastValues[1];
  lp->lastValues[1]=lp->lastValues[2];
  lp->lastValues[2]=newVal;
  
  return result;
}
  