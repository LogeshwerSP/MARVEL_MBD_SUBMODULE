/*
 * ChargingAlgorithm.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "ChargingAlgorithm".
 *
 * Model version              : 4.4
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C source code generated on : Mon Oct 14 20:47:21 2024
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: STMicroelectronics->Cortex_M3
 * Code generation objective: Execution efficiency
 * Validation result: Passed (9), Warning (1), Error (0)
 */

#include "ChargingAlgorithm.h"
#include "rtwtypes.h"
#include "ChargingAlgorithm_private.h"
#include <math.h>
#include "multiword_types.h"
#include "ChargingAlgorithm_types.h"
#include <string.h>

/* Named constants for Chart: '<S1>/ChargingAlgorithmProcessing' */
#define Chargi_IN_TrickleChargeDisabled ((uint8_T)1U)
#define Chargin_IN_TrickleChargeEnabled ((uint8_T)2U)
#define ChargingAlgo_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define ChargingAlgo_IN_TrickleCharging ((uint8_T)2U)
#define ChargingAlgor_IN_NormalCharging ((uint8_T)1U)
#define ChargingAlgori_IN_chargingLobby ((uint8_T)3U)
#define ChargingAlgorit_IN_FastCharging ((uint8_T)1U)
#define ChargingAlgorit_IN_SlowCharging ((uint8_T)2U)
#define ChargingAlgorithm_IN_CC        ((uint8_T)1U)
#define ChargingAlgorithm_IN_CV        ((uint8_T)2U)

/* Named constants for Chart: '<S1>/ChargingStateMachine' */
#define ChargingAlgorithm_IN_FastCharge ((uint8_T)1U)
#define ChargingAlgorithm_IN_IRCalc    ((uint8_T)2U)
#define ChargingAlgorithm_IN_NoCharge  ((uint8_T)3U)
#define ChargingAlgorithm_IN_SlowCharge ((uint8_T)4U)

/* Named constants for Chart: '<S1>/IRCalculation' */
#define ChargingAlgori_IN_IRCalculation ((uint8_T)2U)
#define ChargingAlgorith_IN_IRCalcBegin ((uint8_T)3U)
#define ChargingAlgorithm_IN_DropPulse ((uint8_T)1U)
#define ChargingAlgorithm_IN_DropSense ((uint8_T)2U)
#define ChargingAlgorithm_IN_Entry     ((uint8_T)1U)
#define ChargingAlgorithm_IN_IRLobby   ((uint8_T)3U)
#define ChargingAlgorithm_IN_UpSense   ((uint8_T)4U)

/* Block signals (default storage) */
B_ChargingAlgorithm_T ChargingAlgorithm_B;

/* Block states (default storage) */
DW_ChargingAlgorithm_T ChargingAlgorithm_DW;

/* External inputs (root inport signals with default storage) */
ExtU_ChargingAlgorithm_T ChargingAlgorithm_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_ChargingAlgorithm_T ChargingAlgorithm_Y;

/* Real-time model */
static RT_MODEL_ChargingAlgorithm_T ChargingAlgorithm_M_;
RT_MODEL_ChargingAlgorithm_T *const ChargingAlgorithm_M = &ChargingAlgorithm_M_;
const CC_OutputsBus ChargingAlgorithm_rtZCC_Outputs = {0,/* Total_CapacityRemains_mAh */
  0,                                   /* SOC_cpct */
  Vehicle_at_Rest,                     /* CC_State */
  0,                                   /* MaxUsableCapacity_mAh */
  0,                                   /* TotalCapacityExchange_mAh */
  0.0F,                                /* SOH_pct */
  0.0F,                                /* SoH2 */
  false                                /* EKF_resetTimer */
};

void MultiWordSignedWrap_chg(const uint32_T u1[], int32_T n1, uint32_T n2, uint32_T
  y[])
{
  int32_T i;
  int32_T n1m1;
  n1m1 = n1 - 1;
  for (i = 0; i < n1m1; i++) {
    y[i] = u1[i];
  }

  uint32_T mask;
  uint32_T ys;
  mask = 1U << (31U - n2);
  ys = (u1[n1 - 1] & mask) != 0U ? MAX_uint32_T : 0U;
  mask = (mask << 1U) - 1U;
  y[n1 - 1] = (u1[n1 - 1] & mask) | (~mask & ys);
}

void sMultiWordMul_chg(const uint32_T u1[], int32_T n1, const uint32_T u2[], int32_T
                   n2, uint32_T y[], int32_T n)
{
  int32_T i;
  int32_T j;
  int32_T k;
  uint32_T cb;
  uint32_T cb1;
  uint32_T yk;
  boolean_T isNegative1;
  boolean_T isNegative2;
  isNegative1 = ((u1[n1 - 1] & 2147483648U) != 0U);
  isNegative2 = ((u2[n2 - 1] & 2147483648U) != 0U);
  cb1 = 1U;

  /* Initialize output to zero */
  for (k = 0; k < n; k++) {
    y[k] = 0U;
  }

  for (i = 0; i < n1; i++) {
    int32_T ni;
    uint32_T a0;
    uint32_T a1;
    uint32_T cb2;
    uint32_T u1i;
    cb = 0U;
    u1i = u1[i];
    if (isNegative1) {
      u1i = ~u1i + cb1;
      cb1 = (uint32_T)(u1i < cb1);
    }

    a1 = u1i >> 16U;
    a0 = u1i & 65535U;
    cb2 = 1U;
    ni = n - i;
    ni = n2 <= ni ? n2 : ni;
    k = i;
    for (j = 0; j < ni; j++) {
      uint32_T b1;
      uint32_T w01;
      uint32_T w10;
      u1i = u2[j];
      if (isNegative2) {
        u1i = ~u1i + cb2;
        cb2 = (uint32_T)(u1i < cb2);
      }

      b1 = u1i >> 16U;
      u1i &= 65535U;
      w10 = a1 * u1i;
      w01 = a0 * b1;
      yk = y[k] + cb;
      cb = (uint32_T)(yk < cb);
      u1i *= a0;
      yk += u1i;
      cb += (uint32_T)(yk < u1i);
      u1i = w10 << 16U;
      yk += u1i;
      cb += (uint32_T)(yk < u1i);
      u1i = w01 << 16U;
      yk += u1i;
      cb += (uint32_T)(yk < u1i);
      y[k] = yk;
      cb += w10 >> 16U;
      cb += w01 >> 16U;
      cb += a1 * b1;
      k++;
    }

    if (k < n) {
      y[k] = cb;
    }
  }

  /* Apply sign */
  if (isNegative1 != isNegative2) {
    cb = 1U;
    for (k = 0; k < n; k++) {
      yk = ~y[k] + cb;
      y[k] = yk;
      cb = (uint32_T)(yk < cb);
    }
  }
}

