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

// Definitions
//
#define TIME_INT_PS_ACTIVITY			250		// мс

// Variables
//
DeviceState CONTROL_State = DS_None;
SubState CONTROL_SubState = SS_None;
static Boolean CycleActive = FALSE;
//
volatile Int16U CONTROL_Values_DUTCurrent[VALUES_x_SIZE];
volatile Int16U CONTROL_Values_Counter = 0;
//
volatile Int64U CONTROL_TimeCounter = 0;
Int64U CONTROL_BatteryChargeTimeCounter = 0;
Int64U CONTROL_DeviceStateTimeCounter = 0;
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
	DT_Init(EPROMService, FALSE);
	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	DEVPROFILE_InitEPService(EPIndexes, EPSized, EPCounters, EPDatas);
	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaults(TRUE);
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
				LOGIC_BatteryCharge(TRUE);
			}
			else if(CONTROL_State != DS_Ready)
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DISABLE_POWER:
			if((CONTROL_State == DS_Ready) || ((CONTROL_State == DS_InProcess) && (CONTROL_SubState == SS_PowerPrepare)))
				CONTROL_ResetToDefaults(TRUE);
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
				LOGIC_SofwarePulseStart(TRUE);
			else
				if (CONTROL_State == DS_InProcess)
					*pUserError = ERR_OPERATION_BLOCKED;
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_CLR_FAULT:
			if (CONTROL_State == DS_Fault)
				CONTROL_ResetToDefaults(TRUE);
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

	return TRUE;
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
	if((CONTROL_State == DS_InProcess) && (CONTROL_SubState == SS_PulsePrepare))
	{
		LL_IntPowerSupplyEn(TRUE);
		DELAY_MS(TIME_INT_PS_ACTIVITY);
		LL_IntPowerSupplyEn(FALSE);

		DataTable[REG_INT_PS_VOLTAGE] = MEASURE_IntPSVoltage() * 10;

		CONTROL_SetDeviceState(DS_ConfigReady, SS_None);

		CONTROL_DeviceStateTimeCounter = CONTROL_TimeCounter + DataTable[REG_CONFIG_RDY_STATE_TIMEOUT];
	}
}
//-----------------------------------------------

void CONTROL_HandleBatteryCharge()
{
	float BatteryVoltage;

	BatteryVoltage = MEASURE_BatteryVoltage();

	if ((CONTROL_SubState == SS_PowerPrepare) && (CONTROL_TimeCounter < CONTROL_BatteryChargeTimeCounter))
	{
		if (BatteryVoltage >= DataTable[REG_BAT_VOLTAGE_THRESHOLD])
			CONTROL_SetDeviceState(DS_Ready, SS_None);
	}
	else
	{
		if (CONTROL_SubState == SS_PowerPrepare)
			CONTROL_SwitchToFault(DF_BATTERY);
	}

	DataTable[REG_BAT_VOLTAGE] = (Int16U) (BatteryVoltage * 10);
}
//-----------------------------------------------

void CONTROL_StopProcess()
{
	LOGIC_ResetHWToDefaults(FALSE);
}
//-----------------------------------------------

void CONTROL_RegistersReset()
{
	DataTable[REG_CURRENT] = 0;

	DataTable[REG_WARNING] = 0;
	DataTable[REG_PROBLEM] = 0;
	DataTable[REG_FAULT_REASON] = 0;

	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
}
//-----------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	LOGIC_ResetHWToDefaults(TRUE);
	//
	CONTROL_SetDeviceState(DS_Fault, SS_None);
	DataTable[REG_FAULT_REASON] = Reason;
}
//-----------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState, SubState NewSubState)
{
	CONTROL_State = NewState;
	CONTROL_SubState = NewSubState;
	DataTable[REG_DEV_STATE] = NewState;
}
//-----------------------------------------------

void CONTROL_WatchDogUpdate()
{
	if (BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//-----------------------------------------------
