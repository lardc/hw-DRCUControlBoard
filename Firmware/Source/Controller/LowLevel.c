// Header
#include "LowLevel.h"
#include "Delay.h"
#include "Board.h"
#include "DeviceObjectDictionary.h"
#include "DataTable.h"

// Functions
//
// LED on board
void LL_ToggleBoardLED()
{
	GPIO_Toggle(GPIO_LED);
}
//------------------------------------------------------------------------------

// Software trigger
void LL_SW_Trig(bool Start)
{
	if(Start)
	{
		TIM_Reset(TIM16);
		TIMx_PWM_SetValue(TIM16, TIMx_CHANNEL1, DataTable[REG_SW_PULSE_WIDTH]);
		TIM_Start(TIM16);
	}
	else
	{
		TIM_Stop(TIM16);
		TIMx_PWM_SetValue(TIM16, TIMx_CHANNEL1, 0);
	}
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

void LL_OutputCompensation(bool State)
{
	GPIO_SetState(GPIO_OUTPUT_COMPENS, !State);
}
//------------------------------------------------------------------------------

bool LL_ReadLineSync()
{
	return GPIO_GetState(GPIO_SYNC);
}
//------------------------------------------------------------------------------
