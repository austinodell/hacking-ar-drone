#include "moving_average.h"

void moving_average_init(struct moving_average_struct* mavg)
{
  int i;
  for(i = 0;i < MOVING_AVERAGE_VALUES; ++i)
  {
    mavg->values[i] = 0;
  }
  mavg->current = 0;
}

float moving_average_update(struct moving_average_struct* mavg, float value)
{
  int i = 0;
  float result = 0;
  ++mavg->current;
  mavg->current %= MOVING_AVERAGE_VALUES;
  mavg->values[mavg->current] = value;
  for(i = 0;i < MOVING_AVERAGE_VALUES; ++i)
  {
    result+=mavg->values[i];
  }
  return result/MOVING_AVERAGE_VALUES;
}
