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

// Varibales
//
volatile uint16_t LOGIC_DUTCurrentRaw[PULSE_ARR_MAX_LENGTH];
Int16U CurrentRateCode;

// Forward functions
//
void LOGIC_ClearDataArrays();
void LOGIC_SetCompensationVoltage();

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
	LL_OverVoltageProtectionReset(TRUE);
	LL_OutputCompensation(FALSE);
	LL_External_DC_RDY(FALSE);
	LL_ExternalLamp(FALSE);

	// Переключение АЦП в базовый режим
	ADC_SwitchToBase();
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


	// Настройка аппаратной части
	//
	ADC_SwitchToHighSpeed();
	LOGIC_SetCompensationVoltage();
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

void LOGIC_SetCompensationVoltage()
{

}
//-------------------------------------------

void LOGIC_VariablePulseRateConfig(Int16U PulseWidth)
{
	TIM_Config(TIM3, SYSCLK, PulseWidth);
}
//-------------------------------------------

void LOGIC_ConstantPulseRateConfig(Int16U PulseWidth)
{
	TIM_Config(TIM2, SYSCLK, PulseWidth);
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
#ifdef TYPE_UNIT_DCU
	TIM_Start(TIM3);
#else
	TIM_Start(TIM2);
#endif
}
//-------------------------------------------

void LOGIC_SofwarePulseStart(bool State)
{
	State ? TIM_Start(TIM16) : TIM_Stop(TIM16);
}
//-------------------------------------------

void LOGIC_ClearDataArrays()
{
	uint16_t i;

	for (i = 0; i < PULSE_ARR_MAX_LENGTH; ++i)
		LOGIC_DUTCurrentRaw[i] = 0;
}
//-------------------------------------------
