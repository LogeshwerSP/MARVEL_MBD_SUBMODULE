/*
 * SOCEstimation_types.h
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

 #ifndef SOCEstimation_types_h_
 #define SOCEstimation_types_h_
 #include "rtwtypes.h"
 #ifndef DEFINED_TYPEDEF_FOR_VoltageSenseBus_
 #define DEFINED_TYPEDEF_FOR_VoltageSenseBus_
 
 typedef struct {
   int32_T Voltages_mV[18];
   int32_T mV_min;
   int32_T mV_max;
   int32_T VoltageDelta_mV;
 } VoltageSenseBus;
 
 #endif
 
 #ifndef DEFINED_TYPEDEF_FOR_TemperatureSenseBus_
 #define DEFINED_TYPEDEF_FOR_TemperatureSenseBus_
 
 typedef struct {
   int16_T Temperatures_C[7];
   int16_T T_min;
   int16_T T_max;
   int16_T TemperatureDelta_C;
 } TemperatureSenseBus;
 
 #endif
 
 #ifndef DEFINED_TYPEDEF_FOR_VCU_
 #define DEFINED_TYPEDEF_FOR_VCU_
 
 typedef struct {
   boolean_T SlowCharge;
   boolean_T FastCharge;
   boolean_T isChargerConnected;
   boolean_T TransmissionFail;
   boolean_T VCUPermanentFail;
   boolean_T ServiceMode;
   boolean_T BalanceEn_atRest;
   boolean_T EmergencyDisconnectEn;
   uint32_T SlowChargersCurrentLimit_A;
   uint32_T FastChargersCurrentLimit_A;
 } VCU;
 
 #endif
 
 #ifndef DEFINED_TYPEDEF_FOR_DataPipelineBus_
 #define DEFINED_TYPEDEF_FOR_DataPipelineBus_
 
 typedef struct {
   int32_T Current_mA;
   VoltageSenseBus VoltageSenseBus;
   int16_T MaxTemperature_C;
   int16_T DeltaTemperature_C;
   int16_T MinTemperature_C;
   int16_T DeltaTemperatureGroup1_C;
   int16_T DeltaTemperatureGroup2_C;
   TemperatureSenseBus TemperatureSenseBus[2];
   uint8_T isChargeEn;
   boolean_T isDynamicCurrentEn;
   uint8_T nCells_series;
   int8_T nCells_parallel;
   real32_T DCL_ChargingCurrent_A;
   real32_T DCL_DisChargingCurrent_A;
   real32_T DCL_arcReactor_A;
   real32_T i2t_ChargingCurrent_A2sec;
   real32_T i2t_DisChargingCurrent_A2sec;
   real32_T LoopTimer_SOC_msec;
   VCU VCU;
   boolean_T PreChargeLogic;
   int32_T TerminalVoltage_mV;
   boolean_T IR_Calculation_En;
   uint32_T RecordedCycleCount;
   boolean_T IRSlowGuard;
   boolean_T IRFastGuard;
   boolean_T IRComplete;
 } DataPipelineBus;
 
 #endif
 
 #ifndef DEFINED_TYPEDEF_FOR_EKF_InputsBus_
 #define DEFINED_TYPEDEF_FOR_EKF_InputsBus_
 
 typedef struct {
   real_T SoCData[101];
   real_T ocvData[101];
   real_T cellIR_mOhm;
   real_T loopTimeEKF;
   real32_T processNoise;
   real32_T measurementNoise;
   int32_T lowerActivationThreshold;
   int32_T higherActivationThreshold;
   boolean_T enableEKF;
   int32_T delCurrentThresh_mA;
   int32_T delVoltThresh_mV;
   uint32_T currentTime;
   uint32_T timeToWaitUnderLoad;
 } EKF_InputsBus;
 
 #endif
 
 #ifndef DEFINED_TYPEDEF_FOR_SlowCharge_
 #define DEFINED_TYPEDEF_FOR_SlowCharge_
 
 typedef struct {
   int32_T MaxVoltageLimit_mV;
   int32_T MaxCurrentLimit_mA;
   int32_T MinCurrentLimit_mA;
   int32_T MaxAllowedImb_mV;
 } SlowCharge;
 
 #endif
 
 #ifndef DEFINED_TYPEDEF_FOR_FastCharge_
 #define DEFINED_TYPEDEF_FOR_FastCharge_
 
 typedef struct {
   int32_T MaxVoltageLimit_mV;
   int32_T MaxCurrentLimit_mA;
   int32_T MinCurrentLimit_mA;
   int32_T MaxAllowedImb_mV;
 } FastCharge;
 
 #endif
 
 #ifndef DEFINED_TYPEDEF_FOR_Coefficients_
 #define DEFINED_TYPEDEF_FOR_Coefficients_
 
 typedef struct {
   real_T elementZero;
   real_T elementOne;
   real_T elementTwo;
   real_T elementThree;
   real_T elementFour;
 } Coefficients;
 
 #endif
 
 #ifndef DEFINED_TYPEDEF_FOR_CC_InputsBus_
 #define DEFINED_TYPEDEF_FOR_CC_InputsBus_
 
 typedef struct {
   int32_T InstalledCapacity_mAh;
   uint8_T SoHThresh;
   int16_T CCTimeout_msec;
   int16_T DebouncingTimeout_msec;
   SlowCharge SlowCharge;
   FastCharge FastCharge;
   uint16_T minVoltageForLatch_mV;
   uint16_T alternateMinVoltageLatch_mV;
   uint16_T alternateMaxLatchVoltage_mV;
   boolean_T pseudoLatchFlag;
   boolean_T fullChargeFlag;
   Coefficients Coefficients;
   real32_T SoH2Memory;
   real32_T SoHMemory;
   real32_T Tcomp;
   real32_T SoHTolerance;
   uint8_T cycleCountThreshold;
   uint8_T TempThreshForSoHCalib;
   uint8_T TempDeltaAllowed;
   real32_T prevLatchtCycleCountFromMem;
 } CC_InputsBus;
 
 #endif
 
 #ifndef DEFINED_TYPEDEF_FOR_CCState_
 #define DEFINED_TYPEDEF_FOR_CCState_
 
 typedef enum {
   Vehicle_at_Rest = 0,                 /* Default value */
   CoulombCounting,
   PseudoLatching,
   Recalibrate,
   EKFestimation
 } CCState;
 
 #endif
 
 #ifndef DEFINED_TYPEDEF_FOR_CC_OutputsBus_
 #define DEFINED_TYPEDEF_FOR_CC_OutputsBus_
 
 typedef struct {
   int32_T Total_CapacityRemains_mAh;
   int32_T SOC_cpct;
   CCState CC_State;
   int32_T MaxUsableCapacity_mAh;
   real32_T cycleCount;
   real32_T SOH_pct;
   real32_T SoH2;
   boolean_T EKF_resetTimer;
 } CC_OutputsBus;
 
 #endif
 
 /* Forward declaration for rtModel */
 typedef struct tag_RTM_SOCEstimation_T RT_MODEL_SOCEstimation_T;
 
 #endif                                 /* SOCEstimation_types_h_ */
 