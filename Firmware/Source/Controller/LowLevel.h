#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "ZwGPIO.h"
#include "ZwSPI.h"

// Functions
//
void LL_ToggleBoardLED();
void LL_ExternalLED(bool State);
void LL_ExternalFAN(bool State);
void LL_PowerOn(bool State);
void LL_External_DC_RDY(bool State);
void LL_DAC_Write(uint16_t Data);
void LL_SW_Trig(bool State);
void LL_R0_Set();
void LL_R1_Set();
void LL_R2_Set();
void LL_DRCU_HVPS(bool State);

#endif //__LOWLEVEL_H