boolean_T sMultiWordGt(const uint32_T u1[], const uint32_T u2[], int32_T n)
{
  return sMultiWordCmp_chg(u1, u2, n) > 0;
}

int32_T sMultiWordCmp_chg(const uint32_T u1[], const uint32_T u2[], int32_T n)
{
  int32_T y;
  uint32_T su1;
  su1 = u1[n - 1] & 2147483648U;
  if ((u2[n - 1] & 2147483648U) != su1) {
    y = su1 != 0U ? -1 : 1;
  } else {
    int32_T i;
    y = 0;
    i = n;
    while ((y == 0) && (i > 0)) {
      uint32_T u2i;
      i--;
      su1 = u1[i];
      u2i = u2[i];
      if (su1 != u2i) {
        y = su1 > u2i ? 1 : -1;
      }
    }
  }

  return y;
}

boolean_T sMultiWordLt(const uint32_T u1[], const uint32_T u2[], int32_T n)
{
  return sMultiWordCmp_chg(u1, u2, n) < 0;
}

real32_T sMultiWord2Single_chg(const uint32_T u1[], int32_T n1, int32_T e1)
{
  int32_T exp_0;
  int32_T i;
  real32_T y;
  y = 0.0F;
  exp_0 = e1;
  if ((u1[n1 - 1] & 2147483648U) != 0U) {
    uint32_T cb;
    cb = 1U;
    for (i = 0; i < n1; i++) {
      uint32_T u1i;
      u1i = ~u1[i];
      cb += u1i;
      y -= (real32_T)ldexp((real32_T)cb, exp_0);
      cb = (uint32_T)(cb < u1i);
      exp_0 += 32;
    }
  } else {
    for (i = 0; i < n1; i++) {
      y += (real32_T)ldexp((real32_T)u1[i], exp_0);
      exp_0 += 32;
    }
  }

  return y;
}

real32_T uMultiWordSingle(const uint32_T u1[], int32_T n1, int32_T e1)
{
  int32_T exp_1;
  int32_T i;
  real32_T y;
  y = 0.0F;
  exp_1 = e1;
  for (i = 0; i < n1; i++) {
    y += (real32_T)ldexp((real32_T)u1[i], exp_1);
    exp_1 += 32;
  }

  return y;
}

void MultiWordUnsignedWrap(const uint32_T u1[], int32_T n1, uint32_T n2,
  uint32_T y[])
{
  int32_T i;
  int32_T n1m1;
  n1m1 = n1 - 1;
  for (i = 0; i < n1m1; i++) {
    y[i] = u1[i];
  }

  y[n1 - 1] = ((1U << (32U - n2)) - 1U) & u1[n1 - 1];
}

void uMultiWordMul(const uint32_T u1[], int32_T n1, const uint32_T u2[], int32_T
                   n2, uint32_T y[], int32_T n)
{
  int32_T i;
  int32_T j;
  int32_T k;

  /* Initialize output to zero */
  for (k = 0; k < n; k++) {
    y[k] = 0U;
  }

  for (i = 0; i < n1; i++) {
    int32_T ni;
    uint32_T a0;
    uint32_T a1;
    uint32_T cb;
    uint32_T u1i;
    cb = 0U;
    u1i = u1[i];
    a1 = u1i >> 16U;
    a0 = u1i & 65535U;
    ni = n - i;
    ni = n2 <= ni ? n2 : ni;
    k = i;
    for (j = 0; j < ni; j++) {
      uint32_T b1;
      uint32_T w01;
      uint32_T w10;
      uint32_T yk;
      u1i = u2[j];
      b1 = u1i >> 16U;
      u1i &= 65535U;
      w10 = a1 * u1i;
      w01 = a0 * b1;
      yk = y[k] + cb;
      cb = (uint32_T)(yk < cb);
      u1i *= a0;
      yk += u1i;
      cb += (uint32_T)(yk < u1i);
      u1i = w10 << 16U;
      yk += u1i;
      cb += (uint32_T)(yk < u1i);
      u1i = w01 << 16U;
      yk += u1i;
      cb += (uint32_T)(yk < u1i);
      y[k] = yk;
      cb += w10 >> 16U;
      cb += w01 >> 16U;
      cb += a1 * b1;
      k++;
    }

    if (k < n) {
      y[k] = cb;
    }
  }
}

