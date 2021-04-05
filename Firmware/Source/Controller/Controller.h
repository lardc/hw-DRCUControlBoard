// -----------------------------------------
// Logic controller
// ----------------------------------------

#ifndef __CONTROLLER_H
#define __CONTROLLER_H


// Includes
//
#include "stdinc.h"


//Types
//
typedef enum __SubState
{
	SS_None				= 0,
	SS_PowerPrepare		= 1,
	SS_PulsePrepare		= 2,
	SS_Pulse			= 3
} SubState;
//
typedef enum __DeviceState
{
	DS_None				= 0,
	DS_Fault			= 1,
	DS_Disabled			= 2,
	DS_BatteryCharge	= 3,
	DS_Ready			= 4,
	DS_ConfigReady		= 5,
	DS_InProcess		= 6
} DeviceState;


// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
//
extern volatile Int16U CONTROL_Values_DUTCurrent[];
extern volatile Int16U CONTROL_Values_Counter;


// Functions
//
void CONTROL_SetDeviceState(DeviceState NewState, SubState NewSubState);

#endif // __CONTROLLER_H
