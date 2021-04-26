// Header
#include "LowLevel.h"
#include "Delay.h"
#include "Board.h"

// Functions
//
// LED on board
void LL_ToggleBoardLED()
{
	GPIO_Toggle(GPIO_LED);
}
//------------------------------------------------------------------------------

// External lamp
void LL_ExternalLamp(bool State)
{
	GPIO_SetState(GPIO_LAMP, State);
}
//------------------------------------------------------------------------------

// FAN
void LL_FAN(bool State)
{
	GPIO_SetState(GPIO_FAN, State);
}
//------------------------------------------------------------------------------

// External DC Ready
void LL_External_DC_RDY(bool State)
{
	GPIO_SetState(GPIO_CURRENT_READY, State);
}
//------------------------------------------------------------------------------

// Software trigger
void LL_SW_Trig(bool State)
{
	GPIO_SetState(GPIO_SYNC_OUT, State);
}
//------------------------------------------------------------------------------

void LL_PowerOnMechRelay(bool State)
{
	GPIO_SetState(GPIO_RELAY_MECH, State);
}
//------------------------------------------------------------------------------

void LL_PowerOnSolidStateRelay(bool State)
{
	GPIO_SetState(GPIO_RELAY_SOLID, State);
}
//------------------------------------------------------------------------------

void LL_OutputCompensation(bool State)
{
	GPIO_SetState(GPIO_OUTPUT_COMPENS, !State);
}
//------------------------------------------------------------------------------

void LL_OutputLock(bool State)
{
	GPIO_SetState(GPIO_OUTPUT_LOCK, State);
}
//------------------------------------------------------------------------------

void LL_IntPowerSupplyEn(bool State)
{
	GPIO_SetState(GPIO_INT_PS, !State);
}
//------------------------------------------------------------------------------

void LL_OverVoltageProtectionReset()
{
	GPIO_SetState(GPIO_PROTECTION_RST, FALSE);
	DELAY_US(50);
	GPIO_SetState(GPIO_PROTECTION_RST, TRUE);
}
//------------------------------------------------------------------------------

void LL_IntPowerSupplyDischarge(bool State)
{
	GPIO_SetState(GPIO_INT_PS_DISCHARGE, State);
}
//------------------------------------------------------------------------------

void LL_ExtRegWriteData(Int16U Data)
{
	SPI_WriteByte8b(SPI1, Data);

	DELAY_US(10);
	GPIO_SetState(GPIO_SPI_RCK, true);
	DELAY_US(10);
	GPIO_SetState(GPIO_SPI_RCK, false);
}
//------------------------------------------------------------------------------

bool LL_ReadLineSync()
{
	return GPIO_GetState(GPIO_SYNC);
}
//------------------------------------------------------------------------------
