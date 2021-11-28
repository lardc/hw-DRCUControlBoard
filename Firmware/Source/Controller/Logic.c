// Header
//
#include "Logic.h"

// Includes
//
#include "LowLevel.h"
#include "Board.h"
#include "Controller.h"
#include "Global.h"
#include "math.h"
#include "stdlib.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "InitConfig.h"
#include "Delay.h"
#include "Measurement.h"


// Structs
//
struct __ConfigParamsStruct ConfigParams;

void LOGIC_SetCompensationVoltage(Int16U Current);

// Functions
//
// Сброс аппаратных линий в состояния по умолчанию
void LOGIC_ResetHWToDefaults()
{
	LOGIC_SofwarePulseStart(false);
	LL_OutputLock(true);
	LL_IntPowerSupplyDischarge(false);
	LL_IntPowerSupplyEn(false);
	LL_OverVoltageProtectionReset();
	LL_OutputCompensation(false);
}
//-------------------------------------------

void LOGIC_Config()
{
	// Кеширование переменных
	ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH];
	ConfigParams.MaxPulseWidth_CTRL2 = DataTable[REG_CTRL2_MAX_WIDTH];
	ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_K] / 1000;
	ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_OFFSET];
	ConfigParams.PulseWidth_CTRL2_K = (float)DataTable[REG_CTRL2_K] / 1000;
	ConfigParams.PulseWidth_CTRL2_Offset = (Int16S)DataTable[REG_CTRL2_OFFSET];
	//

	if(DataTable[REG_V_INTPS_SETPOINT])
		ConfigParams.IntPsVoltage = DataTable[REG_V_INTPS_SETPOINT];
	else
		ConfigParams.IntPsVoltage = DataTable[REG_V_INTPS_DEF];

	ConfigParams.PulseWidth_CTRL1 = DataTable[REG_CURRENT_SETPOINT] * ConfigParams.PulseWidth_CTRL1_K + ConfigParams.PulseWidth_CTRL1_Offset;
	if(ConfigParams.PulseWidth_CTRL1 > ConfigParams.MaxPulseWidth_CTRL1)
		ConfigParams.PulseWidth_CTRL1 = ConfigParams.MaxPulseWidth_CTRL1;

	ConfigParams.PulseWidth_CTRL2 = DataTable[REG_CURRENT_SETPOINT] * ConfigParams.PulseWidth_CTRL2_K + ConfigParams.PulseWidth_CTRL2_Offset;
	if(ConfigParams.PulseWidth_CTRL2 > ConfigParams.MaxPulseWidth_CTRL2)
		ConfigParams.PulseWidth_CTRL2 = ConfigParams.MaxPulseWidth_CTRL2;

	LOGIC_RiseEdgeConfig(ConfigParams.PulseWidth_CTRL2);
	LOGIC_SetCompensationVoltage(DataTable[REG_CURRENT_SETPOINT]);
}
//-------------------------------------------

void LOGIC_SetCompensationVoltage(Int16U Current)
{
	DAC_SetValueCh1(DAC1, MEASURE_ConvertValxtoDAC(Current, REG_I_TO_DAC_OFFSET, REG_I_TO_DAC_K,
			REG_I_TO_DAC_P2,  REG_I_TO_DAC_P1,  REG_I_TO_DAC_P0));
	DAC_ForceSWTrigCh1(DAC1);
}
//-------------------------------------------

void LOGIC_RiseEdgeConfig(Int16U PulseWidth)
{
	TIM_Reset(TIM2);
	TIMx_PWM_SetValue(TIM2, TIMx_CHANNEL3, PulseWidth);
}
//-------------------------------------------

void LOGIC_FallEdgeConfig(Int16U PulseWidth)
{
	TIM_Reset(TIM3);
	TIMx_PWM_SetValue(TIM3, TIMx_CHANNEL4, PulseWidth);
}
//-------------------------------------------

void LOGIC_StartRiseEdge()
{
	TIM_Start(TIM2);
}
//-------------------------------------------

void LOGIC_StartFallEdge()
{
	LOGIC_SofwarePulseStart(false);
	TIM_Start(TIM3);
}
//-------------------------------------------

void LOGIC_SofwarePulseStart(bool Start)
{
	LL_SW_Trig(Start);
}
//-------------------------------------------
