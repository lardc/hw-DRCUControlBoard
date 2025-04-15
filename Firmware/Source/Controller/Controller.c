//-----------------------------------------------
// Основная логика
//-----------------------------------------------

// Header
#include "Controller.h"
//
// Includes
#include "SysConfig.h"
#include "DataTable.h"
#include "SCCISlave.h"
#include "DeviceProfile.h"
#include "BCCITypes.h"
#include "Board.h"
#include "Global.h"
#include "LowLevel.h"
#include "Logic.h"
#include "Measurement.h"
#include "Diagnostic.h"
#include "Delay.h"
#include "stdlib.h"
#include "InitConfig.h"
#include "BCCIxParams.h"
#include "Constraints.h"

// Definitions
//
#define TIME_INT_PS_ACTIVITY			250		// мс
//
#define EXT_LAMP_ON_STATE_TIME			500		// Время работы внешнего индикатора, мс

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
volatile SubState CONTROL_SubState = SS_None;
static Boolean CycleActive = false;
//
volatile Int16U CONTROL_Values_DUTCurrent[VALUES_x_SIZE];
volatile Int16U CONTROL_Values_Counter = 0;
//
volatile Int64U CONTROL_TimeCounter = 0;
Int64U CONTROL_BatteryChargeTimeCounter = 0;
Int64U CONTROL_DeviceStateTimeCounter = 0;
Int64U CONTROL_AfterPulsePause = 0;
//

// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_ResetToDefaults(bool StopPowerSupply);
void CONTROL_Idle();
void CONTROL_WatchDogUpdate();
void CONTROL_RegistersReset();
void CONTROL_HandleBatteryCharge_DCU();
void CONTROL_HandleBatteryCharge_RCU();
void CONTROL_HandleIntPSTune();
void CONTROL_DeviceStateControl();
void CONTROL_SaveResults();
Int16U CONTROL_CalcPostPulseDelay();
void CONTROL_CoolingProcess();
void CONTROL_HandleFanLogic(bool IsImpulse);
void CONTROL_HandleExternalLamp(bool IsImpulse);

// Functions
//
void CONTROL_Init()
{
	// Переменные для конфигурации EndPoint
	Int16U EPIndexes[EP_COUNT] = { EP_DUT_I };
	Int16U EPSized[EP_COUNT] = { VALUES_x_SIZE };
	pInt16U EPCounters[EP_COUNT] = { (pInt16U)&CONTROL_Values_Counter };
	pInt16U EPDatas[EP_COUNT] = { (pInt16U)CONTROL_Values_DUTCurrent };
	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	DEVPROFILE_InitEPService(EPIndexes, EPSized, EPCounters, EPDatas);
	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaults(true);
}
//------------------------------------------------------------------------------

void CONTROL_ResetToDefaults(bool StopPowerSupply)
{
	LOGIC_ResetHWToDefaults(StopPowerSupply);

	CONTROL_SetDeviceState(DS_None, SS_None);
	CONTROL_RegistersReset();
}
//------------------------------------------------------------------------------

