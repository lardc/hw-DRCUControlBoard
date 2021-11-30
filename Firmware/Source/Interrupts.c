// Include
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
#include "Delay.h"

// Functions prototypes
//
void TIMx_Process(TIM_TypeDef* TIMx, Int32U Event);
void INT_OutputLockCheck();

// Functions
//
void EXTI9_5_IRQHandler()
{
	if (EXTI_FlagCheck(EXTI_6))
	{
		if(CONTROL_SubState == SS_ConfigReady)
		{
			// Формирование переднего фронта импульса
			if (LL_ReadLineSync())
			{
				LOGIC_RiseEdgeConfig(ConfigParams.PulseWidth_CTRL2);
				LL_OutputLock(false);
				LOGIC_StartRiseEdge();

				CONTROL_SetDeviceState(DS_Ready, SS_RiseEdge);
			}
		}
		else
		{
			// Формирование заднего фронта импульса
			if((!LL_ReadLineSync()) && (CONTROL_SubState == SS_Plate))
			{
				LOGIC_StartFallEdge();
				CONTROL_SetDeviceState(DS_Ready, SS_FallEdge);

			}
		}

		// Запуск импульса в отладочном режиме
		if ((CONTROL_State == DS_None))
		{
			if (LL_ReadLineSync())
				LOGIC_StartRiseEdge();
			else
			{
				LOGIC_StartFallEdge();
			}
		}
	}

	EXTI_FlagReset(EXTI_6);
}
//-----------------------------------------

void TIM2_IRQHandler()
{
	TIMx_Process(TIM2, TIM_SR_CC3IF);
}
//-----------------------------------------

void TIM3_IRQHandler()
{
	TIMx_Process(TIM3, TIM_SR_CC4IF);
}
//-----------------------------------------

void TIMx_Process(TIM_TypeDef* TIMx, Int32U Event)
{
	if (TIM_InterruptEventFlagCheck(TIMx, Event))
	{
		TIM_Stop(TIMx);

		if (CONTROL_SubState == SS_RiseEdge)
		{
			CONTROL_SetDeviceState(DS_Ready, SS_Plate);

			LOGIC_FallEdgeConfig(ConfigParams.PulseWidth_CTRL1);
		}

		if (CONTROL_SubState == SS_FallEdge)
			CONTROL_StopProcess();

		TIM_InterruptEventFlagClear(TIMx, Event);
	}
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

		INT_OutputLockCheck();

		TIM_StatusClear(TIM7);
	}
}
//-----------------------------------------

void INT_OutputLockCheck()
{
	if(!LL_ReadLineSync() && CONTROL_State != DS_None)
	{
		if((CONTROL_SubState != SS_FallEdge) && (CONTROL_SubState != SS_RiseEdge) && (CONTROL_SubState != SS_Plate))
			LL_OutputLock(true);
	}
}
//-----------------------------------------
