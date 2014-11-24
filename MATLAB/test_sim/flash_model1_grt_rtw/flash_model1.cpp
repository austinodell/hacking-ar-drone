/*
 * flash_model1.cpp
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
#include "flash_model1.h"
#include "flash_model1_private.h"
#include "flash_model1_dt.h"

/* Block states (auto storage) */
DW_flash_model1_T flash_model1_DW;

/* Real-time model */
RT_MODEL_flash_model1_T flash_model1_M_;
RT_MODEL_flash_model1_T *const flash_model1_M = &flash_model1_M_;

/* Model step function */
void flash_model1_step(void)
{
  /* MATLAB Function: '<Root>/centralLED1' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   *  Constant: '<Root>/Constant3'
   *  Constant: '<Root>/Constant4'
   *  Constant: '<Root>/Constant5'
   */
  /* MATLAB Function 'centralLED1': '<S1>:1' */
  if (!flash_model1_DW.flag_not_empty) {
    /* '<S1>:1:19' */
    mot_Init();
    flash_model1_DW.flag_not_empty = true;
  }

  /* '<S1>:1:24' */
  mot_Run(flash_model1_P.Constant1_Value, flash_model1_P.Constant2_Value,
          flash_model1_P.Constant3_Value, flash_model1_P.Constant4_Value);
  mot_SetLeds(flash_model1_P.Constant5_Value, flash_model1_P.Constant5_Value,
              flash_model1_P.Constant5_Value, flash_model1_P.Constant5_Value);

  /* End of MATLAB Function: '<Root>/centralLED1' */

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.1s, 0.0s] */
    rtExtModeUpload(0, flash_model1_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.1s, 0.0s] */
    if ((rtmGetTFinal(flash_model1_M)!=-1) &&
        !((rtmGetTFinal(flash_model1_M)-flash_model1_M->Timing.taskTime0) >
          flash_model1_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(flash_model1_M, "Simulation finished");
    }

    if (rtmGetStopRequested(flash_model1_M)) {
      rtmSetErrorStatus(flash_model1_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++flash_model1_M->Timing.clockTick0)) {
    ++flash_model1_M->Timing.clockTickH0;
  }

  flash_model1_M->Timing.taskTime0 = flash_model1_M->Timing.clockTick0 *
    flash_model1_M->Timing.stepSize0 + flash_model1_M->Timing.clockTickH0 *
    flash_model1_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void flash_model1_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)flash_model1_M, 0,
                sizeof(RT_MODEL_flash_model1_T));
  rtmSetTFinal(flash_model1_M, 10.0);
  flash_model1_M->Timing.stepSize0 = 0.1;

  /* External mode info */
  flash_model1_M->Sizes.checksums[0] = (4244856469U);
  flash_model1_M->Sizes.checksums[1] = (429193881U);
  flash_model1_M->Sizes.checksums[2] = (1831289807U);
  flash_model1_M->Sizes.checksums[3] = (80125936U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    flash_model1_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(flash_model1_M->extModeInfo,
      &flash_model1_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(flash_model1_M->extModeInfo,
                        flash_model1_M->Sizes.checksums);
    rteiSetTPtr(flash_model1_M->extModeInfo, rtmGetTPtr(flash_model1_M));
  }

  /* states (dwork) */
  (void) memset((void *)&flash_model1_DW, 0,
                sizeof(DW_flash_model1_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    flash_model1_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* InitializeConditions for MATLAB Function: '<Root>/centralLED1' */
  flash_model1_DW.flag_not_empty = false;
}

/* Model terminate function */
void flash_model1_terminate(void)
{
  /* (no terminate code required) */
}
