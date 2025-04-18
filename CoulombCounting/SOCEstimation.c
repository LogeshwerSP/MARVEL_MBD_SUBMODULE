/*
 * SOCEstimation.c
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

#include "SOCEstimation.h"
#include "rtwtypes.h"
#include "SOCEstimation_types.h"
#include "SOC_ReadFromEEPROM.h"
#include <math.h>
#include "SOCEstimation_private.h"
#include "multiword_types.h"
#include <string.h>
#include "zero_crossing_types.h"

/* Named constants for Chart: '<S6>/SOC_Estimator' */
#define SOCEsti_IN_Recalibrate_Charging ((uint8_T)4U)
#define SOCEstimatio_IN_CoulombCounting ((uint8_T)1U)
#define SOCEstimatio_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define SOCEstimatio_IN_Vehicle_at_Rest ((uint8_T)5U)
#define SOCEstimation_IN_HybridCounting ((uint8_T)2U)
#define SOCEstimation_IN_PseudoLatching ((uint8_T)3U)

/* Named constants for Chart: '<S8>/IntegCurrent' */
#define SOCEstimat_IN_IntegratedCurrent ((uint8_T)1U)
#define SOCEstimatio_IN_IntegratorReset ((uint8_T)2U)

/* Block signals (default storage) */
B_SOCEstimation_T SOCEstimation_B;

/* Block states (default storage) */
DW_SOCEstimation_T SOCEstimation_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_SOCEstimation_T SOCEstimation_PrevZCX;

/* External inputs (root inport signals with default storage) */
ExtU_SOCEstimation_T SOCEstimation_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_SOCEstimation_T SOCEstimation_Y;

/* Real-time model */
static RT_MODEL_SOCEstimation_T SOCEstimation_M_;
RT_MODEL_SOCEstimation_T *const SOCEstimation_M = &SOCEstimation_M_;

/* Forward declaration for local functions */
static void SOCEstimation_eml_find(const boolean_T x[101], int32_T i_data[],
  int32_T i_size[2]);
static boolean_T SOCEstimation_ifWhileCond(const boolean_T x_data[], const
  int32_T x_size[2]);
static real_T SOCEstimation_mrdiv(const real_T A_data[], const int32_T A_size[2],
  const real_T B_data[], const int32_T B_size[2]);
static real_T SOCEstimation_EKFController(int32_T current, int32_T terminalV,
  real_T loopTime, real_T mode, int32_T maxCapUsable, real32_T processNoise,
  real32_T measurementNoise, real_T cellIR, int32_T initSoC, boolean_T resetFlag,
  const real_T socData[101], const real_T ocvData[101]);
const CC_OutputsBus SOCEstimation_rtZCC_OutputsBus = { 0,/* Total_CapacityRemains_mAh */
  0,                                   /* SOC_cpct */
  Vehicle_at_Rest,                     /* CC_State */
  0,                                   /* MaxUsableCapacity_mAh */
  0.0F,                                /* cycleCount */
  0.0F,                                /* SOH_pct */
  0.0F,                                /* SoH2 */
  false                                /* EKF_resetTimer */
};

real_T sMultiWord2Double(const uint32_T u1[], int32_T n1, int32_T e1)
{
  real_T y;
  int32_T exp_0;
  int32_T i;
  y = 0.0;
  exp_0 = e1;
  if ((u1[n1 - 1] & 2147483648U) != 0U) {
    uint32_T cb;
    cb = 1U;
    for (i = 0; i < n1; i++) {
      uint32_T u1i;
      u1i = ~u1[i];
      cb += u1i;
      y -= ldexp(cb, exp_0);
      cb = (uint32_T)(cb < u1i);
      exp_0 += 32;
    }
  } else {
    for (i = 0; i < n1; i++) {
      y += ldexp(u1[i], exp_0);
      exp_0 += 32;
    }
  }

  return y;
}

void sMultiWordMul_cc(const uint32_T u1[], int32_T n1, const uint32_T u2[], int32_T
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

real32_T sMultiWord2Single_cc(const uint32_T u1[], int32_T n1, int32_T e1)
{
  int32_T exp_1;
  int32_T i;
  real32_T y;
  y = 0.0F;
  exp_1 = e1;
  if ((u1[n1 - 1] & 2147483648U) != 0U) {
    uint32_T cb;
    cb = 1U;
    for (i = 0; i < n1; i++) {
      uint32_T u1i;
      u1i = ~u1[i];
      cb += u1i;
      y -= (real32_T)ldexp((real32_T)cb, exp_1);
      cb = (uint32_T)(cb < u1i);
      exp_1 += 32;
    }
  } else {
    for (i = 0; i < n1; i++) {
      y += (real32_T)ldexp((real32_T)u1[i], exp_1);
      exp_1 += 32;
    }
  }

  return y;
}

void MultiWordSignedWrap_cc(const uint32_T u1[], int32_T n1, uint32_T n2, uint32_T
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

void sMultiWordShl_cc(const uint32_T u1[], int32_T n1, uint32_T n2, uint32_T y[],
                   int32_T n)
{
  int32_T i;
  int32_T nb;
  int32_T nc;
  uint32_T u1i;
  uint32_T ys;
  nb = (int32_T)(n2 >> 5);
  ys = (u1[n1 - 1] & 2147483648U) != 0U ? MAX_uint32_T : 0U;
  nc = nb > n ? n : nb;
  u1i = 0U;
  for (i = 0; i < nc; i++) {
    y[i] = 0U;
  }

  if (nb < n) {
    uint32_T nl;
    nl = n2 - ((uint32_T)nb << 5);
    nb += n1;
    if (nb > n) {
      nb = n;
    }

    nb -= i;
    if (nl > 0U) {
      for (nc = 0; nc < nb; nc++) {
        uint32_T yi;
        yi = u1i >> (32U - nl);
        u1i = u1[nc];
        y[i] = u1i << nl | yi;
        i++;
      }

      if (i < n) {
        y[i] = u1i >> (32U - nl) | ys << nl;
        i++;
      }
    } else {
      for (nc = 0; nc < nb; nc++) {
        y[i] = u1[nc];
        i++;
      }
    }
  }

  while (i < n) {
    y[i] = ys;
    i++;
  }
}

void sLong2MultiWord_cc(int32_T u, uint32_T y[], int32_T n)
{
  int32_T i;
  uint32_T yi;
  y[0] = (uint32_T)u;
  yi = u < 0 ? MAX_uint32_T : 0U;
  for (i = 1; i < n; i++) {
    y[i] = yi;
  }
}

void mul_wide_s32_cc(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi, uint32_T
                  *ptrOutBitsLo)
{
  uint32_T absIn0;
  uint32_T absIn1;
  uint32_T in0Hi;
  uint32_T in0Lo;
  uint32_T in1Hi;
  uint32_T productHiLo;
  uint32_T productLoHi;
  absIn0 = in0 < 0 ? ~(uint32_T)in0 + 1U : (uint32_T)in0;
  absIn1 = in1 < 0 ? ~(uint32_T)in1 + 1U : (uint32_T)in1;
  in0Hi = absIn0 >> 16U;
  in0Lo = absIn0 & 65535U;
  in1Hi = absIn1 >> 16U;
  absIn0 = absIn1 & 65535U;
  productHiLo = in0Hi * absIn0;
  productLoHi = in0Lo * in1Hi;
  absIn0 *= in0Lo;
  absIn1 = 0U;
  in0Lo = (productLoHi << 16U) + absIn0;
  if (in0Lo < absIn0) {
    absIn1 = 1U;
  }

  absIn0 = in0Lo;
  in0Lo += productHiLo << 16U;
  if (in0Lo < absIn0) {
    absIn1++;
  }

  absIn0 = (((productLoHi >> 16U) + (productHiLo >> 16U)) + in0Hi * in1Hi) +
    absIn1;
  if ((in0 != 0) && ((in1 != 0) && ((in0 > 0) != (in1 > 0)))) {
    absIn0 = ~absIn0;
    in0Lo = ~in0Lo;
    in0Lo++;
    if (in0Lo == 0U) {
      absIn0++;
    }
  }

  *ptrOutBitsHi = absIn0;
  *ptrOutBitsLo = in0Lo;
}

int32_T mul_s32_sat_cc(int32_T a, int32_T b)
{
  int32_T result;
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_s32_cc(a, b, &u32_chi, &u32_clo);
  if (((int32_T)u32_chi > 0) || ((u32_chi == 0U) && (u32_clo >= 2147483648U))) {
    result = MAX_int32_T;
  } else if (((int32_T)u32_chi < -1) || (((int32_T)u32_chi == -1) && (u32_clo <
               2147483648U))) {
    result = MIN_int32_T;
  } else {
    result = (int32_T)u32_clo;
  }

  return result;
}

real_T rt_roundd(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Function for Chart: '<S6>/SOC_Estimator' */
static void SOCEstimation_eml_find(const boolean_T x[101], int32_T i_data[],
  int32_T i_size[2])
{
  int32_T idx;
  int32_T ii;
  boolean_T exitg1;
  idx = 0;
  i_size[0] = 1;
  i_size[1] = 1;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii < 101)) {
    if (x[ii]) {
      idx = 1;
      i_data[0] = ii + 1;
      exitg1 = true;
    } else {
      ii++;
    }
  }

  if (idx == 0) {
    i_size[0] = 1;
    i_size[1] = 0;
  }
}

/* Function for Chart: '<S6>/SOC_Estimator' */
static boolean_T SOCEstimation_ifWhileCond(const boolean_T x_data[], const
  int32_T x_size[2])
{
  boolean_T y;
  y = (x_size[1] != 0);
  if (y) {
    int32_T k;
    boolean_T exitg1;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x_size[1] - 1)) {
      if (!x_data[0]) {
        y = false;
        exitg1 = true;
      } else {
        k = 1;
      }
    }
  }

  return y;
}

/* Function for Chart: '<S6>/SOC_Estimator' */
static real_T SOCEstimation_mrdiv(const real_T A_data[], const int32_T A_size[2],
  const real_T B_data[], const int32_T B_size[2])
{
  real_T Y;
  if ((A_size[1] == 0) || (B_size[1] == 0)) {
    Y = 0.0;
  } else {
    Y = A_data[0] / B_data[0];
  }

  return Y;
}

/*
 * Function for Chart: '<S6>/SOC_Estimator'
 * function socEst = EKFController(current, terminalV, loopTime, mode, maxCapUsable, ...
 *                                 processNoise, measurementNoise, cellIR, initSoC, ...
 *                                 resetFlag, socData, ocvData)
 */
