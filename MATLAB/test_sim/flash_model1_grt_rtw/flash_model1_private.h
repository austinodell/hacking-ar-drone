/*
 * flash_model1_private.h
 *
 * Code generation for model "flash_model1".
 *
 * Model version              : 1.38
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C++ source code generated on : Sat Nov 22 21:27:00 2014
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_flash_model1_private_h_
#define RTW_HEADER_flash_model1_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               (&(rtm)->Timing.taskTime0)
#endif
#endif                                 /* RTW_HEADER_flash_model1_private_h_ */