static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;

	switch (ActionID)
	{
		case ACT_ENABLE_POWER:
			if(CONTROL_State == DS_None)
			{
				CONTROL_BatteryChargeTimeCounter = CONTROL_TimeCounter + DataTable[REG_BATTERY_FULL_CHRAGE_TIMEOUT];
				CONTROL_SetDeviceState(DS_InProcess, SS_PowerPrepare);
				LOGIC_BatteryCharge(true);
				if (DataTable[REG_UNIT_DRCU] == VERSION_RCU)
					LOGIC_SetReversVoltage();
			}
			else if(CONTROL_State != DS_Ready)
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DISABLE_POWER:
			if((CONTROL_State == DS_Ready) || (CONTROL_State == DS_ConfigReady) ||
					((CONTROL_State == DS_InProcess) && (CONTROL_SubState == SS_PowerPrepare || CONTROL_SubState == SS_Cooling)))
				CONTROL_ResetToDefaults(true);
			else if(CONTROL_State != DS_None)
					*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_CONFIG_UNIT:
			if (CONTROL_State == DS_Ready)
			{
				CONTROL_SetDeviceState(DS_InProcess, SS_PulsePrepare);
				LOGIC_Config();
			}
			else
				if (CONTROL_State == DS_InProcess)
					*pUserError = ERR_OPERATION_BLOCKED;
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_SOFTWARE_START:
			if (CONTROL_State == DS_ConfigReady)
			{
				LL_IntPowerSupplyEn(false);
				CONTROL_SetDeviceState(DS_ConfigReady, SS_None);

				LOGIC_SofwarePulseStart(true);
			}
			else
				if (CONTROL_State == DS_InProcess)
					*pUserError = ERR_OPERATION_BLOCKED;
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_CLR_FAULT:
			if (CONTROL_State == DS_Fault)
				CONTROL_ResetToDefaults(true);
			break;

		case ACT_CLR_WARNING:
			DataTable[REG_WARNING] = WARNING_NONE;
			break;

		default:
			if (CONTROL_State == DS_None)
				return DIAG_HandleDiagnosticAction(ActionID, pUserError);
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;
	}

	return true;
}
//-----------------------------------------------

void CONTROL_Idle()
{
	// Process battery charge
	(DataTable[REG_UNIT_DRCU] == VERSION_RCU) ? CONTROL_HandleBatteryCharge_RCU() : CONTROL_HandleBatteryCharge_DCU();

	// Process internal power supply tune
	CONTROL_HandleIntPSTune();

	// Unit cooling process
	CONTROL_CoolingProcess();

	// Control of device state
	CONTROL_DeviceStateControl();

	// Process WD and interface
	CONTROL_WatchDogUpdate();
	DEVPROFILE_ProcessRequests();
}
//-----------------------------------------------

void CONTROL_DeviceStateControl()
{
	if((CONTROL_State == DS_ConfigReady) && (CONTROL_TimeCounter >= CONTROL_DeviceStateTimeCounter))
		CONTROL_SetDeviceState(DS_Ready, SS_None);
}
//-----------------------------------------------

void CONTROL_HandleIntPSTune()
{
	float dV = 0;
	static Int64U IntPsStabCounter = 0;

	if ((CONTROL_SubState == SS_PulsePrepare) || (CONTROL_State == DS_ConfigReady) ||
				(CONTROL_State == DS_None && DataTable[REG_V_INTPS_SETPOINT]))
	{
		if(DataTable[REG_V_INTPS_SETPOINT])
			ConfigParams.IntPsVoltage = DataTable[REG_V_INTPS_SETPOINT];

		if(DataTable[REG_UNIT_DRCU] == VERSION_RCU)
		{
			DataTable[REG_INT_PS_VOLTAGE] = MEASURE_ConvertIntPsVoltage(0, true) * 10;
		}
		else
		{
			DataTable[REG_INT_PS_VOLTAGE] = LOGIC_IntPsVoltage * 10;
		}

		dV = abs((float)(DataTable[REG_INT_PS_VOLTAGE] - ConfigParams.IntPsVoltage) / ConfigParams.IntPsVoltage * 1000);

		if ((CONTROL_SubState == SS_PulsePrepare) && (dV <= DataTable[REG_INTPS_ALLOWED_ERROR]))
		{
			IntPsStabCounter++;

			if(IntPsStabCounter >= DataTable[REG_INTPS_STAB_COUNTER_VALUE])
			{
				IntPsStabCounter = 0;
				CONTROL_DeviceStateTimeCounter = CONTROL_TimeCounter + DataTable[REG_CONFIG_RDY_STATE_TIMEOUT];

				CONTROL_SetDeviceState(DS_ConfigReady, SS_None);
			}
		}

		if (DataTable[REG_INT_PS_VOLTAGE] < ConfigParams.IntPsVoltage)
		{
			LL_IntPowerSupplyEn(true);
			LL_IntPowerSupplyDischarge(false);
		}
		else
		{
			LL_IntPowerSupplyEn(false);

			if(dV >= DataTable[REG_ERR_FOR_FORCED_DISCHARGE])
				LL_IntPowerSupplyDischarge(true);
		}
	}
	else
		if(CONTROL_State != DS_None)
			LL_IntPowerSupplyEn(false);
}
//-----------------------------------------------

