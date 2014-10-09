
#include <stdio.h>
#include "lowpass.h"



int main(int argc, char *argv[])
{
  struct lowpass_struct lp;
  
  lowpass_init(&lp);
  
  int i;
  for(i=0; i<15;i++) {
    float val=i/10.0;
    if(val>1.0) val=1.0;
    float lpv=lowpass_update(&lp,val);
    printf("%2d: %4.3f => %4.3f\n",i,val, lpv);
  }
  return 0;
}