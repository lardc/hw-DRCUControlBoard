#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "ZwGPIO.h"
#include "ZwSPI.h"

// Functions
//
void LL_ToggleBoardLED();
void LL_SW_Trig(bool Start);
void LL_OutputLock(bool State);
void LL_IntPowerSupplyEn(bool State);
void LL_OverVoltageProtectionReset();
void LL_IntPowerSupplyDischarge(bool State);
bool LL_ReadLineSync();

#endif //__LOWLEVEL_H
