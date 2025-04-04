/*
 * SOCEstimation.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "SOCEstimation".
 *
 * Model version              : 7.160
 * Simulink Coder version : 24.1 (R2024a) 19-Nov-2023
 * C source code generated on : Mon Feb 17 13:54:37 2025
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
#include "bmsConfiguration.h"
#include "monitorOperations.h"
extern float SoHFromCycleCountVal;
extern uint32_t debugLatchCapacity;
/* Named constants for Chart: '<S8>/SOC_Estimator' */
#define SOCEsti_IN_Recalibrate_Charging ((uint8_T)4U)
#define SOCEstimatio_IN_CoulombCounting ((uint8_T)1U)
#define SOCEstimatio_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define SOCEstimatio_IN_Vehicle_at_Rest ((uint8_T)5U)
#define SOCEstimation_IN_HybridCounting ((uint8_T)2U)
#define SOCEstimation_IN_PseudoLatching ((uint8_T)3U)

/* Named constants for Chart: '<S10>/IntegCurrent' */
#define SOCEstimat_IN_IntegratedCurrent ((uint8_T)1U)
#define SOCEstimatio_IN_IntegratorReset ((uint8_T)2U)

/* Block signals (default storage) */
B_SOCEstimation_T SOCEstimation_B;

/* Block states (default storage) */
DW_SOCEstimation_T SOCEstimation_DW;

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
  0,                                   /* TotalCapacityExchange_mAh */
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

/* Function for Chart: '<S8>/SOC_Estimator' */
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

/* Function for Chart: '<S8>/SOC_Estimator' */
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

/* Function for Chart: '<S8>/SOC_Estimator' */
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
 * Function for Chart: '<S8>/SOC_Estimator'
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

  /* MATLAB Function 'EKFController': '<S13>:221' */
  /* '<S13>:221:6' if isempty(x) */
  /* '<S13>:221:13' if resetFlag */
  if (resetFlag) {
    /* '<S13>:221:14' x = 0; */
    SOCEstimation_DW.x = 0.0;

    /* '<S13>:221:15' EKF_P = double(1e-3); */
    SOCEstimation_DW.EKF_P = 0.001;

    /* '<S13>:221:16' H_prev = 0; */
    SOCEstimation_DW.H_prev = 0.0;

    /* '<S13>:221:17' filteredVoltage = 0; */
    SOCEstimation_DW.filteredVoltage = 0.0;

    /* '<S13>:221:18' else */
    /* '<S13>:221:19' if mode == 1 */
  } else if (mode == 1.0) {
    /* '<S13>:221:20' x = double(initSoC); */
    SOCEstimation_DW.x = initSoC;

    /* '<S13>:221:21' EKF_P = double(1e-3); */
    SOCEstimation_DW.EKF_P = 0.001;

    /* '<S13>:221:22' filteredVoltage = double(terminalV); */
    SOCEstimation_DW.filteredVoltage = terminalV;
  } else {
    /* '<S13>:221:23' else */
    /* '<S13>:221:25' dt_hr = double(loopTime) / 3600000; */
    /* '<S13>:221:26' delta_x = (double(current) * dt_hr / double(maxCapUsable)) * 100; */
    /* '<S13>:221:27' x_pred = x + delta_x; */
    /* '<S13>:221:28' x_pred = max(0, min(100, x_pred)); */
    x_pred_tmp = loopTime / 3.6E+6 * (real_T)current / (real_T)maxCapUsable *
      100.0 + SOCEstimation_DW.x;
    x_pred = fmax(0.0, fmin(100.0, x_pred_tmp));

    /* '<S13>:221:29' P_pred = double(EKF_P + processNoise); */
    P_pred = (real32_T)SOCEstimation_DW.EKF_P + processNoise;

    /* '<S13>:221:32' if x_pred <= socData(1) */
    if (x_pred <= socData[0]) {
      /* '<S13>:221:33' ocv_pred = ocvData(1); */
      ocv_pred_size_idx_1 = 1;
      ocv_pred_data = ocvData[0];

      /* '<S13>:221:49' H = (ocvData(2) - ocvData(1)) / (socData(2) - socData(1)) + epsilon; */
      H = (ocvData[1] - ocvData[0]) / (socData[1] - socData[0]) + 1.0E-6;
    } else {
      if (x_pred >= socData[100]) {
        /* '<S13>:221:34' elseif x_pred >= socData(end) */
        /* '<S13>:221:35' ocv_pred = ocvData(end); */
        ocv_pred_size_idx_1 = 1;
        ocv_pred_data = ocvData[100];
      } else {
        /* '<S13>:221:36' else */
        /* '<S13>:221:37' idx = find(socData >= x_pred, 1); */
        for (c = 0; c < 101; c++) {
          socData_0[c] = (socData[c] >= x_pred);
        }

        SOCEstimation_eml_find(socData_0, &c_data, c_size);

        /* '<S13>:221:38' if idx > 1 */
        c_size_0[0] = 1;
        c_size_0[1] = c_size[1];
        if (c_size[1] - 1 >= 0) {
          c_data_0 = (c_data > 1);
        }

        if (SOCEstimation_ifWhileCond(&c_data_0, c_size_0)) {
          /* '<S13>:221:39' t = (x_pred - socData(idx-1)) / (socData(idx) - socData(idx-1)); */
          x_pred_size[0] = 1;
          x_pred_size[1] = c_size[1];
          socData_size[0] = 1;
          socData_size[1] = c_size[1];
          if (c_size[1] - 1 >= 0) {
            H = socData[c_data - 2];
            K = x_pred - H;
            socData_data = socData[c_data - 1] - H;
          }

          /* '<S13>:221:40' ocv_pred = ocvData(idx-1) + t * (ocvData(idx) - ocvData(idx-1)); */
          ocv_pred_size_idx_1 = c_size[1];
          if (c_size[1] - 1 >= 0) {
            H = ocvData[c_data - 2];
            ocv_pred_data = (ocvData[c_data - 1] - H) * SOCEstimation_mrdiv(&K,
              x_pred_size, &socData_data, socData_size) + H;
          }
        } else {
          /* '<S13>:221:41' else */
          /* '<S13>:221:42' ocv_pred = ocvData(idx); */
          ocv_pred_size_idx_1 = c_size[1];
          if (c_size[1] - 1 >= 0) {
            ocv_pred_data = ocvData[c_data - 1];
          }
        }
      }

      if (x_pred >= socData[100]) {
        /* '<S13>:221:50' elseif x_pred >= socData(end) */
        /* '<S13>:221:51' H = (ocvData(end) - ocvData(end-1)) / (socData(end) - socData(end-1)) + epsilon; */
        H = (ocvData[100] - ocvData[99]) / (socData[100] - socData[99]) + 1.0E-6;
      } else {
        /* '<S13>:221:52' else */
        /* '<S13>:221:53' idx = find(socData >= x_pred, 1); */
        for (c = 0; c < 101; c++) {
          socData_0[c] = (socData[c] >= x_pred);
        }

        SOCEstimation_eml_find(socData_0, &c_data, c_size);

        /* '<S13>:221:54' if idx > 1 */
        c_size_0[0] = 1;
        c_size_0[1] = c_size[1];
        if (c_size[1] - 1 >= 0) {
          c_data_0 = (c_data > 1);
        }

        if (SOCEstimation_ifWhileCond(&c_data_0, c_size_0)) {
          /* '<S13>:221:55' H = (ocvData(idx) - ocvData(idx-1)) / (socData(idx) - socData(idx-1)) + epsilon; */
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
          /* '<S13>:221:56' else */
          /* '<S13>:221:57' H = epsilon; */
          H = 1.0E-6;
        }
      }
    }

    /* '<S13>:221:47' epsilon = 1e-6; */
    /* '<S13>:221:48' if x_pred <= socData(1) */
    /* '<S13>:221:62' alpha_LPF = 0.8; */
    /* '<S13>:221:63' H_filtered = alpha_LPF * H_prev + (1 - alpha_LPF) * H; */
    SOCEstimation_DW.H_prev = 0.8 * SOCEstimation_DW.H_prev +
      0.19999999999999996 * H;

    /* '<S13>:221:64' H_prev = H_filtered; */
    /* '<S13>:221:67' ir_drop = (double(current) * cellIR) / 1000; */
    H = (real_T)current * cellIR / 1000.0;

    /* '<S13>:221:68' v_ocv_pred = double(ocv_pred) - ir_drop; */
    ocv_pred_size_idx_1--;
    for (c = 0; c <= ocv_pred_size_idx_1; c++) {
      ocv_pred_data -= H;
    }

    /* '<S13>:221:71' alpha_voltage_LPF = 0.7; */
    /* '<S13>:221:72' filteredVoltage = alpha_voltage_LPF * filteredVoltage + (1 - alpha_voltage_LPF) * double(terminalV); */
    SOCEstimation_DW.filteredVoltage = 0.7 * SOCEstimation_DW.filteredVoltage +
      0.30000000000000004 * (real_T)terminalV;

    /* '<S13>:221:75' load_variation = abs(current); */
    /* '<S13>:221:76' adaptiveNoise = double(measurementNoise) + min(1e4, max(1e-3, 1 / (abs(H_filtered) + 1e-4))) + (0.1 * load_variation); */
    /* '<S13>:221:79' denominator = H_filtered^2 * P_pred + adaptiveNoise; */
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

    /* '<S13>:221:80' if abs(denominator) < 1e-6 */
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
      /* '<S13>:221:81' K = 0.1; */
      K = 0.1;
    } else {
      /* '<S13>:221:82' else */
      /* '<S13>:221:83' K = double(double(P_pred * H_filtered) / denominator); */
      K = rt_roundd(P_pred * SOCEstimation_DW.H_prev / (real_T)c);
      if (K < 2.147483648E+9) {
        if (K < -2.147483648E+9) {
          K = -2.147483648E+9;
        }
      } else {
        K = 2.147483647E+9;
      }
    }

    /* '<S13>:221:87' vDiff = double(filteredVoltage) - v_ocv_pred(1); */
    /* '<S13>:221:88' x_corrected = x_pred + K * vDiff; */
    /* '<S13>:221:89' x_corrected = max(0, min(100, x_corrected)); */
    /* '<S13>:221:92' EKF_P = double((1 - K * H_filtered) * P_pred); */
    SOCEstimation_DW.EKF_P = (1.0 - K * SOCEstimation_DW.H_prev) * P_pred;

    /* '<S13>:221:95' alpha_hybrid = max(0.1, min(0.9, abs(H_filtered))); */
    P_pred = fmax(0.1, fmin(0.9, H));

    /* '<S13>:221:96' x = alpha_hybrid * x_corrected + (1 - alpha_hybrid) * (x + delta_x); */
    SOCEstimation_DW.x = fmax(0.0, fmin(100.0, (SOCEstimation_DW.filteredVoltage
      - ocv_pred_data) * K + x_pred)) * P_pred + (1.0 - P_pred) * x_pred_tmp;

    /* '<S13>:221:97' x = max(0, min(100, x)); */
    SOCEstimation_DW.x = fmax(0.0, fmin(100.0, SOCEstimation_DW.x));
  }

  /* '<S13>:221:101' socEst = x; */
  socEst = SOCEstimation_DW.x;
  return socEst;
}