static real_T SOCEstimation_EKFController(int32_T current, int32_T terminalV,
  real_T loopTime, real_T mode, int32_T maxCapUsable, real32_T processNoise,
  real32_T measurementNoise, real_T cellIR, int32_T initSoC, boolean_T resetFlag,
  const real_T socData[101], const real_T ocvData[101])
{
  real_T H;
  real_T K;
  real_T P_pred;
  real_T ocv_pred_data = 0;
  real_T socData_data;
  real_T socEst;
  real_T x_pred;
  real_T x_pred_tmp;
  int32_T c_size[2];
  int32_T c_size_0[2];
  int32_T socData_size[2];
  int32_T x_pred_size[2];
  int32_T c;
  int32_T c_data;
  int32_T ocv_pred_size_idx_1;
  boolean_T socData_0[101];
  boolean_T c_data_0;

  /* MATLAB Function 'EKFController': '<S11>:221' */
  /* '<S11>:221:6' if isempty(x) */
  /* '<S11>:221:13' if resetFlag */
  if (resetFlag) {
    /* '<S11>:221:14' x = 0; */
    SOCEstimation_DW.x = 0.0;

    /* '<S11>:221:15' EKF_P = double(1e-3); */
    SOCEstimation_DW.EKF_P = 0.001;

    /* '<S11>:221:16' H_prev = 0; */
    SOCEstimation_DW.H_prev = 0.0;

    /* '<S11>:221:17' filteredVoltage = 0; */
    SOCEstimation_DW.filteredVoltage = 0.0;

    /* '<S11>:221:18' else */
    /* '<S11>:221:19' if mode == 1 */
  } else if (mode == 1.0) {
    /* '<S11>:221:20' x = double(initSoC); */
    SOCEstimation_DW.x = initSoC;

    /* '<S11>:221:21' EKF_P = double(1e-3); */
    SOCEstimation_DW.EKF_P = 0.001;

    /* '<S11>:221:22' filteredVoltage = double(terminalV); */
    SOCEstimation_DW.filteredVoltage = terminalV;
  } else {
    /* '<S11>:221:23' else */
    /* '<S11>:221:25' dt_hr = double(loopTime) / 3600000; */
    /* '<S11>:221:26' delta_x = (double(current) * dt_hr / double(maxCapUsable)) * 100; */
    /* '<S11>:221:27' x_pred = x + delta_x; */
    /* '<S11>:221:28' x_pred = max(0, min(100, x_pred)); */
    x_pred_tmp = loopTime / 3.6E+6 * (real_T)current / (real_T)maxCapUsable *
      100.0 + SOCEstimation_DW.x;
    x_pred = fmax(0.0, fmin(100.0, x_pred_tmp));

    /* '<S11>:221:29' P_pred = double(EKF_P + processNoise); */
    P_pred = (real32_T)SOCEstimation_DW.EKF_P + processNoise;

    /* '<S11>:221:32' if x_pred <= socData(1) */
    if (x_pred <= socData[0]) {
      /* '<S11>:221:33' ocv_pred = ocvData(1); */
      ocv_pred_size_idx_1 = 1;
      ocv_pred_data = ocvData[0];

      /* '<S11>:221:49' H = (ocvData(2) - ocvData(1)) / (socData(2) - socData(1)) + epsilon; */
      H = (ocvData[1] - ocvData[0]) / (socData[1] - socData[0]) + 1.0E-6;
    } else {
      if (x_pred >= socData[100]) {
        /* '<S11>:221:34' elseif x_pred >= socData(end) */
        /* '<S11>:221:35' ocv_pred = ocvData(end); */
        ocv_pred_size_idx_1 = 1;
        ocv_pred_data = ocvData[100];
      } else {
        /* '<S11>:221:36' else */
        /* '<S11>:221:37' idx = find(socData >= x_pred, 1); */
        for (c = 0; c < 101; c++) {
          socData_0[c] = (socData[c] >= x_pred);
        }

        SOCEstimation_eml_find(socData_0, &c_data, c_size);

        /* '<S11>:221:38' if idx > 1 */
        c_size_0[0] = 1;
        c_size_0[1] = c_size[1];
        if (c_size[1] - 1 >= 0) {
          c_data_0 = (c_data > 1);
        }

        if (SOCEstimation_ifWhileCond(&c_data_0, c_size_0)) {
          /* '<S11>:221:39' t = (x_pred - socData(idx-1)) / (socData(idx) - socData(idx-1)); */
          x_pred_size[0] = 1;
          x_pred_size[1] = c_size[1];
          socData_size[0] = 1;
          socData_size[1] = c_size[1];
          if (c_size[1] - 1 >= 0) {
            H = socData[c_data - 2];
            K = x_pred - H;
            socData_data = socData[c_data - 1] - H;
          }

          /* '<S11>:221:40' ocv_pred = ocvData(idx-1) + t * (ocvData(idx) - ocvData(idx-1)); */
          ocv_pred_size_idx_1 = c_size[1];
          if (c_size[1] - 1 >= 0) {
            H = ocvData[c_data - 2];
            ocv_pred_data = (ocvData[c_data - 1] - H) * SOCEstimation_mrdiv(&K,
              x_pred_size, &socData_data, socData_size) + H;
          }
        } else {
          /* '<S11>:221:41' else */
          /* '<S11>:221:42' ocv_pred = ocvData(idx); */
          ocv_pred_size_idx_1 = c_size[1];
          if (c_size[1] - 1 >= 0) {
            ocv_pred_data = ocvData[c_data - 1];
          }
        }
      }

      if (x_pred >= socData[100]) {
        /* '<S11>:221:50' elseif x_pred >= socData(end) */
        /* '<S11>:221:51' H = (ocvData(end) - ocvData(end-1)) / (socData(end) - socData(end-1)) + epsilon; */
        H = (ocvData[100] - ocvData[99]) / (socData[100] - socData[99]) + 1.0E-6;
      } else {
        /* '<S11>:221:52' else */
        /* '<S11>:221:53' idx = find(socData >= x_pred, 1); */
        for (c = 0; c < 101; c++) {
          socData_0[c] = (socData[c] >= x_pred);
        }

        SOCEstimation_eml_find(socData_0, &c_data, c_size);

        /* '<S11>:221:54' if idx > 1 */
        c_size_0[0] = 1;
        c_size_0[1] = c_size[1];
        if (c_size[1] - 1 >= 0) {
          c_data_0 = (c_data > 1);
        }

        if (SOCEstimation_ifWhileCond(&c_data_0, c_size_0)) {
          /* '<S11>:221:55' H = (ocvData(idx) - ocvData(idx-1)) / (socData(idx) - socData(idx-1)) + epsilon; */
          x_pred_size[0] = 1;
          x_pred_size[1] = c_size[1];
          socData_size[0] = 1;
          socData_size[1] = c_size[1];
          if (c_size[1] - 1 >= 0) {
            K = ocvData[c_data - 1] - ocvData[c_data - 2];
            socData_data = socData[c_data - 1] - socData[c_data - 2];
          }

          H = SOCEstimation_mrdiv(&K, x_pred_size, &socData_data, socData_size)
            + 1.0E-6;
        } else {
          /* '<S11>:221:56' else */
          /* '<S11>:221:57' H = epsilon; */
          H = 1.0E-6;
        }
      }
    }

    /* '<S11>:221:47' epsilon = 1e-6; */
    /* '<S11>:221:48' if x_pred <= socData(1) */
    /* '<S11>:221:62' alpha_LPF = 0.8; */
    /* '<S11>:221:63' H_filtered = alpha_LPF * H_prev + (1 - alpha_LPF) * H; */
    SOCEstimation_DW.H_prev = 0.8 * SOCEstimation_DW.H_prev +
      0.19999999999999996 * H;

    /* '<S11>:221:64' H_prev = H_filtered; */
    /* '<S11>:221:67' ir_drop = (double(current) * cellIR) / 1000; */
    H = (real_T)current * cellIR / 1000.0;

    /* '<S11>:221:68' v_ocv_pred = double(ocv_pred) - ir_drop; */
    ocv_pred_size_idx_1--;
    for (c = 0; c <= ocv_pred_size_idx_1; c++) {
      ocv_pred_data -= H;
    }

    /* '<S11>:221:71' alpha_voltage_LPF = 0.7; */
    /* '<S11>:221:72' filteredVoltage = alpha_voltage_LPF * filteredVoltage + (1 - alpha_voltage_LPF) * double(terminalV); */
    SOCEstimation_DW.filteredVoltage = 0.7 * SOCEstimation_DW.filteredVoltage +
      0.30000000000000004 * (real_T)terminalV;

    /* '<S11>:221:75' load_variation = abs(current); */
    /* '<S11>:221:76' adaptiveNoise = double(measurementNoise) + min(1e4, max(1e-3, 1 / (abs(H_filtered) + 1e-4))) + (0.1 * load_variation); */
    /* '<S11>:221:79' denominator = H_filtered^2 * P_pred + adaptiveNoise; */
    H = fabs(SOCEstimation_DW.H_prev);
    if (current < 0) {
      if (current <= MIN_int32_T) {
        c = MAX_int32_T;
      } else {
        c = -current;
      }
    } else {
      c = current;
    }

    K = rt_roundd((fmax(0.001, 1.0 / (H + 0.0001)) + measurementNoise) +
                  rt_roundd(0.1 * (real_T)c));
    if (K < 2.147483648E+9) {
      if (K >= -2.147483648E+9) {
        c = (int32_T)K;
      } else {
        c = MIN_int32_T;
      }
    } else {
      c = MAX_int32_T;
    }

    K = rt_roundd(SOCEstimation_DW.H_prev * SOCEstimation_DW.H_prev * P_pred +
                  (real_T)c);
    if (K < 2.147483648E+9) {
      if (K >= -2.147483648E+9) {
        c = (int32_T)K;
      } else {
        c = MIN_int32_T;
      }
    } else {
      c = MAX_int32_T;
    }

    /* '<S11>:221:80' if abs(denominator) < 1e-6 */
    if (c < 0) {
      if (c <= MIN_int32_T) {
        ocv_pred_size_idx_1 = MAX_int32_T;
      } else {
        ocv_pred_size_idx_1 = -c;
      }
    } else {
      ocv_pred_size_idx_1 = c;
    }

    if (ocv_pred_size_idx_1 < 1.0E-6) {
      /* '<S11>:221:81' K = 0.1; */
      K = 0.1;
    } else {
      /* '<S11>:221:82' else */
      /* '<S11>:221:83' K = double(double(P_pred * H_filtered) / denominator); */
      K = rt_roundd(P_pred * SOCEstimation_DW.H_prev / (real_T)c);
      if (K < 2.147483648E+9) {
        if (K < -2.147483648E+9) {
          K = -2.147483648E+9;
        }
      } else {
        K = 2.147483647E+9;
      }
    }

    /* '<S11>:221:87' vDiff = double(filteredVoltage) - v_ocv_pred(1); */
    /* '<S11>:221:88' x_corrected = x_pred + K * vDiff; */
    /* '<S11>:221:89' x_corrected = max(0, min(100, x_corrected)); */
    /* '<S11>:221:92' EKF_P = double((1 - K * H_filtered) * P_pred); */
    SOCEstimation_DW.EKF_P = (1.0 - K * SOCEstimation_DW.H_prev) * P_pred;

    /* '<S11>:221:95' alpha_hybrid = max(0.1, min(0.9, abs(H_filtered))); */
    P_pred = fmax(0.1, fmin(0.9, H));

    /* '<S11>:221:96' x = alpha_hybrid * x_corrected + (1 - alpha_hybrid) * (x + delta_x); */
    SOCEstimation_DW.x = fmax(0.0, fmin(100.0, (SOCEstimation_DW.filteredVoltage
      - ocv_pred_data) * K + x_pred)) * P_pred + (1.0 - P_pred) * x_pred_tmp;

    /* '<S11>:221:97' x = max(0, min(100, x)); */
    SOCEstimation_DW.x = fmax(0.0, fmin(100.0, SOCEstimation_DW.x));
  }

  /* '<S11>:221:101' socEst = x; */
  socEst = SOCEstimation_DW.x;
  return socEst;
}

