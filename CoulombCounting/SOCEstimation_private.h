/*
 * SOCEstimation_private.h
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

 #ifndef SOCEstimation_private_h_
 #define SOCEstimation_private_h_
 #include "rtwtypes.h"
 #include "multiword_types.h"
 #include "zero_crossing_types.h"
 #include "SOCEstimation_types.h"
 #include "SOCEstimation.h"
 #include "rtw_continuous.h"
 #include "rtw_solver.h"
 #ifndef UCHAR_MAX
 #include <limits.h>
 #endif
 
 #if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
 #error Code was generated for compiler with different sized uchar/char. \
 Consider adjusting Test hardware word size settings on the \
 Hardware Implementation pane to match your compiler word sizes as \
 defined in limits.h of the compiler. Alternatively, you can \
 select the Test hardware is the same as production hardware option and \
 select the Enable portable word sizes option on the Code Generation > \
 Verification pane for ERT based targets, which will disable the \
 preprocessor word size checks.
 #endif
 
 #if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
 #error Code was generated for compiler with different sized ushort/short. \
 Consider adjusting Test hardware word size settings on the \
 Hardware Implementation pane to match your compiler word sizes as \
 defined in limits.h of the compiler. Alternatively, you can \
 select the Test hardware is the same as production hardware option and \
 select the Enable portable word sizes option on the Code Generation > \
 Verification pane for ERT based targets, which will disable the \
 preprocessor word size checks.
 #endif
 
 #if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
 #error Code was generated for compiler with different sized uint/int. \
 Consider adjusting Test hardware word size settings on the \
 Hardware Implementation pane to match your compiler word sizes as \
 defined in limits.h of the compiler. Alternatively, you can \
 select the Test hardware is the same as production hardware option and \
 select the Enable portable word sizes option on the Code Generation > \
 Verification pane for ERT based targets, which will disable the \
 preprocessor word size checks.
 #endif
 
 #if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
 #error Code was generated for compiler with different sized ulong/long. \
 Consider adjusting Test hardware word size settings on the \
 Hardware Implementation pane to match your compiler word sizes as \
 defined in limits.h of the compiler. Alternatively, you can \
 select the Test hardware is the same as production hardware option and \
 select the Enable portable word sizes option on the Code Generation > \
 Verification pane for ERT based targets, which will disable the \
 preprocessor word size checks.
 #endif
 
 extern real_T rt_roundd(real_T u);
 extern real_T sMultiWord2Double(const uint32_T u1[], int32_T n1, int32_T e1);
 extern void sMultiWordMul_cc(const uint32_T u1[], int32_T n1, const uint32_T u2[],
   int32_T n2, uint32_T y[], int32_T n);
 extern real32_T sMultiWord2Single_cc(const uint32_T u1[], int32_T n1, int32_T e1);
 extern void MultiWordSignedWrap_cc(const uint32_T u1[], int32_T n1, uint32_T n2,
   uint32_T y[]);
 extern void sMultiWordShl_cc(const uint32_T u1[], int32_T n1, uint32_T n2, uint32_T
   y[], int32_T n);
 extern void sLong2MultiWord_cc(int32_T u, uint32_T y[], int32_T n);
 extern void mul_wide_s32_cc(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi,
   uint32_T *ptrOutBitsLo);
 extern int32_T mul_s32_sat_cc(int32_T a, int32_T b);
 
 #endif                                 /* SOCEstimation_private_h_ */
 