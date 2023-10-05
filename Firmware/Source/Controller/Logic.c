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
#define CURRENT_RATE_R1				1
#define CURRENT_RATE_R2				2
#define CURRENT_RATE_R3				3
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
#define ARRAY_SORTING_PART_LENGHT	10					// Часть массива для сортировки
#define RESULT_AVERAGE_POINTS		10					// Количество точек усредения результата измерения
//
#define EXT_LAMP_ON_STATE_TIME		500					// Время работы внешнего индикатора, мс


// Structs
//
struct __ConfigParamsStruct ConfigParams;

// Varibales
//
volatile Int16U LOGIC_ADCRaw[ADC_CHANNELS];
float TestCurrent = 0;
float TestCurrentRate = 0;
float LOGIC_BatteryVoltage = 0;
float LOGIC_IntPsVoltage = 0;

// Forward functions
//
void LOGIC_SetCompensationVoltage(Int16U Current);
int MEASURE_SortCondition(const void *A, const void *B);
void LOGIC_SetCurrentRangeRate(Int16U Code);
void LOGIC_CurrentSourceTurnOff();

// Functions
//
// Сброс аппаратных линий в состояния по умолчанию
void LOGIC_ResetHWToDefaults(bool StopPowerSupply)
{
	LL_PulseEn(false);
	LOGIC_SofwarePulseStart(false);
	LOGIC_CurrentSourceTurnOff();

	if (StopPowerSupply)
		LOGIC_BatteryCharge(false);


	LL_OutputLock(true);
	LL_IntPowerSupplyDischarge(false);
	LL_IntPowerSupplyEn(false);
	LL_OverVoltageProtectionReset();
	LL_OutputCompensation(false);
	LL_External_DC_RDY(false);
}
//-------------------------------------------

