#ifndef __LOGIC_H
#define __LOGIC_H

#include "stdinc.h"

// Structs
//
struct __ConfigParamsStruct
{
	Int16U IntPsVoltage;
	Int16U PulseWidth_CTRL1;
	Int16U PulseWidth_CTRL2;
	Int16U MaxPulseWidth_CTRL1;
	Int16U MaxPulseWidth_CTRL2;
	float PulseWidth_CTRL1_K;
	float PulseWidth_CTRL1_Offset;
	float PulseWidth_CTRL2_K;
	Int16S PulseWidth_CTRL2_Offset;
};
extern struct __ConfigParamsStruct ConfigParams;

//Functions
//
void LOGIC_ResetHWToDefaults();
void LOGIC_SofwarePulseStart(bool Start);
void LOGIC_RiseEdgeConfig(Int16U PulseWidth);
void LOGIC_FallEdgeConfig(Int16U PulseWidth);
void LOGIC_Config();
void LOGIC_StartFallEdge();
void LOGIC_StartRiseEdge();

#endif //__LOGIC_H