void CONTROL_CoolingProcess()
{
	static Int64U TimeoutCounter = 0;
	static Int16U CurrentPulseCounter = 0;

	// Задержка после импульса
	if (CONTROL_SubState == SS_PostPulseDelay)
	{
		if (CONTROL_TimeCounter >= CONTROL_AfterPulsePause)
		{
			if(!DataTable[REG_CALIBRATION_PROCESS])
			{
				CurrentPulseCounter++;
				TimeoutCounter = CONTROL_TimeCounter + DataTable[REG_TQ_TIMEOUT];
			}

			CONTROL_SetDeviceState(DS_Ready, SS_None);
		}
	}

	// Если в течении времени REG_PULSE_DELAY_TQ_TIMEOUT не было нового формирвоания тока,
	// то блок переходит в режим охлаждения
	if(!DataTable[REG_CALIBRATION_PROCESS])
	{
		if (CONTROL_State == DS_Ready)
		{
			if(CONTROL_TimeCounter >= TimeoutCounter || CurrentPulseCounter >= UNIT_MAX_NUM_OF_PULSES)
			{
				CONTROL_SetDeviceState(DS_InProcess, SS_Cooling);
				TimeoutCounter = CONTROL_TimeCounter + CONTROL_CalcPostPulseDelay() * CurrentPulseCounter;
				CurrentPulseCounter = 0;
			}
		}

		//Охлаждение блока
		if (CONTROL_SubState == SS_Cooling)
		{
			if (CONTROL_TimeCounter >= TimeoutCounter)
				CONTROL_SetDeviceState(DS_Ready, SS_None);
		}
	}
}
//-----------------------------------------------

void CONTROL_HandleBatteryCharge_DCU()
{
	DataTable[REG_BAT_VOLTAGE] = (Int16U) (LOGIC_BatteryVoltage * 10);

	if (CONTROL_SubState == SS_PowerPrepare)
	{
		LL_PowerOnSolidStateRelay(true);

		if (DataTable[REG_BAT_VOLTAGE] >= DataTable[REG_BAT_VOLTAGE_THRESHOLD])
			CONTROL_SetDeviceState(DS_InProcess, SS_PostPulseDelay);
		else
		{
			if (CONTROL_TimeCounter > CONTROL_BatteryChargeTimeCounter)
				CONTROL_SwitchToFault(DF_BATTERY_LOW);
		}
	}
}
//-----------------------------------------------

void CONTROL_HandleBatteryCharge_RCU()
{
	float BatteryVoltage;
	BatteryVoltage = MEASURE_ConvertBatteryVoltage(0, true) * 10;

	if(CONTROL_SubState == SS_PowerPrepare)
	{
		if(BatteryVoltage < (float)DataTable[REG_BAT_VOLTAGE_THRESHOLD])
			LL_PowerOnSolidStateRelay(true);

		if(BatteryVoltage >= (float)DataTable[REG_BAT_VOLTAGE_THRESHOLD])
		{
			LL_PowerOnSolidStateRelay(false);
			CONTROL_SetDeviceState(DS_InProcess, SS_PostPulseDelay);
		}
		else
		{
			if(CONTROL_TimeCounter > CONTROL_BatteryChargeTimeCounter)
				CONTROL_SwitchToFault(DF_BATTERY_LOW);
		}
	}
	// Поддержание заряда батареи
	if(CONTROL_State == DS_Ready)
	{
		if(BatteryVoltage < (float)(DataTable[REG_BAT_VOLTAGE_THRESHOLD] - BAT_VOLTAGE_HYST))
		{
			CONTROL_BatteryChargeTimeCounter = CONTROL_TimeCounter + DataTable[REG_BATTERY_RECHRAGE_TIMEOUT];
			CONTROL_SetDeviceState(DS_InProcess, SS_PowerPrepare);
		}
		if(BatteryVoltage > (float)(DataTable[REG_BAT_VOLTAGE_THRESHOLD] + BAT_VOLTAGE_HYST))
		{
			CONTROL_SwitchToFault(DF_BATTERY_UP);
		}
	}
	DataTable[REG_BAT_VOLTAGE] = (Int16U)BatteryVoltage;
}
//-----------------------------------------------

