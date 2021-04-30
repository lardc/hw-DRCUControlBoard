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
#define RESULT_AVERAGE_POINTS		50					// Количество точек усредения результата измерения

// Varibales
//
volatile Int16U LOGIC_DUTCurrentRaw[ADC_AVG_SAMPLES];
Int16U CurrentRateCode;
Int32U PulseWidth_CTRL1, PulseWidth_CTRL2;

// Forward functions
//
void LOGIC_ClearDataArrays();
void LOGIC_SetCompensationVoltage(Int16U Current);
int MEASURE_SortCondition(const void *A, const void *B);

// Functions
//
// Сброс аппаратных линий в состояния по умолчанию
void LOGIC_ResetHWToDefaults(bool StopPowerSupply)
{
	if (StopPowerSupply)
		LOGIC_BatteryCharge(false);

	//MEASURE_Start(false);
	LL_OutputLock(true);
	LL_IntPowerSupplyDischarge(false);
	LL_IntPowerSupplyEn(false);
	LL_OverVoltageProtectionReset();
	LL_OutputCompensation(false);
	LL_External_DC_RDY(false);
	LL_ExternalLamp(false);

	// Переключение АЦП в базовый режим
	//ADC_SwitchToBase();

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
	Int32U MaxPulseWidth_CTRL1;

	LOGIC_ClearDataArrays();

	// Настройка аппаратной части
	//
	LOGIC_SetCompensationVoltage(DataTable[REG_CURRENT_SETPOINT]);
	LL_OutputLock(false);
	LL_PowerOnSolidStateRelay(false);

	switch(DataTable[REG_CURRENT_RATE])
	{
		case CURRENT_RATE_050:
			CurrentRateCode = CODE_CURRENT_RATE_050;
			MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_050];
			break;

		case CURRENT_RATE_075:
			CurrentRateCode = CODE_CURRENT_RATE_075;
			MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_075];
			break;

		case CURRENT_RATE_100:
			CurrentRateCode = CODE_CURRENT_RATE_100;
			MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_100];
			break;

		case CURRENT_RATE_250:
			CurrentRateCode = CODE_CURRENT_RATE_250;
			MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_250];
			break;

		case CURRENT_RATE_500:
			CurrentRateCode = CODE_CURRENT_RATE_500;
			MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_500];
			break;

		case CURRENT_RATE_750:
			CurrentRateCode = CODE_CURRENT_RATE_750;
			MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_750];
			break;

		case CURRENT_RATE_1000:
			CurrentRateCode = CODE_CURRENT_RATE_1000;
			MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_1000];
			break;

		case CURRENT_RATE_1500:
			CurrentRateCode = CODE_CURRENT_RATE_1500;
			MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_1500];
			break;

		case CURRENT_RATE_2500:
			CurrentRateCode = CODE_CURRENT_RATE_2500;
			MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_2500];
			break;

		case CURRENT_RATE_3000:
			CurrentRateCode = CODE_CURRENT_RATE_3000;
			MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_3000];
			break;

		case CURRENT_RATE_5000:
			CurrentRateCode = CODE_CURRENT_RATE_5000;
			MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_5000];
			break;

		default:
			CurrentRateCode = CODE_CURRENT_RATE_OFF;
			MaxPulseWidth_CTRL1 = 0;
			break;
	}

	LL_ExtRegWriteData(CurrentRateCode);

	PulseWidth_CTRL1 = MaxPulseWidth_CTRL1 * (float)DataTable[REG_CURRENT_SETPOINT] / DataTable[REG_MAXIMUM_UNIT_CURRENT];
	PulseWidth_CTRL2 = DataTable[REG_CTRL2_MAX_WIDTH] * (float)DataTable[REG_CURRENT_SETPOINT] / DataTable[REG_MAXIMUM_UNIT_CURRENT];

#ifdef TYPE_UNIT_DCU
	LOGIC_ConstantPulseRateConfig(PulseWidth_CTRL2);
#else
	LOGIC_VariablePulseRateConfig(PulseWidth_CTRL1);
#endif
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
#ifdef TYPE_UNIT_DCU
	TIM_Start(TIM2);
#else
	TIM_Start(TIM3);
#endif
}
//-------------------------------------------

void LOGIC_StartFallEdge()
{
	LL_OutputCompensation(false);

#ifdef TYPE_UNIT_DCU
	TIM_Start(TIM3);
#else
	TIM_Start(TIM2);
#endif
}
//-------------------------------------------

void LOGIC_SofwarePulseStart()
{
	LL_SW_Trig(true);
	DELAY_US(3000);
	LL_SW_Trig(false);
}
//-------------------------------------------

Int16U LOGIC_ExctractCurrentValue()
{
	Int16U ArrayTemp[VALUES_x_SIZE];
	float AvgData = 0;

	// Копирование данных
	for (int i = 0; i < VALUES_x_SIZE; ++i)
		ArrayTemp[i] = CONTROL_Values_DUTCurrent[i];

	// Сортировка
	qsort(ArrayTemp, VALUES_x_SIZE, sizeof(*ArrayTemp), MEASURE_SortCondition);

	// Усреднение и возврат результата
	for (int i = VALUES_x_SIZE - RESULT_AVERAGE_POINTS; i < VALUES_x_SIZE; ++i)
		AvgData += ArrayTemp[i];

	return (Int16U)(AvgData / RESULT_AVERAGE_POINTS);
}
//-------------------------------------------

void LOGIC_HandleAdcSamples()
{
	float AvgData = 0, Error;
	static Int16U AllowedErrorCounter = 0;
	static Int16U UnallowedErrorCounter = 0;

	// Сохранение усредненного результата
	for (int i = 0; i < ADC_AVG_SAMPLES; ++i)
		AvgData += LOGIC_DUTCurrentRaw[i];

	if (CONTROL_Values_Counter < VALUES_x_SIZE)
	{
		CONTROL_Values_DUTCurrent[CONTROL_Values_Counter] = (Int16U)(AvgData / ADC_AVG_SAMPLES);
		CONTROL_Values_Counter++;
	}

	// Определение выхода тока на заданный уровень
	if(CONTROL_SubState == SS_Plate)
	{
		Error = AvgData / DataTable[REG_CURRENT_SETPOINT] * 1000;

		if (Error <= DataTable[REG_ALLOWED_ERROR])
			AllowedErrorCounter++;
		else
			UnallowedErrorCounter++;

		if (AllowedErrorCounter >= DataTable[REG_ERROR_COUNTER_MAX])
			LL_External_DC_RDY(true);
		else if (AllowedErrorCounter >= DataTable[REG_ERROR_COUNTER_MAX])
				DataTable[REG_WARNING] = WARNING_CURRENT_READY;
	}
	else
	{
		AllowedErrorCounter = 0;
		UnallowedErrorCounter = 0;
	}
}
//-------------------------------------------

void LOGIC_ClearDataArrays()
{
	for (int i = 0; i < VALUES_x_SIZE; ++i)
		CONTROL_Values_DUTCurrent[i] = 0;

	CONTROL_Values_Counter = 0;
}
//-------------------------------------------

int MEASURE_SortCondition(const void *A, const void *B)
{
	return (int)(*(Int16U *)A) - (int)(*(Int16U *)B);
}
//-----------------------------------------
