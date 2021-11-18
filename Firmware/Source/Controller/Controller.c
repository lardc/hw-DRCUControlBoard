//-----------------------------------------------
// �������� ������
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

// Variables
//
DeviceState CONTROL_State = DS_None;
SubState CONTROL_SubState = SS_None;
static Boolean CycleActive = false;
//
volatile Int64U CONTROL_TimeCounter = 0;
//

// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_ResetToDefaults();
void CONTROL_Idle();
void CONTROL_WatchDogUpdate();
void CONTROL_RegistersReset();
void CONTROL_HandleIntPSTune();
bool CONTROL_HandleIntPSVoltgeSet(Int16U Voltage);

// Functions
//
void CONTROL_Init()
{
	// ������������ ������� ������ Data-table � EPROM
	EPROMServiceConfig EPROMService = { (FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT };
	// ������������� data table
	DT_Init(EPROMService, false);
	DT_SaveFirmwareInfo(CAN_SLAVE_NID, 0);
	// ������������� device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	// ����� ��������
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaults();
}
//------------------------------------------------------------------------------

void CONTROL_ResetToDefaults()
{
	LOGIC_ResetHWToDefaults();
	CONTROL_RegistersReset();

	CONTROL_SetDeviceState(DS_None, SS_None);
}
//------------------------------------------------------------------------------

static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;

	switch (ActionID)
	{
		case ACT_ENABLE_POWER:
			if(CONTROL_State == DS_None)
				CONTROL_SetDeviceState(DS_InProcess, SS_PowerPrepare);
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
	// Process internal power supply tune
	CONTROL_HandleIntPSTune();

	// Process WD and interface
	CONTROL_WatchDogUpdate();
	DEVPROFILE_ProcessRequests();
}
//-----------------------------------------------

void CONTROL_HandleIntPSTune()
{
	if ((CONTROL_SubState == SS_PulsePrepare) || (CONTROL_State == DS_ConfigReady))
	{
		if(CONTROL_HandleIntPSVoltgeSet(ConfigParams.IntPsVoltage) && (CONTROL_SubState == SS_PulsePrepare))
			CONTROL_SetDeviceState(DS_ConfigReady, SS_None);
	}
	else
		if(CONTROL_State == DS_None)
			CONTROL_HandleIntPSVoltgeSet(DataTable[REG_V_INTPS_SETPOINT]);
		else
			LL_IntPowerSupplyEn(false);
}
//-----------------------------------------------

bool CONTROL_HandleIntPSVoltgeSet(Int16U Voltage)
{
	float dV = 0;
	static Int64U IntPsStabCounter = 0;
	bool Result = false;

	DataTable[REG_INT_PS_VOLTAGE] = MEASURE_IntPSVoltage() * 10;

	dV = abs((float)(DataTable[REG_INT_PS_VOLTAGE] - Voltage) / Voltage * 1000);

	if (dV <= DataTable[REG_INTPS_ALLOWED_ERROR])
	{
		IntPsStabCounter++;

		if(IntPsStabCounter >= DataTable[REG_INTPS_STAB_COUNTER_VALUE])
		{
			IntPsStabCounter = 0;
			Result = TRUE;
		}
	}

	if (DataTable[REG_INT_PS_VOLTAGE] < Voltage)
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

	return Result;
}
//-----------------------------------------------

void CONTROL_StopProcess()
{
	LOGIC_ResetHWToDefaults(false);
	CONTROL_SetDeviceState(DS_InProcess, SS_PowerPrepare);
}
//-----------------------------------------------

void CONTROL_RegistersReset()
{
	DataTable[REG_WARNING] = 0;
	DataTable[REG_PROBLEM] = 0;
	DataTable[REG_FAULT_REASON] = 0;
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
