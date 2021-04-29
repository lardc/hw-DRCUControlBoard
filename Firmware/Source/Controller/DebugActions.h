#ifndef __DEBUGACTIONS_H
#define __DEBUGACTIONS_H

// Include
//
#include "ZwBase.h"

// Functions
//
void DBGACT_Fan();
void DBGACT_Lamp();
void DBGACT_RelayMech();
void DBGACT_RelaySolid();
void DBGACT_InternalPowerSupplyControl();
void DBGACT_InternalPowerSupplyDischarge();
void DBGACT_ProtectionReset();
void DBGACT_OutputLockControl();
void DBGACT_Sync();
void DBGACT_ExtRegWriteData();
void DBGACT_GeneratePulse();
void DBGACT_CurrentReadyOutput();
void DBGACT_SetCompensationVoltage();

#endif //__DEBUGACTIONS_H
