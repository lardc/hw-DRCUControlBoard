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

// Functions prototypes
//
void TIMx_Process(TIM_TypeDef* TIMx);

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
	if ((CONTROL_State == DS_ConfigReady) || (CONTROL_State == DS_InProcess))
	{
		if (LL_ReadLineSync())
		{
			MEASURE_Start(TRUE);
			LOGIC_StartRiseEdge();

			CONTROL_SetDeviceState(DS_InProcess, SS_RiseEdge);
		}
		else
		{
			LOGIC_StartFallEdge();
			CONTROL_SetDeviceState(DS_InProcess, SS_FallEdge);
		}
	}
}
//-----------------------------------------

void TIM2_IRQHandler()
{
	TIMx_Process(TIM2);
}
//-----------------------------------------

void TIM3_IRQHandler()
{
	TIMx_Process(TIM3);
}
//-----------------------------------------

void TIMx_Process(TIM_TypeDef* TIMx)
{
	if (TIM_StatusCheck(TIMx))
	{
		if (CONTROL_SubState == SS_RiseEdge)
		{
			CONTROL_SetDeviceState(DS_InProcess, SS_Plate);
			LL_OutputCompensation(TRUE);
		}

		if (CONTROL_SubState == SS_FallEdge)
			CONTROL_StopProcess();

		TIM_StatusClear(TIMx);
		TIM_Stop(TIMx);
		TIM_Reset(TIMx);
	}
}
//-----------------------------------------

void EXTI15_10_IRQHandler()
{
	if (EXTI_FlagCheck(EXTI_PR_PR13))
	{
		CONTROL_SwitchToFault(DF_PROTECTION);
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

		TIM_StatusClear(TIM7);
	}
}
//-----------------------------------------