/* Model step function */
void ChargingAlgorithm_step(void)
{
  int64m_T rtb_Saturation;
  int64m_T tmp;
  uint64m_T tmp_2;
  uint64m_T tmp_3;
  uint32_T tmp_0;
  uint32_T tmp_1;

  /* Chart: '<S1>/ChargingStateMachine' incorporates:
   *  DataStoreRead: '<S1>/Data Store Read'
   *  Inport: '<Root>/CC_Outputs'
   *  Inport: '<Root>/DataPipeline'
   *  Inport: '<Root>/IR_calcEnable'
   *  Inport: '<Root>/Thresholds'
   */
  if (ChargingAlgorithm_DW.is_active_c34_ChargingAlgorithm == 0U) {
    ChargingAlgorithm_DW.is_active_c34_ChargingAlgorithm = 1U;
    ChargingAlgorithm_DW.is_c34_ChargingAlgorithm =
      ChargingAlgorithm_IN_NoCharge;
    ChargingAlgorithm_DW.IRSlowGuard = false;
    ChargingAlgorithm_DW.IRFastGuard = false;
    ChargingAlgorithm_Y.ChargingState = NoCharging;
  } else {
    switch (ChargingAlgorithm_DW.is_c34_ChargingAlgorithm) {
     case ChargingAlgorithm_IN_FastCharge:
      {
        boolean_T tmp_6;
        ChargingAlgorithm_Y.ChargingState = FastCharging;
        tmp_6 = !ChargingAlgorithm_U.DataPipeline.VCU.FastCharge;
        if ((!ChargingAlgorithm_U.DataPipeline.VCU.isChargerConnected) ||
            ((!ChargingAlgorithm_U.DataPipeline.VCU.SlowCharge) && tmp_6)) {
          ChargingAlgorithm_DW.is_c34_ChargingAlgorithm =
            ChargingAlgorithm_IN_NoCharge;
          ChargingAlgorithm_DW.IRSlowGuard = false;
          ChargingAlgorithm_DW.IRFastGuard = false;
          ChargingAlgorithm_Y.ChargingState = NoCharging;
        } else if ((ChargingAlgorithm_U.CC_Outputs.SOC_cpct >=
                    ChargingAlgorithm_U.Thresholds.iR_startSOC_cpct) &&
                   (ChargingAlgorithm_U.CC_Outputs.SOC_cpct <
                    ChargingAlgorithm_U.Thresholds.iR_startSOC_cpct + 1.0) &&
                   (ChargingAlgorithm_U.DataPipeline.RecordedCycleCount >=
                    ChargingAlgorithm_U.Thresholds.IRCycleCount) &&
                   ChargingAlgorithm_DW.IRFastGuard &&
                   (!ChargingAlgorithm_DW.IR_COMPLETE) &&
                   (ChargingAlgorithm_U.IR_calcEnable != 0.0)) {
          ChargingAlgorithm_DW.is_c34_ChargingAlgorithm =
            ChargingAlgorithm_IN_IRCalc;
          ChargingAlgorithm_Y.ChargingState = IR_Measurement;
        } else if (ChargingAlgorithm_U.DataPipeline.VCU.SlowCharge && tmp_6) {
          ChargingAlgorithm_DW.is_c34_ChargingAlgorithm =
            ChargingAlgorithm_IN_SlowCharge;
          ChargingAlgorithm_Y.ChargingState = SlowCharging;
        } else {
          ChargingAlgorithm_DW.IRFastGuard =
            ((ChargingAlgorithm_U.CC_Outputs.SOC_cpct <=
              ChargingAlgorithm_U.Thresholds.iR_chargingWait_SOCcpct) ||
             ChargingAlgorithm_DW.IRFastGuard);
        }
      }
      break;

     case ChargingAlgorithm_IN_IRCalc:
      ChargingAlgorithm_Y.ChargingState = IR_Measurement;
      if (ChargingAlgorithm_DW.IR_COMPLETE) {
        ChargingAlgorithm_DW.IRSlowGuard = false;
        ChargingAlgorithm_DW.is_c34_ChargingAlgorithm =
          ChargingAlgorithm_IN_SlowCharge;
        ChargingAlgorithm_Y.ChargingState = SlowCharging;
      } else if (!ChargingAlgorithm_U.DataPipeline.VCU.isChargerConnected) {
        ChargingAlgorithm_DW.is_c34_ChargingAlgorithm =
          ChargingAlgorithm_IN_NoCharge;
        ChargingAlgorithm_DW.IRSlowGuard = false;
        ChargingAlgorithm_DW.IRFastGuard = false;
        ChargingAlgorithm_Y.ChargingState = NoCharging;
      }
      break;

     case ChargingAlgorithm_IN_NoCharge:
      ChargingAlgorithm_Y.ChargingState = NoCharging;
      if (ChargingAlgorithm_U.DataPipeline.VCU.isChargerConnected &&
          ChargingAlgorithm_U.DataPipeline.VCU.SlowCharge) {
        ChargingAlgorithm_DW.is_c34_ChargingAlgorithm =
          ChargingAlgorithm_IN_SlowCharge;
        ChargingAlgorithm_Y.ChargingState = SlowCharging;
      } else if (ChargingAlgorithm_U.DataPipeline.VCU.isChargerConnected &&
                 ChargingAlgorithm_U.DataPipeline.VCU.FastCharge) {
        ChargingAlgorithm_DW.is_c34_ChargingAlgorithm =
          ChargingAlgorithm_IN_FastCharge;
        ChargingAlgorithm_Y.ChargingState = FastCharging;
      }
      break;

     default:
      {
        boolean_T tmp_6;

        /* case IN_SlowCharge: */
        ChargingAlgorithm_Y.ChargingState = SlowCharging;
        tmp_6 = !ChargingAlgorithm_U.DataPipeline.VCU.SlowCharge;
        if ((!ChargingAlgorithm_U.DataPipeline.VCU.isChargerConnected) || (tmp_6
             && (!ChargingAlgorithm_U.DataPipeline.VCU.FastCharge))) {
          ChargingAlgorithm_DW.is_c34_ChargingAlgorithm =
            ChargingAlgorithm_IN_NoCharge;
          ChargingAlgorithm_DW.IRSlowGuard = false;
          ChargingAlgorithm_DW.IRFastGuard = false;
          ChargingAlgorithm_Y.ChargingState = NoCharging;
        } else if (ChargingAlgorithm_U.DataPipeline.VCU.FastCharge && tmp_6) {
          ChargingAlgorithm_DW.is_c34_ChargingAlgorithm =
            ChargingAlgorithm_IN_FastCharge;
          ChargingAlgorithm_Y.ChargingState = FastCharging;
        } else if ((ChargingAlgorithm_U.CC_Outputs.SOC_cpct >=
                    ChargingAlgorithm_U.Thresholds.iR_startSOC_cpct) &&
                   (ChargingAlgorithm_U.CC_Outputs.SOC_cpct <
                    ChargingAlgorithm_U.Thresholds.iR_startSOC_cpct + 1.0) &&
                   (ChargingAlgorithm_U.DataPipeline.RecordedCycleCount >=
                    ChargingAlgorithm_U.Thresholds.IRCycleCount) &&
                   ChargingAlgorithm_DW.IRSlowGuard &&
                   (!ChargingAlgorithm_DW.IR_COMPLETE) &&
                   (ChargingAlgorithm_U.IR_calcEnable != 0.0)) {
          ChargingAlgorithm_DW.is_c34_ChargingAlgorithm =
            ChargingAlgorithm_IN_IRCalc;
          ChargingAlgorithm_Y.ChargingState = IR_Measurement;
        } else {
          ChargingAlgorithm_DW.IRSlowGuard =
            ((ChargingAlgorithm_U.CC_Outputs.SOC_cpct <=
              ChargingAlgorithm_U.Thresholds.iR_chargingWait_SOCcpct) ||
             ChargingAlgorithm_DW.IRSlowGuard);
        }
      }
      break;
    }
  }

  /* End of Chart: '<S1>/ChargingStateMachine' */

  /* Chart: '<S1>/ChargingAlgorithmProcessing' incorporates:
   *  Inport: '<Root>/DataPipeline'
   *  Inport: '<Root>/Thresholds'
   */
  if (ChargingAlgorithm_DW.is_active_c32_ChargingAlgorithm == 0U) {
    ChargingAlgorithm_DW.is_active_c32_ChargingAlgorithm = 1U;
    ChargingAlgorithm_DW.durationCounter_1_c = 0U;
    ChargingAlgorithm_DW.is_c32_ChargingAlgorithm =
      ChargingAlgori_IN_chargingLobby;
    ChargingAlgorithm_B.Constant_K = 0.0;
    ChargingAlgorithm_B.trickleChargingEnabled = false;
  } else {
    switch (ChargingAlgorithm_DW.is_c32_ChargingAlgorithm) {
     case ChargingAlgor_IN_NormalCharging:
      if (ChargingAlgorithm_Y.ChargingState != NoCharging) {
        ChargingAlgorithm_DW.durationCounter_2 = 0U;
      }

      if ((uint32_T)((int32_T)ChargingAlgorithm_DW.durationCounter_2 * ChargingAlgorithm_U.looptimeCharging) >=
          ChargingAlgorithm_U.Thresholds.ChargeAlgorithm.TransitionTimeout_msec)
      {
        ChargingAlgorithm_DW.is_FastCharging = ChargingAlgo_IN_NO_ACTIVE_CHILD;
        ChargingAlgorithm_DW.is_SlowCharging = ChargingAlgo_IN_NO_ACTIVE_CHILD;
        ChargingAlgorithm_DW.is_NormalCharging = ChargingAlgo_IN_NO_ACTIVE_CHILD;
        ChargingAlgorithm_DW.durationCounter_1_c = 0U;
        ChargingAlgorithm_DW.is_c32_ChargingAlgorithm =
          ChargingAlgori_IN_chargingLobby;
        ChargingAlgorithm_B.Constant_K = 0.0;
        ChargingAlgorithm_B.trickleChargingEnabled = false;
      } else {
        if (ChargingAlgorithm_U.DataPipeline.VoltageSenseBus.mV_min >=
            ChargingAlgorithm_U.Thresholds.trickleChargingLimit) {
          ChargingAlgorithm_DW.durationCounter_1_im = 0U;
        }

        if ((uint32_T)((int32_T)ChargingAlgorithm_DW.durationCounter_1_im * ChargingAlgorithm_U.looptimeCharging)
            >=
            ChargingAlgorithm_U.Thresholds.ChargeAlgorithm.TransitionTimeout_msec)
        {
          ChargingAlgorithm_DW.is_FastCharging = ChargingAlgo_IN_NO_ACTIVE_CHILD;
          ChargingAlgorithm_DW.is_SlowCharging = ChargingAlgo_IN_NO_ACTIVE_CHILD;
          ChargingAlgorithm_DW.is_NormalCharging =
            ChargingAlgo_IN_NO_ACTIVE_CHILD;
          ChargingAlgorithm_DW.durationCounter_1_i = 0U;
          ChargingAlgorithm_DW.is_c32_ChargingAlgorithm =
            ChargingAlgo_IN_TrickleCharging;
          ChargingAlgorithm_DW.is_TrickleCharging =
            Chargi_IN_TrickleChargeDisabled;
        } else if (ChargingAlgorithm_DW.is_NormalCharging ==
                   ChargingAlgorit_IN_FastCharging) {
          if ((!ChargingAlgorithm_U.DataPipeline.VCU.SlowCharge) ||
              (!ChargingAlgorithm_U.DataPipeline.VCU.FastCharge)) {
            ChargingAlgorithm_DW.durationCounter_1_p = 0U;
          }

          if ((uint32_T)((int32_T)ChargingAlgorithm_DW.durationCounter_1_p * ChargingAlgorithm_U.looptimeCharging)
              >=
              ChargingAlgorithm_U.Thresholds.ChargeAlgorithm.TransitionTimeout_msec)
          {
            ChargingAlgorithm_DW.is_FastCharging =
              ChargingAlgo_IN_NO_ACTIVE_CHILD;
            ChargingAlgorithm_DW.durationCounter_1_n = 0U;
            ChargingAlgorithm_DW.is_NormalCharging =
              ChargingAlgorit_IN_SlowCharging;
            ChargingAlgorithm_DW.is_SlowCharging = ChargingAlgorithm_IN_CC;
          } else if (ChargingAlgorithm_DW.is_FastCharging ==
                     ChargingAlgorithm_IN_CC) {
            if (ChargingAlgorithm_U.DataPipeline.VoltageSenseBus.mV_max >=
                ChargingAlgorithm_U.Thresholds.transitionVoltageCV) {
              ChargingAlgorithm_DW.is_FastCharging = ChargingAlgorithm_IN_CV;
            } else {
              ChargingAlgorithm_B.Constant_K =
                ChargingAlgorithm_U.Thresholds.FastCharge_CC_K;
            }
          } else {
            /* case IN_CV: */
            ChargingAlgorithm_B.Constant_K =
              ChargingAlgorithm_U.Thresholds.FastCharge_CV_K;
            ChargingAlgorithm_B.cvModeActivated = false;
          }
        } else {
          /* case IN_SlowCharging: */
          if ((!ChargingAlgorithm_U.DataPipeline.VCU.FastCharge) ||
              ChargingAlgorithm_U.DataPipeline.VCU.SlowCharge) {
            ChargingAlgorithm_DW.durationCounter_1_n = 0U;
          }

          if ((uint32_T)((int32_T)ChargingAlgorithm_DW.durationCounter_1_n * ChargingAlgorithm_U.looptimeCharging)
              >=
              ChargingAlgorithm_U.Thresholds.ChargeAlgorithm.TransitionTimeout_msec)
          {
            ChargingAlgorithm_DW.is_SlowCharging =
              ChargingAlgo_IN_NO_ACTIVE_CHILD;
            ChargingAlgorithm_DW.durationCounter_1_p = 0U;
            ChargingAlgorithm_DW.is_NormalCharging =
              ChargingAlgorit_IN_FastCharging;
            ChargingAlgorithm_DW.is_FastCharging = ChargingAlgorithm_IN_CC;
          } else if (ChargingAlgorithm_DW.is_SlowCharging ==
                     ChargingAlgorithm_IN_CC) {
            if (ChargingAlgorithm_U.DataPipeline.VoltageSenseBus.mV_max >=
                ChargingAlgorithm_U.Thresholds.transitionVoltageCV) {
              ChargingAlgorithm_DW.is_SlowCharging = ChargingAlgorithm_IN_CV;
            } else {
              ChargingAlgorithm_B.Constant_K =
                ChargingAlgorithm_U.Thresholds.SlowCharge_CC_K;
            }
          } else {
            /* case IN_CV: */
            ChargingAlgorithm_B.Constant_K =
              ChargingAlgorithm_U.Thresholds.SlowCharge_CV_K;
            ChargingAlgorithm_B.cvModeActivated = true;
          }
        }
      }
      break;

     case ChargingAlgo_IN_TrickleCharging:
      if (ChargingAlgorithm_Y.ChargingState != NoCharging) {
        ChargingAlgorithm_DW.durationCounter_1_i = 0U;
      }

      if ((uint32_T)((int32_T)ChargingAlgorithm_DW.durationCounter_1_i * ChargingAlgorithm_U.looptimeCharging) >=
          ChargingAlgorithm_U.Thresholds.ChargeAlgorithm.TransitionTimeout_msec)
      {
        ChargingAlgorithm_DW.is_TrickleCharging =
          ChargingAlgo_IN_NO_ACTIVE_CHILD;
        ChargingAlgorithm_DW.durationCounter_1_c = 0U;
        ChargingAlgorithm_DW.is_c32_ChargingAlgorithm =
          ChargingAlgori_IN_chargingLobby;
        ChargingAlgorithm_B.Constant_K = 0.0;
        ChargingAlgorithm_B.trickleChargingEnabled = false;
      } else if (ChargingAlgorithm_DW.is_TrickleCharging ==
                 Chargi_IN_TrickleChargeDisabled) {
        if (ChargingAlgorithm_U.DataPipeline.VoltageSenseBus.mV_min <=
            ChargingAlgorithm_U.Thresholds.trickleChargingLimit) {
          ChargingAlgorithm_DW.is_TrickleCharging =
            Chargin_IN_TrickleChargeEnabled;
        } else if ((ChargingAlgorithm_Y.ChargingState == FastCharging) &&
                   (!ChargingAlgorithm_B.trickleChargingEnabled)) {
          ChargingAlgorithm_B.Constant_K =
            ChargingAlgorithm_U.Thresholds.FastCharge_CC_K;
          ChargingAlgorithm_DW.is_TrickleCharging =
            ChargingAlgo_IN_NO_ACTIVE_CHILD;
          ChargingAlgorithm_DW.durationCounter_2 = 0U;
          ChargingAlgorithm_DW.durationCounter_1_im = 0U;
          ChargingAlgorithm_DW.is_c32_ChargingAlgorithm =
            ChargingAlgor_IN_NormalCharging;
          ChargingAlgorithm_DW.durationCounter_1_p = 0U;
          ChargingAlgorithm_DW.is_NormalCharging =
            ChargingAlgorit_IN_FastCharging;
          ChargingAlgorithm_DW.is_FastCharging = ChargingAlgorithm_IN_CC;
        } else if ((ChargingAlgorithm_Y.ChargingState == SlowCharging) &&
                   (!ChargingAlgorithm_B.trickleChargingEnabled)) {
          ChargingAlgorithm_B.Constant_K =
            ChargingAlgorithm_U.Thresholds.SlowCharge_CC_K;
          ChargingAlgorithm_DW.is_TrickleCharging =
            ChargingAlgo_IN_NO_ACTIVE_CHILD;
          ChargingAlgorithm_DW.durationCounter_2 = 0U;
          ChargingAlgorithm_DW.durationCounter_1_im = 0U;
          ChargingAlgorithm_DW.is_c32_ChargingAlgorithm =
            ChargingAlgor_IN_NormalCharging;
          ChargingAlgorithm_DW.durationCounter_1_n = 0U;
          ChargingAlgorithm_DW.is_NormalCharging =
            ChargingAlgorit_IN_SlowCharging;
          ChargingAlgorithm_DW.is_SlowCharging = ChargingAlgorithm_IN_CC;
        } else {
          ChargingAlgorithm_B.trickleChargingEnabled = false;
        }

        /* case IN_TrickleChargeEnabled: */
      } else if (ChargingAlgorithm_U.DataPipeline.VoltageSenseBus.mV_min >
                 ChargingAlgorithm_U.Thresholds.trickleChargingLimit) {
        ChargingAlgorithm_DW.is_TrickleCharging =
          Chargi_IN_TrickleChargeDisabled;
      } else {
        ChargingAlgorithm_B.trickleChargingEnabled = true;
      }
      break;

     default:
      /* case IN_chargingLobby: */
      if (ChargingAlgorithm_Y.ChargingState == NoCharging) {
        ChargingAlgorithm_DW.durationCounter_1_c = 0U;
      }

      if ((uint32_T)((int32_T)ChargingAlgorithm_DW.durationCounter_1_c * ChargingAlgorithm_U.looptimeCharging) >=
          ChargingAlgorithm_U.Thresholds.ChargeAlgorithm.TransitionTimeout_msec)
      {
        ChargingAlgorithm_DW.durationCounter_1_i = 0U;
        ChargingAlgorithm_DW.is_c32_ChargingAlgorithm =
          ChargingAlgo_IN_TrickleCharging;
        ChargingAlgorithm_DW.is_TrickleCharging =
          Chargi_IN_TrickleChargeDisabled;
      }
      break;
    }
  }

  if (ChargingAlgorithm_U.DataPipeline.VCU.SlowCharge &&
      ChargingAlgorithm_U.DataPipeline.VCU.FastCharge) {
    ChargingAlgorithm_DW.durationCounter_1_p++;
  } else {
    ChargingAlgorithm_DW.durationCounter_1_p = 0U;
  }

  if (ChargingAlgorithm_U.DataPipeline.VCU.FastCharge &&
      (!ChargingAlgorithm_U.DataPipeline.VCU.SlowCharge)) {
    ChargingAlgorithm_DW.durationCounter_1_n++;
  } else {
    ChargingAlgorithm_DW.durationCounter_1_n = 0U;
  }

  if (ChargingAlgorithm_Y.ChargingState != NoCharging) {
    ChargingAlgorithm_DW.durationCounter_1_c++;
    ChargingAlgorithm_DW.durationCounter_1_i = 0U;
  } else {
    ChargingAlgorithm_DW.durationCounter_1_c = 0U;
    ChargingAlgorithm_DW.durationCounter_1_i++;
  }

  if (ChargingAlgorithm_U.DataPipeline.VoltageSenseBus.mV_min <
      ChargingAlgorithm_U.Thresholds.trickleChargingLimit) {
    ChargingAlgorithm_DW.durationCounter_1_im++;
  } else {
    ChargingAlgorithm_DW.durationCounter_1_im = 0U;
  }

  if (ChargingAlgorithm_Y.ChargingState == NoCharging) {
    ChargingAlgorithm_DW.durationCounter_2++;
  } else {
    ChargingAlgorithm_DW.durationCounter_2 = 0U;
  }

  /* End of Chart: '<S1>/ChargingAlgorithmProcessing' */

  /* Switch: '<S1>/Switch2' */
  if (ChargingAlgorithm_B.trickleChargingEnabled) {
    /* Switch: '<S1>/Switch2' incorporates:
     *  Inport: '<Root>/Thresholds'
     */
    ChargingAlgorithm_Y.RequestedCurrent_mA =
      ChargingAlgorithm_U.Thresholds.TrickleChargingCurrent;
  } else {
    int32_T tmp_4;
    int32_T tmp_5;

    /* Gain: '<S1>/Gain1' */
    tmp_0 = 1000U;

    /* Switch: '<S1>/Switch' incorporates:
     *  Inport: '<Root>/DataPipeline'
     *  Inport: '<Root>/Thresholds'
     */
    if (ChargingAlgorithm_U.DataPipeline.VCU.FastCharge) {
      tmp_4 = ChargingAlgorithm_U.Thresholds.targetVoltageFastCharging_mV;
    } else {
      tmp_4 = ChargingAlgorithm_U.Thresholds.targetVoltageSlowCharging_mV;
    }

    /* Switch: '<S1>/Switch4' incorporates:
     *  Inport: '<Root>/DataPipeline'
     */
    if (ChargingAlgorithm_B.cvModeActivated) {
      tmp_5 = ChargingAlgorithm_U.DataPipeline.VoltageSenseBus.mV_min;
    } else {
      tmp_5 = ChargingAlgorithm_U.DataPipeline.VoltageSenseBus.mV_max;
    }

    /* Gain: '<S1>/Gain1' incorporates:
     *  Product: '<S1>/Product'
     *  Sum: '<S1>/Minus'
     *  Switch: '<S1>/Switch'
     *  Switch: '<S1>/Switch4'
     */
    tmp_1 = (uint32_T)(int32_T)floor((real_T)(tmp_4 - tmp_5) *
      ChargingAlgorithm_B.Constant_K);
    sMultiWordMul_chg(&tmp_0, 1, &tmp_1, 1, &tmp.chunks[0U], 2);
    MultiWordSignedWrap_chg(&tmp.chunks[0U], 2, 16U, &rtb_Saturation.chunks[0U]);

    /* Saturate: '<S1>/Saturation' */
    if (sMultiWordGt(&rtb_Saturation.chunks[0U],
                     &ChargingAlgorithm_ConstP.Saturation_UpperSat.chunks[0], 2))
    {
      rtb_Saturation = ChargingAlgorithm_ConstP.Saturation_UpperSat;
    } else if (sMultiWordLt(&rtb_Saturation.chunks[0U],
                            &ChargingAlgorithm_ConstP.Saturation_LowerSat.chunks[
                            0], 2)) {
      rtb_Saturation = ChargingAlgorithm_ConstP.Saturation_LowerSat;
    }

    /* End of Saturate: '<S1>/Saturation' */

    /* Switch: '<S1>/Switch3' incorporates:
     *  Inport: '<Root>/DataPipeline'
     */
    if (ChargingAlgorithm_U.DataPipeline.VCU.FastCharge) {
      tmp_1 = ChargingAlgorithm_U.DataPipeline.VCU.FastChargersCurrentLimit_A;
    } else {
      tmp_1 = ChargingAlgorithm_U.DataPipeline.VCU.SlowChargersCurrentLimit_A;
    }

    /* Gain: '<S1>/Gain3' incorporates:
     *  Switch: '<S1>/Switch3'
     */
    uMultiWordMul(&tmp_0, 1, &tmp_1, 1, &tmp_3.chunks[0U], 2);
    MultiWordUnsignedWrap(&tmp_3.chunks[0U], 2, 16U, &tmp_2.chunks[0U]);

    /* Switch: '<S1>/Switch2' incorporates:
     *  Gain: '<S1>/Gain2'
     *  Inport: '<Root>/DataPipeline'
     *  MinMax: '<S1>/Min'
     */
    ChargingAlgorithm_Y.RequestedCurrent_mA = fminf(fminf(sMultiWord2Single_chg
      (&rtb_Saturation.chunks[0U], 2, 0), 1000.0F *
      ChargingAlgorithm_U.DataPipeline.DCL_ChargingCurrent_A), uMultiWordSingle(
      &tmp_2.chunks[0U], 2, 0));
  }

  /* End of Switch: '<S1>/Switch2' */

  /* Chart: '<S1>/IRCalculation' incorporates:
   *  Inport: '<Root>/DataPipeline'
   *  Inport: '<Root>/Thresholds'
   */
  if (ChargingAlgorithm_DW.temporalCounter_i1 < MAX_uint32_T) {
    ChargingAlgorithm_DW.temporalCounter_i1++;
  }

  if (ChargingAlgorithm_DW.is_active_c31_ChargingAlgorithm == 0U) {
    ChargingAlgorithm_DW.is_active_c31_ChargingAlgorithm = 1U;
    ChargingAlgorithm_DW.is_c31_ChargingAlgorithm = ChargingAlgorithm_IN_IRLobby;
    ChargingAlgorithm_B.firstVolt = 0;
    ChargingAlgorithm_B.secondVolt = 0;
    ChargingAlgorithm_B.firstRequestedCurrent = 10;
    ChargingAlgorithm_B.secondRequestedCurrent = 0;
    ChargingAlgorithm_B.internalResistancePulseCurrent =
      ChargingAlgorithm_Y.RequestedCurrent_mA;
  } else {
    switch (ChargingAlgorithm_DW.is_c31_ChargingAlgorithm) {
     case ChargingAlgorithm_IN_Entry:
      if ((!ChargingAlgorithm_U.DataPipeline.VCU.isChargerConnected) ||
          (ChargingAlgorithm_Y.ChargingState != IR_Measurement)) {
        ChargingAlgorithm_DW.durationCounter_1 = 0U;
      }

      if ((real_T)(uint32_T)((int32_T)ChargingAlgorithm_DW.durationCounter_1 *
                             100) >=
          ChargingAlgorithm_U.Thresholds.IRTransition_msec) {
        ChargingAlgorithm_DW.durationCounter_1_f = 0U;
        ChargingAlgorithm_DW.is_c31_ChargingAlgorithm =
          ChargingAlgori_IN_IRCalculation;
        ChargingAlgorithm_DW.is_IRCalculation = ChargingAlgorith_IN_IRCalcBegin;
        ChargingAlgorithm_DW.temporalCounter_i1 = 0U;
      }
      break;

     case ChargingAlgori_IN_IRCalculation:
      if (ChargingAlgorithm_U.DataPipeline.VCU.isChargerConnected) {
        ChargingAlgorithm_DW.durationCounter_1_f = 0U;
      }

      if ((real_T)(uint32_T)((int32_T)ChargingAlgorithm_DW.durationCounter_1_f *
           100) >= ChargingAlgorithm_U.Thresholds.IRTransition_msec) {
        ChargingAlgorithm_DW.is_IRCalculation = ChargingAlgo_IN_NO_ACTIVE_CHILD;
        ChargingAlgorithm_DW.durationCounter_1 = 0U;
        ChargingAlgorithm_DW.is_c31_ChargingAlgorithm =
          ChargingAlgorithm_IN_Entry;
      } else {
        switch (ChargingAlgorithm_DW.is_IRCalculation) {
         case ChargingAlgorithm_IN_DropPulse:
          if (ChargingAlgorithm_DW.temporalCounter_i1 >=
              ChargingAlgorithm_U.Thresholds.IRPulseDropTime_sec * 10.0F) {
            ChargingAlgorithm_DW.is_IRCalculation =
              ChargingAlgorithm_IN_DropSense;
            ChargingAlgorithm_DW.temporalCounter_i1 = 0U;
          } else {
            ChargingAlgorithm_B.internalResistancePulseCurrent = 0.0;
          }
          break;

         case ChargingAlgorithm_IN_DropSense:
          if ((uint32_T)((int32_T)ChargingAlgorithm_DW.temporalCounter_i1 * 100)
              >= ChargingAlgorithm_U.Thresholds.IRTransition_msec) {
            ChargingAlgorithm_B.internalResistancePulseCurrent =
              ChargingAlgorithm_Y.RequestedCurrent_mA;
            ChargingAlgorithm_DW.is_IRCalculation = ChargingAlgorithm_IN_UpSense;
          } else {
            ChargingAlgorithm_B.secondVolt =
              ChargingAlgorithm_U.DataPipeline.TerminalVoltage_mV;
            ChargingAlgorithm_B.secondRequestedCurrent =
              ChargingAlgorithm_U.DataPipeline.Current_mA;
          }
          break;

         case ChargingAlgorith_IN_IRCalcBegin:
          if ((uint32_T)((int32_T)ChargingAlgorithm_DW.temporalCounter_i1 * 100)
              >= ChargingAlgorithm_U.Thresholds.IRTransition_msec) {
            ChargingAlgorithm_DW.is_IRCalculation =
              ChargingAlgorithm_IN_DropPulse;
            ChargingAlgorithm_DW.temporalCounter_i1 = 0U;
          } else {
            ChargingAlgorithm_B.firstRequestedCurrent =
              ChargingAlgorithm_U.DataPipeline.Current_mA;
            ChargingAlgorithm_B.firstVolt =
              ChargingAlgorithm_U.DataPipeline.TerminalVoltage_mV;
            ChargingAlgorithm_B.internalResistancePulseCurrent =
              ChargingAlgorithm_Y.RequestedCurrent_mA;
          }
          break;

         default:
          /* case IN_UpSense: */
          ChargingAlgorithm_B.IRComplete = true;
          break;
        }
      }
      break;

     default:
      /* case IN_IRLobby: */
      ChargingAlgorithm_DW.durationCounter_1 = 0U;
      ChargingAlgorithm_DW.is_c31_ChargingAlgorithm = ChargingAlgorithm_IN_Entry;
      break;
    }
  }

  if (ChargingAlgorithm_U.DataPipeline.VCU.isChargerConnected &&
      (ChargingAlgorithm_Y.ChargingState == IR_Measurement)) {
    ChargingAlgorithm_DW.durationCounter_1++;
  } else {
    ChargingAlgorithm_DW.durationCounter_1 = 0U;
  }

  if (!ChargingAlgorithm_U.DataPipeline.VCU.isChargerConnected) {
    ChargingAlgorithm_DW.durationCounter_1_f++;
  } else {
    ChargingAlgorithm_DW.durationCounter_1_f = 0U;
  }

  /* End of Chart: '<S1>/IRCalculation' */

  /* DataStoreWrite: '<S1>/Data Store Write' */
  ChargingAlgorithm_DW.IR_COMPLETE = ChargingAlgorithm_B.IRComplete;
  ChargingAlgorithm_Y.IR_Complete  = ChargingAlgorithm_DW.IR_COMPLETE;

  /* Switch: '<S1>/Switch1' */
  if (ChargingAlgorithm_Y.ChargingState > PseudoCharging) {
    /* Switch: '<S1>/Switch2' incorporates:
     *  Outport: '<Root>/RequestedCurrent_mA'
     */
    ChargingAlgorithm_Y.RequestedCurrent_mA =
      ChargingAlgorithm_B.internalResistancePulseCurrent;
  }

  /* End of Switch: '<S1>/Switch1' */

  /* Outport: '<Root>/internalResistance' incorporates:
   *  Product: '<S1>/Divide'
   *  Sum: '<S1>/Subtract'
   *  Sum: '<S1>/Subtract1'
   */
  ChargingAlgorithm_Y.internalResistance = (real_T)
    (ChargingAlgorithm_B.firstVolt - ChargingAlgorithm_B.secondVolt) / (real_T)
    (ChargingAlgorithm_B.firstRequestedCurrent -
     ChargingAlgorithm_B.secondRequestedCurrent);
}

