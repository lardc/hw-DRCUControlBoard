#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "ZwGPIO.h"
#include "ZwSPI.h"

// Functions
//
void LL_ToggleBoardLED();
void LL_ExternalLamp(bool State);
void LL_FAN(bool State);
void LL_SW_Trig(bool Start);
void LL_PowerOnMechRelay(bool State);
void LL_PowerOnSolidStateRelay(bool State);
void LL_ReversVCompensation(bool State);
void LL_OutputLock(bool State);
void LL_IntPowerSupplyEn(bool State);
void LL_OverVoltageProtectionReset();
void LL_IntPowerSupplyDischarge(bool State);
void LL_ExtRegWriteData(Int16U Data);
bool LL_ReadLineSync();
void LL_FlipLineRCK();

#endif //__LOWLEVEL_H
