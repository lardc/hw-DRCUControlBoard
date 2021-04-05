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
#include "math.h"
#include "Diagnostic.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

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
volatile Int64U CONTROL_TimeCounterDelay = 0;
Int64U CONTROL_BatteryChargeTimeCounter = 0;
//

// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_ResetToDefaults(bool StopPowerSupply);
void CONTROL_Idle();
void CONTROL_WatchDogUpdate();
void CONTROL_RegistersReset();
void CONTROL_SaveResultToEndpoints(ProcessResult Result);
void CONTROL_SaveResultToRegisters(ProcessResult Result);
uint16_t CONTROL_HandleWarningCondition(ProcessResult Result);

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
				LOGIC_BatteryCharge();
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
			{
				CONTROL_SetDeviceState(DS_InProcess, SS_Pulse);
				CONTROL_StartProcess();
			}
			else
				if (CONTROL_State == DS_InProcess)
					*pUserError = ERR_OPERATION_BLOCKED;
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_CLR_FAULT:
			if (CONTROL_State == DS_Fault)
			{
				CONTROL_SetDeviceState(DS_None, SS_None);
				DataTable[REG_FAULT_REASON] = DF_NONE;
			}
			break;

		case ACT_CLR_WARNING:
			DataTable[REG_WARNING] = WARNING_NONE;
			break;

		default:
			if (CONTROL_State == DS_None)
				return DIAG_HandleDiagnosticAction(ActionID, pUserError);
			else
				return FALSE;
	}

	return TRUE;
}
//-----------------------------------------------

void CONTROL_HandleBatteryCharge()
{
	float BatteryVoltage;

	BatteryVoltage = MEASURE_BatteryVoltage();

	if ((CONTROL_State == DS_BatteryCharge) && (CONTROL_TimeCounter < CONTROL_BatteryChargeTimeCounter))
	{
		if (BatteryVoltage >= DataTable[REG_BAT_VOLTAGE_THRESHOLD])
			CONTROL_State = DS_Ready;
	}
	else
	{
		if (CONTROL_State == DS_BatteryCharge)
			CONTROL_SwitchToFault(DF_BATTERY);
	}

	DataTable[REG_BAT_VOLTAGE] = (Int16U) (BatteryVoltage * 10);
}
//-----------------------------------------------

void CONTROL_SaveResultToEndpoints(Int16U Current)
{
	CONTROL_Values_DUTCurrent[CONTROL_Values_DiagEPCounter] = Current;
	CONTROL_Values_Counter++;
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

void CONTROL_Idle()
{
	// Process battery charge
	CONTROL_HandleBatteryCharge();

	// Process WD and interface
	CONTROL_WatchDogUpdate();
	DEVPROFILE_ProcessRequests();
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
