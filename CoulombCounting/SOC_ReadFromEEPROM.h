/*
 * Code generation for system system '<S1>/SOC_ReadFromEEPROM'
 * For more details, see corresponding source file SOC_ReadFromEEPROM.c
 *
 */

 #ifndef SOC_ReadFromEEPROM_h_
 #define SOC_ReadFromEEPROM_h_
 #ifndef SOCEstimation_COMMON_INCLUDES_
 #define SOCEstimation_COMMON_INCLUDES_
 #include <stdio.h>
 #include "rtwtypes.h"
 #include "rtw_continuous.h"
 #include "rtw_solver.h"
 #endif                                 /* SOCEstimation_COMMON_INCLUDES_ */
 
 /* Block signals for system '<S1>/SOC_ReadFromEEPROM' */
 typedef struct {
   real32_T cycleCount;                 /* '<S1>/SOC_ReadFromEEPROM' */
   int32_T CapacityRemains_mAh;         /* '<S1>/SOC_ReadFromEEPROM' */
 } B_SOC_ReadFromEEPROM_SOCEstim_T;
 
 extern void SOCEstimatio_SOC_ReadFromEEPROM(B_SOC_ReadFromEEPROM_SOCEstim_T
   *localB);
 
 #endif                                 /* SOC_ReadFromEEPROM_h_ */
 