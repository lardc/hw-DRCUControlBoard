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
	float CurrentTemp;

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
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_050_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_050_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_50_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_50_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_50_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_050_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_050_OFFSET];
			break;

		case CURRENT_RATE_075:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_075;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_075];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_075_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_075_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_75_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_75_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_75_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_075_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_075_OFFSET];
			break;

		case CURRENT_RATE_100:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_100;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_100];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_100_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_100_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_100_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_100_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_100_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_100_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_100_OFFSET];
			break;

		case CURRENT_RATE_250:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_250;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_250];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_250_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_250_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_250_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_250_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_250_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_250_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_250_OFFSET];
			break;

		case CURRENT_RATE_500:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_500;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_500];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_500_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_500_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_500_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_500_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_500_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_500_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_500_OFFSET];
			break;

		case CURRENT_RATE_750:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_750;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_750];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_750_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_750_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_750_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_750_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_750_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_750_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_750_OFFSET];
			break;

		case CURRENT_RATE_1000:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_1000;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_1000];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_1000_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_1000_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_1000_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_1000_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_1000_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_1000_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_1000_OFFSET];
			break;

		case CURRENT_RATE_1500:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_1500;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_1500];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_1500_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_1500_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_1500_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_1500_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_1500_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_1500_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_1500_OFFSET];
			break;

		case CURRENT_RATE_2500:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_2500;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_2500];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_2500_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_2500_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_2500_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_2500_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_2500_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_2500_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_2500_OFFSET];
			break;

		case CURRENT_RATE_3000:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_3000;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_3000];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_3000_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_3000_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_3000_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_3000_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_3000_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_3000_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_3000_OFFSET];
			break;

		case CURRENT_RATE_5000:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_5000;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_5000];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_5000_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_5000_OFFSET];
			ConfigParams.PulseWidth_CTRL1_P2 = (float)(Int16S)DataTable[REG_CTRL1_5000_P2] / 1e6;
			ConfigParams.PulseWidth_CTRL1_P1 = (float)DataTable[REG_CTRL1_5000_P1] / 1000;
			ConfigParams.PulseWidth_CTRL1_P0 = (Int16S)DataTable[REG_CTRL1_5000_P0];
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_5000_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_5000_OFFSET];
			break;

		default:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_OFF;
			ConfigParams.IntPsVoltage = 0;
			break;
	}

	if(DataTable[REG_V_INTPS_SETPOINT])
		ConfigParams.IntPsVoltage = DataTable[REG_V_INTPS_SETPOINT];
	else
		ConfigParams.IntPsVoltage = DataTable[REG_CURRENT_SETPOINT] * ConfigParams.IntPsVoltageK + ConfigParams.IntPsVoltageOffset;

	if(ConfigParams.IntPsVoltage > INTPS_VOLTAGE_MAX)
		ConfigParams.IntPsVoltage = INTPS_VOLTAGE_MAX;

	if(ConfigParams.IntPsVoltage < INTPS_VOLTAGE_MIN)
		ConfigParams.IntPsVoltage = INTPS_VOLTAGE_MIN;

	LL_ExtRegWriteData(ConfigParams.CurrentRateCode);

	ConfigParams.PulseWidth_CTRL2_K = (float)DataTable[REG_CTRL2_K] / 1000;
	ConfigParams.PulseWidth_CTRL2_Offset = (Int16S)DataTable[REG_CTRL2_OFFSET];
	CurrentTemp = DataTable[REG_CURRENT_SETPOINT] * ConfigParams.PulseWidth_CTRL2_K + ConfigParams.PulseWidth_CTRL2_Offset;
	ConfigParams.PulseWidth_CTRL2 = (Int16U)(DataTable[REG_CTRL2_MAX_WIDTH] * CurrentTemp / DataTable[REG_MAXIMUM_UNIT_CURRENT]);

	// Тонкая подстройка
	float I = DataTable[REG_CURRENT_SETPOINT];
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

	DataTable[150] = PulseWidth;

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
	TIM_Stop(TIM16);
	TIM_Start(TIM2);
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

	for (int i = 0; i < CONTROL_Values_Counter; ++i)
		ArrayTemp[i] = CONTROL_Values_DUTCurrent[i];

	// Сортировка
	qsort(ArrayTemp, CONTROL_Values_Counter, sizeof(*ArrayTemp), MEASURE_SortCondition);

	// Усреднение и возврат результата
	for (int i = CONTROL_Values_Counter - RESULT_AVERAGE_POINTS; i < CONTROL_Values_Counter; ++i)
		AvgData += ArrayTemp[i];

	return (Int16U)(AvgData / RESULT_AVERAGE_POINTS);
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
