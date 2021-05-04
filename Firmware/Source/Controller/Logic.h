#ifndef __LOGIC_H
#define __LOGIC_H

#include "stdinc.h"

// Variables
//
extern volatile Int16U LOGIC_DUTCurrentRaw[];
extern Int32U PulseWidth_CTRL1;
extern Int32U PulseWidth_CTRL2;
extern Int16U IntPsVoltage;

//Functions
//
void LOGIC_ResetHWToDefaults(bool StopPowerSupply);
void LOGIC_BatteryCharge(bool State);
void LOGIC_SofwarePulseStart();
void LOGIC_ConstantPulseRateConfig(Int16U PulseWidth);
void LOGIC_VariablePulseRateConfig(Int16U PulseWidth);
void LOGIC_Config();
void LOGIC_StartFallEdge();
void LOGIC_StartRiseEdge();
Int16U LOGIC_ExctractCurrentValue();
void LOGIC_HandleAdcSamples();

#endif //__LOGIC_H
