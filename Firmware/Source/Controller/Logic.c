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

// Definitions
//
#define CURRENT_RATE_R0				0
#define CURRENT_RATE_R1 			1
#define CURRENT_RATE_R2				2
#define CURRENT_RATE_R3 			3
#define CURRENT_RATE_R4				4
#define CURRENT_RATE_R5				5
#define CURRENT_RATE_R6				6
#define CURRENT_RATE_R7				7
#define CURRENT_RATE_R8				8
#define CURRENT_RATE_R9				9
#define CURRENT_RATE_R10			10
//
#define CODE_CURRENT_RATE_OFF		0x7F
#define CODE_CURRENT_RATE_R0		0x77
#define CODE_CURRENT_RATE_R1		0x7B
#define CODE_CURRENT_RATE_R2		0x7D
#define CODE_CURRENT_RATE_R3		0x7E
#define CODE_CURRENT_RATE_R4		0x6F
#define CODE_CURRENT_RATE_R5		0x6E
#define CODE_CURRENT_RATE_R6		0x60
#define CODE_CURRENT_RATE_R7		0x5F
#define CODE_CURRENT_RATE_R8		0x40
#define CODE_CURRENT_RATE_R9		0x3F
#define CODE_CURRENT_RATE_R10		0x0F
//
#define RESULT_AVERAGE_POINTS		10					// Количество точек усредения результата измерения
//
#define EXT_LAMP_ON_STATE_TIME		500					// Время работы внешнего индикатора, мс


// Structs
//
struct __ConfigParamsStruct ConfigParams;

// Varibales
//
volatile Int16U LOGIC_DUTCurrentRaw[ADC_AVG_SAMPLES];
float TestCurrent = 0;

// Forward functions
//
int MEASURE_SortCondition(const void *A, const void *B);
void LOGIC_SetCurrentRangeRate(Int16U Code);
void LOGIC_CurrentSourceTurnOff();

// Functions
//
// Сброс аппаратных линий в состояния по умолчанию
void LOGIC_ResetHWToDefaults(bool StopPowerSupply)
{
	LOGIC_SofwarePulseStart(false);
	LOGIC_CurrentSourceTurnOff();

	if (StopPowerSupply)
		LOGIC_BatteryCharge(false);

	MEASURE_HighSpeedStart(false);
	LL_OutputLock(true);
	LL_IntPowerSupplyDischarge(false);
	LL_IntPowerSupplyEn(false);
	LL_OverVoltageProtectionReset();
}
//-------------------------------------------

void LOGIC_CurrentSourceTurnOff()
{
	LOGIC_ConstantPulseRateConfig(0);
	LOGIC_VariablePulseRateConfig(0, 0);
	LOGIC_SetCurrentRangeRate(CODE_CURRENT_RATE_OFF);
}
//-------------------------------------------

void LOGIC_SetCurrentRangeRate(Int16U Code)
{
	LL_ExtRegWriteData(Code);
	LL_FlipLineRCK();
	LL_ExtRegWriteData(CODE_CURRENT_RATE_OFF);
}
//-------------------------------------------

// Включение заряда батареи
void LOGIC_BatteryCharge(bool State)
{
	if (State)
	{
		LL_PowerOnMechRelay(true);
		DELAY_MS(100);
		LL_PowerOnSolidStateRelay(true);
	}
	else
	{
		LL_PowerOnMechRelay(false);
		LL_PowerOnSolidStateRelay(false);
	}
}
//-------------------------------------------

