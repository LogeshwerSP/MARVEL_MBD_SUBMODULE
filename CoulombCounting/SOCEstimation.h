/*
 * SOCEstimation.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "SOCEstimation".
 *
 * Model version              : 7.214
 * Simulink Coder version : 24.1 (R2024a) 19-Nov-2023
 * C source code generated on : Wed Apr 16 22:59:08 2025
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objective: Execution efficiency
 * Validation result: All passed
 */

#ifndef SOCEstimation_h_
#define SOCEstimation_h_
#ifndef SOCEstimation_COMMON_INCLUDES_
#define SOCEstimation_COMMON_INCLUDES_
#include <stdio.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* SOCEstimation_COMMON_INCLUDES_ */

#include "SOCEstimation_types.h"
#include "SOC_ReadFromEEPROM.h"
#include <math.h>
#include <stddef.h>
#include <string.h>
#include "zero_crossing_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Switch1;                      /* '<S19>/Switch1' */
  real_T SoCEst;                       /* '<S6>/SOC_Estimator' */
  real32_T DataTypeConversion;         /* '<S20>/Data Type Conversion' */
  real32_T ModIntegratedCurrent;       /* '<S8>/Modulus IntegCurrent' */
  real32_T IntegratedCurrent;          /* '<S8>/IntegCurrent' */
  int32_T TotalCapacityRemains_mAh;    /* '<S6>/SOC_Estimator' */
  int32_T Initial_Capacity_mAh;        /* '<S6>/SOC_Estimator' */
  boolean_T calcSoH2;                  /* '<S6>/SOC_Estimator' */
  B_SOC_ReadFromEEPROM_SOCEstim_T sf_SOC_ReadFromEEPROM;/* '<S1>/SOC_ReadFromEEPROM' */
} B_SOCEstimation_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T x;                            /* '<S6>/SOC_Estimator' */
  real_T EKF_P;                        /* '<S6>/SOC_Estimator' */
  real_T H_prev;                       /* '<S6>/SOC_Estimator' */
  real_T filteredVoltage;              /* '<S6>/SOC_Estimator' */
  real32_T Delay2_DSTATE;              /* '<S1>/Delay2' */
  int32_T Delay_DSTATE;                /* '<S1>/Delay' */
  int32_T Delay1_DSTATE;               /* '<S7>/Delay1' */
  int32_T Delay_DSTATE_i;              /* '<S7>/Delay' */
  int32_T Delay1_DSTATE_m;             /* '<S2>/Delay1' */
  CCState UnitDelay_DSTATE;            /* '<S2>/Unit Delay' */
  int32_T initialSoC;                  /* '<S6>/SOC_Estimator' */
  uint32_T temporalCounter_i1;         /* '<S6>/SOC_Estimator' */
  uint32_T durationCounter_1;          /* '<S6>/SOC_Estimator' */
  uint32_T durationCounter_2;          /* '<S6>/SOC_Estimator' */
  uint32_T durationCounter_1_l;        /* '<S6>/SOC_Estimator' */
  uint32_T durationCounter_3;          /* '<S6>/SOC_Estimator' */
  uint8_T is_active_c20_SOCEstimation; /* '<S8>/Modulus IntegCurrent' */
  uint8_T is_active_c42_SOCEstimation; /* '<S8>/IntegCurrent' */
  uint8_T is_c42_SOCEstimation;        /* '<S8>/IntegCurrent' */
  uint8_T is_active_c15_SOCEstimation; /* '<S6>/SOC_Estimator' */
  uint8_T is_c15_SOCEstimation;        /* '<S6>/SOC_Estimator' */
  boolean_T resetEKF;                  /* '<S6>/SOC_Estimator' */
} DW_SOCEstimation_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState SoH1calculation_Trig_ZCE; /* '<S17>/SoH1 calculation' */
  ZCSigState SoHcalculation_Trig_ZCE;  /* '<S17>/SoH calculation' */
} PrevZCX_SOCEstimation_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  DataPipelineBus DataPipeline;        /* '<Root>/DataPipeline' */
  int32_T Current_mA;                  /* '<Root>/Current_mA' */
  EKF_InputsBus EKF_Inputs;            /* '<Root>/EKF_Inputs' */
  CC_InputsBus CC_Inputs;              /* '<Root>/CC_Inputs' */
  real_T looptimeSoC; /* Added variable */
}ExtU_SOCEstimation_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  CC_OutputsBus CC_Outputs;            /* '<Root>/CC_Outputs' */
} ExtY_SOCEstimation_T;

/* Real-time Model Data Structure */
struct tag_RTM_SOCEstimation_T {
  const char_T *errorStatus;
};

/* Block signals (default storage) */
extern B_SOCEstimation_T SOCEstimation_B;

/* Block states (default storage) */
extern DW_SOCEstimation_T SOCEstimation_DW;

/* Zero-crossing (trigger) state */
extern PrevZCX_SOCEstimation_T SOCEstimation_PrevZCX;

