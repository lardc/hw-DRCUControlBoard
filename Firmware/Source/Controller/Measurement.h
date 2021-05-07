#ifndef __MEASUREMENT_H
#define __MEASUREMENT_H

#include "stdinc.h"

// Functions
//
float MEASURE_BatteryVoltage();
float MEASURE_IntPSVoltage();
void MEASURE_HighSpeedStart(bool State);
//
void MEASURE_ConvertCurrentArr(volatile Int16U *InputArray, float *OutputArray, Int16U DataLength);
Int16U MEASURE_ConvertValxtoDAC(float Value, Int16U RegisterOffset, Int16U RegisterK, Int16U RegisterP2,  Int16U RegisterP1,  Int16U RegisterP0);

#endif // __MEASUREMENT_H