void LOGIC_CurrentSourceTurnOff()
{
	LOGIC_ConstantPulseRateConfig(0, 0);
	LOGIC_VariablePulseRateConfig(0);
	LOGIC_SetCurrentRangeRate(CODE_CURRENT_RATE_OFF);
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
	ConfigParams.IntPsVoltageOffset_Ext = (Int16S)DataTable[REG_I_TO_V_INTPS_EXT_OFFSET];
	ConfigParams.IntPsVoltageK_Ext = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_EXT_K] / 1000;
	ConfigParams.IntPsVoltageK2_Ext = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_EXT_K2];

	switch(DataTable[REG_CURRENT_RATE])
	{
		case CURRENT_RATE_R0:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R0;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R0];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R0_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R0_OFFSET];
			ConfigParams.IntPsVoltageK4 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R0_K4] * 1e7;
			ConfigParams.IntPsVoltageK2 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R0_K2] / 1e6;
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R0_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R0_OFFSET];
			break;

		case CURRENT_RATE_R1:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R1;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R1];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R1_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R1_OFFSET];
			ConfigParams.IntPsVoltageK4 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R1_K4] * 1e7;
			ConfigParams.IntPsVoltageK2 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R1_K2] / 1e6;
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R1_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R1_OFFSET];
			break;

		case CURRENT_RATE_R2:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R2;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R2];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R2_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R2_OFFSET];
			ConfigParams.IntPsVoltageK4 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R2_K4] * 1e7;
			ConfigParams.IntPsVoltageK2 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R2_K2] / 1e6;
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R2_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R2_OFFSET];
			break;

		case CURRENT_RATE_R3:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R3;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R3];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R3_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R3_OFFSET];
			ConfigParams.IntPsVoltageK4 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R3_K4] * 1e7;
			ConfigParams.IntPsVoltageK2 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R3_K2] / 1e6;
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R3_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R3_OFFSET];
			break;

		case CURRENT_RATE_R4:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R4;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R4];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R4_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R4_OFFSET];
			ConfigParams.IntPsVoltageK4 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R4_K4] * 1e7;
			ConfigParams.IntPsVoltageK2 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R4_K2] / 1e6;
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R4_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R4_OFFSET];
			break;

		case CURRENT_RATE_R5:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R5;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R5];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R5_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R5_OFFSET];
			ConfigParams.IntPsVoltageK4 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R5_K4] * 1e7;
			ConfigParams.IntPsVoltageK2 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R5_K2] / 1e6;
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R5_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R5_OFFSET];
			break;

		case CURRENT_RATE_R6:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R6;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R6];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R6_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R6_OFFSET];
			ConfigParams.IntPsVoltageK4 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R6_K4] * 1e7;
			ConfigParams.IntPsVoltageK2 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R6_K2] / 1e6;
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R6_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R6_OFFSET];
			break;

		case CURRENT_RATE_R7:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R7;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R7];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R7_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R7_OFFSET];
			ConfigParams.IntPsVoltageK4 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R7_K4] * 1e7;
			ConfigParams.IntPsVoltageK2 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R7_K2] / 1e6;
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R7_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R7_OFFSET];
			break;

		case CURRENT_RATE_R8:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R8;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R8];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R8_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R8_OFFSET];
			ConfigParams.IntPsVoltageK4 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R8_K4] * 1e7;
			ConfigParams.IntPsVoltageK2 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R8_K2] / 1e6;
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R8_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R8_OFFSET];
			break;

		case CURRENT_RATE_R9:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R9;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R9];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R9_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R9_OFFSET];
			ConfigParams.IntPsVoltageK4 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R9_K4] * 1e7;
			ConfigParams.IntPsVoltageK2 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R9_K2] / 1e6;
			ConfigParams.IntPsVoltageK = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R9_K] / 1000;
			ConfigParams.IntPsVoltageOffset = (Int16S)DataTable[REG_I_TO_V_INTPS_R9_OFFSET];
			break;

		case CURRENT_RATE_R10:
			ConfigParams.CurrentRateCode = CODE_CURRENT_RATE_R10;
			ConfigParams.MaxPulseWidth_CTRL1 = DataTable[REG_CTRL1_MAX_WIDTH_R10];
			ConfigParams.PulseWidth_CTRL1_K = (float)DataTable[REG_CTRL1_R10_K] / 1000;
			ConfigParams.PulseWidth_CTRL1_Offset = (Int16S)DataTable[REG_CTRL1_R10_OFFSET];
			ConfigParams.IntPsVoltageK4 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R10_K4] * 1e7;
			ConfigParams.IntPsVoltageK2 = (float)(Int16S)DataTable[REG_I_TO_V_INTPS_R10_K2] / 1e6;
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
	{
		//Напряжение по коэффицентам
		float EXTRate = ((ConfigParams.IntPsVoltageK2_Ext / TestCurrent) + ConfigParams.IntPsVoltageK_Ext * TestCurrent + ConfigParams.IntPsVoltageOffset_Ext);
		ConfigParams.IntPsVoltage = ConfigParams.IntPsVoltageK4 / (TestCurrent*TestCurrent*TestCurrent*TestCurrent) + TestCurrent * TestCurrent * ConfigParams.IntPsVoltageK2 * ConfigParams.IntPsVoltageK2_Ext + TestCurrent * ConfigParams.IntPsVoltageK  + ConfigParams.IntPsVoltageOffset + EXTRate;
	}
	if(ConfigParams.IntPsVoltage > INTPS_VOLTAGE_MAX)
		ConfigParams.IntPsVoltage = INTPS_VOLTAGE_MAX;

	if(ConfigParams.IntPsVoltage < INTPS_VOLTAGE_MIN)
		ConfigParams.IntPsVoltage = INTPS_VOLTAGE_MIN;

	LOGIC_SetCurrentRangeRate(ConfigParams.CurrentRateCode);

	ConfigParams.PulseWidth_CTRL2_K = (float)DataTable[REG_CTRL2_K] / 1000;
	ConfigParams.PulseWidth_CTRL2_Offset = (Int16S)DataTable[REG_CTRL2_OFFSET];
	CurrentTemp = TestCurrent * ConfigParams.PulseWidth_CTRL2_K + ConfigParams.PulseWidth_CTRL2_Offset;
	ConfigParams.PulseWidth_CTRL2 = (Int16U)(DataTable[REG_CTRL2_MAX_WIDTH] * CurrentTemp / DataTable[REG_MAXIMUM_UNIT_CURRENT]);

	ConfigParams.PulseWidth_CTRL1 = (Int16U)((TestCurrent + ConfigParams.PulseWidth_CTRL1_Offset) * ConfigParams.PulseWidth_CTRL1_K);

	if(ConfigParams.PulseWidth_CTRL1 > ConfigParams.MaxPulseWidth_CTRL1)
		ConfigParams.PulseWidth_CTRL1 = ConfigParams.MaxPulseWidth_CTRL1;

	LOGIC_ConstantPulseRateConfig(ConfigParams.PulseWidth_CTRL2, ConfigParams.IntPsVoltage);
	LOGIC_SetCompensationVoltage(TestCurrent);

}
//-------------------------------------------

