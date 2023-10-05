// Header
#include "LowLevel.h"
#include "Delay.h"
#include "Board.h"
#include "DataTable.h"
#include "Global.h"

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
void LL_SW_Trig(bool Start)
{
	Int16U PWM_PulseWidth = 0;

	if(Start)
	{
		PWM_PulseWidth = (float)DataTable[REG_PULSE_WIDTH] * 100 / TIMER16_uS * TIM16_MAX_VALUE;

		TIM_Reset(TIM16);
		TIMx_PWM_SetValue(TIM16, TIMx_CHANNEL1, PWM_PulseWidth);
		TIM_Start(TIM16);
	}
	else
	{
		TIM_Stop(TIM16);
		TIMx_PWM_SetValue(TIM16, TIMx_CHANNEL1, 0);
	}
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
	GPIO_SetState(GPIO_PROTECTION_RST, false);
	DELAY_US(50);
	GPIO_SetState(GPIO_PROTECTION_RST, true);
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
}
//------------------------------------------------------------------------------

void LL_FlipLineRCK()
{
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

void LL_PulseEn(bool State)
{
	GPIO_SetState(GPIO_PULSE_EN, State);
}
//------------------------------------------------------------------------------
