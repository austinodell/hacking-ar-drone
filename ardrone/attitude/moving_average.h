#ifndef MOVING_AVERAGE_H
#define MOVING_AVERAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#define MOVING_AVERAGE_VALUES 1

struct moving_average_struct {
  float values[MOVING_AVERAGE_VALUES];
  int current;
};

void moving_average_init(struct moving_average_struct* mavg);
float moving_average_update(struct moving_average_struct* mavg, float value);

#ifdef __cplusplus
}
#endif
#endif