/* External inputs (root inport signals with default storage) */
extern ExtU_SOCEstimation_T SOCEstimation_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_SOCEstimation_T SOCEstimation_Y;

/* External data declarations for dependent source files */
extern const CC_OutputsBus SOCEstimation_rtZCC_OutputsBus;/* CC_OutputsBus ground */

/* Model entry point functions */
extern void SOCEstimation_initialize(void);
extern void SOCEstimation_step(void);
extern void SOCEstimation_terminate(void);

/* Real-time Model object */
extern RT_MODEL_SOCEstimation_T *const SOCEstimation_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Display' : Unused code path elimination
 * Block '<S1>/Display1' : Unused code path elimination
 * Block '<S1>/Display2' : Unused code path elimination
 * Block '<S1>/Display3' : Unused code path elimination
 * Block '<S1>/Display5' : Unused code path elimination
 * Block '<S1>/Display6' : Unused code path elimination
 * Block '<S1>/Display7' : Unused code path elimination
 * Block '<S1>/Display8' : Unused code path elimination
 * Block '<S6>/Display' : Unused code path elimination
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Propagation' : Unused code path elimination
 * Block '<S6>/Scope' : Unused code path elimination
 * Block '<S2>/Display1' : Unused code path elimination
 * Block '<S2>/Display2' : Unused code path elimination
 * Block '<S2>/Display3' : Unused code path elimination
 * Block '<S7>/Display' : Unused code path elimination
 * Block '<S7>/Display1' : Unused code path elimination
 * Block '<S7>/Display2' : Unused code path elimination
 * Block '<S7>/Display3' : Unused code path elimination
 * Block '<S7>/Display4' : Unused code path elimination
 * Block '<S7>/Display5' : Unused code path elimination
 * Block '<S7>/Display6' : Unused code path elimination
 * Block '<S7>/Display7' : Unused code path elimination
 * Block '<S8>/Display' : Unused code path elimination
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S2>/Scope1' : Unused code path elimination
 * Block '<S4>/Display' : Unused code path elimination
 * Block '<S4>/Display1' : Unused code path elimination
 * Block '<S1>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S6>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S20>/Data Type Conversion1' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('v00_0A_0F/SOCEstimation')    - opens subsystem v00_0A_0F/SOCEstimation
 * hilite_system('v00_0A_0F/SOCEstimation/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'v00_0A_0F'
 * '<S1>'   : 'v00_0A_0F/SOCEstimation'
 * '<S2>'   : 'v00_0A_0F/SOCEstimation/SOC_Calc'
 * '<S3>'   : 'v00_0A_0F/SOCEstimation/SOC_ReadFromEEPROM'
 * '<S4>'   : 'v00_0A_0F/SOCEstimation/SoH calculation'
 * '<S5>'   : 'v00_0A_0F/SOCEstimation/powergui'
 * '<S6>'   : 'v00_0A_0F/SOCEstimation/SOC_Calc/Capacity Estimator'
 * '<S7>'   : 'v00_0A_0F/SOCEstimation/SOC_Calc/EKFStateChangeChecker'
 * '<S8>'   : 'v00_0A_0F/SOCEstimation/SOC_Calc/Integrators'
 * '<S9>'   : 'v00_0A_0F/SOCEstimation/SOC_Calc/LatchFlagSet//Reset'
 * '<S10>'  : 'v00_0A_0F/SOCEstimation/SOC_Calc/SoC estimator'
 * '<S11>'  : 'v00_0A_0F/SOCEstimation/SOC_Calc/Capacity Estimator/SOC_Estimator'
 * '<S12>'  : 'v00_0A_0F/SOCEstimation/SOC_Calc/Capacity Estimator/Saturation Dynamic2'
 * '<S13>'  : 'v00_0A_0F/SOCEstimation/SOC_Calc/EKFStateChangeChecker/MATLAB Function'
 * '<S14>'  : 'v00_0A_0F/SOCEstimation/SOC_Calc/Integrators/IntegCurrent'
 * '<S15>'  : 'v00_0A_0F/SOCEstimation/SOC_Calc/Integrators/Modulus IntegCurrent'
 * '<S16>'  : 'v00_0A_0F/SOCEstimation/SoH calculation/SoH calculation EN'
 * '<S17>'  : 'v00_0A_0F/SOCEstimation/SoH calculation/Subsystem'
 * '<S18>'  : 'v00_0A_0F/SOCEstimation/SoH calculation/efff_usable_Capacity'
 * '<S19>'  : 'v00_0A_0F/SOCEstimation/SoH calculation/Subsystem/SoH calculation'
 * '<S20>'  : 'v00_0A_0F/SOCEstimation/SoH calculation/Subsystem/SoH1 calculation'
 * '<S21>'  : 'v00_0A_0F/SOCEstimation/SoH calculation/Subsystem/SoH calculation/SoH Blend'
 * '<S22>'  : 'v00_0A_0F/SOCEstimation/SoH calculation/Subsystem/SoH1 calculation/MATLAB Function'
 */
#endif                                 /* SOCEstimation_h_ */
