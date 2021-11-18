#ifndef __DEBUGACTIONS_H
#define __DEBUGACTIONS_H

// Include
//
#include "ZwBase.h"

// Functions
//
void DBGACT_InternalPowerSupplyControl();
void DBGACT_InternalPowerSupplyDischarge();
void DBGACT_ProtectionReset();
void DBGACT_OutputLockControl();
void DBGACT_Sync();
void DBGACT_GeneratePulse();

#endif //__DEBUGACTIONS_H
