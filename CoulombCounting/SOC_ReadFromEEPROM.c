 /*
 * Code generation for system system '<S1>/SOC_ReadFromEEPROM'
 *
 * Model                      : SOCEstimation
 * Model version              : 7.214
 * Simulink Coder version : 24.1 (R2024a) 19-Nov-2023
 * C source code generated on : Wed Apr 16 22:59:08 2025
 *
 * Note that the functions contained in this file are part of a Simulink
 * model, and are not self-contained algorithms.
 */

 #include "SOC_ReadFromEEPROM.h"
 #include "SOCEstimation_private.h"
 #include "bmsConfiguration.h"
 #include "controlOperations.h"

/**************Private Variables****************/
uint8_t ReadFromFlashCounter = 0;

/**************External Variables****************/
extern bool SoCFromLookupTableFlag;
extern uint8_t eepromCorrupted;
extern coulombCountingOutput_t ccOutputDataMemory;
extern coulombCountingOutput_t ccInputData;

/* Output and update for atomic system: '<S1>/SOC_ReadFromEEPROM' */
void SOCEstimatio_SOC_ReadFromEEPROM(B_SOC_ReadFromEEPROM_SOCEstim_T *localB)
{
  if((ReadFromFlashCounter == 0) && (SoCFromLookupTableFlag == false))
  {
      localB->CapacityRemains_mAh = ccOutputDataMemory.totalCapacityRemaining;
      localB->cycleCount          = ccOutputDataMemory.CycleCount;

      ReadFromFlashCounter++;
  }
}


