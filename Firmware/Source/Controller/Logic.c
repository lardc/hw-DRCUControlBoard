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
#define CODE_CURRENT_RATE_OFF		0x00
#define CODE_CURRENT_RATE_050		0x08
#define CODE_CURRENT_RATE_075		0x04
#define CODE_CURRENT_RATE_100		0x02
#define CODE_CURRENT_RATE_250		0x01
#define CODE_CURRENT_RATE_500		0x10
#define CODE_CURRENT_RATE_750		0x11
#define CODE_CURRENT_RATE_1000		0x1F
#define CODE_CURRENT_RATE_1500		0x20
#define CODE_CURRENT_RATE_2500		0x3F
#define CODE_CURRENT_RATE_3000		0x20
#define CODE_CURRENT_RATE_5000		0x7F
//
#define RESULT_AVERAGE_POINTS		50					// Количество точек усредения результата измерения

// Varibales
//
volatile uint16_t LOGIC_DUTCurrentRaw[ADC_AVG_SAMPLES];
Int16U CurrentRateCode;

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
		LOGIC_BatteryCharge(FALSE);

	LOGIC_SofwarePulseStart(FALSE);
	MEASURE_Start(FALSE);

	LL_OutputLock(TRUE);
	LL_IntPowerSupplyDischarge(FALSE);
	LL_IntPowerSupplyEn(FALSE);
	LL_OverVoltageProtectionReset();
	LL_OutputCompensation(FALSE);
	LL_External_DC_RDY(FALSE);
	LL_ExternalLamp(FALSE);

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
		LL_PowerOnMechRelay(TRUE);
		DELAY_MS(100);
		LL_PowerOnSolidStateRelay(TRUE);
	}
	else
	{
		LL_PowerOnMechRelay(TRUE);
		LL_PowerOnSolidStateRelay(TRUE);
	}
}
//-------------------------------------------

void LOGIC_Config()
{
	Int32U MaxPulseWidth_CTRL1, PulseWidth_CTRL1, PulseWidth_CTRL2;

	LOGIC_ClearDataArrays();

	// Настройка аппаратной части
	//
	ADC_SwitchToHighSpeed();
	LOGIC_SetCompensationVoltage(DataTable[REG_CURRENT_SETPOINT]);
	LL_OutputLock(FALSE);
	LL_PowerOnSolidStateRelay(FALSE);

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

	PulseWidth_CTRL1 = MaxPulseWidth_CTRL1 * (float)DataTable[REG_CURRENT_SETPOINT] / DataTable[REG_CURRENT_SETPOINT_MAX];
	PulseWidth_CTRL2 = DataTable[REG_CTRL2_MAX_WIDTH] * (float)DataTable[REG_CURRENT_SETPOINT] / DataTable[REG_CURRENT_SETPOINT_MAX];

	LOGIC_VariablePulseRateConfig(PulseWidth_CTRL1);
	LOGIC_ConstantPulseRateConfig(PulseWidth_CTRL2);
}
//-------------------------------------------

void LOGIC_SetCompensationVoltage(Int16U Current)
{
	DAC_SetValueCh1(DAC1, MEASURE_ConvertValxtoDAC(Current, REG_I_TO_DAC_OFFSET, REG_I_TO_DAC_K,
			REG_I_TO_DAC_P2,  REG_I_TO_DAC_P1,  REG_I_TO_DAC_P0));
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
	LL_OutputCompensation(FALSE);

#ifdef TYPE_UNIT_DCU
	TIM_Start(TIM3);
#else
	TIM_Start(TIM2);
#endif
}
//-------------------------------------------

void LOGIC_SofwarePulseStart(bool State)
{
	if (State)
		TIM_Start(TIM16);
	else
	{
		TIM_Stop(TIM16);
		TIM_Reset(TIM16);
	}
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
			LL_External_DC_RDY(TRUE);
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
	return (int)(*(uint16_t *)A) - (int)(*(uint16_t *)B);
}
//-----------------------------------------
