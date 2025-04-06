/*
 * SOCEstimation.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "SOCEstimation".
 *
 * Model version              : 7.76
 * Simulink Coder version : 24.1 (R2024a) 19-Nov-2023
 * C source code generated on : Fri Jan 17 17:05:33 2025
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

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T SoCEst;                       /* '<S8>/SOC_Estimator' */
  real32_T Switch;                     /* '<S5>/Switch' */
  real32_T ModIntegratedCurrent;       /* '<S10>/Modulus IntegCurrent' */
  real32_T IntegratedCurrent;          /* '<S10>/IntegCurrent' */
  int32_T Effectiveusablecapacity;     /* '<S20>/Data Type Conversion1' */
  int32_T capLatch;                    /* '<S8>/SOC_Estimator' */
  int32_T TotalCapacityRemains_mAh;    /* '<S8>/SOC_Estimator' */
  int32_T Initial_Capacity_mAh;        /* '<S8>/SOC_Estimator' */
  B_SOC_ReadFromEEPROM_SOCEstim_T sf_SOC_ReadFromEEPROM;/* '<S1>/SOC_ReadFromEEPROM' */
} B_SOCEstimation_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T counter;                      /* '<S6>/MATLAB Function' */
  real_T x;                            /* '<S8>/SOC_Estimator' */
  real_T EKF_P;                        /* '<S8>/SOC_Estimator' */
  real_T H_prev;                       /* '<S8>/SOC_Estimator' */
  real_T filteredVoltage;              /* '<S8>/SOC_Estimator' */
  int32_T Delay1_DSTATE;               /* '<S9>/Delay1' */
  int32_T Delay_DSTATE;                /* '<S9>/Delay' */
  int32_T Delay1_DSTATE_m;             /* '<S3>/Delay1' */
  CCState UnitDelay_DSTATE;            /* '<S3>/Unit Delay' */
  int32_T initialSoC;                  /* '<S8>/SOC_Estimator' */
  uint32_T temporalCounter_i1;         /* '<S8>/SOC_Estimator' */
  uint32_T durationCounter_1;          /* '<S8>/SOC_Estimator' */
  uint32_T durationCounter_2;          /* '<S8>/SOC_Estimator' */
  uint32_T durationCounter_1_l;        /* '<S8>/SOC_Estimator' */
  uint32_T durationCounter_3;          /* '<S8>/SOC_Estimator' */
  uint8_T is_active_c20_SOCEstimation; /* '<S10>/Modulus IntegCurrent' */
  uint8_T is_active_c42_SOCEstimation; /* '<S10>/IntegCurrent' */
  uint8_T is_c42_SOCEstimation;        /* '<S10>/IntegCurrent' */
  uint8_T is_active_c15_SOCEstimation; /* '<S8>/SOC_Estimator' */
  uint8_T is_c15_SOCEstimation;        /* '<S8>/SOC_Estimator' */
  boolean_T counter_not_empty;         /* '<S6>/MATLAB Function' */
  boolean_T resetEKF;                  /* '<S8>/SOC_Estimator' */
  boolean_T SoHcalculation_MODE;       /* '<S1>/SoH calculation' */
} DW_SOCEstimation_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  DataPipelineBus DataPipeline;        /* '<Root>/DataPipeline' */
  int32_T Current_mA;                  /* '<Root>/Current_mA' */
  EKF_InputsBus EKF_Inputs;            /* '<Root>/EKF_Inputs' */
  CC_InputsBus CC_Inputs;              /* '<Root>/CC_Inputs' */
  real_T looptimeSoC; /* Added variable */
} ExtU_SOCEstimation_T;

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
 * Block '<S8>/Display' : Unused code path elimination
 * Block '<S14>/Data Type Duplicate' : Unused code path elimination
 * Block '<S14>/Data Type Propagation' : Unused code path elimination
 * Block '<S8>/Scope' : Unused code path elimination
 * Block '<S3>/Display' : Unused code path elimination
 * Block '<S3>/Display1' : Unused code path elimination
 * Block '<S3>/Display2' : Unused code path elimination
 * Block '<S3>/Display3' : Unused code path elimination
 * Block '<S9>/Display' : Unused code path elimination
 * Block '<S9>/Display1' : Unused code path elimination
 * Block '<S9>/Display2' : Unused code path elimination
 * Block '<S9>/Display3' : Unused code path elimination
 * Block '<S9>/Display4' : Unused code path elimination
 * Block '<S9>/Display5' : Unused code path elimination
 * Block '<S9>/Display6' : Unused code path elimination
 * Block '<S9>/Display7' : Unused code path elimination
 * Block '<S10>/Display' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S3>/Scope1' : Unused code path elimination
 * Block '<S5>/Display' : Unused code path elimination
 * Block '<S5>/Display1' : Unused code path elimination
 * Block '<S1>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion2' : Eliminate redundant data type conversion
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
 * '<S2>'   : 'v00_0A_0F/SOCEstimation/MATLAB Function'
 * '<S3>'   : 'v00_0A_0F/SOCEstimation/SOC_Calc'
 * '<S4>'   : 'v00_0A_0F/SOCEstimation/SOC_ReadFromEEPROM'
 * '<S5>'   : 'v00_0A_0F/SOCEstimation/SoH calculation'
 * '<S6>'   : 'v00_0A_0F/SOCEstimation/Subsystem1'
 * '<S7>'   : 'v00_0A_0F/SOCEstimation/powergui'
 * '<S8>'   : 'v00_0A_0F/SOCEstimation/SOC_Calc/Capacity Estimator'
 * '<S9>'   : 'v00_0A_0F/SOCEstimation/SOC_Calc/EKFStateChangeChecker'
 * '<S10>'  : 'v00_0A_0F/SOCEstimation/SOC_Calc/Integrators'
 * '<S11>'  : 'v00_0A_0F/SOCEstimation/SOC_Calc/MATLAB Function'
 * '<S12>'  : 'v00_0A_0F/SOCEstimation/SOC_Calc/SoC estimator'
 * '<S13>'  : 'v00_0A_0F/SOCEstimation/SOC_Calc/Capacity Estimator/SOC_Estimator'
 * '<S14>'  : 'v00_0A_0F/SOCEstimation/SOC_Calc/Capacity Estimator/Saturation Dynamic2'
 * '<S15>'  : 'v00_0A_0F/SOCEstimation/SOC_Calc/EKFStateChangeChecker/MATLAB Function'
 * '<S16>'  : 'v00_0A_0F/SOCEstimation/SOC_Calc/Integrators/IntegCurrent'
 * '<S17>'  : 'v00_0A_0F/SOCEstimation/SOC_Calc/Integrators/Modulus IntegCurrent'
 * '<S18>'  : 'v00_0A_0F/SOCEstimation/SoH calculation/SoH calculation'
 * '<S19>'  : 'v00_0A_0F/SOCEstimation/SoH calculation/SoH1 calculation'
 * '<S20>'  : 'v00_0A_0F/SOCEstimation/SoH calculation/efff_usable_Capacity'
 * '<S21>'  : 'v00_0A_0F/SOCEstimation/SoH calculation/SoH calculation/SoH Blend'
 * '<S22>'  : 'v00_0A_0F/SOCEstimation/SoH calculation/SoH1 calculation/MATLAB Function'
 * '<S23>'  : 'v00_0A_0F/SOCEstimation/Subsystem1/MATLAB Function'
 */
#endif                                 /* SOCEstimation_h_ */