void CONTROL_StopProcess()
{
	LOGIC_ResetHWToDefaults(false);
	CONTROL_SaveResults();

	CONTROL_AfterPulsePause = CONTROL_TimeCounter + CONTROL_CalcPostPulseDelay();
	CONTROL_BatteryChargeTimeCounter = CONTROL_TimeCounter + DataTable[REG_BATTERY_RECHRAGE_TIMEOUT];

	CONTROL_SetDeviceState(DS_InProcess, SS_PowerPrepare);
}
//-----------------------------------------------

Int16U CONTROL_CalcPostPulseDelay()
{
	float PulseDelayCoef = (float)DataTable[REG_CURRENT_SETPOINT] / DataTable[REG_MAXIMUM_UNIT_CURRENT];
	return (DataTable[REG_CALIBRATION_PROCESS]) ? (UNIT_PULSE_DELAY_MIN + DataTable[REG_PULSE_DELAY_TQ]) :
			(UNIT_PULSE_DELAY_MIN + DataTable[REG_PULSE_DELAY_TQ] * PulseDelayCoef);
}
//------------------------------------------

void CONTROL_SaveResults()
{
	DataTable[REG_CURRENT] = LOGIC_ExctractCurrentValue();
}
//-----------------------------------------------

void CONTROL_RegistersReset()
{
	DataTable[REG_CURRENT] = 0;
	DataTable[REG_WARNING] = 0;
	DataTable[REG_PROBLEM] = 0;
	DataTable[REG_FAULT_REASON] = 0;
	DataTable[REG_FAILED_SUBSTATE] = 0;

	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
}
//-----------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_SetDeviceState(DS_Fault, SS_None);
	DataTable[REG_FAULT_REASON] = Reason;
	DataTable[REG_FAILED_SUBSTATE] = CONTROL_SubState;

	LOGIC_ResetHWToDefaults(true);
}
//-----------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState, SubState NewSubState)
{
	CONTROL_State = NewState;
	CONTROL_SubState = NewSubState;
	DataTable[REG_DEV_STATE] = NewState;
	DataTable[REG_DEV_SUBSTATE] = NewSubState;
}
//-----------------------------------------------

void CONTROL_WatchDogUpdate()
{
	if (BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//-----------------------------------------------

void CONTROL_HandleFanLogic(bool IsImpulse)
{
	static uint32_t IncrementCounter = 0;
	static uint64_t FanOnTimeout = 0;

	if(CONTROL_State != DS_None)
	{
		if(DataTable[REG_FAN_CTRL])
		{
			// Увеличение счётчика в простое
			if (!IsImpulse)
				IncrementCounter++;

			// Включение вентилятора
			if ((IncrementCounter > ((uint32_t)DataTable[REG_FAN_OPERATE_PERIOD] * 1000)) || IsImpulse)
			{
				IncrementCounter = 0;
				FanOnTimeout = CONTROL_TimeCounter + ((uint32_t)DataTable[REG_FAN_OPERATE_TIME] * 1000);
				LL_FAN(true);
			}

			// Отключение вентилятора
			if (FanOnTimeout && (CONTROL_TimeCounter > FanOnTimeout))
			{
				FanOnTimeout = 0;
				LL_FAN(false);
			}
		}
		else
			LL_FAN(false);
	}
}
//-----------------------------------------------

void CONTROL_HandleExternalLamp(bool IsImpulse)
{
	static Int64U ExternalLampTimeout = 0;

	if(CONTROL_State != DS_None)
	{
		if(IsImpulse)
		{
			LL_ExternalLamp(true);
			ExternalLampTimeout = CONTROL_TimeCounter + EXT_LAMP_ON_STATE_TIME;
		}
		else
		{
			if(CONTROL_TimeCounter >= ExternalLampTimeout)
				LL_ExternalLamp(false);
		}
	}
}
//-----------------------------------------------
