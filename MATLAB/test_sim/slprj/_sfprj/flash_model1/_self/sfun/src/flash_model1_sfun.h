#ifndef __flash_model1_sfun_h__
#define __flash_model1_sfun_h__

/* Include files */
#define S_FUNCTION_NAME                sf_sfun
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "sf_runtime/sf_runtime_errors.h"
#include "rtwtypes.h"
#include "simtarget/slClientServerAPIBridge.h"
#include "multiword_types.h"
#include "sf_runtime/sfcdebug.h"
#define rtInf                          (mxGetInf())
#define rtMinusInf                     (-(mxGetInf()))
#define rtNaN                          (mxGetNaN())
#define rtIsNaN(X)                     ((int)mxIsNaN(X))
#define rtIsInf(X)                     ((int)mxIsInf(X))

struct SfDebugInstanceStruct;
extern struct SfDebugInstanceStruct* sfGlobalDebugInstanceStruct;

/* Auxiliary Header Files */
#include "/Users/aodell/Documents/MATLAB/test_sim/mycfiles/gpio.h"
#include "/Users/aodell/Documents/MATLAB/test_sim/mycfiles/mot.h"
#include "/Users/aodell/Documents/MATLAB/test_sim/mycfiles/motorboard.h"
#include "/Users/aodell/Documents/MATLAB/test_sim/mycfiles/util.h"

/* Custom Code from Simulation Target dialog*/
#include "/Users/aodell/Google Drive/Documents/MATLAB/test_sim/mycfiles/motorboard.h"
#include "/Users/aodell/Google Drive/Documents/MATLAB/test_sim/mycfiles/mot.h"
#include "/Users/aodell/Google Drive/Documents/MATLAB/test_sim/mycfiles/util.h"
#include "/Users/aodell/Google Drive/Documents/MATLAB/test_sim/mycfiles/gpio.h"
#include "/Users/aodell/Google Drive/Documents/MATLAB/test_sim/mycfiles/type.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */
extern uint32_T _flash_model1MachineNumber_;

/* Variable Definitions */

/* Function Declarations */
extern void flash_model1_initializer(void);
extern void flash_model1_terminator(void);

/* Function Definitions */

/* We load infoStruct for rtw_optimation_info on demand in mdlSetWorkWidths and
   free it immediately in mdlStart. Given that this is machine-wide as
   opposed to chart specific, we use NULL check to make sure it gets loaded
   and unloaded once per machine even though the  methods mdlSetWorkWidths/mdlStart
   are chart/instance specific. The following methods abstract this out. */
extern mxArray* load_flash_model1_optimization_info(void);
extern void unload_flash_model1_optimization_info(void);

#endif
