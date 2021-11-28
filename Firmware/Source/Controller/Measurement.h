#ifndef __MEASUREMENT_H
#define __MEASUREMENT_H

#include "stdinc.h"

// Functions
//
float MEASURE_IntPSVoltage();
Int16U MEASURE_ConvertValxtoDAC(float Value, Int16U RegisterOffset, Int16U RegisterK, Int16U RegisterP2,  Int16U RegisterP1,  Int16U RegisterP0);

#endif // __MEASUREMENT_H
