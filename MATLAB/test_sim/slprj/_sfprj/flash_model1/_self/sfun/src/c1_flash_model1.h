#ifndef __c1_flash_model1_h__
#define __c1_flash_model1_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_flash_model1InstanceStruct
#define typedef_SFc1_flash_model1InstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_isStable;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_flash_model1;
  real_T *c1_motor1;
  real_T *c1_motor2;
  real_T *c1_motor3;
  real_T *c1_motor4;
  real_T *c1_led;
} SFc1_flash_model1InstanceStruct;

#endif                                 /*typedef_SFc1_flash_model1InstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_flash_model1_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_flash_model1_get_check_sum(mxArray *plhs[]);
extern void c1_flash_model1_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
