// Header
#include "DebugActions.h"

// Include
//
#include "LowLevel.h"
#include "Board.h"
#include "DataTable.h"
#include "Delay.h"
#include "Logic.h"

// Functions
//
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
}
//-----------------------------------------------

void DBGACT_GeneratePulse()
{
	LOGIC_RiseEdgeConfig(DataTable[REG_DBG]);
	DELAY_US(500);

	LL_OutputLock(false);
	DELAY_US(1000);

	LL_SW_Trig(true);

	DELAY_US(DataTable[REG_SW_PULSE_WIDTH] / 2);
	LOGIC_FallEdgeConfig(DataTable[REG_DBG2]);
	DELAY_US(DataTable[REG_SW_PULSE_WIDTH] / 2);

	LL_SW_Trig(false);
	DELAY_US(1000);

	LL_OutputLock(true);
}
//-----------------------------------------------
