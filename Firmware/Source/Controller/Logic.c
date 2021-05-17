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
#define CURRENT_RATE_050			50					// A * 10 / мкс
#define CURRENT_RATE_075			75					// A * 10 / мкс
#define CURRENT_RATE_100			100					// A * 10 / мкс
#define CURRENT_RATE_250			250					// A * 10 / мкс
#define CURRENT_RATE_500			500					// A * 10 / мкс
#define CURRENT_RATE_750			750					// A * 10 / мкс
#define CURRENT_RATE_1000			1000				// A * 10 / мкс
#define CURRENT_RATE_1500			1500				// A * 10 / мкс
#define CURRENT_RATE_2500			2500				// A * 10 / мкс
#define CURRENT_RATE_3000			3000				// A * 10 / мкс
#define CURRENT_RATE_5000			5000				// A * 10 / мкс
//
#define CODE_CURRENT_RATE_OFF		0x7F
#define CODE_CURRENT_RATE_050		0x77
#define CODE_CURRENT_RATE_075		0x7B
#define CODE_CURRENT_RATE_100		0x7D
#define CODE_CURRENT_RATE_250		0x7E
#define CODE_CURRENT_RATE_500		0x6F
#define CODE_CURRENT_RATE_750		0x6E
#define CODE_CURRENT_RATE_1000		0x60
#define CODE_CURRENT_RATE_1500		0x5F
#define CODE_CURRENT_RATE_2500		0x40
#define CODE_CURRENT_RATE_3000		0x3F
#define CODE_CURRENT_RATE_5000		0x0F
//
#define ARRAY_SORTING_PART_LENGHT	4					// Часть массива для сортировки
#define RESULT_AVERAGE_POINTS		10					// Количество точек усредения результата измерения
//
#define EXT_LAMP_ON_STATE_TIME		500					// Время работы внешнего индикатора, мс


// Structs
//
struct __ConfigParamsStruct ConfigParams;

// Varibales
//
volatile Int16U LOGIC_DUTCurrentRaw[ADC_AVG_SAMPLES];

// Forward functions
//
void LOGIC_SetCompensationVoltage(Int16U Current);
int MEASURE_SortCondition(const void *A, const void *B);

// Functions
//
// Сброс аппаратных линий в состояния по умолчанию
void LOGIC_ResetHWToDefaults(bool StopPowerSupply)
{
	if (StopPowerSupply)
		LOGIC_BatteryCharge(false);

	MEASURE_HighSpeedStart(false);
	LL_OutputLock(true);
	LL_IntPowerSupplyDischarge(false);
	LL_IntPowerSupplyEn(false);
	LL_OverVoltageProtectionReset();
	LL_OutputCompensation(false);
	LL_External_DC_RDY(false);

	// Переключение АЦП в базовый режим
	ADC_SwitchToBase();

	// Отключение формирователя
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
	float CurrentTemp, K;

	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();

	// Настройка аппаратной части
	//
	LL_PowerOnSolidStateRelay(false);

	switch(DataTable[REG_CURRENT_RATE])
	{
		case CURRENT_RATE_050:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_050;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_050];
			ConfigParams.IntPsVoltage = DataTable[REG_INTPS_VOLTAGE_050] - (DataTable[REG_CURRENT_SETPOINT] - 100) * (float)DataTable[REG_I_RATE_COMPENS_050] * 1e-3;
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_050_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_050_OFFSET];
			break;

		case CURRENT_RATE_075:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_075;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_075];
			ConfigParams.IntPsVoltage = DataTable[REG_INTPS_VOLTAGE_075] - (DataTable[REG_CURRENT_SETPOINT] - 100) * (float)DataTable[REG_I_RATE_COMPENS_075] * 1e-3;
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_075_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_075_OFFSET];
			break;

		case CURRENT_RATE_100:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_100;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_100];
			ConfigParams.IntPsVoltage = DataTable[REG_INTPS_VOLTAGE_100] - (DataTable[REG_CURRENT_SETPOINT] - 100) * (float)DataTable[REG_I_RATE_COMPENS_100] * 1e-3;
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_100_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_100_OFFSET];
			break;

		case CURRENT_RATE_250:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_250;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_250];
			ConfigParams.IntPsVoltage = DataTable[REG_INTPS_VOLTAGE_250] - (DataTable[REG_CURRENT_SETPOINT] - 100) * (float)DataTable[REG_I_RATE_COMPENS_250] * 1e-3;
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_250_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_250_OFFSET];
			break;

		case CURRENT_RATE_500:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_500;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_500];
			ConfigParams.IntPsVoltage = DataTable[REG_INTPS_VOLTAGE_500] - (DataTable[REG_CURRENT_SETPOINT] - 100) * (float)DataTable[REG_I_RATE_COMPENS_500] * 1e-3;
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_500_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_500_OFFSET];
			break;

		case CURRENT_RATE_750:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_750;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_750];
			ConfigParams.IntPsVoltage = DataTable[REG_INTPS_VOLTAGE_750] - (DataTable[REG_CURRENT_SETPOINT] - 100) * (float)DataTable[REG_I_RATE_COMPENS_750] * 1e-3;
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_750_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_750_OFFSET];
			break;

		case CURRENT_RATE_1000:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_1000;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_1000];
			ConfigParams.IntPsVoltage = DataTable[REG_INTPS_VOLTAGE_1000] - (DataTable[REG_CURRENT_SETPOINT] - 100) * (float)DataTable[REG_I_RATE_COMPENS_1000] * 1e-3;
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_1000_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_1000_OFFSET];
			break;

		case CURRENT_RATE_1500:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_1500;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_1500];
			ConfigParams.IntPsVoltage = DataTable[REG_INTPS_VOLTAGE_1500] - (DataTable[REG_CURRENT_SETPOINT] - 100) * (float)DataTable[REG_I_RATE_COMPENS_1500] * 1e-3;
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_1500_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_1500_OFFSET];
			break;

		case CURRENT_RATE_2500:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_2500;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_2500];
			ConfigParams.IntPsVoltage = DataTable[REG_INTPS_VOLTAGE_2500] - (DataTable[REG_CURRENT_SETPOINT] - 100) * (float)DataTable[REG_I_RATE_COMPENS_2500] * 1e-3;
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_2500_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_2500_OFFSET];
			break;

		case CURRENT_RATE_3000:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_3000;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_3000];
			ConfigParams.IntPsVoltage = DataTable[REG_INTPS_VOLTAGE_3000] - (DataTable[REG_CURRENT_SETPOINT] - 100) * (float)DataTable[REG_I_RATE_COMPENS_3000] * 1e-3;
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_3000_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_3000_OFFSET];
			break;

		case CURRENT_RATE_5000:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_5000;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_5000];
			ConfigParams.IntPsVoltage = DataTable[REG_INTPS_VOLTAGE_5000] - (DataTable[REG_CURRENT_SETPOINT] - 100) * (float)DataTable[REG_I_RATE_COMPENS_5000] * 1e-3;
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_5000_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_5000_OFFSET];
			break;

		default:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_OFF;
			ConfigParams.IntPsVoltage = 0;
			break;
	}

	if(ConfigParams.IntPsVoltage > INTPS_VOLTAGE_MAX)
		ConfigParams.IntPsVoltage = INTPS_VOLTAGE_MAX;

	if(ConfigParams.IntPsVoltage < INTPS_VOLTAGE_MIN)
		ConfigParams.IntPsVoltage = INTPS_VOLTAGE_MIN;

	LL_ExtRegWriteData(ConfigParams.CurrentRateCode);

	ConfigParams.PulseWidth_CTRL2_K = (float)DataTable[REG_CTRL2_K] / 1000;
	ConfigParams.PulseWidth_CTRL2_Offset = (Int16S)DataTable[REG_CTRL2_OFFSET];
	CurrentTemp = DataTable[REG_CURRENT_SETPOINT] * ConfigParams.PulseWidth_CTRL2_K + ConfigParams.PulseWidth_CTRL2_Offset;
	ConfigParams.PulseWidth_CTRL2 = DataTable[REG_CTRL2_MAX_WIDTH] * CurrentTemp / DataTable[REG_MAXIMUM_UNIT_CURRENT];

	CurrentTemp = DataTable[REG_CURRENT_SETPOINT] * ConfigParams.PulseWidth_CTRL1_K + ConfigParams.PulseWidth_CTRL1_Offset;
	ConfigParams.PulseWidth_CTRL1 = ConfigParams.MaxPulseWidth_CTRL1 * CurrentTemp / DataTable[REG_MAXIMUM_UNIT_CURRENT];

	// Коэффициент компенсации амлитуды тока от напряжения внутренего источника
	K = INTPS_VOLTAGE_MAX / ConfigParams.IntPsVoltage;

	LOGIC_VariablePulseRateConfig(ConfigParams.PulseWidth_CTRL1 * K);
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