/* Model step function */
void SOCEstimation_step(void)
{
  int64m_T tmp_0;
  int64m_T tmp_3;
  int64m_T tmp_4;
  int64m_T tmp_5;
  real_T coefficients[5];
  real_T rtb_SOC_ChargeDischarge;
  int32_T DataTypeConversion3;
  int32_T rtb_Effectiveusablecapacity;
  int32_T rtb_TotalSOCRemains_cpct;
  int32_T tmp;
  real32_T rtb_Multiply1;
  real32_T rtb_weight1;
  uint32_T tmp_1;
  uint32_T tmp_2;
  boolean_T rtb_ChargerconnectedandLatchf_0;
  boolean_T rtb_ChargerconnectedandLatchf_1;
  boolean_T rtb_ChargerconnectedandLatchfla;
  boolean_T rtb_Vdel170mV;
  boolean_T rtb_iflastlatchcyclecurrentcycl;
  boolean_T rtb_vmax3535;

  /* MATLAB Function: '<S1>/SOC_ReadFromEEPROM' */
  SOCEstimatio_SOC_ReadFromEEPROM(&SOCEstimation_B.sf_SOC_ReadFromEEPROM);

  /* Outputs for Atomic SubSystem: '<S1>/SoH calculation' */
  /* RelationalOperator: '<S16>/Relational Operator1' incorporates:
   *  Delay: '<S1>/Delay2'
   *  Inport: '<Root>/CC_Inputs'
   *  Sum: '<S16>/Subtract'
   */
  rtb_iflastlatchcyclecurrentcycl = (SOCEstimation_DW.Delay2_DSTATE -
    SOCEstimation_U.CC_Inputs.prevLatchtCycleCountFromMem >=
    SOCEstimation_U.CC_Inputs.cycleCountThreshold);

  /* RelationalOperator: '<S16>/Relational Operator' incorporates:
   *  Constant: '<S16>/Constant'
   *  Inport: '<Root>/CC_Inputs'
   */
  rtb_vmax3535 = (SOCEstimation_U.CC_Inputs.prevLatchtCycleCountFromMem >= 2.0F);

  /* Logic: '<S16>/AND1' incorporates:
   *  Delay: '<S1>/Delay1'
   */
  rtb_ChargerconnectedandLatchfla = (SOCEstimation_B.calcSoH2 && rtb_vmax3535);

  /* Logic: '<S16>/OR' incorporates:
   *  Logic: '<S16>/NOT'
   */
  rtb_vmax3535 = (rtb_ChargerconnectedandLatchfla || (!rtb_vmax3535));

  /* Switch: '<S16>/Switch1' incorporates:
   *  Delay: '<S1>/Delay3'
   *  Gain: '<S16>/Gain'
   *  Inport: '<Root>/CC_Inputs'
   *  Product: '<S16>/Divide'
   */
  if (rtb_ChargerconnectedandLatchfla) {
    rtb_Multiply1 = (real32_T)SOCEstimation_B.TotalCapacityRemains_mAh /
      (real32_T)SOCEstimation_U.CC_Inputs.InstalledCapacity_mAh * 100.0F;
  } else {
    rtb_Multiply1 = SOCEstimation_U.CC_Inputs.SoH2Memory;
  }

  /* End of Switch: '<S16>/Switch1' */

  /* Saturate: '<S16>/Saturation' */
  if (rtb_Multiply1 > 100.0F) {
    rtb_Multiply1 = 100.0F;
  } else if (rtb_Multiply1 < 50.0F) {
    rtb_Multiply1 = 50.0F;
  }

  /* End of Saturate: '<S16>/Saturation' */

  /* Logic: '<S17>/OR' incorporates:
   *  Logic: '<S4>/OR'
   */
  rtb_ChargerconnectedandLatchfla = (rtb_iflastlatchcyclecurrentcycl ||
    rtb_vmax3535);

  /* Outputs for Triggered SubSystem: '<S17>/SoH1 calculation' incorporates:
   *  TriggerPort: '<S20>/Trigger'
   */
  if (rtb_ChargerconnectedandLatchfla &&
      (SOCEstimation_PrevZCX.SoH1calculation_Trig_ZCE != POS_ZCSIG)) {
    /* MATLAB Function: '<S20>/MATLAB Function' incorporates:
     *  DataTypeConversion: '<S17>/Data Type Conversion'
     *  Delay: '<S1>/Delay2'
     *  Inport: '<Root>/CC_Inputs'
     */
    /* MATLAB Function 'SOCEstimation/SoH calculation/Subsystem/SoH1 calculation/MATLAB Function': '<S22>:1' */
    /* '<S22>:1:4' y = calculateSoH(cycleCount, A, B, C, D, E); */
    /* 'calculateSoH:4' coefficients = [ A, B, C, D, E]; */
    coefficients[0] = SOCEstimation_U.CC_Inputs.Coefficients.elementZero;
    coefficients[1] = SOCEstimation_U.CC_Inputs.Coefficients.elementOne;
    coefficients[2] = SOCEstimation_U.CC_Inputs.Coefficients.elementTwo;
    coefficients[3] = SOCEstimation_U.CC_Inputs.Coefficients.elementThree;
    coefficients[4] = SOCEstimation_U.CC_Inputs.Coefficients.elementFour;

    /* 'calculateSoH:5' y = 0.0; */
    rtb_SOC_ChargeDischarge = 0.0;

    /* 'calculateSoH:7' for i = 1:length(coefficients) */
    for (rtb_Effectiveusablecapacity = 0; rtb_Effectiveusablecapacity < 5;
         rtb_Effectiveusablecapacity++) {
      /* 'calculateSoH:8' y = y + coefficients(i) * cycleCount^(5 - (i)); */
      rtb_SOC_ChargeDischarge += pow(SOCEstimation_DW.Delay2_DSTATE, 5.0 -
        ((real_T)rtb_Effectiveusablecapacity + 1.0)) *
        coefficients[rtb_Effectiveusablecapacity];
    }

    /* 'calculateSoH:10' fprintf('For cycleCount = %.3f, y = %.3f\n', cycleCount, y); */
    printf("For cycleCount = %.3f, y = %.3f\n", (real_T)
           SOCEstimation_DW.Delay2_DSTATE, rtb_SOC_ChargeDischarge);
    fflush(stdout);

    /* Saturate: '<S20>/Saturation' incorporates:
     *  MATLAB Function: '<S20>/MATLAB Function'
     */
    if (rtb_SOC_ChargeDischarge > 100.0) {
      rtb_SOC_ChargeDischarge = 100.0;
    } else if (rtb_SOC_ChargeDischarge < 0.0) {
      rtb_SOC_ChargeDischarge = 0.0;
    }

    /* End of Saturate: '<S20>/Saturation' */
    /* DataTypeConversion: '<S20>/Data Type Conversion' */
    SOCEstimation_B.DataTypeConversion = (real32_T)rtb_SOC_ChargeDischarge;
  }

  SOCEstimation_PrevZCX.SoH1calculation_Trig_ZCE =
    rtb_ChargerconnectedandLatchfla;

  /* End of Logic: '<S17>/OR' */
  /* End of Outputs for SubSystem: '<S17>/SoH1 calculation' */

  /* Outputs for Triggered SubSystem: '<S17>/SoH calculation' incorporates:
   *  TriggerPort: '<S19>/Trigger'
   */
  if (rtb_vmax3535 && (SOCEstimation_PrevZCX.SoHcalculation_Trig_ZCE !=
                       POS_ZCSIG)) {
    /* Switch: '<S19>/Switch' incorporates:
     *  Abs: '<S19>/Abs'
     *  Constant: '<S21>/Constant2'
     *  Inport: '<Root>/CC_Inputs'
     *  Product: '<S21>/Product'
     *  Product: '<S21>/Product1'
     *  RelationalOperator: '<S19>/GreaterThan'
     *  Sum: '<S19>/Subtract2'
     *  Sum: '<S21>/Add1'
     *  Sum: '<S21>/Subtract'
     */
    if (fabsf(rtb_Multiply1 - SOCEstimation_B.DataTypeConversion) >
        SOCEstimation_U.CC_Inputs.SoHThresh) {
      /* Product: '<S21>/Divide2' incorporates:
       *  Sum: '<S21>/Add'
       */
      rtb_weight1 = SOCEstimation_B.DataTypeConversion /
        (SOCEstimation_B.DataTypeConversion + rtb_Multiply1);
      rtb_SOC_ChargeDischarge = (1.0 - rtb_weight1) * rtb_Multiply1 +
        SOCEstimation_B.DataTypeConversion * rtb_weight1;
    } else {
      rtb_SOC_ChargeDischarge = SOCEstimation_B.DataTypeConversion;
    }

    /* End of Switch: '<S19>/Switch' */

    /* Saturate: '<S19>/Saturation' */
    if (rtb_SOC_ChargeDischarge > 100.0) {
      rtb_SOC_ChargeDischarge = 100.0;
    } else if (rtb_SOC_ChargeDischarge < 0.0) {
      rtb_SOC_ChargeDischarge = 0.0;
    }

    /* End of Saturate: '<S19>/Saturation' */

    /* Switch: '<S19>/Switch1' incorporates:
     *  Inport: '<Root>/CC_Inputs'
     *  RelationalOperator: '<S19>/Relational Operator'
     *  RelationalOperator: '<S19>/Relational Operator2'
     *  Sum: '<S19>/Add'
     *  Switch: '<S19>/Switch2'
     */
    if (rtb_SOC_ChargeDischarge <= SOCEstimation_U.CC_Inputs.SoHMemory) {
      /* Switch: '<S19>/Switch1' */
      SOCEstimation_B.Switch1 = rtb_SOC_ChargeDischarge;
    } else if (rtb_SOC_ChargeDischarge <= SOCEstimation_U.CC_Inputs.SoHMemory +
               SOCEstimation_U.CC_Inputs.SoHTolerance) {
      /* Switch: '<S19>/Switch2' incorporates:
       *  Switch: '<S19>/Switch1'
       */
      SOCEstimation_B.Switch1 = rtb_SOC_ChargeDischarge;
    } else {
      /* Switch: '<S19>/Switch1' incorporates:
       *  Sum: '<S19>/Add1'
       *  Switch: '<S19>/Switch2'
       */
      SOCEstimation_B.Switch1 = rtb_SOC_ChargeDischarge +
        SOCEstimation_U.CC_Inputs.SoHTolerance;
    }

    /* End of Switch: '<S19>/Switch1' */
  }

  SOCEstimation_PrevZCX.SoHcalculation_Trig_ZCE = rtb_vmax3535;

  /* End of Outputs for SubSystem: '<S17>/SoH calculation' */

  /* Switch: '<S4>/Switch' incorporates:
   *  Inport: '<Root>/CC_Inputs'
   */
  if (rtb_ChargerconnectedandLatchfla) {
    /* Switch: '<S17>/Switch1' incorporates:
     *  Inport: '<Root>/CC_Inputs'
     *  Inport: '<Root>/DataPipeline'
     *  Logic: '<S17>/AND'
     *  RelationalOperator: '<S17>/Relational Operator'
     *  RelationalOperator: '<S17>/Relational Operator1'
     *  Selector: '<S1>/Selector'
     */
    if ((SOCEstimation_U.DataPipeline.TemperatureSenseBus[0].TemperatureDelta_C <=
         SOCEstimation_U.CC_Inputs.TempDeltaAllowed) &&
        (SOCEstimation_U.DataPipeline.TemperatureSenseBus[0].T_min >=
         SOCEstimation_U.CC_Inputs.TempThreshForSoHCalib)) {
      /* Switch: '<S17>/Switch' */
      if (rtb_iflastlatchcyclecurrentcycl) {
        rtb_SOC_ChargeDischarge = SOCEstimation_B.DataTypeConversion;
      } else {
        rtb_SOC_ChargeDischarge = SOCEstimation_B.Switch1;
      }

      /* End of Switch: '<S17>/Switch' */
    } else {
      rtb_SOC_ChargeDischarge = rtb_Multiply1;
    }

    /* End of Switch: '<S17>/Switch1' */

    /* Saturate: '<S17>/Saturation' */
    if (rtb_SOC_ChargeDischarge > 100.0) {
      rtb_weight1 = 100.0F;
    } else if (rtb_SOC_ChargeDischarge < 50.0) {
      rtb_weight1 = 50.0F;
    } else {
      rtb_weight1 = (real32_T)rtb_SOC_ChargeDischarge;
    }

    /* End of Saturate: '<S17>/Saturation' */
  } else {
    rtb_weight1 = SOCEstimation_U.CC_Inputs.SoHMemory;
  }

  /* End of Switch: '<S4>/Switch' */

  /* Product: '<S18>/Product4' incorporates:
   *  Constant: '<S18>/Constant3'
   *  Inport: '<Root>/CC_Inputs'
   *  Product: '<S18>/Divide3'
   */
  rtb_SOC_ChargeDischarge = (real_T)
    SOCEstimation_U.CC_Inputs.InstalledCapacity_mAh / 100.0 * rtb_weight1;

  /* DataTypeConversion: '<S18>/Data Type Conversion1' */
  rtb_Effectiveusablecapacity = (int32_T)floor(rtb_SOC_ChargeDischarge);

  /* End of Outputs for SubSystem: '<S1>/SoH calculation' */

  /* Outputs for Atomic SubSystem: '<S1>/SOC_Calc' */
  /* Sum: '<S7>/Add1' incorporates:
   *  Delay: '<S7>/Delay1'
   *  Inport: '<Root>/Current_mA'
   */
  /* MATLAB Function 'SOCEstimation/SOC_Calc/EKFStateChangeChecker/MATLAB Function': '<S13>:1' */
  /* '<S13>:1:3' if stable == 1 */
  DataTypeConversion3 = SOCEstimation_U.Current_mA -
    SOCEstimation_DW.Delay1_DSTATE;

  /* Sum: '<S7>/Add' incorporates:
   *  Delay: '<S7>/Delay'
   *  Inport: '<Root>/DataPipeline'
   *  SignalConversion generated from: '<S2>/Bus Selector3'
   */
  rtb_TotalSOCRemains_cpct = SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min
    - SOCEstimation_DW.Delay_DSTATE_i;

  /* Abs: '<S7>/Abs' */
  if (DataTypeConversion3 < 0) {
    DataTypeConversion3 = -DataTypeConversion3;
  }

  /* Abs: '<S7>/Abs1' */
  if (rtb_TotalSOCRemains_cpct < 0) {
    rtb_TotalSOCRemains_cpct = -rtb_TotalSOCRemains_cpct;
  }

  /* MATLAB Function: '<S7>/MATLAB Function' incorporates:
   *  Abs: '<S7>/Abs'
   *  Abs: '<S7>/Abs1'
   *  Inport: '<Root>/EKF_Inputs'
   *  Logic: '<S7>/Logical Operator'
   *  RelationalOperator: '<S7>/Relational Operator'
   *  RelationalOperator: '<S7>/Relational Operator1'
   *  RelationalOperator: '<S7>/Relational Operator2'
   */
  if ((DataTypeConversion3 < SOCEstimation_U.EKF_Inputs.delCurrentThresh_mA) &&
      (rtb_TotalSOCRemains_cpct < SOCEstimation_U.EKF_Inputs.delVoltThresh_mV))
  {
    /* '<S13>:1:4' resetTimer = false; */
    SOCEstimation_Y.CC_Outputs.EKF_resetTimer = false;

    /* '<S13>:1:5' if loadElapsedTime */
    if (SOCEstimation_U.EKF_Inputs.currentTime >=
        SOCEstimation_U.EKF_Inputs.timeToWaitUnderLoad) {
      /* '<S13>:1:6' stateChange = true; */
      rtb_ChargerconnectedandLatchfla = true;
    } else {
      /* '<S13>:1:7' else */
      /* '<S13>:1:8' stateChange = false; */
      rtb_ChargerconnectedandLatchfla = false;
    }
  } else {
    /* '<S13>:1:10' else */
    /* '<S13>:1:11' resetTimer = true; */
    SOCEstimation_Y.CC_Outputs.EKF_resetTimer = true;

    /* '<S13>:1:12' stateChange = false; */
    rtb_ChargerconnectedandLatchfla = false;
  }

  /* End of MATLAB Function: '<S7>/MATLAB Function' */

  /* Logic: '<S7>/Logical Operator2' incorporates:
   *  Inport: '<Root>/EKF_Inputs'
   */
  rtb_iflastlatchcyclecurrentcycl = (rtb_ChargerconnectedandLatchfla &&
    SOCEstimation_U.EKF_Inputs.enableEKF);

  /* Product: '<S7>/Product' incorporates:
   *  Inport: '<Root>/Current_mA'
   *  Inport: '<Root>/EKF_Inputs'
   */
  rtb_SOC_ChargeDischarge = SOCEstimation_U.EKF_Inputs.cellIR_mOhm * (real_T)
    SOCEstimation_U.Current_mA;

  /* Logic: '<S7>/Logical Operator3' incorporates:
   *  Delay: '<S2>/Delay1'
   *  Gain: '<S7>/Gain'
   *  Inport: '<Root>/DataPipeline'
   *  Inport: '<Root>/EKF_Inputs'
   *  Logic: '<S7>/NOT'
   *  RelationalOperator: '<S7>/Relational Operator3'
   *  RelationalOperator: '<S7>/Relational Operator5'
   *  SignalConversion generated from: '<S2>/Bus Selector3'
   *  Sum: '<S7>/Add2'
   */
  rtb_ChargerconnectedandLatchfla =
    ((SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min <= 0.001 *
      rtb_SOC_ChargeDischarge + (real_T)
      SOCEstimation_U.EKF_Inputs.lowerActivationThreshold) &&
     (SOCEstimation_DW.Delay1_DSTATE_m > 20));

  /* Gain: '<S7>/Gain1' incorporates:
   *  Inport: '<Root>/Current_mA'
   */
  tmp_1 = 1099511628U;
  tmp_2 = (uint32_T)SOCEstimation_U.Current_mA;
  sMultiWordMul_cc(&tmp_1, 1, &tmp_2, 1, &tmp_0.chunks[0U], 2);

  /* Product: '<S7>/Product1' incorporates:
   *  Inport: '<Root>/EKF_Inputs'
   */
  rtb_SOC_ChargeDischarge = sMultiWord2Double(&tmp_0.chunks[0U], 2, 0) *
    9.0949470177292824E-13 * SOCEstimation_U.EKF_Inputs.cellIR_mOhm;

  /* Logic: '<S7>/Logical Operator4' incorporates:
   *  Delay: '<S2>/Delay1'
   *  Inport: '<Root>/DataPipeline'
   *  Inport: '<Root>/EKF_Inputs'
   *  Logic: '<S7>/Logical Operator1'
   *  Logic: '<S7>/Logical Operator5'
   *  Logic: '<S7>/NOT1'
   *  RelationalOperator: '<S7>/Relational Operator4'
   *  RelationalOperator: '<S7>/Relational Operator6'
   *  SignalConversion generated from: '<S2>/Bus Selector3'
   *  Sum: '<S7>/Add3'
   */
  rtb_vmax3535 = ((rtb_ChargerconnectedandLatchfla ||
                   ((SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min >=
                     (real_T)
                     SOCEstimation_U.EKF_Inputs.higherActivationThreshold +
                     rtb_SOC_ChargeDischarge) &&
                    (SOCEstimation_DW.Delay1_DSTATE_m < 80))) &&
                  SOCEstimation_U.EKF_Inputs.enableEKF);

  /* Chart: '<S8>/IntegCurrent' incorporates:
   *  Inport: '<Root>/CC_Inputs'
   *  Inport: '<Root>/Current_mA'
   *  Inport: '<Root>/DataPipeline'
   *  UnitDelay: '<S2>/Unit Delay'
   */
  /* Gateway: SOCEstimation/SOC_Calc/Integrators/IntegCurrent */
  /* During: SOCEstimation/SOC_Calc/Integrators/IntegCurrent */
  if (SOCEstimation_DW.is_active_c42_SOCEstimation == 0U) {
    /* Entry: SOCEstimation/SOC_Calc/Integrators/IntegCurrent */
    SOCEstimation_DW.is_active_c42_SOCEstimation = 1U;

    /* Entry Internal: SOCEstimation/SOC_Calc/Integrators/IntegCurrent */
    /* Transition: '<S14>:4' */
    SOCEstimation_DW.is_c42_SOCEstimation = SOCEstimat_IN_IntegratedCurrent;

    /* Entry 'IntegratedCurrent': '<S14>:3' */
  } else if (SOCEstimation_DW.is_c42_SOCEstimation ==
             SOCEstimat_IN_IntegratedCurrent) {
    /* During 'IntegratedCurrent': '<S14>:3' */
    /* '<S14>:8:1' sf_internal_predicateOutput =   CC_State == CCState.Vehicle_at_Rest... */
    /* '<S14>:8:2' || CC_State == CCState.Recalibrate... */
    /* '<S14>:8:3' || CC_State == CCState.EKFestimation; */
    if ((SOCEstimation_DW.UnitDelay_DSTATE == Vehicle_at_Rest) ||
        (SOCEstimation_DW.UnitDelay_DSTATE == Recalibrate) ||
        (SOCEstimation_DW.UnitDelay_DSTATE == EKFestimation)) {
      /* Transition: '<S14>:8' */
      SOCEstimation_DW.is_c42_SOCEstimation = SOCEstimatio_IN_IntegratorReset;

      /* Entry 'IntegratorReset': '<S14>:7' */
    } else {
      /* '<S14>:3:3' IntegratedCurrent = single((single(LoopTimer_SOC_msec)*single(Current_mA)) / Tcomp)+IntegratedCurrent; */
      SOCEstimation_B.IntegratedCurrent +=
        SOCEstimation_U.DataPipeline.LoopTimer_SOC_msec * (real32_T)
        SOCEstimation_U.Current_mA / SOCEstimation_U.CC_Inputs.Tcomp;
    }

    /* During 'IntegratorReset': '<S14>:7' */
    /* '<S14>:12:1' sf_internal_predicateOutput =   CC_State  == CCState.CoulombCounting... */
    /* '<S14>:12:2'  || CC_State == CCState.PseudoLatching; */
  } else if ((SOCEstimation_DW.UnitDelay_DSTATE == CoulombCounting) ||
             (SOCEstimation_DW.UnitDelay_DSTATE == PseudoLatching)) {
    /* Transition: '<S14>:12' */
    SOCEstimation_DW.is_c42_SOCEstimation = SOCEstimat_IN_IntegratedCurrent;

    /* Entry 'IntegratedCurrent': '<S14>:3' */
  } else {
    /* '<S14>:7:3' IntegratedCurrent = 0; */
    SOCEstimation_B.IntegratedCurrent = 0.0F;
  }

  /* End of Chart: '<S8>/IntegCurrent' */

  /* DataTypeConversion: '<S8>/Data Type Conversion3' incorporates:
   *  Gain: '<S8>/Gain2'
   *  Gain: '<S8>/Multiply2'
   */
  DataTypeConversion3 = (int32_T)floorf(0.001F *
    SOCEstimation_B.IntegratedCurrent * 0.000277777785F);

  /* Logic: '<S9>/OR' incorporates:
   *  Chart: '<S6>/SOC_Estimator'
   *  Inport: '<Root>/CC_Inputs'
   */
  rtb_ChargerconnectedandLatchf_0 = !SOCEstimation_U.CC_Inputs.pseudoLatchFlag;
  rtb_ChargerconnectedandLatchf_1 = !SOCEstimation_U.CC_Inputs.fullChargeFlag;

  /* Logic: '<S9>/AND' incorporates:
   *  Inport: '<Root>/DataPipeline'
   *  Logic: '<S9>/NOT'
   *  Logic: '<S9>/OR'
   */
  rtb_ChargerconnectedandLatchfla = (rtb_ChargerconnectedandLatchf_1 &&
    rtb_ChargerconnectedandLatchf_0 &&
    SOCEstimation_U.DataPipeline.VCU.isChargerConnected);

  /* Switch: '<S2>/Switch4' incorporates:
   *  Inport: '<Root>/CC_Inputs'
   *  Inport: '<Root>/DataPipeline'
   */
  if (SOCEstimation_U.DataPipeline.VCU.FastCharge) {
    rtb_TotalSOCRemains_cpct =
      SOCEstimation_U.CC_Inputs.FastCharge.MaxAllowedImb_mV;
  } else {
    rtb_TotalSOCRemains_cpct =
      SOCEstimation_U.CC_Inputs.SlowCharge.MaxAllowedImb_mV;
  }

  /* End of Switch: '<S2>/Switch4' */

  /* Sum: '<S9>/Subtract1' incorporates:
   *  Constant: '<S9>/Constant1'
   */
  rtb_SOC_ChargeDischarge = (real_T)rtb_TotalSOCRemains_cpct - 30.0;

  /* RelationalOperator: '<S9>/Vdel <= 170mV ' incorporates:
   *  Inport: '<Root>/DataPipeline'
   */
  rtb_Vdel170mV = (SOCEstimation_U.DataPipeline.VoltageSenseBus.VoltageDelta_mV <=
                   rtb_SOC_ChargeDischarge);

  /* Sum: '<S9>/Subtract' incorporates:
   *  Constant: '<S9>/Constant'
   */
  rtb_SOC_ChargeDischarge = (real_T)rtb_TotalSOCRemains_cpct - 45.0;

  /* Switch: '<S2>/Switch5' incorporates:
   *  Inport: '<Root>/CC_Inputs'
   *  Inport: '<Root>/DataPipeline'
   *  Switch: '<S2>/Switch6'
   */
  if (SOCEstimation_U.DataPipeline.VCU.FastCharge) {
    rtb_TotalSOCRemains_cpct =
      SOCEstimation_U.CC_Inputs.FastCharge.MaxCurrentLimit_mA;
    tmp = SOCEstimation_U.CC_Inputs.FastCharge.MinCurrentLimit_mA;
  } else {
    rtb_TotalSOCRemains_cpct =
      SOCEstimation_U.CC_Inputs.SlowCharge.MaxCurrentLimit_mA;
    tmp = SOCEstimation_U.CC_Inputs.SlowCharge.MinCurrentLimit_mA;
  }

  /* Logic: '<S9>/OR1' incorporates:
   *  Inport: '<Root>/CC_Inputs'
   *  Inport: '<Root>/Current_mA'
   *  Inport: '<Root>/DataPipeline'
   *  Logic: '<S9>/155 < Vdel < 185'
   *  Logic: '<S9>/AND1'
   *  Logic: '<S9>/AND3'
   *  Logic: '<S9>/latchCriteriaAbnormal'
   *  Logic: '<S9>/latchCriteriaNormal'
   *  RelationalOperator: '<S9>/I > Imin'
   *  RelationalOperator: '<S9>/Imax > I'
   *  RelationalOperator: '<S9>/Vdel > 155mV '
   *  RelationalOperator: '<S9>/vmax > 3535'
   *  RelationalOperator: '<S9>/vmin > Vlatch'
   *  SignalConversion generated from: '<S2>/Bus Selector3'
   *  Switch: '<S2>/Switch5'
   *  Switch: '<S2>/Switch6'
   */
  rtb_ChargerconnectedandLatchfla = ((rtb_ChargerconnectedandLatchfla &&
    ((SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min >=
      SOCEstimation_U.CC_Inputs.minVoltageForLatch_mV) &&
     (rtb_TotalSOCRemains_cpct >= SOCEstimation_U.Current_mA) &&
     (SOCEstimation_U.Current_mA >= tmp) && rtb_Vdel170mV)) ||
    (rtb_ChargerconnectedandLatchfla &&
     ((SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_max >
       SOCEstimation_U.CC_Inputs.alternateMaxLatchVoltage_mV) && (rtb_Vdel170mV &&
    (SOCEstimation_U.DataPipeline.VoltageSenseBus.VoltageDelta_mV >
     rtb_SOC_ChargeDischarge)))));

  /* Chart: '<S6>/SOC_Estimator' incorporates:
   *  Delay: '<S1>/Delay'
   *  Inport: '<Root>/CC_Inputs'
   *  Inport: '<Root>/DataPipeline'
   *  Inport: '<Root>/EKF_Inputs'
   */
  /* Gateway: SOCEstimation/SOC_Calc/Capacity Estimator/SOC_Estimator */
  if (SOCEstimation_DW.temporalCounter_i1 < MAX_uint32_T) {
    SOCEstimation_DW.temporalCounter_i1++;
  }

  /* During: SOCEstimation/SOC_Calc/Capacity Estimator/SOC_Estimator */
  if (SOCEstimation_DW.is_active_c15_SOCEstimation == 0U) {
    /* Entry: SOCEstimation/SOC_Calc/Capacity Estimator/SOC_Estimator */
    SOCEstimation_DW.is_active_c15_SOCEstimation = 1U;

    /* Entry Internal: SOCEstimation/SOC_Calc/Capacity Estimator/SOC_Estimator */
    /* Transition: '<S11>:24' */
    SOCEstimation_DW.temporalCounter_i1 = 0U;
    SOCEstimation_DW.is_c15_SOCEstimation = SOCEstimatio_IN_Vehicle_at_Rest;

    /* Entry 'Vehicle_at_Rest': '<S11>:9' */
    /* '<S11>:9:2' CC_State = CCState.Vehicle_at_Rest; */
    SOCEstimation_DW.UnitDelay_DSTATE = Vehicle_at_Rest;
  } else {
    switch (SOCEstimation_DW.is_c15_SOCEstimation) {
     case SOCEstimatio_IN_CoulombCounting:
      SOCEstimation_DW.UnitDelay_DSTATE = CoulombCounting;

      /* During 'CoulombCounting': '<S11>:3' */
      /* '<S11>:219:1' sf_internal_predicateOutput = duration(EKFstateChange && EKFcalibration && ~DataPipeline.VCU.isChargerConnected... */
      /* '<S11>:219:2' , msec ) > DebouncingTimeout_msec; */
      if ((!rtb_iflastlatchcyclecurrentcycl) || (!rtb_vmax3535) ||
          SOCEstimation_U.DataPipeline.VCU.isChargerConnected) {
        SOCEstimation_DW.durationCounter_1 = 0U;
      }

      if ((uint32_T)((int32_T)SOCEstimation_DW.durationCounter_1 * SOCEstimation_U.looptimeSoC) >
          (uint16_T)SOCEstimation_U.CC_Inputs.DebouncingTimeout_msec) {
        /* Transition: '<S11>:219' */
        SOCEstimation_DW.temporalCounter_i1 = 0U;
        SOCEstimation_DW.is_c15_SOCEstimation = SOCEstimation_IN_HybridCounting;

        /* Entry 'HybridCounting': '<S11>:217' */
        /* '<S11>:217:3' CC_State  = CCState.EKFestimation; */
        SOCEstimation_DW.UnitDelay_DSTATE = EKFestimation;

        /* '<S11>:217:4' initialSoC     = (double(TotalCapacityRemains_mAh) / MaxUsableCapacity_mAh) * 100; */
        rtb_SOC_ChargeDischarge = rt_roundd((real_T)
          SOCEstimation_B.TotalCapacityRemains_mAh / (real_T)
          SOCEstimation_DW.Delay_DSTATE);
        if (rtb_SOC_ChargeDischarge < 2.147483648E+9) {
          if (rtb_SOC_ChargeDischarge >= -2.147483648E+9) {
            rtb_TotalSOCRemains_cpct = (int32_T)rtb_SOC_ChargeDischarge;
          } else {
            rtb_TotalSOCRemains_cpct = MIN_int32_T;
          }
        } else {
          rtb_TotalSOCRemains_cpct = MAX_int32_T;
        }

        SOCEstimation_DW.initialSoC = mul_s32_sat_cc(rtb_TotalSOCRemains_cpct, 100);

        /* '<S11>:217:5' modeSel = 1; */
        /* '<S11>:217:6' resetEKF = true; */
        /* '<S11>:217:7' SoCEst = EKFController(DataPipeline.Current_mA , DataPipeline.VoltageSenseBus.mV_min,... */
        /* '<S11>:217:8'            EKF_Inputs.loopTimeEKF, modeSel, MaxUsableCapacity_mAh, EKF_Inputs.processNoise,... */
        /* '<S11>:217:9'            EKF_Inputs.measurementNoise, EKF_Inputs.cellIR_mOhm, initialSoC, resetEKF, EKF_Inputs.SoCData , EKF_Inputs.ocvData); */
        SOCEstimation_EKFController(SOCEstimation_U.DataPipeline.Current_mA,
          SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min,
          SOCEstimation_U.EKF_Inputs.loopTimeEKF, 1.0,
          SOCEstimation_DW.Delay_DSTATE, SOCEstimation_U.EKF_Inputs.processNoise,
          SOCEstimation_U.EKF_Inputs.measurementNoise,
          SOCEstimation_U.EKF_Inputs.cellIR_mOhm, SOCEstimation_DW.initialSoC,
          true, SOCEstimation_U.EKF_Inputs.SoCData,
          SOCEstimation_U.EKF_Inputs.ocvData);

        /* '<S11>:217:10' resetEKF = false; */
        SOCEstimation_DW.resetEKF = false;

        /* '<S11>:217:11' modeSel = 1; */
        /* '<S11>:217:12' SoCEst = EKFController(DataPipeline.Current_mA , DataPipeline.VoltageSenseBus.mV_min,... */
        /* '<S11>:217:13'            EKF_Inputs.loopTimeEKF, modeSel, MaxUsableCapacity_mAh, EKF_Inputs.processNoise,... */
        /* '<S11>:217:14'            EKF_Inputs.measurementNoise, EKF_Inputs.cellIR_mOhm, initialSoC, resetEKF, EKF_Inputs.SoCData , EKF_Inputs.ocvData); */
        SOCEstimation_B.SoCEst = SOCEstimation_EKFController
          (SOCEstimation_U.DataPipeline.Current_mA,
           SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min,
           SOCEstimation_U.EKF_Inputs.loopTimeEKF, 1.0,
           SOCEstimation_DW.Delay_DSTATE,
           SOCEstimation_U.EKF_Inputs.processNoise,
           SOCEstimation_U.EKF_Inputs.measurementNoise,
           SOCEstimation_U.EKF_Inputs.cellIR_mOhm, SOCEstimation_DW.initialSoC,
           false, SOCEstimation_U.EKF_Inputs.SoCData,
           SOCEstimation_U.EKF_Inputs.ocvData);
      } else {
        /* '<S11>:158:1' sf_internal_predicateOutput = duration((pseudoLatchFlag == true && fullChargeFlag == false)... */
        /* '<S11>:158:2' ,msec) > DebouncingTimeout_msec; */
        if (rtb_ChargerconnectedandLatchf_0 ||
            SOCEstimation_U.CC_Inputs.fullChargeFlag) {
          SOCEstimation_DW.durationCounter_2 = 0U;
        }

        if ((uint32_T)((int32_T)SOCEstimation_DW.durationCounter_2 * SOCEstimation_U.looptimeSoC) >
            (uint16_T)SOCEstimation_U.CC_Inputs.DebouncingTimeout_msec) {
          /* Transition: '<S11>:158' */
          SOCEstimation_DW.durationCounter_1_l = 0U;
          SOCEstimation_DW.temporalCounter_i1 = 0U;
          SOCEstimation_DW.is_c15_SOCEstimation =
            SOCEstimation_IN_PseudoLatching;

          /* Entry 'PseudoLatching': '<S11>:153' */
          /* '<S11>:153:3' CC_State = CCState.PseudoLatching; */
          SOCEstimation_DW.UnitDelay_DSTATE = PseudoLatching;
        } else {
          /* '<S11>:78:1' sf_internal_predicateOutput = duration( latchMake == true, msec) >DebouncingTimeout_msec; */
          if (!rtb_ChargerconnectedandLatchfla) {
            SOCEstimation_DW.durationCounter_3 = 0U;
          }

          if ((uint32_T)((int32_T)SOCEstimation_DW.durationCounter_3 * SOCEstimation_U.looptimeSoC) >
              (uint16_T)SOCEstimation_U.CC_Inputs.DebouncingTimeout_msec) {
            /* Transition: '<S11>:78' */
            /* '<S11>:78:1' calcSoH2 = true; */
            SOCEstimation_B.calcSoH2 = true;
            SOCEstimation_DW.temporalCounter_i1 = 0U;
            SOCEstimation_DW.is_c15_SOCEstimation =
              SOCEsti_IN_Recalibrate_Charging;

            /* Entry 'Recalibrate_Charging': '<S11>:6' */
            /* '<S11>:6:4' CC_State = CCState.Recalibrate; */
            SOCEstimation_DW.UnitDelay_DSTATE = Recalibrate;

            /* '<S11>:3:5' TotalCapacityRemains_mAh = Initial_Capacity_mAh + IntegratedCurrent */
          } else if ((SOCEstimation_B.Initial_Capacity_mAh < 0) &&
                     (DataTypeConversion3 < MIN_int32_T
                      - SOCEstimation_B.Initial_Capacity_mAh)) {
            SOCEstimation_B.TotalCapacityRemains_mAh = MIN_int32_T;
          } else if ((SOCEstimation_B.Initial_Capacity_mAh > 0) &&
                     (DataTypeConversion3 > MAX_int32_T
                      - SOCEstimation_B.Initial_Capacity_mAh)) {
            SOCEstimation_B.TotalCapacityRemains_mAh = MAX_int32_T;
          } else {
            SOCEstimation_B.TotalCapacityRemains_mAh =
              SOCEstimation_B.Initial_Capacity_mAh + DataTypeConversion3;
          }
        }
      }
      break;

     case SOCEstimation_IN_HybridCounting:
      SOCEstimation_DW.UnitDelay_DSTATE = EKFestimation;

      /* During 'HybridCounting': '<S11>:217' */
      /* '<S11>:218:1' sf_internal_predicateOutput = (EKFstateChange == false  ||  EKFcalibration == false) && after(CCTimeout_msec * 5, msec); */
      rtb_TotalSOCRemains_cpct = SOCEstimation_U.CC_Inputs.CCTimeout_msec * 5;
      if (rtb_TotalSOCRemains_cpct > 32767) {
        rtb_TotalSOCRemains_cpct = 32767;
      } else if (rtb_TotalSOCRemains_cpct < -32768) {
        rtb_TotalSOCRemains_cpct = -32768;
      }

      if (((!rtb_iflastlatchcyclecurrentcycl) || (!rtb_vmax3535)) && ((uint32_T)
           ((int32_T)SOCEstimation_DW.temporalCounter_i1 * 100) >= (uint16_T)
           rtb_TotalSOCRemains_cpct)) {
        /* Transition: '<S11>:218' */
        SOCEstimation_DW.durationCounter_3 = 0U;
        SOCEstimation_DW.durationCounter_2 = 0U;
        SOCEstimation_DW.durationCounter_1 = 0U;
        SOCEstimation_DW.is_c15_SOCEstimation = SOCEstimatio_IN_CoulombCounting;

        /* Entry 'CoulombCounting': '<S11>:3' */
        /* '<S11>:3:3' CC_State = CCState.CoulombCounting; */
        SOCEstimation_DW.UnitDelay_DSTATE = CoulombCounting;
      } else {
        /* '<S11>:217:16' modeSel = 0; */
        /* '<S11>:217:17' SoCEst = EKFController(DataPipeline.Current_mA , DataPipeline.VoltageSenseBus.mV_min,... */
        /* '<S11>:217:18'           EKF_Inputs.loopTimeEKF, modeSel, MaxUsableCapacity_mAh, EKF_Inputs.processNoise,... */
        /* '<S11>:217:19'           EKF_Inputs.measurementNoise, EKF_Inputs.cellIR_mOhm, initialSoC, resetEKF, EKF_Inputs.SoCData , EKF_Inputs.ocvData); */
        SOCEstimation_B.SoCEst = SOCEstimation_EKFController
          (SOCEstimation_U.DataPipeline.Current_mA,
           SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min,
           SOCEstimation_U.EKF_Inputs.loopTimeEKF, 0.0,
           SOCEstimation_DW.Delay_DSTATE,
           SOCEstimation_U.EKF_Inputs.processNoise,
           SOCEstimation_U.EKF_Inputs.measurementNoise,
           SOCEstimation_U.EKF_Inputs.cellIR_mOhm, SOCEstimation_DW.initialSoC,
           SOCEstimation_DW.resetEKF, SOCEstimation_U.EKF_Inputs.SoCData,
           SOCEstimation_U.EKF_Inputs.ocvData);

        /* '<S11>:217:20' Initial_Capacity_mAh = (int32(SoCEst) * MaxUsableCapacity_mAh)/100; */
        rtb_SOC_ChargeDischarge = rt_roundd(SOCEstimation_B.SoCEst);
        if (rtb_SOC_ChargeDischarge < 2.147483648E+9) {
          if (rtb_SOC_ChargeDischarge >= -2.147483648E+9) {
            rtb_TotalSOCRemains_cpct = (int32_T)rtb_SOC_ChargeDischarge;
          } else {
            rtb_TotalSOCRemains_cpct = MIN_int32_T;
          }
        } else {
          rtb_TotalSOCRemains_cpct = MAX_int32_T;
        }

        SOCEstimation_B.Initial_Capacity_mAh = (int32_T)rt_roundd((real_T)
          mul_s32_sat_cc(rtb_TotalSOCRemains_cpct, SOCEstimation_DW.Delay_DSTATE) /
          100.0);
      }
      break;

     case SOCEstimation_IN_PseudoLatching:
      SOCEstimation_DW.UnitDelay_DSTATE = PseudoLatching;

      /* During 'PseudoLatching': '<S11>:153' */
      /* '<S11>:159:1' sf_internal_predicateOutput = (TotalCapacityRemains_mAh >= MaxUsableCapacity_mAh) && after(DebouncingTimeout_msec, msec); */
      if ((SOCEstimation_B.TotalCapacityRemains_mAh >=
           SOCEstimation_DW.Delay_DSTATE) && ((uint32_T)((int32_T)
            SOCEstimation_DW.temporalCounter_i1 * 100) >= (uint16_T)
           SOCEstimation_U.CC_Inputs.DebouncingTimeout_msec)) {
        /* Transition: '<S11>:159' */
        SOCEstimation_DW.temporalCounter_i1 = 0U;
        SOCEstimation_DW.is_c15_SOCEstimation = SOCEsti_IN_Recalibrate_Charging;

        /* Entry 'Recalibrate_Charging': '<S11>:6' */
        /* '<S11>:6:4' CC_State = CCState.Recalibrate; */
        SOCEstimation_DW.UnitDelay_DSTATE = Recalibrate;
      } else {
        /* '<S11>:206:1' sf_internal_predicateOutput = duration((pseudoLatchFlag == false && fullChargeFlag == false)... */
        /* '<S11>:206:2' ,msec) > DebouncingTimeout_msec; */
        if (SOCEstimation_U.CC_Inputs.pseudoLatchFlag ||
            SOCEstimation_U.CC_Inputs.fullChargeFlag) {
          SOCEstimation_DW.durationCounter_1_l = 0U;
        }

        if ((uint32_T)((int32_T)SOCEstimation_DW.durationCounter_1_l * SOCEstimation_U.looptimeSoC) >
            (uint16_T)SOCEstimation_U.CC_Inputs.DebouncingTimeout_msec) {
          /* Transition: '<S11>:206' */
          SOCEstimation_DW.durationCounter_3 = 0U;
          SOCEstimation_DW.durationCounter_2 = 0U;
          SOCEstimation_DW.durationCounter_1 = 0U;
          SOCEstimation_DW.is_c15_SOCEstimation =
            SOCEstimatio_IN_CoulombCounting;

          /* Entry 'CoulombCounting': '<S11>:3' */
          /* '<S11>:3:3' CC_State = CCState.CoulombCounting; */
          SOCEstimation_DW.UnitDelay_DSTATE = CoulombCounting;

          /* '<S11>:153:5' TotalCapacityRemains_mAh = Initial_Capacity_mAh + IntegratedCurrent; */
        } else if ((SOCEstimation_B.Initial_Capacity_mAh < 0) &&
                   (DataTypeConversion3 < MIN_int32_T
                    - SOCEstimation_B.Initial_Capacity_mAh)) {
          SOCEstimation_B.TotalCapacityRemains_mAh = MIN_int32_T;
        } else if ((SOCEstimation_B.Initial_Capacity_mAh > 0) &&
                   (DataTypeConversion3 > MAX_int32_T
                    - SOCEstimation_B.Initial_Capacity_mAh)) {
          SOCEstimation_B.TotalCapacityRemains_mAh = MAX_int32_T;
        } else {
          SOCEstimation_B.TotalCapacityRemains_mAh =
            SOCEstimation_B.Initial_Capacity_mAh + DataTypeConversion3;
        }
      }
      break;

     case SOCEsti_IN_Recalibrate_Charging:
      SOCEstimation_DW.UnitDelay_DSTATE = Recalibrate;

      /* During 'Recalibrate_Charging': '<S11>:6' */
      /* '<S11>:28:1' sf_internal_predicateOutput = after(CCTimeout_msec, msec); */
      if ((uint32_T)((int32_T)SOCEstimation_DW.temporalCounter_i1 * 100) >=
          (uint16_T)SOCEstimation_U.CC_Inputs.CCTimeout_msec) {
        /* Transition: '<S11>:28' */
        /* Exit 'Recalibrate_Charging': '<S11>:6' */
        /* '<S11>:6:8' Initial_Capacity_mAh = int32(MaxUsableCapacity_mAh); */
        SOCEstimation_B.Initial_Capacity_mAh = SOCEstimation_DW.Delay_DSTATE;

        /* '<S11>:6:9' TotalCapacityRemains_mAh = Initial_Capacity_mAh; */
        SOCEstimation_B.TotalCapacityRemains_mAh =
          SOCEstimation_B.Initial_Capacity_mAh;
        SOCEstimation_DW.durationCounter_3 = 0U;
        SOCEstimation_DW.durationCounter_2 = 0U;
        SOCEstimation_DW.durationCounter_1 = 0U;
        SOCEstimation_DW.is_c15_SOCEstimation = SOCEstimatio_IN_CoulombCounting;

        /* Entry 'CoulombCounting': '<S11>:3' */
        /* '<S11>:3:3' CC_State = CCState.CoulombCounting; */
        SOCEstimation_DW.UnitDelay_DSTATE = CoulombCounting;
      } else {
        /* '<S11>:6:6' calcSoH2 = false; */
        SOCEstimation_B.calcSoH2 = false;
      }
      break;

     default:
      SOCEstimation_DW.UnitDelay_DSTATE = Vehicle_at_Rest;

      /* During 'Vehicle_at_Rest': '<S11>:9' */
      /* '<S11>:19:1' sf_internal_predicateOutput = after(CCTimeout_msec, msec); */
      if ((uint32_T)((int32_T)SOCEstimation_DW.temporalCounter_i1 * 100) >=
          (uint16_T)SOCEstimation_U.CC_Inputs.CCTimeout_msec) {
        /* Transition: '<S11>:19' */
        SOCEstimation_DW.durationCounter_3 = 0U;
        SOCEstimation_DW.durationCounter_2 = 0U;
        SOCEstimation_DW.durationCounter_1 = 0U;
        SOCEstimation_DW.is_c15_SOCEstimation = SOCEstimatio_IN_CoulombCounting;

        /* Entry 'CoulombCounting': '<S11>:3' */
        /* '<S11>:3:3' CC_State = CCState.CoulombCounting; */
        SOCEstimation_DW.UnitDelay_DSTATE = CoulombCounting;
      } else {
        /* Switch: '<S12>/Switch2' incorporates:
         *  Delay: '<S1>/Delay'
         *  RelationalOperator: '<S12>/LowerRelop1'
         *  RelationalOperator: '<S12>/UpperRelop'
         *  Switch: '<S12>/Switch'
         */
        /* '<S11>:9:4' Initial_Capacity_mAh = int32(Initial_Guess_mAh); */
        if (SOCEstimation_B.sf_SOC_ReadFromEEPROM.CapacityRemains_mAh >
            SOCEstimation_DW.Delay_DSTATE) {
          SOCEstimation_B.Initial_Capacity_mAh = SOCEstimation_DW.Delay_DSTATE;
        } else if (SOCEstimation_B.sf_SOC_ReadFromEEPROM.CapacityRemains_mAh < 0)
        {
          /* Switch: '<S12>/Switch' incorporates:
           *  Constant: '<S6>/Constant2'
           */
          SOCEstimation_B.Initial_Capacity_mAh = 0;
        } else {
          SOCEstimation_B.Initial_Capacity_mAh =
            SOCEstimation_B.sf_SOC_ReadFromEEPROM.CapacityRemains_mAh;
        }

        /* End of Switch: '<S12>/Switch2' */
        /* '<S11>:9:5' TotalCapacityRemains_mAh = Initial_Capacity_mAh */
        SOCEstimation_B.TotalCapacityRemains_mAh =
          SOCEstimation_B.Initial_Capacity_mAh;
      }
      break;
    }
  }

  if (rtb_iflastlatchcyclecurrentcycl && rtb_vmax3535 &&
      (!SOCEstimation_U.DataPipeline.VCU.isChargerConnected)) {
    SOCEstimation_DW.durationCounter_1++;
  } else {
    SOCEstimation_DW.durationCounter_1 = 0U;
  }

  if (SOCEstimation_U.CC_Inputs.pseudoLatchFlag &&
      rtb_ChargerconnectedandLatchf_1) {
    SOCEstimation_DW.durationCounter_2++;
  } else {
    SOCEstimation_DW.durationCounter_2 = 0U;
  }

  if (rtb_ChargerconnectedandLatchf_0 && rtb_ChargerconnectedandLatchf_1) {
    SOCEstimation_DW.durationCounter_1_l++;
  } else {
    SOCEstimation_DW.durationCounter_1_l = 0U;
  }

  if (rtb_ChargerconnectedandLatchfla) {
    SOCEstimation_DW.durationCounter_3++;
  } else {
    SOCEstimation_DW.durationCounter_3 = 0U;
  }

  /* Product: '<S10>/Divide2' incorporates:
   *  Delay: '<S1>/Delay'
   */
  rtb_SOC_ChargeDischarge = (real_T)SOCEstimation_B.TotalCapacityRemains_mAh /
    (real_T)SOCEstimation_DW.Delay_DSTATE;

  /* Saturate: '<S10>/Saturation' incorporates:
   *  Gain: '<S10>/Gain1'
   */
  SOCEstimation_DW.Delay1_DSTATE_m = (int32_T)floor(10000.0 *
    rtb_SOC_ChargeDischarge);

  /* Saturate: '<S10>/Saturation' */
  if (SOCEstimation_DW.Delay1_DSTATE_m > 10000) {
    /* Saturate: '<S10>/Saturation' */
    SOCEstimation_DW.Delay1_DSTATE_m = 10000;
  } else if (SOCEstimation_DW.Delay1_DSTATE_m < 0) {
    /* Saturate: '<S10>/Saturation' */
    SOCEstimation_DW.Delay1_DSTATE_m = 0;
  }

  /* End of Saturate: '<S10>/Saturation' */

  /* Switch: '<S10>/Switch' incorporates:
   *  Saturate: '<S10>/Saturation1'
   */
  if (SOCEstimation_DW.UnitDelay_DSTATE >= EKFestimation) {
    /* Gain: '<S10>/Gain' */
    rtb_SOC_ChargeDischarge = 100.0 * SOCEstimation_B.SoCEst;

    /* Saturate: '<S10>/Saturation1' */
    if (rtb_SOC_ChargeDischarge > 10000.0) {
      rtb_SOC_ChargeDischarge = 10000.0;
    } else if (rtb_SOC_ChargeDischarge < 0.0) {
      rtb_SOC_ChargeDischarge = 0.0;
    }

    SOCEstimation_Y.CC_Outputs.SOC_cpct = (int32_T)floor(rtb_SOC_ChargeDischarge);
  } else {
    SOCEstimation_Y.CC_Outputs.SOC_cpct = SOCEstimation_DW.Delay1_DSTATE_m;
  }

  /* End of Switch: '<S10>/Switch' */

  /* Chart: '<S8>/Modulus IntegCurrent' incorporates:
   *  Abs: '<S8>/Abs'
   *  Inport: '<Root>/DataPipeline'
   */
  /* Gateway: SOCEstimation/SOC_Calc/Integrators/Modulus IntegCurrent */
  /* During: SOCEstimation/SOC_Calc/Integrators/Modulus IntegCurrent */
  if (SOCEstimation_DW.is_active_c20_SOCEstimation == 0U) {
    /* Entry: SOCEstimation/SOC_Calc/Integrators/Modulus IntegCurrent */
    SOCEstimation_DW.is_active_c20_SOCEstimation = 1U;

    /* Entry Internal: SOCEstimation/SOC_Calc/Integrators/Modulus IntegCurrent */
    /* Transition: '<S15>:4' */
    /* Entry 'ModIntegratedCurrent': '<S15>:3' */
  } else {
    /* Abs: '<S8>/Abs' incorporates:
     *  Inport: '<Root>/Current_mA'
     */
    /* During 'ModIntegratedCurrent': '<S15>:3' */
    /* '<S15>:3:3' ModIntegratedCurrent = single(single(LoopTimer_SOC_msec)*single(Current_mA))+ModIntegratedCurrent; */
    if (SOCEstimation_U.Current_mA < 0) {
      rtb_TotalSOCRemains_cpct = -SOCEstimation_U.Current_mA;
    } else {
      rtb_TotalSOCRemains_cpct = SOCEstimation_U.Current_mA;
    }

    SOCEstimation_B.ModIntegratedCurrent +=
      SOCEstimation_U.DataPipeline.LoopTimer_SOC_msec * (real32_T)
      rtb_TotalSOCRemains_cpct;
  }

  /* End of Chart: '<S8>/Modulus IntegCurrent' */

  /* Gain: '<S8>/Multiply' incorporates:
   *  Inport: '<Root>/CC_Inputs'
   */
  sLong2MultiWord_cc(SOCEstimation_U.CC_Inputs.InstalledCapacity_mAh,
                  &tmp_5.chunks[0U], 2);
  sMultiWordShl_cc(&tmp_5.chunks[0U], 2, 1U, &tmp_4.chunks[0U], 2);
  MultiWordSignedWrap_cc(&tmp_4.chunks[0U], 2, 24U, &tmp_3.chunks[0U]);

  /* Sum: '<S8>/Add' incorporates:
   *  Gain: '<S8>/Gain3'
   *  Gain: '<S8>/Multiply1'
   *  Product: '<S8>/Divide'
   */
  SOCEstimation_DW.Delay2_DSTATE = 0.001F * SOCEstimation_B.ModIntegratedCurrent
    * 0.000277777785F / sMultiWord2Single_cc(&tmp_3.chunks[0U], 2, 0) +
    SOCEstimation_B.sf_SOC_ReadFromEEPROM.cycleCount;

  /* Update for Delay: '<S7>/Delay1' incorporates:
   *  Inport: '<Root>/Current_mA'
   */
  SOCEstimation_DW.Delay1_DSTATE = SOCEstimation_U.Current_mA;

  /* Update for Delay: '<S7>/Delay' incorporates:
   *  Inport: '<Root>/DataPipeline'
   *  SignalConversion generated from: '<S2>/Bus Selector3'
   */
  SOCEstimation_DW.Delay_DSTATE_i =
    SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min;

  /* End of Outputs for SubSystem: '<S1>/SOC_Calc' */

  /* BusCreator: '<S1>/Bus Creator1' incorporates:
   *  Delay: '<S1>/Delay'
   *  Outport: '<Root>/CC_Outputs'
   */
  SOCEstimation_Y.CC_Outputs.Total_CapacityRemains_mAh =
    SOCEstimation_B.TotalCapacityRemains_mAh;
  SOCEstimation_Y.CC_Outputs.CC_State = SOCEstimation_DW.UnitDelay_DSTATE;
  SOCEstimation_Y.CC_Outputs.MaxUsableCapacity_mAh =
    SOCEstimation_DW.Delay_DSTATE;
  SOCEstimation_Y.CC_Outputs.cycleCount = SOCEstimation_DW.Delay2_DSTATE;
  SOCEstimation_Y.CC_Outputs.SOH_pct = rtb_weight1;
  SOCEstimation_Y.CC_Outputs.SoH2 = rtb_Multiply1;

  /* Update for Delay: '<S1>/Delay' */
  SOCEstimation_DW.Delay_DSTATE = rtb_Effectiveusablecapacity;
}

