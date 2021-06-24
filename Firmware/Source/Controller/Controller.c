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

// Definitions
//
#define TIME_INT_PS_ACTIVITY			250		// мс

// Variables
//
DeviceState CONTROL_State = DS_None;
SubState CONTROL_SubState = SS_None;
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
void CONTROL_HandleBatteryCharge();
void CONTROL_HandleIntPSTune();
void CONTROL_DeviceStateControl();

// Functions
//
void CONTROL_Init()
{
	// Переменные для конфигурации EndPoint
	Int16U EPIndexes[EP_COUNT] = { EP_DUT_I };
	Int16U EPSized[EP_COUNT] = { VALUES_x_SIZE };
	pInt16U EPCounters[EP_COUNT] = { (pInt16U)&CONTROL_Values_Counter };
	pInt16U EPDatas[EP_COUNT] = { (pInt16U)CONTROL_Values_DUTCurrent };

	// Конфигурация сервиса работы Data-table и EPROM
	EPROMServiceConfig EPROMService = { (FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT };
	// Инициализация data table
	DT_Init(EPROMService, false);
	DT_SaveFirmwareInfo(CAN_SLAVE_NID, 0);
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
			}
			else if(CONTROL_State != DS_Ready)
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DISABLE_POWER:
			if((CONTROL_State == DS_Ready) || (CONTROL_State == DS_ConfigReady) ||
					((CONTROL_State == DS_InProcess) && (CONTROL_SubState == SS_PowerPrepare)))
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
				CONTROL_SetDeviceState(DS_ConfigReady, SS_SyncWaiting);

				LOGIC_SofwarePulseStart(true);
			}
			else
				if (CONTROL_State == DS_InProcess)
					*pUserError = ERR_OPERATION_BLOCKED;
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_INTPS_FORCE_MUTE:
			{
				if (CONTROL_State == DS_ConfigReady)
				{
					LL_IntPowerSupplyEn(false);
					CONTROL_SetDeviceState(DS_ConfigReady, SS_SyncWaiting);
				}
			}
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
	CONTROL_HandleBatteryCharge();

	// Process internal power supply tune
	CONTROL_HandleIntPSTune();

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

	if ((CONTROL_SubState == SS_PulsePrepare) || (CONTROL_State == DS_ConfigReady))
	{
		DataTable[REG_INT_PS_VOLTAGE] = MEASURE_IntPSVoltage() * 10;

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
			if(CONTROL_SubState != SS_SyncWaiting)
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

void CONTROL_HandleBatteryCharge()
{
	float BatteryVoltage;

	if (CONTROL_SubState == SS_PowerPrepare)
	{
		LL_PowerOnSolidStateRelay(true);

		BatteryVoltage = MEASURE_BatteryVoltage() * 10;

		if (BatteryVoltage >= DataTable[REG_BAT_VOLTAGE_THRESHOLD])
		{
			if (CONTROL_TimeCounter >= CONTROL_AfterPulsePause)
				CONTROL_SetDeviceState(DS_Ready, SS_None);
		}
		else
		{
			if (CONTROL_TimeCounter > CONTROL_BatteryChargeTimeCounter)
				CONTROL_SwitchToFault(DF_BATTERY);
		}

		DataTable[REG_BAT_VOLTAGE] = (Int16U) BatteryVoltage;
	}
}
//-----------------------------------------------

void CONTROL_StopProcess()
{
	LOGIC_ResetHWToDefaults(false);

	CONTROL_AfterPulsePause = CONTROL_TimeCounter + DataTable[REG_AFTER_PULSE_PAUSE];
	CONTROL_BatteryChargeTimeCounter = CONTROL_TimeCounter + DataTable[REG_BATTERY_RECHRAGE_TIMEOUT];

	CONTROL_SetDeviceState(DS_InProcess, SS_PowerPrepare);
}
//-----------------------------------------------

void CONTROL_RegistersReset()
{
	DataTable[REG_WARNING] = 0;
	DataTable[REG_PROBLEM] = 0;
	DataTable[REG_FAULT_REASON] = 0;

	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
}
//-----------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_SetDeviceState(DS_Fault, SS_None);
	DataTable[REG_FAULT_REASON] = Reason;

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
