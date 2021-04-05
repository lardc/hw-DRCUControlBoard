// Header
#include "DebugActions.h"

// Include
//
#include "LowLevel.h"
#include "Board.h"
#include "DataTable.h"
#include "Delay.h"

// Functions
//
void DBGACT_Fan()
{
	LL_FAN(DataTable[REG_DBG]);
}
//-----------------------------------------------

void DBGACT_Lamp()
{
	LL_ExternalLamp(DataTable[REG_DBG]);
}
//-----------------------------------------------

void DBGACT_RelayMech()
{
	LL_PowerOnMechRelay(DataTable[REG_DBG]);
}
//-----------------------------------------------

void DBGACT_RelaySolid()
{
	LL_PowerOnSolidStateRelay(DataTable[REG_DBG]);
}
//-----------------------------------------------

void DBGACT_InternalPowerSupplyControl()
{
	LL_IntPowerSupplyEn(DataTable[REG_DBG]);
}
//-----------------------------------------------

void DBGACT_InternalPowerSupplyDischarge()
{
	LL_IntPowerSupplyDischarge(DataTable[REG_DBG]);
}
//-----------------------------------------------

void DBGACT_ProtectionReset()
{
	LL_OverVoltageProtectionReset(false);
	LL_OverVoltageProtectionReset(true);
}
//-----------------------------------------------

void DBGACT_OutputLockControl()
{
	LL_OutputLock(DataTable[REG_DBG]);
}
//-----------------------------------------------

void DBGACT_Sync()
{
	LL_SW_Trig(true);
	DELAY_US(1000);
	LL_SW_Trig(false);
}
//-----------------------------------------------
