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
#include "DataTable.h"

// Functions prototypes
//
void TIMx_Process(TIM_TypeDef* TIMx, Int32U Event);

// Functions
//
void DMA1_Channel1_IRQHandler()
{
	if (DMA_IsTransferComplete(DMA1, DMA_ISR_TCIF1))
	{
		LOGIC_HandleAdcSamples();
		DMA_TransferCompleteReset(DMA1, DMA_IFCR_CTCIF1);
	}
}
//-----------------------------------------

void EXTI9_5_IRQHandler()
{
	if (EXTI_FlagCheck(EXTI_6))
	{
		if ((CONTROL_State == DS_ConfigReady) || (CONTROL_SubState == SS_RiseEdge) || (CONTROL_SubState == SS_Plate))
		{
			LL_IntPowerSupplyEn(false);

			if (LL_ReadLineSync())
			{
				LOGIC_StartRiseEdge();
				ADC_SwitchToHighSpeed();
				MEASURE_HighSpeedStart(true);

				CONTROL_SetDeviceState(DS_InProcess, SS_RiseEdge);
			}
			else
			{
				if(CONTROL_SubState == SS_Plate)
				{
					LOGIC_StartFallEdge();
					CONTROL_SetDeviceState(DS_InProcess, SS_FallEdge);
				}
			}
		}
		else
		{
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

		CONTROL_HandleFanLogic(true);
		CONTROL_HandleExternalLamp(true);
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
			CONTROL_SetDeviceState(DS_InProcess, SS_Plate);
			LOGIC_ConstantPulseRateConfig(ConfigParams.PulseWidth_CTRL2);
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
	}

	EXTI_FlagReset(EXTI_13);
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
		CONTROL_HandleFanLogic(false);
		CONTROL_HandleExternalLamp(false);

		CONTROL_TimeCounter++;
		if (++LED_BlinkTimeCounter > TIME_LED_BLINK)
		{
			LL_ToggleBoardLED();
			LED_BlinkTimeCounter = 0;
		}

		TIM_StatusClear(TIM7);
	}
}
//-----------------------------------------
