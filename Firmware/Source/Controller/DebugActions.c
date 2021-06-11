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
}
//-----------------------------------------------

void DBGACT_ExtRegWriteData()
{
	LL_ExtRegWriteData(DataTable[REG_DBG]);
	LL_FlipLineRCK();
}
//-----------------------------------------------

void DBGACT_GeneratePulse()
{
	LOGIC_ConstantPulseRateConfig(DataTable[REG_DBG], INTPS_VOLTAGE_MAX);
	DELAY_US(500);

	LL_OutputLock(false);
	DELAY_US(1000);

	LL_SW_Trig(true);
	DELAY_US(3000);

	LOGIC_VariablePulseRateConfig(DataTable[REG_DBG2]);
	DELAY_US(1000);

	LL_SW_Trig(false);
	DELAY_US(1000);

	LL_OutputLock(true);
}
//-----------------------------------------------

void DBGACT_CurrentReadyOutput()
{
	LL_External_DC_RDY(true);
	DELAY_US(1000);
	LL_External_DC_RDY(false);
}
//-----------------------------------------------

void DBGACT_SetCompensationVoltage()
{
	LL_OutputLock(false);
	LL_OutputCompensation(true);
	DAC_SetValueCh1(DAC1, DataTable[REG_DBG]);
	DAC_ForceSWTrigCh1(DAC1);

	DELAY_US(1000);

	DAC_SetValueCh1(DAC1, 0);
	DAC_ForceSWTrigCh1(DAC1);

	LL_OutputCompensation(false);
	LL_OutputLock(true);
}
//-----------------------------------------------