/* Model step function */
void SOCEstimation_step(void)
{
  int64m_T tmp_0;
  real_T coefficients[5];
  real_T rtb_HigherthresholdwithIcomp;
  real_T rtb_SOC_ChargeDischarge;
  real_T rtb_factor1;
  real_T rtb_weight1;
  int32_T DataTypeConversion3;
  int32_T Switch_f;
  int32_T tmp;
  int32_T tmp_3;
  int32_T u;
  real32_T rtb_SoH2;
  uint32_T tmp_1;
  uint32_T tmp_2;
  boolean_T guard1;
  boolean_T latchMake;
  boolean_T rtb_LogicalOperator3;
  boolean_T rtb_calcSoH;
  boolean_T rtb_stateChange;
  boolean_T tmp_4;
  boolean_T tmp_5;

  /* MATLAB Function: '<S1>/SOC_ReadFromEEPROM' */
  SOCEstimatio_SOC_ReadFromEEPROM(&SOCEstimation_B.sf_SOC_ReadFromEEPROM);

  /* Outputs for Enabled SubSystem: '<S1>/SoH calculation' incorporates:
   *  EnablePort: '<S5>/Enable'
   */
  if (SOCEstimation_B.sf_SOC_ReadFromEEPROM.SoHCalcEn) {
    SOCEstimation_DW.SoHcalculation_MODE = true;

    /* MATLAB Function: '<S19>/MATLAB Function' incorporates:
     *  DataTypeConversion: '<S19>/Data Type Conversion1'
     *  Inport: '<Root>/CC_Inputs'
     */
    /* MATLAB Function 'SOCEstimation/SoH calculation/SoH1 calculation/MATLAB Function': '<S22>:1' */
    /* '<S22>:1:4' coefficients = [ A, B, C, D, E]; */
    coefficients[0] = SOCEstimation_U.CC_Inputs.Coefficients.elementZero;
    coefficients[1] = SOCEstimation_U.CC_Inputs.Coefficients.elementOne;
    coefficients[2] = SOCEstimation_U.CC_Inputs.Coefficients.elementTwo;
    coefficients[3] = SOCEstimation_U.CC_Inputs.Coefficients.elementThree;
    coefficients[4] = SOCEstimation_U.CC_Inputs.Coefficients.elementFour;

    /* '<S22>:1:5' y = 0.0; */
    rtb_SOC_ChargeDischarge = 0.0;

    if(SOCEstimation_B.sf_SOC_ReadFromEEPROM.cycleCount < 2.0f)       //manual changes 
    {
      rtb_SOC_ChargeDischarge = 100.0;
    }
    else
    {
        /* '<S22>:1:7' for i = 1:length(coefficients) */
        for (Switch_f = 0; Switch_f < 5; Switch_f++) {
          /* '<S22>:1:8' y = y + coefficients(i) * cycleCount^(5 - (i)); */
          rtb_SOC_ChargeDischarge += pow
            (SOCEstimation_B.sf_SOC_ReadFromEEPROM.cycleCount, 5.0 - ((real_T)
              Switch_f + 1.0)) * coefficients[Switch_f];
        }
    }

    SoHFromCycleCountVal = rtb_SOC_ChargeDischarge; //for testing purpose
    
    /* Saturate: '<S19>/Saturation' incorporates:
     *  MATLAB Function: '<S19>/MATLAB Function'
     */
    if (rtb_SOC_ChargeDischarge > 100.0) {
      rtb_SOC_ChargeDischarge = 100.0;
    } else if (rtb_SOC_ChargeDischarge < 0.0) {
      rtb_SOC_ChargeDischarge = 0.0;
    }

    /* End of Saturate: '<S19>/Saturation' */

    /* Switch: '<S18>/Switch' incorporates:
     *  Abs: '<S18>/Abs'
     *  Constant: '<S18>/Constant'
     *  Constant: '<S21>/Constant2'
     *  Constant: '<S21>/Constant3'
     *  DataTypeConversion: '<S19>/Data Type Conversion'
     *  Inport: '<Root>/CC_Inputs'
     *  Logic: '<S18>/AND'
     *  Product: '<S21>/Product'
     *  Product: '<S21>/Product1'
     *  Product: '<S21>/Product2'
     *  RelationalOperator: '<S18>/GreaterThan'
     *  RelationalOperator: '<S18>/GreaterThan1'
     *  Sum: '<S18>/Subtract2'
     *  Sum: '<S21>/Add1'
     *  Sum: '<S21>/Subtract'
     */
    if ((fabsf(SOCEstimation_B.sf_SOC_ReadFromEEPROM.SoH2 - (real32_T)
               rtb_SOC_ChargeDischarge) <= SOCEstimation_U.CC_Inputs.SoHThresh) &&        //5% delta for SoH calculation
        SOCEstimation_B.sf_SOC_ReadFromEEPROM.PrevLatch &&
        (SOCEstimation_B.sf_SOC_ReadFromEEPROM.SoH2 > 50.0F)) {
      /* Product: '<S21>/Divide1' incorporates:
       *  Constant: '<S21>/Constant1'
       */
      rtb_HigherthresholdwithIcomp = SOCEstimation_B.sf_SOC_ReadFromEEPROM.SoH2 /
        100.0;

      /* Product: '<S21>/Divide' incorporates:
       *  Constant: '<S21>/Constant'
       */
      rtb_factor1 = (real32_T)rtb_SOC_ChargeDischarge / 100.0;

      /* Product: '<S21>/Divide2' incorporates:
       *  Sum: '<S21>/Add'
       */
      rtb_weight1 = rtb_factor1 / (rtb_factor1 + rtb_HigherthresholdwithIcomp);
      rtb_HigherthresholdwithIcomp = ((1.0 - rtb_weight1) *
        rtb_HigherthresholdwithIcomp + rtb_factor1 * rtb_weight1) * 100.0;
    } else {
      rtb_HigherthresholdwithIcomp = (real32_T)rtb_SOC_ChargeDischarge;
    }

    /* End of Switch: '<S18>/Switch' */

    /* Saturate: '<S18>/Saturation' */
    if (rtb_HigherthresholdwithIcomp > 100.0) {
      rtb_HigherthresholdwithIcomp = 100.0;
    } else if (rtb_HigherthresholdwithIcomp < 0.0) {
      rtb_HigherthresholdwithIcomp = 0.0;
    }

    /* End of Saturate: '<S18>/Saturation' */

    /* Switch: '<S5>/Switch' incorporates:
     *  Logic: '<S5>/AND'
     *  RelationalOperator: '<S5>/GreaterThan'
     */
    if ((rtb_HigherthresholdwithIcomp >=
         SOCEstimation_B.sf_SOC_ReadFromEEPROM.SoH) &&
        SOCEstimation_B.sf_SOC_ReadFromEEPROM.PrevLatch) {
      /* Switch: '<S5>/Switch' */
      SOCEstimation_B.Switch = SOCEstimation_B.sf_SOC_ReadFromEEPROM.SoH;
    } else {
      /* Switch: '<S5>/Switch' */
      SOCEstimation_B.Switch = (real32_T)rtb_HigherthresholdwithIcomp;
    }

    /* End of Switch: '<S5>/Switch' */

    /* DataTypeConversion: '<S20>/Data Type Conversion1' incorporates:
     *  Constant: '<S20>/Constant3'
     *  DataTypeConversion: '<S20>/Data Type Conversion2'
     *  Inport: '<Root>/CC_Inputs'
     *  Product: '<S20>/Divide3'
     *  Product: '<S20>/Product4'
     */
    SOCEstimation_B.Effectiveusablecapacity = (int32_T)floorf((real32_T)((real_T)
      SOCEstimation_U.CC_Inputs.InstalledCapacity_mAh / 100.0 *
      SOCEstimation_B.Switch));
      SOCEstimation_B.sf_SOC_ReadFromEEPROM.SoHCalcEn = false;
  } else {
    SOCEstimation_DW.SoHcalculation_MODE = false;
  }

  /* End of Outputs for SubSystem: '<S1>/SoH calculation' */

  /* Sum: '<S9>/Add1' incorporates:
   *  Delay: '<S9>/Delay1'
   *  Inport: '<Root>/Current_mA'
   */
  /* MATLAB Function 'SOCEstimation/SOC_Calc/EKFStateChangeChecker/MATLAB Function': '<S15>:1' */
  /* '<S15>:1:3' if stable == 1 */
  Switch_f = SOCEstimation_U.Current_mA - SOCEstimation_DW.Delay1_DSTATE;

  /* Sum: '<S9>/Add' incorporates:
   *  Delay: '<S9>/Delay'
   *  Inport: '<Root>/DataPipeline'
   *  SignalConversion generated from: '<S3>/Bus Selector3'
   */
  u = SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min -
    SOCEstimation_DW.Delay_DSTATE;

  /* Abs: '<S9>/Abs' */
  if (Switch_f < 0) {
    Switch_f = -Switch_f;
  }

  /* Abs: '<S9>/Abs1' */
  if (u < 0) {
    u = -u;
  }

  /* MATLAB Function: '<S9>/MATLAB Function' incorporates:
   *  Abs: '<S9>/Abs'
   *  Abs: '<S9>/Abs1'
   *  Inport: '<Root>/EKF_Inputs'
   *  Logic: '<S9>/Logical Operator'
   *  RelationalOperator: '<S9>/Relational Operator'
   *  RelationalOperator: '<S9>/Relational Operator1'
   *  RelationalOperator: '<S9>/Relational Operator2'
   */
  if ((Switch_f < SOCEstimation_U.EKF_Inputs.delCurrentThresh_mA) && (u <
       SOCEstimation_U.EKF_Inputs.delVoltThresh_mV)) {
    /* '<S15>:1:4' resetTimer = false; */
    SOCEstimation_Y.CC_Outputs.EKF_resetTimer = false;

    /* '<S15>:1:5' if loadElapsedTime */
    if (SOCEstimation_U.EKF_Inputs.currentTime >=
        SOCEstimation_U.EKF_Inputs.timeToWaitUnderLoad) {
      /* '<S15>:1:6' stateChange = true; */
      rtb_stateChange = true;
    } else {
      /* '<S15>:1:7' else */
      /* '<S15>:1:8' stateChange = false; */
      rtb_stateChange = false;
    }
  } else {
    /* '<S15>:1:10' else */
    /* '<S15>:1:11' resetTimer = true; */
    SOCEstimation_Y.CC_Outputs.EKF_resetTimer = true;

    /* '<S15>:1:12' stateChange = false; */
    rtb_stateChange = false;
  }

  /* End of MATLAB Function: '<S9>/MATLAB Function' */

  /* Logic: '<S9>/Logical Operator2' incorporates:
   *  Inport: '<Root>/EKF_Inputs'
   */
  rtb_stateChange = (rtb_stateChange && SOCEstimation_U.EKF_Inputs.enableEKF);

  /* MATLAB Function: '<S6>/MATLAB Function' incorporates:
   *  Constant: '<S6>/Constant'
   */
  /* MATLAB Function 'SOCEstimation/Subsystem1/MATLAB Function': '<S23>:1' */
  /* '<S23>:1:3' if isempty(counter) */
  /* '<S23>:1:4' counter = init_value; */
  if (!SOCEstimation_DW.counter_not_empty) {
    SOCEstimation_DW.counter = 0.0;
    SOCEstimation_DW.counter_not_empty = true;
  } else if (SOCEstimation_DW.counter != 9.0) {
    if(SOCEstimation_DW.counter == 7.0) {        //manually added
          memoryWriteOverride = true;
        }
    /* '<S23>:1:10' else */
    /* '<S23>:1:11' counter = counter + 1; */
    SOCEstimation_DW.counter++;
  } else {
    /* '<S23>:1:5' elseif counter == 9 */
    /* '<S23>:1:9' counter = counter; */
  }

  /* Sum: '<S9>/Add2' incorporates:
   *  Gain: '<S9>/Gain'
   *  Inport: '<Root>/Current_mA'
   *  Inport: '<Root>/EKF_Inputs'
   *  Product: '<S9>/Product'
   */
  /* '<S23>:1:13' counterOut = counter; */
  rtb_SOC_ChargeDischarge = SOCEstimation_U.EKF_Inputs.cellIR_mOhm * (real_T)
    SOCEstimation_U.Current_mA * 0.001 + (real_T)
    SOCEstimation_U.EKF_Inputs.lowerActivationThreshold;

  /* Logic: '<S9>/Logical Operator3' incorporates:
   *  Delay: '<S3>/Delay1'
   *  Inport: '<Root>/DataPipeline'
   *  Logic: '<S9>/NOT'
   *  RelationalOperator: '<S9>/Relational Operator3'
   *  RelationalOperator: '<S9>/Relational Operator5'
   *  SignalConversion generated from: '<S3>/Bus Selector3'
   */
  rtb_LogicalOperator3 = ((SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min <=
    rtb_SOC_ChargeDischarge) && (SOCEstimation_DW.Delay1_DSTATE_m > 20));

  /* Gain: '<S9>/Gain1' incorporates:
   *  Inport: '<Root>/Current_mA'
   */
  tmp_1 = 1099511628U;
  tmp_2 = (uint32_T)SOCEstimation_U.Current_mA;
  sMultiWordMul_cc(&tmp_1, 1, &tmp_2, 1, &tmp_0.chunks[0U], 2);

  /* Product: '<S9>/Product1' incorporates:
   *  Inport: '<Root>/EKF_Inputs'
   */
  rtb_SOC_ChargeDischarge = sMultiWord2Double(&tmp_0.chunks[0U], 2, 0) *
    9.0949470177292824E-13 * SOCEstimation_U.EKF_Inputs.cellIR_mOhm;

  /* Logic: '<S9>/Logical Operator4' incorporates:
   *  Delay: '<S3>/Delay1'
   *  Inport: '<Root>/DataPipeline'
   *  Inport: '<Root>/EKF_Inputs'
   *  Logic: '<S9>/Logical Operator1'
   *  Logic: '<S9>/Logical Operator5'
   *  Logic: '<S9>/NOT1'
   *  RelationalOperator: '<S9>/Relational Operator4'
   *  RelationalOperator: '<S9>/Relational Operator6'
   *  SignalConversion generated from: '<S3>/Bus Selector3'
   *  Sum: '<S9>/Add3'
   */
  rtb_LogicalOperator3 = ((rtb_LogicalOperator3 ||
    ((SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min >= (real_T)
      SOCEstimation_U.EKF_Inputs.higherActivationThreshold +
      rtb_SOC_ChargeDischarge) && (SOCEstimation_DW.Delay1_DSTATE_m < 80))) &&
    SOCEstimation_U.EKF_Inputs.enableEKF);

  /* Chart: '<S10>/IntegCurrent' incorporates:
   *  Inport: '<Root>/Current_mA'
   *  Inport: '<Root>/DataPipeline'
   *  UnitDelay: '<S3>/Unit Delay'
   */
  /* Gateway: SOCEstimation/SOC_Calc/Integrators/IntegCurrent */
  /* During: SOCEstimation/SOC_Calc/Integrators/IntegCurrent */
  if (SOCEstimation_DW.is_active_c42_SOCEstimation == 0U) {
    /* Entry: SOCEstimation/SOC_Calc/Integrators/IntegCurrent */
    SOCEstimation_DW.is_active_c42_SOCEstimation = 1U;

    /* Entry Internal: SOCEstimation/SOC_Calc/Integrators/IntegCurrent */
    /* Transition: '<S16>:4' */
    SOCEstimation_DW.is_c42_SOCEstimation = SOCEstimat_IN_IntegratedCurrent;

    /* Entry 'IntegratedCurrent': '<S16>:3' */
  } else if (SOCEstimation_DW.is_c42_SOCEstimation ==
             SOCEstimat_IN_IntegratedCurrent) {
    /* During 'IntegratedCurrent': '<S16>:3' */
    /* '<S16>:8:1' sf_internal_predicateOutput =   CC_State == CCState.Vehicle_at_Rest... */
    /* '<S16>:8:2' || CC_State == CCState.Recalibrate... */
    /* '<S16>:8:3' || CC_State == CCState.EKFestimation; */
    if ((SOCEstimation_DW.UnitDelay_DSTATE == Vehicle_at_Rest) ||
        (SOCEstimation_DW.UnitDelay_DSTATE == Recalibrate) ||
        (SOCEstimation_DW.UnitDelay_DSTATE == EKFestimation)) {
      /* Transition: '<S16>:8' */
      SOCEstimation_DW.is_c42_SOCEstimation = SOCEstimatio_IN_IntegratorReset;

      /* Entry 'IntegratorReset': '<S16>:7' */
    } else {
      /* '<S16>:3:3' IntegratedCurrent = single((single(LoopTimer_SOC_msec)*single(Current_mA)))+IntegratedCurrent; */
      SOCEstimation_B.IntegratedCurrent +=
        SOCEstimation_U.DataPipeline.LoopTimer_SOC_msec * (real32_T)
        SOCEstimation_U.Current_mA;
    }

    /* During 'IntegratorReset': '<S16>:7' */
    /* '<S16>:12:1' sf_internal_predicateOutput =   CC_State  == CCState.CoulombCounting... */
    /* '<S16>:12:2'  || CC_State == CCState.PseudoLatching; */
  } else if ((SOCEstimation_DW.UnitDelay_DSTATE == CoulombCounting) ||
             (SOCEstimation_DW.UnitDelay_DSTATE == PseudoLatching)) {
    /* Transition: '<S16>:12' */
    SOCEstimation_DW.is_c42_SOCEstimation = SOCEstimat_IN_IntegratedCurrent;

    /* Entry 'IntegratedCurrent': '<S16>:3' */
  } else {
    /* '<S16>:7:3' IntegratedCurrent = 0; */
    SOCEstimation_B.IntegratedCurrent = 0.0F;
  }

  /* End of Chart: '<S10>/IntegCurrent' */

  /* DataTypeConversion: '<S10>/Data Type Conversion3' incorporates:
   *  Gain: '<S10>/Gain2'
   *  Gain: '<S10>/Multiply2'
   */
  DataTypeConversion3 = (int32_T)floorf(0.001F *
    SOCEstimation_B.IntegratedCurrent * 0.000277777785F);

  /* Switch: '<S6>/Switch' incorporates:
   *  MATLAB Function: '<S6>/MATLAB Function'
   */
  if (SOCEstimation_DW.counter > 7.0) {
    /* Switch: '<S6>/Switch' incorporates:
     *  Product: '<S6>/Product'
     */
    Switch_f = (int32_T)floor((real_T)SOCEstimation_B.Effectiveusablecapacity *
      SOCEstimation_B.sf_SOC_ReadFromEEPROM.TcompPersist);
  } else {
    /* Switch: '<S6>/Switch' */
    Switch_f = SOCEstimation_B.Effectiveusablecapacity;
  }

  /* End of Switch: '<S6>/Switch' */

  /* MATLAB Function: '<S3>/MATLAB Function' incorporates:
   *  Chart: '<S8>/SOC_Estimator'
   *  Inport: '<Root>/CC_Inputs'
   *  Inport: '<Root>/Current_mA'
   *  Inport: '<Root>/DataPipeline'
   *  SignalConversion generated from: '<S3>/Bus Selector3'
   */
  /* MATLAB Function 'SOCEstimation/SOC_Calc/MATLAB Function': '<S11>:1' */
  /* '<S11>:1:6' if (((fullChargeLatch || pseudoChargeLatch) == false) && isChargerConnected == 1) */
  tmp_4 = !SOCEstimation_U.CC_Inputs.pseudoLatchFlag;
  tmp_5 = !SOCEstimation_U.CC_Inputs.fullChargeFlag;
  if (tmp_5 && tmp_4 && SOCEstimation_U.DataPipeline.VCU.isChargerConnected) {
    /* '<S11>:1:8' if ((vMin >= minVoltageForLatch) && (abs(Current_mA) < MaxCurrentLimit_mA && ... */
    /* '<S11>:1:9'             abs(Current_mA) > MinCurrentLimit_mA) &&  isChargerConnected == 1 && ... */
    /* '<S11>:1:10'                 MaxImbalance_mV < MaxAllowedImb_mV) */
    guard1 = false;
    if (SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min >=
        SOCEstimation_U.CC_Inputs.minVoltageForLatch_mV) {
      if (SOCEstimation_U.Current_mA < 0) {
        if (SOCEstimation_U.Current_mA <= MIN_int32_T) {
          u = MAX_int32_T;
        } else {
          u = -SOCEstimation_U.Current_mA;
        }
      } else {
        u = SOCEstimation_U.Current_mA;
      }

      /* Switch: '<S3>/Switch5' incorporates:
       *  Inport: '<Root>/Current_mA'
       */
      if (SOCEstimation_U.DataPipeline.VCU.FastCharge) {
        tmp_3 = SOCEstimation_U.CC_Inputs.FastCharge.MaxCurrentLimit_mA;
      } else {
        tmp_3 = SOCEstimation_U.CC_Inputs.SlowCharge.MaxCurrentLimit_mA;
      }

      /* End of Switch: '<S3>/Switch5' */
      if (u < tmp_3) {
        if (SOCEstimation_U.Current_mA < 0) {
          if (SOCEstimation_U.Current_mA <= MIN_int32_T) {
            u = MAX_int32_T;
          } else {
            u = -SOCEstimation_U.Current_mA;
          }
        } else {
          u = SOCEstimation_U.Current_mA;
        }

        /* Switch: '<S3>/Switch6' incorporates:
         *  Inport: '<Root>/Current_mA'
         *  Switch: '<S3>/Switch4'
         */
        if (SOCEstimation_U.DataPipeline.VCU.FastCharge) {
          tmp_3 = SOCEstimation_U.CC_Inputs.FastCharge.MinCurrentLimit_mA;
          tmp = SOCEstimation_U.CC_Inputs.FastCharge.MaxAllowedImb_mV;
        } else {
          tmp_3 = SOCEstimation_U.CC_Inputs.SlowCharge.MinCurrentLimit_mA;
          tmp = SOCEstimation_U.CC_Inputs.SlowCharge.MaxAllowedImb_mV;
        }

        /* End of Switch: '<S3>/Switch6' */
        if ((u > tmp_3) && SOCEstimation_U.DataPipeline.VCU.isChargerConnected &&
            (SOCEstimation_U.DataPipeline.VoltageSenseBus.VoltageDelta_mV < tmp))
        {
          /* '<S11>:1:12' calcSoH  = true; */
          rtb_calcSoH = true;

          /* '<S11>:1:13' latchMake = true; */
          latchMake = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      if ((SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min >= 3550) &&
          (SOCEstimation_U.CC_Inputs.CycleCountTo_SOH > 200.0F)) {
        /* '<S11>:1:15' elseif ((vMax >= 3550 && cycleCount> 200)) */
        /* '<S11>:1:17' calcSoH  = true; */
        rtb_calcSoH = true;

        /* '<S11>:1:18' latchMake = false; */
        latchMake = false;
      } else {
        /* '<S11>:1:20' else */
        /* '<S11>:1:22' calcSoH  = false; */
        rtb_calcSoH = false;

        /* '<S11>:1:23' latchMake = false; */
        latchMake = false;
      }
    }
  } else {
    /* '<S11>:1:25' else */
    /* '<S11>:1:27' calcSoH  = false; */
    rtb_calcSoH = false;

    /* '<S11>:1:28' latchMake = false; */
    latchMake = false;
  }

  /* End of MATLAB Function: '<S3>/MATLAB Function' */

  /* Chart: '<S8>/SOC_Estimator' incorporates:
   *  Inport: '<Root>/CC_Inputs'
   *  Inport: '<Root>/DataPipeline'
   *  Inport: '<Root>/EKF_Inputs'
   *  MATLAB Function: '<S6>/MATLAB Function'
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
    /* Transition: '<S13>:24' */
    SOCEstimation_DW.temporalCounter_i1 = 0U;
    SOCEstimation_DW.is_c15_SOCEstimation = SOCEstimatio_IN_Vehicle_at_Rest;

    /* Entry 'Vehicle_at_Rest': '<S13>:9' */
    /* '<S13>:9:2' CC_State = CCState.Vehicle_at_Rest; */
    SOCEstimation_DW.UnitDelay_DSTATE = Vehicle_at_Rest;
  } else {
    switch (SOCEstimation_DW.is_c15_SOCEstimation) {
     case SOCEstimatio_IN_CoulombCounting:
      SOCEstimation_DW.UnitDelay_DSTATE = CoulombCounting;

      /* During 'CoulombCounting': '<S13>:3' */
      /* '<S13>:219:1' sf_internal_predicateOutput = duration(EKFstateChange && EKFcalibration && ~DataPipeline.VCU.isChargerConnected... */
      /* '<S13>:219:2' , msec ) > DebouncingTimeout_msec; */
      if ((!rtb_stateChange) || (!rtb_LogicalOperator3) ||
          SOCEstimation_U.DataPipeline.VCU.isChargerConnected) {
        SOCEstimation_DW.durationCounter_1 = 0U;
      }

      if ((uint32_T)((int32_T)SOCEstimation_DW.durationCounter_1 * SOCEstimation_U.looptimeSoC) >
          (uint16_T)SOCEstimation_U.CC_Inputs.DebouncingTimeout_msec) {
        /* Transition: '<S13>:219' */
        SOCEstimation_DW.temporalCounter_i1 = 0U;
        SOCEstimation_DW.is_c15_SOCEstimation = SOCEstimation_IN_HybridCounting;

        /* Entry 'HybridCounting': '<S13>:217' */
        /* '<S13>:217:3' CC_State  = CCState.EKFestimation; */
        SOCEstimation_DW.UnitDelay_DSTATE = EKFestimation;

        /* '<S13>:217:4' initialSoC     = (double(TotalCapacityRemains_mAh) / MaxUsableCapacity_mAh) * 100; */
        rtb_SOC_ChargeDischarge = rt_roundd((real_T)
          SOCEstimation_B.TotalCapacityRemains_mAh / (real_T)Switch_f);
        if (rtb_SOC_ChargeDischarge < 2.147483648E+9) {
          if (rtb_SOC_ChargeDischarge >= -2.147483648E+9) {
            u = (int32_T)rtb_SOC_ChargeDischarge;
          } else {
            u = MIN_int32_T;
          }
        } else {
          u = MAX_int32_T;
        }

        SOCEstimation_DW.initialSoC = mul_s32_sat_cc(u, 100);

        /* '<S13>:217:5' modeSel = 1; */
        /* '<S13>:217:6' resetEKF = true; */
        /* '<S13>:217:7' SoCEst = EKFController(DataPipeline.Current_mA , DataPipeline.VoltageSenseBus.mV_min,... */
        /* '<S13>:217:8'            EKF_Inputs.loopTimeEKF, modeSel, MaxUsableCapacity_mAh, EKF_Inputs.processNoise,... */
        /* '<S13>:217:9'            EKF_Inputs.measurementNoise, EKF_Inputs.cellIR_mOhm, initialSoC, resetEKF, EKF_Inputs.SoCData , EKF_Inputs.ocvData); */
        SOCEstimation_EKFController(SOCEstimation_U.DataPipeline.Current_mA,
          SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min,
          SOCEstimation_U.EKF_Inputs.loopTimeEKF, 1.0, Switch_f,
          SOCEstimation_U.EKF_Inputs.processNoise,
          SOCEstimation_U.EKF_Inputs.measurementNoise,
          SOCEstimation_U.EKF_Inputs.cellIR_mOhm, SOCEstimation_DW.initialSoC,
          true, SOCEstimation_U.EKF_Inputs.SoCData,
          SOCEstimation_U.EKF_Inputs.ocvData);

        /* '<S13>:217:10' resetEKF = false; */
        SOCEstimation_DW.resetEKF = false;

        /* '<S13>:217:11' modeSel = 1; */
        /* '<S13>:217:12' SoCEst = EKFController(DataPipeline.Current_mA , DataPipeline.VoltageSenseBus.mV_min,... */
        /* '<S13>:217:13'            EKF_Inputs.loopTimeEKF, modeSel, MaxUsableCapacity_mAh, EKF_Inputs.processNoise,... */
        /* '<S13>:217:14'            EKF_Inputs.measurementNoise, EKF_Inputs.cellIR_mOhm, initialSoC, resetEKF, EKF_Inputs.SoCData , EKF_Inputs.ocvData); */
        SOCEstimation_B.SoCEst = SOCEstimation_EKFController
          (SOCEstimation_U.DataPipeline.Current_mA,
           SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min,
           SOCEstimation_U.EKF_Inputs.loopTimeEKF, 1.0, Switch_f,
           SOCEstimation_U.EKF_Inputs.processNoise,
           SOCEstimation_U.EKF_Inputs.measurementNoise,
           SOCEstimation_U.EKF_Inputs.cellIR_mOhm, SOCEstimation_DW.initialSoC,
           false, SOCEstimation_U.EKF_Inputs.SoCData,
           SOCEstimation_U.EKF_Inputs.ocvData);
      } else {
        /* '<S13>:158:1' sf_internal_predicateOutput = duration((pseudoLatchFlag == true && fullChargeFlag == false)... */
        /* '<S13>:158:2' ,msec) > DebouncingTimeout_msec; */
        if (tmp_4 || SOCEstimation_U.CC_Inputs.fullChargeFlag) {
          SOCEstimation_DW.durationCounter_2 = 0U;
        }

        if ((uint32_T)((int32_T)SOCEstimation_DW.durationCounter_2 * SOCEstimation_U.looptimeSoC) >
            (uint16_T)SOCEstimation_U.CC_Inputs.DebouncingTimeout_msec) {
          /* Transition: '<S13>:158' */
          SOCEstimation_DW.durationCounter_1_l = 0U;
          SOCEstimation_DW.temporalCounter_i1 = 0U;
          SOCEstimation_DW.is_c15_SOCEstimation =
            SOCEstimation_IN_PseudoLatching;

          /* Entry 'PseudoLatching': '<S13>:153' */
          /* '<S13>:153:3' CC_State = CCState.PseudoLatching; */
          SOCEstimation_DW.UnitDelay_DSTATE = PseudoLatching;
        } else {
          /* '<S13>:78:1' sf_internal_predicateOutput = duration( latchMake == true, msec) >DebouncingTimeout_msec; */
          if (!latchMake) {
            SOCEstimation_DW.durationCounter_3 = 0U;
          }

          if ((uint32_T)((int32_T)SOCEstimation_DW.durationCounter_3 * SOCEstimation_U.looptimeSoC) >
              (uint16_T)SOCEstimation_U.CC_Inputs.DebouncingTimeout_msec) {
            /* Transition: '<S13>:78' */
            /* '<S13>:78:2' capLatch = TotalCapacityRemains_mAh; */
            // SOCEstimation_B.capLatch = SOCEstimation_B.TotalCapacityRemains_mAh;
            SOCEstimation_DW.temporalCounter_i1 = 0U;
            SOCEstimation_DW.is_c15_SOCEstimation =
              SOCEsti_IN_Recalibrate_Charging;

            /* Entry 'Recalibrate_Charging': '<S13>:6' */
            /* '<S13>:6:3' CC_State = CCState.Recalibrate; */
            SOCEstimation_DW.UnitDelay_DSTATE = Recalibrate;

            /* '<S13>:6:4' Initial_Capacity_mAh = int32(MaxUsableCapacity_mAh); */
            SOCEstimation_B.Initial_Capacity_mAh = Switch_f;

            /* '<S13>:6:5' TotalCapacityRemains_mAh = Initial_Capacity_mAh; */
            SOCEstimation_B.TotalCapacityRemains_mAh =
              SOCEstimation_B.Initial_Capacity_mAh;

            /* '<S13>:3:5' TotalCapacityRemains_mAh = Initial_Capacity_mAh + IntegratedCurrent */
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

      /* During 'HybridCounting': '<S13>:217' */
      /* '<S13>:218:1' sf_internal_predicateOutput = (EKFstateChange == false  ||  EKFcalibration == false) && after(CCTimeout_msec * 5, msec); */
      u = SOCEstimation_U.CC_Inputs.CCTimeout_msec * 5;
      if (u > 32767) {
        u = 32767;
      } else if (u < -32768) {
        u = -32768;
      }

      if (((!rtb_stateChange) || (!rtb_LogicalOperator3)) && ((uint32_T)
           ((int32_T)SOCEstimation_DW.temporalCounter_i1 * 100) >= (uint16_T)u))
      {
        /* Transition: '<S13>:218' */
        SOCEstimation_DW.durationCounter_3 = 0U;
        SOCEstimation_DW.durationCounter_2 = 0U;
        SOCEstimation_DW.durationCounter_1 = 0U;
        SOCEstimation_DW.is_c15_SOCEstimation = SOCEstimatio_IN_CoulombCounting;

        /* Entry 'CoulombCounting': '<S13>:3' */
        /* '<S13>:3:3' CC_State = CCState.CoulombCounting; */
        SOCEstimation_DW.UnitDelay_DSTATE = CoulombCounting;
      } else {
        /* '<S13>:217:16' modeSel = 0; */
        /* '<S13>:217:17' SoCEst = EKFController(DataPipeline.Current_mA , DataPipeline.VoltageSenseBus.mV_min,... */
        /* '<S13>:217:18'           EKF_Inputs.loopTimeEKF, modeSel, MaxUsableCapacity_mAh, EKF_Inputs.processNoise,... */
        /* '<S13>:217:19'           EKF_Inputs.measurementNoise, EKF_Inputs.cellIR_mOhm, initialSoC, resetEKF, EKF_Inputs.SoCData , EKF_Inputs.ocvData); */
        SOCEstimation_B.SoCEst = SOCEstimation_EKFController
          (SOCEstimation_U.DataPipeline.Current_mA,
           SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min,
           SOCEstimation_U.EKF_Inputs.loopTimeEKF, 0.0, Switch_f,
           SOCEstimation_U.EKF_Inputs.processNoise,
           SOCEstimation_U.EKF_Inputs.measurementNoise,
           SOCEstimation_U.EKF_Inputs.cellIR_mOhm, SOCEstimation_DW.initialSoC,
           SOCEstimation_DW.resetEKF, SOCEstimation_U.EKF_Inputs.SoCData,
           SOCEstimation_U.EKF_Inputs.ocvData);

        /* '<S13>:217:20' Initial_Capacity_mAh = (int32(SoCEst) * MaxUsableCapacity_mAh)/100; */
        rtb_SOC_ChargeDischarge = rt_roundd(SOCEstimation_B.SoCEst);
        if (rtb_SOC_ChargeDischarge < 2.147483648E+9) {
          if (rtb_SOC_ChargeDischarge >= -2.147483648E+9) {
            u = (int32_T)rtb_SOC_ChargeDischarge;
          } else {
            u = MIN_int32_T;
          }
        } else {
          u = MAX_int32_T;
        }

        SOCEstimation_B.Initial_Capacity_mAh = (int32_T)rt_roundd((real_T)
          mul_s32_sat_cc(u, Switch_f) / 100.0);
      }
      break;

     case SOCEstimation_IN_PseudoLatching:
      SOCEstimation_DW.UnitDelay_DSTATE = PseudoLatching;

      /* During 'PseudoLatching': '<S13>:153' */
      /* '<S13>:159:1' sf_internal_predicateOutput = (TotalCapacityRemains_mAh >= MaxUsableCapacity_mAh) && after(DebouncingTimeout_msec, msec); */
      if ((SOCEstimation_B.TotalCapacityRemains_mAh >= Switch_f) && ((uint32_T)
           ((int32_T)SOCEstimation_DW.temporalCounter_i1 * 100) >= (uint16_T)
           SOCEstimation_U.CC_Inputs.DebouncingTimeout_msec)) {
        /* Transition: '<S13>:159' */
        SOCEstimation_DW.temporalCounter_i1 = 0U;
        SOCEstimation_DW.is_c15_SOCEstimation = SOCEsti_IN_Recalibrate_Charging;

        /* Entry 'Recalibrate_Charging': '<S13>:6' */
        /* '<S13>:6:3' CC_State = CCState.Recalibrate; */
        SOCEstimation_DW.UnitDelay_DSTATE = Recalibrate;

        /* '<S13>:6:4' Initial_Capacity_mAh = int32(MaxUsableCapacity_mAh); */
        SOCEstimation_B.Initial_Capacity_mAh = Switch_f;

        /* '<S13>:6:5' TotalCapacityRemains_mAh = Initial_Capacity_mAh; */
        SOCEstimation_B.TotalCapacityRemains_mAh =
          SOCEstimation_B.Initial_Capacity_mAh;
      } else {
        /* '<S13>:206:1' sf_internal_predicateOutput = duration((pseudoLatchFlag == false && fullChargeFlag == false)... */
        /* '<S13>:206:2' ,msec) > DebouncingTimeout_msec; */
        if (SOCEstimation_U.CC_Inputs.pseudoLatchFlag ||
            SOCEstimation_U.CC_Inputs.fullChargeFlag) {
          SOCEstimation_DW.durationCounter_1_l = 0U;
        }

        if ((uint32_T)((int32_T)SOCEstimation_DW.durationCounter_1_l * SOCEstimation_U.looptimeSoC) >
            (uint16_T)SOCEstimation_U.CC_Inputs.DebouncingTimeout_msec) {
          /* Transition: '<S13>:206' */
          SOCEstimation_DW.durationCounter_3 = 0U;
          SOCEstimation_DW.durationCounter_2 = 0U;
          SOCEstimation_DW.durationCounter_1 = 0U;
          SOCEstimation_DW.is_c15_SOCEstimation =
            SOCEstimatio_IN_CoulombCounting;

          /* Entry 'CoulombCounting': '<S13>:3' */
          /* '<S13>:3:3' CC_State = CCState.CoulombCounting; */
          SOCEstimation_DW.UnitDelay_DSTATE = CoulombCounting;

          /* '<S13>:153:5' TotalCapacityRemains_mAh = Initial_Capacity_mAh + IntegratedCurrent; */
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

      /* During 'Recalibrate_Charging': '<S13>:6' */
      /* '<S13>:28:1' sf_internal_predicateOutput = after(CCTimeout_msec, msec); */
      if ((uint32_T)((int32_T)SOCEstimation_DW.temporalCounter_i1 * 100) >=
          (uint16_T)SOCEstimation_U.CC_Inputs.CCTimeout_msec) {
        /* Transition: '<S13>:28' */
        SOCEstimation_DW.durationCounter_3 = 0U;
        SOCEstimation_DW.durationCounter_2 = 0U;
        SOCEstimation_DW.durationCounter_1 = 0U;
        SOCEstimation_DW.is_c15_SOCEstimation = SOCEstimatio_IN_CoulombCounting;

        /* Entry 'CoulombCounting': '<S13>:3' */
        /* '<S13>:3:3' CC_State = CCState.CoulombCounting; */
        SOCEstimation_DW.UnitDelay_DSTATE = CoulombCounting;
      }
      break;

     default:
      SOCEstimation_DW.UnitDelay_DSTATE = Vehicle_at_Rest;

      /* During 'Vehicle_at_Rest': '<S13>:9' */
      /* '<S13>:19:1' sf_internal_predicateOutput = (syncCounter > 7) && after(CCTimeout_msec, msec); */
      if ((SOCEstimation_DW.counter > 7.0) && ((uint32_T)((int32_T)
            SOCEstimation_DW.temporalCounter_i1 * 100) >= (uint16_T)
           SOCEstimation_U.CC_Inputs.CCTimeout_msec)) {
        /* Transition: '<S13>:19' */
        SOCEstimation_DW.durationCounter_3 = 0U;
        SOCEstimation_DW.durationCounter_2 = 0U;
        SOCEstimation_DW.durationCounter_1 = 0U;
        SOCEstimation_DW.is_c15_SOCEstimation = SOCEstimatio_IN_CoulombCounting;

        /* Entry 'CoulombCounting': '<S13>:3' */
        /* '<S13>:3:3' CC_State = CCState.CoulombCounting; */
        SOCEstimation_DW.UnitDelay_DSTATE = CoulombCounting;
      } else {
        /* Switch: '<S14>/Switch2' incorporates:
         *  RelationalOperator: '<S14>/LowerRelop1'
         *  RelationalOperator: '<S14>/UpperRelop'
         *  Switch: '<S14>/Switch'
         */
        /* '<S13>:9:4' Initial_Capacity_mAh = int32(Initial_Guess_mAh); */
        if (SOCEstimation_B.sf_SOC_ReadFromEEPROM.CapacityRemains_mAh > Switch_f)
        {
          SOCEstimation_B.Initial_Capacity_mAh = Switch_f;
        } else if (SOCEstimation_B.sf_SOC_ReadFromEEPROM.CapacityRemains_mAh < 0)
        {
          /* Switch: '<S14>/Switch' incorporates:
           *  Constant: '<S8>/Constant2'
           */
          SOCEstimation_B.Initial_Capacity_mAh = 0;
        } else {
          SOCEstimation_B.Initial_Capacity_mAh =
            SOCEstimation_B.sf_SOC_ReadFromEEPROM.CapacityRemains_mAh;
        }

        /* End of Switch: '<S14>/Switch2' */
        /* '<S13>:9:5' TotalCapacityRemains_mAh = Initial_Capacity_mAh */
        SOCEstimation_B.TotalCapacityRemains_mAh =
          SOCEstimation_B.Initial_Capacity_mAh;
      }
      break;
    }
  }

  if (rtb_stateChange && rtb_LogicalOperator3 &&
      (!SOCEstimation_U.DataPipeline.VCU.isChargerConnected)) {
    SOCEstimation_DW.durationCounter_1++;
  } else {
    SOCEstimation_DW.durationCounter_1 = 0U;
  }

  if (SOCEstimation_U.CC_Inputs.pseudoLatchFlag && tmp_5) {
    SOCEstimation_DW.durationCounter_2++;
  } else {
    SOCEstimation_DW.durationCounter_2 = 0U;
  }

  if (tmp_4 && tmp_5) {
    SOCEstimation_DW.durationCounter_1_l++;
  } else {
    SOCEstimation_DW.durationCounter_1_l = 0U;
  }

  if (latchMake) {
    SOCEstimation_DW.durationCounter_3++;
  } else {
    SOCEstimation_DW.durationCounter_3 = 0U;
  }

  /* Product: '<S12>/Divide2' */
  rtb_SOC_ChargeDischarge = (real_T)SOCEstimation_B.TotalCapacityRemains_mAh /
    (real_T)Switch_f;

  /* Saturate: '<S12>/Saturation' incorporates:
   *  Gain: '<S12>/Gain1'
   */
  SOCEstimation_DW.Delay1_DSTATE_m = (int32_T)floor(10000.0 *
    rtb_SOC_ChargeDischarge);

  /* Saturate: '<S12>/Saturation' */
  if (SOCEstimation_DW.Delay1_DSTATE_m > 10000) {
    /* Saturate: '<S12>/Saturation' */
    SOCEstimation_DW.Delay1_DSTATE_m = 10000;
  } else if (SOCEstimation_DW.Delay1_DSTATE_m < 0) {
    /* Saturate: '<S12>/Saturation' */
    SOCEstimation_DW.Delay1_DSTATE_m = 0;
  }

  /* End of Saturate: '<S12>/Saturation' */

  /* Switch: '<S12>/Switch' */
  if (SOCEstimation_DW.UnitDelay_DSTATE >= EKFestimation) {
    /* Gain: '<S12>/Gain' */
    rtb_SOC_ChargeDischarge = 100.0 * SOCEstimation_B.SoCEst;

    /* Saturate: '<S12>/Saturation1' */
    if (rtb_SOC_ChargeDischarge > 10000.0) {
      rtb_SOC_ChargeDischarge = 10000.0;
    } else if (rtb_SOC_ChargeDischarge < 0.0) {
      rtb_SOC_ChargeDischarge = 0.0;
    }

    /* BusCreator: '<S1>/Bus Creator1' incorporates:
     *  Outport: '<Root>/CC_Outputs'
     *  Saturate: '<S12>/Saturation1'
     */
    SOCEstimation_Y.CC_Outputs.SOC_cpct = (int32_T)floor(rtb_SOC_ChargeDischarge);
  } else {
    /* BusCreator: '<S1>/Bus Creator1' incorporates:
     *  Outport: '<Root>/CC_Outputs'
     */
    SOCEstimation_Y.CC_Outputs.SOC_cpct = SOCEstimation_DW.Delay1_DSTATE_m;
  }

  /* End of Switch: '<S12>/Switch' */

  /* Chart: '<S10>/Modulus IntegCurrent' incorporates:
   *  Abs: '<S10>/Abs'
   *  Inport: '<Root>/DataPipeline'
   */
  /* Gateway: SOCEstimation/SOC_Calc/Integrators/Modulus IntegCurrent */
  /* During: SOCEstimation/SOC_Calc/Integrators/Modulus IntegCurrent */
  if (SOCEstimation_DW.is_active_c20_SOCEstimation == 0U) {
    /* Entry: SOCEstimation/SOC_Calc/Integrators/Modulus IntegCurrent */
    SOCEstimation_DW.is_active_c20_SOCEstimation = 1U;

    /* Entry Internal: SOCEstimation/SOC_Calc/Integrators/Modulus IntegCurrent */
    /* Transition: '<S17>:4' */
    /* Entry 'ModIntegratedCurrent': '<S17>:3' */
  } else {
    /* Abs: '<S10>/Abs' incorporates:
     *  Inport: '<Root>/Current_mA'
     */
    /* During 'ModIntegratedCurrent': '<S17>:3' */
    /* '<S17>:3:3' ModIntegratedCurrent = single(single(LoopTimer_SOC_msec)*single(Current_mA))+ModIntegratedCurrent; */
    if (SOCEstimation_U.Current_mA < 0) {
      u = -SOCEstimation_U.Current_mA;
    } else {
      u = SOCEstimation_U.Current_mA;
    }

    SOCEstimation_B.ModIntegratedCurrent +=
      SOCEstimation_U.DataPipeline.LoopTimer_SOC_msec * (real32_T)u;
  }

  /* End of Chart: '<S10>/Modulus IntegCurrent' */

  /* DataTypeConversion: '<S10>/Data Type Conversion5' incorporates:
   *  Gain: '<S10>/Gain3'
   *  Gain: '<S10>/Multiply1'
   */
  SOCEstimation_Y.CC_Outputs.TotalCapacityExchange_mAh = (int32_T)floorf(0.001F *
    SOCEstimation_B.ModIntegratedCurrent * 0.000277777785F);

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/CC_Inputs'
   */
  /* MATLAB Function 'SOCEstimation/MATLAB Function': '<S2>:1' */
  /* '<S2>:1:3' if (calcSoH && prevLatch) */
  if (rtb_calcSoH && SOCEstimation_B.sf_SOC_ReadFromEEPROM.PrevLatch) {               
    /* '<S2>:1:4' SoH2 = single((single(capLatch) / single(insCap))) * 100; */
    rtb_SoH2 = (real32_T)SOCEstimation_B.TotalCapacityRemains_mAh / (real32_T)
    SOCEstimation_U.CC_Inputs.InstalledCapacity_mAh / (real32_T)
    SOCEstimation_B.sf_SOC_ReadFromEEPROM.TcompPersist * 100.0F;
    int8_t delSoH = rtb_SoH2 - SOCEstimation_Y.CC_Outputs.SOH_pct;
    if(delSoH < 0)
    {
      delSoH *= -1; 
    }

    if(delSoH >= 5)                                                               //Added Tdelta <= 5 cond.  for SoH2 calc.   manual changes                                                                 
    {
      rtb_SoH2 = SOCEstimation_B.sf_SOC_ReadFromEEPROM.SoH2;
    }
    else
    {
      SOCEstimation_B.sf_SOC_ReadFromEEPROM.SoH2        = rtb_SoH2;                  //manual changes done for SoH2 sequence
      rtb_calcSoH                                       = false; 
      SOCEstimation_B.sf_SOC_ReadFromEEPROM.SoHCalcEn   = true;                        
      SOCEstimation_B.sf_SOC_ReadFromEEPROM.cycleCount  += (SOCEstimation_Y.CC_Outputs.Total_CapacityRemains_mAh / SOCEstimation_U.CC_Inputs.InstalledCapacity_mAh);
    }
    debugLatchCapacity = SOCEstimation_B.TotalCapacityRemains_mAh;        //Debug purpose

    /* '<S2>:1:5' prevSoH2 = SoH2; */
    /* '<S2>:1:6' calcSoH = false; */
  } else {
    /* '<S2>:1:7' else */
    /* '<S2>:1:8' SoH2 = prevSoH2; */
    rtb_SoH2 = SOCEstimation_B.sf_SOC_ReadFromEEPROM.SoH2;
  }

  /* End of MATLAB Function: '<S1>/MATLAB Function' */

  /* BusCreator: '<S1>/Bus Creator1' incorporates:
   *  Outport: '<Root>/CC_Outputs'
   */
  SOCEstimation_Y.CC_Outputs.Total_CapacityRemains_mAh =
    SOCEstimation_B.TotalCapacityRemains_mAh;
  SOCEstimation_Y.CC_Outputs.CC_State = SOCEstimation_DW.UnitDelay_DSTATE;
  SOCEstimation_Y.CC_Outputs.MaxUsableCapacity_mAh = Switch_f;
  SOCEstimation_Y.CC_Outputs.SOH_pct = SOCEstimation_B.Switch;

  /* Saturate: '<S1>/Saturation' */
  if (rtb_SoH2 > 100.0F) {
    /* BusCreator: '<S1>/Bus Creator1' incorporates:
     *  Outport: '<Root>/CC_Outputs'
     */
    SOCEstimation_Y.CC_Outputs.SoH2 = 100.0F;
  } else if (rtb_SoH2 < 0.0F) {
    /* BusCreator: '<S1>/Bus Creator1' incorporates:
     *  Outport: '<Root>/CC_Outputs'
     */
    SOCEstimation_Y.CC_Outputs.SoH2 = 0.0F;
  } else {
    /* BusCreator: '<S1>/Bus Creator1' incorporates:
     *  Outport: '<Root>/CC_Outputs'
     */
    SOCEstimation_Y.CC_Outputs.SoH2 = rtb_SoH2;
  }

  /* End of Saturate: '<S1>/Saturation' */

  /* Update for Delay: '<S9>/Delay1' incorporates:
   *  Inport: '<Root>/Current_mA'
   */
  SOCEstimation_DW.Delay1_DSTATE = SOCEstimation_U.Current_mA;

  /* Update for Delay: '<S9>/Delay' incorporates:
   *  Inport: '<Root>/DataPipeline'
   *  SignalConversion generated from: '<S3>/Bus Selector3'
   */
  SOCEstimation_DW.Delay_DSTATE =
    SOCEstimation_U.DataPipeline.VoltageSenseBus.mV_min;
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

  /* InitializeConditions for Delay: '<S9>/Delay1' */
  SOCEstimation_DW.Delay1_DSTATE = 0;

  /* InitializeConditions for Delay: '<S9>/Delay' */
  SOCEstimation_DW.Delay_DSTATE = 0;

  /* InitializeConditions for Saturate: '<S12>/Saturation' incorporates:
   *  Delay: '<S3>/Delay1'
   */
  SOCEstimation_DW.Delay1_DSTATE_m = 0;

  /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
  SOCEstimation_DW.UnitDelay_DSTATE = Vehicle_at_Rest;

  /* SystemInitialize for DataTypeConversion: '<S20>/Data Type Conversion1' incorporates:
   *  Outport: '<S5>/MaxUsableCapacity'
   */
  SOCEstimation_B.Effectiveusablecapacity = 0;

  /* SystemInitialize for Switch: '<S5>/Switch' incorporates:
   *  Outport: '<S5>/SOH_pct'
   */
  SOCEstimation_B.Switch = 0.0F;

  /* End of SystemInitialize for SubSystem: '<S1>/SoH calculation' */

  /* SystemInitialize for MATLAB Function: '<S6>/MATLAB Function' */
  SOCEstimation_DW.counter_not_empty = false;

  /* SystemInitialize for Chart: '<S10>/IntegCurrent' */
  SOCEstimation_B.IntegratedCurrent = 0.0F;
  SOCEstimation_DW.is_active_c42_SOCEstimation = 0U;
  SOCEstimation_DW.is_c42_SOCEstimation = SOCEstimatio_IN_NO_ACTIVE_CHILD;

  /* SystemInitialize for Chart: '<S8>/SOC_Estimator' */
  SOCEstimation_DW.temporalCounter_i1 = 0U;

  /* '<S13>:221:7' x = 0; */
  SOCEstimation_DW.x = 0.0;

  /* '<S13>:221:8' EKF_P = double(1e-3); */
  SOCEstimation_DW.EKF_P = 0.001;

  /* '<S13>:221:9' H_prev = 0; */
  SOCEstimation_DW.H_prev = 0.0;

  /* '<S13>:221:10' filteredVoltage = 0; */
  SOCEstimation_DW.filteredVoltage = 0.0;
  // SOCEstimation_B.capLatch = 0;
  SOCEstimation_B.TotalCapacityRemains_mAh = 0;
  SOCEstimation_B.Initial_Capacity_mAh = 0;
  SOCEstimation_B.SoCEst = 0.0;
  SOCEstimation_DW.resetEKF = false;
  SOCEstimation_DW.initialSoC = 0;
  SOCEstimation_DW.is_active_c15_SOCEstimation = 0U;
  SOCEstimation_DW.is_c15_SOCEstimation = SOCEstimatio_IN_NO_ACTIVE_CHILD;

  /* SystemInitialize for Chart: '<S10>/Modulus IntegCurrent' */
  SOCEstimation_B.ModIntegratedCurrent = 0.0F;
  SOCEstimation_DW.is_active_c20_SOCEstimation = 0U;
}

/* Model terminate function */
void SOCEstimation_terminate(void)
{
  /* (no terminate code required) */
}
