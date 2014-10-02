/*
 * SPtest.c
 *
 * Code generation for model "SPtest".
 *
 * Model version              : 1.253
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Thu Oct 02 14:52:00 2014
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit Embedded Processor
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "SPtest.h"
#include "SPtest_private.h"

/* External outputs (root outports fed by signals with auto storage) */
ExtY_SPtest_T SPtest_Y;

/* Real-time model */
RT_MODEL_SPtest_T SPtest_M_;
RT_MODEL_SPtest_T *const SPtest_M = &SPtest_M_;

/* Model step function */
void SPtest_step(void)
{
  /* Matfile logging */
  rt_UpdateTXYLogVars(SPtest_M->rtwLogInfo, (&SPtest_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.1s, 0.0s] */
    if ((rtmGetTFinal(SPtest_M)!=-1) &&
        !((rtmGetTFinal(SPtest_M)-SPtest_M->Timing.taskTime0) >
          SPtest_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(SPtest_M, "Simulation finished");
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
  if (!(++SPtest_M->Timing.clockTick0)) {
    ++SPtest_M->Timing.clockTickH0;
  }

  SPtest_M->Timing.taskTime0 = SPtest_M->Timing.clockTick0 *
    SPtest_M->Timing.stepSize0 + SPtest_M->Timing.clockTickH0 *
    SPtest_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void SPtest_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)SPtest_M, 0,
                sizeof(RT_MODEL_SPtest_T));
  rtmSetTFinal(SPtest_M, 5.0);
  SPtest_M->Timing.stepSize0 = 0.1;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    SPtest_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(SPtest_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(SPtest_M->rtwLogInfo, (NULL));
    rtliSetLogT(SPtest_M->rtwLogInfo, "");
    rtliSetLogX(SPtest_M->rtwLogInfo, "");
    rtliSetLogXFinal(SPtest_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(SPtest_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(SPtest_M->rtwLogInfo, 2);
    rtliSetLogMaxRows(SPtest_M->rtwLogInfo, 0);
    rtliSetLogDecimation(SPtest_M->rtwLogInfo, 1);
    rtliSetLogY(SPtest_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(SPtest_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(SPtest_M->rtwLogInfo, (NULL));
  }

  /* external outputs */
  SPtest_Y.Out1 = 0.0;

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(SPtest_M->rtwLogInfo, 0.0, rtmGetTFinal
    (SPtest_M), SPtest_M->Timing.stepSize0, (&rtmGetErrorStatus(SPtest_M)));

  /* ConstCode for Outport: '<Root>/Out1' */
  SPtest_Y.Out1 = 2.0;
}

/* Model terminate function */
void SPtest_terminate(void)
{
  /* (no terminate code required) */
}