void LOGIC_VariablePulseRateConfig(Int16U PulseWidth)
{
	TIM_Reset(TIM3);
	TIMx_PWM_SetValue(TIM3, TIMx_CHANNEL4, PulseWidth);
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
	TIM_Start(TIM2);
	LL_OutputCompensation(false);
}
//-------------------------------------------

void LOGIC_SofwarePulseStart()
{
	LL_SW_Trig();
}
//-------------------------------------------

Int16U LOGIC_ExctractCurrentValue()
{
	Int16U ArrayTemp[VALUES_x_SIZE];
	float AvgData = 0;
	Int16U SortStartIndex = 0;
	Int16U SortSize = 0;

	for (int i = 0; i < CONTROL_Values_Counter; ++i)
		ArrayTemp[i] = CONTROL_Values_DUTCurrent[i];

	// Сортировка
	SortSize = CONTROL_Values_Counter / ARRAY_SORTING_PART_LENGHT;
	SortStartIndex = CONTROL_Values_Counter - SortSize;
	qsort((ArrayTemp + SortStartIndex), SortSize, sizeof(*ArrayTemp), MEASURE_SortCondition);

	// Усреднение и возврат результата
	for (int i = CONTROL_Values_Counter - RESULT_AVERAGE_POINTS; i < CONTROL_Values_Counter; ++i)
		AvgData += ArrayTemp[i];

	return (Int16U)(AvgData / RESULT_AVERAGE_POINTS);
}
//-------------------------------------------

void LOGIC_HandleAdcSamples()
{
	float AvgData = 0, Error;
	static Int16U AllowedErrorCounter = 0;
	static Int16U UnallowedErrorCounter = 0;
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

	// Определение выхода тока на заданный уровень
	if(CONTROL_SubState == SS_Plate)
	{
		Error = abs(100 - Current / DataTable[REG_CURRENT_SETPOINT] * 100);

		if (Error <= ((float)DataTable[REG_ALLOWED_ERROR] / 10))
			AllowedErrorCounter++;
		else
			UnallowedErrorCounter++;

		if (AllowedErrorCounter >= DataTable[REG_ERROR_COUNTER_MAX])
			LL_External_DC_RDY(true);
		else if (UnallowedErrorCounter >= DataTable[REG_ERROR_COUNTER_MAX])
				DataTable[REG_WARNING] = WARNING_CURRENT_NOT_READY;
	}
	else
	{
		AllowedErrorCounter = 0;
		UnallowedErrorCounter = 0;
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