/* Model initialize function */
void SOCEstimation_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(SOCEstimation_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &SOCEstimation_B), 0,
                sizeof(B_SOCEstimation_T));

  /* states (dwork) */
  (void) memset((void *)&SOCEstimation_DW, 0,
                sizeof(DW_SOCEstimation_T));

  /* external inputs */
  (void)memset(&SOCEstimation_U, 0, sizeof(ExtU_SOCEstimation_T));

  /* external outputs */
  SOCEstimation_Y.CC_Outputs = SOCEstimation_rtZCC_OutputsBus;
  SOCEstimation_PrevZCX.SoHcalculation_Trig_ZCE = POS_ZCSIG;
  SOCEstimation_PrevZCX.SoH1calculation_Trig_ZCE = POS_ZCSIG;

  /* InitializeConditions for Delay: '<S1>/Delay' */
  SOCEstimation_DW.Delay_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/Delay1' */
  SOCEstimation_B.calcSoH2 = false;

  /* InitializeConditions for Delay: '<S1>/Delay3' */
  SOCEstimation_B.TotalCapacityRemains_mAh = 0;

  /* InitializeConditions for Sum: '<S8>/Add' incorporates:
   *  Delay: '<S1>/Delay2'
   */
  SOCEstimation_DW.Delay2_DSTATE = 0.0F;

  /* SystemInitialize for DataTypeConversion: '<S20>/Data Type Conversion' incorporates:
   *  Outport: '<S20>/SoH1'
   */
  SOCEstimation_B.DataTypeConversion = 0.0F;

  /* End of SystemInitialize for SubSystem: '<S17>/SoH1 calculation' */

  /* SystemInitialize for Triggered SubSystem: '<S17>/SoH calculation' */
  /* SystemInitialize for Switch: '<S19>/Switch1' incorporates:
   *  Outport: '<S19>/SoH'
   */
  SOCEstimation_B.Switch1 = 0.0;

  /* End of SystemInitialize for SubSystem: '<S17>/SoH calculation' */
  /* End of SystemInitialize for SubSystem: '<S1>/SoH calculation' */

  /* SystemInitialize for Atomic SubSystem: '<S1>/SOC_Calc' */
  /* InitializeConditions for Delay: '<S7>/Delay1' */
  SOCEstimation_DW.Delay1_DSTATE = 0;

  /* InitializeConditions for Delay: '<S7>/Delay' */
  SOCEstimation_DW.Delay_DSTATE_i = 0;

  /* InitializeConditions for Saturate: '<S10>/Saturation' incorporates:
   *  Delay: '<S2>/Delay1'
   */
  SOCEstimation_DW.Delay1_DSTATE_m = 0;

  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay' */
  SOCEstimation_DW.UnitDelay_DSTATE = Vehicle_at_Rest;

  /* SystemInitialize for Chart: '<S8>/IntegCurrent' */
  SOCEstimation_B.IntegratedCurrent = 0.0F;
  SOCEstimation_DW.is_active_c42_SOCEstimation = 0U;
  SOCEstimation_DW.is_c42_SOCEstimation = SOCEstimatio_IN_NO_ACTIVE_CHILD;

  /* SystemInitialize for Chart: '<S6>/SOC_Estimator' */
  SOCEstimation_DW.temporalCounter_i1 = 0U;

  /* '<S11>:221:7' x = 0; */
  SOCEstimation_DW.x = 0.0;

  /* '<S11>:221:8' EKF_P = double(1e-3); */
  SOCEstimation_DW.EKF_P = 0.001;

  /* '<S11>:221:9' H_prev = 0; */
  SOCEstimation_DW.H_prev = 0.0;

  /* '<S11>:221:10' filteredVoltage = 0; */
  SOCEstimation_DW.filteredVoltage = 0.0;
  SOCEstimation_B.Initial_Capacity_mAh = 0;
  SOCEstimation_B.SoCEst = 0.0;
  SOCEstimation_DW.resetEKF = false;
  SOCEstimation_DW.initialSoC = 0;
  SOCEstimation_DW.is_active_c15_SOCEstimation = 0U;
  SOCEstimation_DW.is_c15_SOCEstimation = SOCEstimatio_IN_NO_ACTIVE_CHILD;

  /* SystemInitialize for Chart: '<S8>/Modulus IntegCurrent' */
  SOCEstimation_B.ModIntegratedCurrent = 0.0F;
  SOCEstimation_DW.is_active_c20_SOCEstimation = 0U;

  /* End of SystemInitialize for SubSystem: '<S1>/SOC_Calc' */
}

/* Model terminate function */
void SOCEstimation_terminate(void)
{
  /* (no terminate code required) */
}