void LOGIC_SetCurrentRangeRate(Int16U Code)
{
	LL_ExtRegWriteData(Code);
	LL_FlipLineRCK();
	LL_ExtRegWriteData(CODE_CURRENT_RATE_OFF);
}
//-------------------------------------------

void LOGIC_SetCompensationVoltage(Int16U Current)
{
	DAC_SetValueCh1(DAC1, MEASURE_ConvertValxtoDAC(Current, REG_I_TO_DAC_OFFSET, REG_I_TO_DAC_K,
			REG_I_TO_DAC_P2,  REG_I_TO_DAC_P1,  REG_I_TO_DAC_P0));
	DAC_ForceSWTrigCh1(DAC1);
}
//-------------------------------------------

void LOGIC_ConstantPulseRateConfig(Int16U PulseWidth, Int16U IntPsVoltage)
{
	// Коэффициент компенсации амлитуды тока от напряжения внутренего источника
	PulseWidth = PulseWidth * (INTPS_VOLTAGE_MAX / IntPsVoltage);

	TIM_Reset(TIM2);
	TIMx_PWM_SetValue(TIM2, TIMx_CHANNEL3, PulseWidth);
}
//-------------------------------------------

void LOGIC_VariablePulseRateConfig(Int16U PulseWidth)
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
	LL_OutputCompensation(false);
}
//-------------------------------------------
void LOGIC_StopFallEdge()
{
	LL_PulseEn(false);
	TIM_Stop(TIM3);
	TIM_Reset(TIM3);
	LL_OutputLock(true);
}
//-------------------------------------------

void LOGIC_SofwarePulseStart(bool Start)
{
	LL_SW_Trig(Start);
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
	SortStartIndex = CONTROL_Values_Counter / ARRAY_SORTING_PART_LENGHT;
	SortSize = CONTROL_Values_Counter - SortStartIndex;
	qsort((ArrayTemp + SortStartIndex), SortSize, sizeof(*ArrayTemp), MEASURE_SortCondition);

	// Усреднение и возврат результата
	for (int i = CONTROL_Values_Counter - RESULT_AVERAGE_POINTS; i < CONTROL_Values_Counter; ++i)
		AvgData += ArrayTemp[i];

	return (Int16U)(AvgData / RESULT_AVERAGE_POINTS);
}
//-------------------------------------------

void LOGIC_HandleAdcSamples()
{
	float Error;
	static Int16S AllowedErrorCounter = 0;
	float Current;

	if (CONTROL_SubState == SS_RiseEdge || CONTROL_SubState == SS_Plate || CONTROL_SubState == SS_FallEdge)
	{
		Current = MEASURE_ConvertCurrent(LOGIC_ADCRaw[ADC_CURRENT_POS]);

		if(CONTROL_Values_Counter < VALUES_x_SIZE)
		{
			CONTROL_Values_DUTCurrent[CONTROL_Values_Counter] = Current * 10;
			CONTROL_Values_Counter++;
		}

		// Определение выхода тока на заданный уровень
		if(CONTROL_SubState == SS_Plate)
		{
			Error = abs(100 - Current / TestCurrent * 100);

			if ((Error <= ((float)DataTable[REG_ALLOWED_ERROR] / 10)) || (Current > TestCurrent))
				AllowedErrorCounter++;
			else
				AllowedErrorCounter--;

			if (AllowedErrorCounter >= DataTable[REG_ERROR_COUNTER_MAX])
				LL_External_DC_RDY(true);
			else if (-AllowedErrorCounter >= DataTable[REG_ERROR_COUNTER_MAX])
					DataTable[REG_WARNING] = WARNING_CURRENT_NOT_READY;
		}
		else
			AllowedErrorCounter = 0;
	}
	else
	{
		LOGIC_BatteryVoltage = MEASURE_ConvertBatteryVoltage(LOGIC_ADCRaw[ADC_BAT_VOLTAGE_POS]);
		LOGIC_IntPsVoltage = MEASURE_ConvertIntPsVoltage(LOGIC_ADCRaw[ADC_INTPS_VOLTAGE_POS]);
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
//-----------------------------------------------
