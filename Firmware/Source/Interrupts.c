﻿// Include
#include "Interrupts.h"
//
#include "LowLevel.h"
#include "Board.h"
#include "Controller.h"
#include "Logic.h"
#include "Global.h"
#include "DeviceObjectDictionary.h"
#include "Measurement.h"
#include "InitConfig.h"
#include "DataTable.h"


// Functions prototypes
//
void INT_OutputLockCheck();
void INT_ActivateProtection();

// Functions
//
void EXTI9_5_IRQHandler()
{
	// Формирование переднего фронта импульса
	if (LL_ReadLineSync() && (CONTROL_State == DS_ConfigReady))
	{
		LL_IntPowerSupplyEn(false);
		LL_OutputLock(false);

		LOGIC_StartRiseEdge();

		CONTROL_SetDeviceState(DS_InProcess, SS_RiseEdge);

		CONTROL_HandleFanLogic(true);
		CONTROL_HandleExternalLamp(true);
		INT_ActivateProtection();
	}
	else
	{
		// Формирование заднего фронта импульса
		if(!LL_ReadLineSync() && ((CONTROL_SubState == SS_Plate || CONTROL_SubState == SS_RiseEdge)))
		{
			CONTROL_SetDeviceState(DS_InProcess, SS_FallEdge);
			LOGIC_StartFallEdge();
		}
	}

	// Запуск импульса в отладочном режиме
	if ((CONTROL_State == DS_None))
	{
		if (LL_ReadLineSync())
			LOGIC_StartRiseEdge();
		else
			LOGIC_StartFallEdge();
	}

	EXTI_FlagReset(EXTI_6);
}
//-----------------------------------------

void TIM2_IRQHandler()
{
	TIM_Stop(TIM2);

	if (CONTROL_SubState == SS_FallEdge)
		CONTROL_StopProcess();

	TIM_InterruptEventFlagClear(TIM2, TIM_SR_CC3IF);
}
//-----------------------------------------

void TIM3_IRQHandler()
{
	TIM_Stop(TIM3);

	if (CONTROL_SubState == SS_RiseEdge)
		CONTROL_SetDeviceState(DS_InProcess, SS_Plate);

	TIM_InterruptEventFlagClear(TIM3, TIM_SR_CC4IF);
}
//-----------------------------------------

void EXTI15_10_IRQHandler()
{
	if (EXTI_FlagCheck(EXTI_13))
	{
		CONTROL_SwitchToFault(DF_PROTECTION);
		EXTI_FlagReset(EXTI_13);
	}
}
//-----------------------------------------

void USART1_IRQHandler()
{
	if (ZwSCI_RecieveCheck(USART1))
	{
		ZwSCI_RegisterToFIFO(USART1);
		ZwSCI_RecieveFlagClear(USART1);
	}
}
//-----------------------------------------

void USB_LP_CAN_RX0_IRQHandler()
{
	if (NCAN_RecieveCheck())
	{
		NCAN_RecieveData();
		NCAN_RecieveFlagReset();
	}
}
//-----------------------------------------

void TIM7_IRQHandler()
{
	static uint16_t LED_BlinkTimeCounter = 0;

	if (TIM_StatusCheck(TIM7))
	{
		CONTROL_TimeCounter++;
		if (++LED_BlinkTimeCounter > TIME_LED_BLINK)
		{
			LL_ToggleBoardLED();
			LED_BlinkTimeCounter = 0;
		}

		CONTROL_HandleFanLogic(false);
		CONTROL_HandleExternalLamp(false);
		INT_OutputLockCheck();

		TIM_StatusClear(TIM7);
	}
}
//-----------------------------------------

void TIM6_IRQHandler()
{
	// Выкл. формирователя
	LL_FlipLineRCK();
	LL_OutputLock(true);

	if (CONTROL_SubState == SS_Plate || CONTROL_SubState == SS_RiseEdge || CONTROL_SubState == SS_FallEdge)
		DataTable[REG_WARNING] = WARNING_SYNC;

	TIM_StatusClear(TIM6);
	TIM_Stop(TIM6);
}
//-----------------------------------------

void INT_OutputLockCheck()
{
	if(!LL_ReadLineSync())
	{
		if((CONTROL_SubState != SS_FallEdge) && (CONTROL_SubState != SS_RiseEdge)
																		&& (CONTROL_SubState != SS_Plate))
		{
			LL_OutputLock(true);
		}
	}
}
//-----------------------------------------

void INT_ActivateProtection()
{
	TIM_Reset(TIM6);
	TIM_Start(TIM6);
}
//-----------------------------------------