void LOGIC_Config()
{
	float CurrentTemp;

	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();

	// Настройка аппаратной части
	LL_PowerOnSolidStateRelay(false);

	// Кеширование переменных
	TestCurrent = DataTable[REG_CURRENT_SETPOINT];

	switch(DataTable[REG_CURRENT_RATE])
	{
		case CURRENT_RATE_R0:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R0;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R0];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R0_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R0_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_R0_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_R0_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_R0_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R0_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R0_OFFSET];
			break;

		case CURRENT_RATE_R1:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R1;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R1];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R1_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R1_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_R1_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_R1_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_R1_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R1_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R1_OFFSET];
			break;

		case CURRENT_RATE_R2:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R2;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R2];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R2_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R2_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_R2_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_R2_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_R2_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R2_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R2_OFFSET];
			break;

		case CURRENT_RATE_R3:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R3;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R3];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R3_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R3_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_R3_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_R3_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_R3_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R3_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R3_OFFSET];
			break;

		case CURRENT_RATE_R4:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R4;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R4];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R4_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R4_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_R4_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_R4_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_R4_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R4_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R4_OFFSET];
			break;

		case CURRENT_RATE_R5:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R5;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R5];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R5_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R5_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_R5_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_R5_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_R5_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R5_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R5_OFFSET];
			break;

		case CURRENT_RATE_R6:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R6;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R6];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R6_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R6_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_R6_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_R6_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_R6_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R6_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R6_OFFSET];
			break;

		case CURRENT_RATE_R7:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R7;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R7];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R7_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R7_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_R7_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_R7_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_R7_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R7_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R7_OFFSET];
			break;

		case CURRENT_RATE_R8:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R8;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R8];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R8_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R8_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_R8_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_R8_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_R8_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R8_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R8_OFFSET];
			break;

		case CURRENT_RATE_R9:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R9;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R9];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R9_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R9_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_R9_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_R9_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_R9_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R9_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R9_OFFSET];
			break;

		case CURRENT_RATE_R10:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R10;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R10];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R10_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R10_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_R10_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_R10_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_R10_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R10_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R10_OFFSET];
			break;

		default:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_OFF;
			ConfigParams.IntPsVoltage = 0;
			break;
	}

	if(DataTable[REG_V_INTPS_SETPOINT])
		ConfigParams.IntPsVoltage = DataTable[REG_V_INTPS_SETPOINT];
	else
		ConfigParams.IntPsVoltage = TestCurrent * ConfigParams.IntPsVoltageK + ConfigParams.IntPsVoltageOffset;

	if(ConfigParams.IntPsVoltage > INTPS_VOLTAGE_MAX)
		ConfigParams.IntPsVoltage = INTPS_VOLTAGE_MAX;

	if(ConfigParams.IntPsVoltage < INTPS_VOLTAGE_MIN)
		ConfigParams.IntPsVoltage = INTPS_VOLTAGE_MIN;

	LOGIC_SetCurrentRangeRate(ConfigParams.CurrentRateCode);

	ConfigParams.PulseWidth_CTRL2_K = (float)DataTable[REG_CTRL2_K] / 1000;
	ConfigParams.PulseWidth_CTRL2_Offset = (Int16S)DataTable[REG_CTRL2_OFFSET];
	CurrentTemp = TestCurrent * ConfigParams.PulseWidth_CTRL2_K + ConfigParams.PulseWidth_CTRL2_Offset;
	ConfigParams.PulseWidth_CTRL2 = (Int16U)(DataTable[REG_CTRL2_MAX_WIDTH] * CurrentTemp / DataTable[REG_MAXIMUM_UNIT_CURRENT]);

	// Тонкая подстройка
	float I = TestCurrent;
	I = I * I * ConfigParams.PulseWidth_CTRL1_P2 + I * ConfigParams.PulseWidth_CTRL1_P1 + ConfigParams.PulseWidth_CTRL1_P0;
	ConfigParams.PulseWidth_CTRL1 = (Int16U)((I + ConfigParams.PulseWidth_CTRL1_Offset) * ConfigParams.PulseWidth_CTRL1_K);

	LOGIC_VariablePulseRateConfig(ConfigParams.PulseWidth_CTRL1, ConfigParams.IntPsVoltage);
}
//-------------------------------------------

void LOGIC_VariablePulseRateConfig(Int16U PulseWidth, Int16U IntPsVoltage)
{
	// Коэффициент компенсации амлитуды тока от напряжения внутренего источника
	PulseWidth = PulseWidth * (INTPS_VOLTAGE_MAX / IntPsVoltage);

	if(PulseWidth > ConfigParams.MaxPulseWidth_CTRL1)
		PulseWidth = ConfigParams.MaxPulseWidth_CTRL1;
	if(PulseWidth < 0)
		PulseWidth = 0;
	TIM_Reset(TIM3);
	TIMx_PWM_SetValue(TIM3, TIMx_CHANNEL4, PulseWidth);
	DataTable[REG_DBG_PULSE_WIDTH] = PulseWidth;
}
//-------------------------------------------

void LOGIC_ConstantPulseRateConfig(Int16U PulseWidth)
{
	TIM_Reset(TIM2);
	TIMx_PWM_SetValue(TIM2, TIMx_CHANNEL3, PulseWidth);
}
//-------------------------------------------

void LOGIC_StartRiseEdge()
{
	TIM_Start(TIM3);
}
//-------------------------------------------

void LOGIC_StartFallEdge()
{
	TIM_Stop(TIM3);
	LOGIC_SofwarePulseStart(false);
	TIM_Start(TIM2);
	LOGIC_VariablePulseRateConfig(0, 0);
}
//-------------------------------------------

void LOGIC_SofwarePulseStart(bool Start)
{
	LL_SW_Trig(Start);
}
//-------------------------------------------

void LOGIC_HandleAdcSamples()
{
	float AvgData = 0;
	float Current;

	// Сохранение усредненного результата
	for (int i = 0; i < ADC_AVG_SAMPLES; ++i)
		AvgData += LOGIC_DUTCurrentRaw[i];

	Current = MEASURE_ConvertCurrent(AvgData / ADC_AVG_SAMPLES);

	if (CONTROL_Values_Counter < VALUES_x_SIZE)
	{
		CONTROL_Values_DUTCurrent[CONTROL_Values_Counter] = Current * 10;
		CONTROL_Values_Counter++;
	}
}
//-------------------------------------------

int MEASURE_SortCondition(const void *A, const void *B)
{
	return (int)(*(Int16U *)A) - (int)(*(Int16U *)B);
}
//-----------------------------------------

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
