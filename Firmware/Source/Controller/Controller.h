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
	SS_RiseEdge			= 3,
	SS_Plate			= 4,
	SS_FallEdge			= 5,
} SubState;
//
typedef enum __DeviceState
{
	DS_None				= 0,
	DS_Fault			= 1,
	DS_Disabled			= 2,
	DS_Ready			= 3,
	DS_ConfigReady		= 4,
	DS_InProcess		= 5,
} DeviceState;


// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
//
extern DeviceState CONTROL_State;
extern SubState CONTROL_SubState;


// Functions
//
void CONTROL_SetDeviceState(DeviceState NewState, SubState NewSubState);
void CONTROL_StopProcess();
void CONTROL_SwitchToFault(Int16U Reason);

#endif // __CONTROLLER_H
