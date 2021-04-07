#ifndef __LOGIC_H
#define __LOGIC_H

#include "stdinc.h"

// Variables
//
extern volatile uint16_t LOGIC_DUTCurrentRaw[];

//Functions
//
void LOGIC_ResetHWToDefaults(bool StopPowerSupply);
void LOGIC_BatteryCharge(bool State);
void LOGIC_SofwarePulseStart(bool State);
void LOGIC_ConstantPulseRateConfig(Int16U PulseWidth);
void LOGIC_VariablePulseRateConfig(Int16U PulseWidth);
void LOGIC_Config();
void LOGIC_StartFallEdge();
void LOGIC_StartRiseEdge();

#endif //__LOGIC_H