/* Model initialize function */
void ChargingAlgorithm_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(ChargingAlgorithm_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &ChargingAlgorithm_B), 0,
                sizeof(B_ChargingAlgorithm_T));

  /* states (dwork) */
  (void) memset((void *)&ChargingAlgorithm_DW, 0,
                sizeof(DW_ChargingAlgorithm_T));

  /* external inputs */
  (void)memset(&ChargingAlgorithm_U, 0, sizeof(ExtU_ChargingAlgorithm_T));
  ChargingAlgorithm_U.CC_Outputs = ChargingAlgorithm_rtZCC_Outputs;

  /* external outputs */
  (void)memset(&ChargingAlgorithm_Y, 0, sizeof(ExtY_ChargingAlgorithm_T));
  ChargingAlgorithm_Y.ChargingState = NoCharging;

  /* Start for DataStoreMemory: '<S1>/Data Store Memory' */
  ChargingAlgorithm_DW.IR_COMPLETE = false;

  /* SystemInitialize for Chart: '<S1>/ChargingStateMachine' */
  ChargingAlgorithm_DW.is_active_c34_ChargingAlgorithm = 0U;
  ChargingAlgorithm_DW.is_c34_ChargingAlgorithm =
    ChargingAlgo_IN_NO_ACTIVE_CHILD;
  ChargingAlgorithm_DW.IRFastGuard = false;
  ChargingAlgorithm_DW.IRSlowGuard = false;

  /* SystemInitialize for Chart: '<S1>/ChargingAlgorithmProcessing' */
  ChargingAlgorithm_DW.is_NormalCharging = ChargingAlgo_IN_NO_ACTIVE_CHILD;
  ChargingAlgorithm_DW.is_FastCharging = ChargingAlgo_IN_NO_ACTIVE_CHILD;
  ChargingAlgorithm_DW.is_SlowCharging = ChargingAlgo_IN_NO_ACTIVE_CHILD;
  ChargingAlgorithm_DW.is_TrickleCharging = ChargingAlgo_IN_NO_ACTIVE_CHILD;
  ChargingAlgorithm_DW.is_active_c32_ChargingAlgorithm = 0U;
  ChargingAlgorithm_DW.is_c32_ChargingAlgorithm =
    ChargingAlgo_IN_NO_ACTIVE_CHILD;
  ChargingAlgorithm_B.Constant_K = 0.0;
  ChargingAlgorithm_B.cvModeActivated = false;
  ChargingAlgorithm_B.trickleChargingEnabled = false;

  /* SystemInitialize for Chart: '<S1>/IRCalculation' */
  ChargingAlgorithm_DW.is_IRCalculation = ChargingAlgo_IN_NO_ACTIVE_CHILD;
  ChargingAlgorithm_DW.temporalCounter_i1 = 0U;
  ChargingAlgorithm_DW.is_active_c31_ChargingAlgorithm = 0U;
  ChargingAlgorithm_DW.is_c31_ChargingAlgorithm =
    ChargingAlgo_IN_NO_ACTIVE_CHILD;
  ChargingAlgorithm_B.internalResistancePulseCurrent = 0.0;
  ChargingAlgorithm_B.secondRequestedCurrent = 0;
  ChargingAlgorithm_B.firstRequestedCurrent = 0;
  ChargingAlgorithm_B.secondVolt = 0;
  ChargingAlgorithm_B.firstVolt = 0;
  ChargingAlgorithm_B.IRComplete = false;
}

/* Model terminate function */
void ChargingAlgorithm_terminate(void)
{
  /* (no terminate code required) */
}
