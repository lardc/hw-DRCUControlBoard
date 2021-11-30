#ifndef __LOGIC_H
#define __LOGIC_H

#include "stdinc.h"

// Structs
//
struct __ConfigParamsStruct
{
	Int16U CurrentRateCode;
	Int16U IntPsVoltage;
	Int16U PulseWidth_CTRL1;
	Int16U PulseWidth_CTRL2;
	Int16U MaxPulseWidth_CTRL1;
	float PulseWidth_CTRL1_K;
	float PulseWidth_CTRL1_Offset;
	float PulseWidth_CTRL2_K;
	Int16S PulseWidth_CTRL2_Offset;
	float PulseWidth_CTRL1_P2;
	float PulseWidth_CTRL1_P1;
	Int16S PulseWidth_CTRL1_P0;
	float IntPsVoltageK;
	Int16S IntPsVoltageOffset;
};
extern struct __ConfigParamsStruct ConfigParams;

// Variables
//
extern volatile Int16U LOGIC_DUTCurrentRaw[];

//Functions
//
void LOGIC_ResetHWToDefaults(bool StopPowerSupply);
void LOGIC_BatteryCharge(bool State);
void LOGIC_SofwarePulseStart(bool Start);
void LOGIC_ConstantPulseRateConfig(Int16U PulseWidth, Int16U IntPsVoltage);
void LOGIC_VariablePulseRateConfig(Int16U PulseWidth);
void LOGIC_Config();
void LOGIC_StartFallEdge();
void LOGIC_StartRiseEdge();
Int16U LOGIC_ExctractCurrentValue();
void LOGIC_HandleAdcSamples();
void CONTROL_HandleFanLogic(bool IsImpulse);
void CONTROL_HandleExternalLamp(bool IsImpulse);

#endif //__LOGIC_H
