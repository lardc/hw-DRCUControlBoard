// Header
#include "Measurement.h"
//
#include "DataTable.h"
#include "Board.h"
#include "Global.h"

// Definitions
//
#define MEASURE_FILTER_SIZE			16		// Кратно 2^x
#define MEASURE_FILTER_MASK			(MEASURE_FILTER_SIZE - 1)

// Forward functions
//
float MEASURE_VoltageX(uint16_t ADC1Channel, uint16_t RegisterOffset, uint16_t RegisterK);
void MEASURE_ConvertADCtoValx(volatile uint16_t *InputArray, float *OutputArray, uint16_t ArrayOffset, uint16_t DataLength,
							  uint16_t RegisterOffset, uint16_t RegisterK, uint16_t RegisterP0, uint16_t RegisterP1, uint16_t RegisterP2);

// Functions
//
float MEASURE_VoltageX(uint16_t ADC1Channel, uint16_t RegisterOffset, uint16_t RegisterK)
{
	float Offset = (float)((int16_t)DataTable[RegisterOffset]);
	float K = (float)DataTable[RegisterK] / 1000;
	float result = ((float)ADC_Measure(ADC1, ADC1Channel) - Offset) * ADC_REF_VOLTAGE / ADC_RESOLUTION * K;

	return (result > 0) ? result : 0;
}
//------------------------------------------------------------------------------

float MEASURE_BatteryVoltage()
{
	return MEASURE_VoltageX(ADC1_BAT_VOLTAGE_CHANNEL, REG_V_BAT_OFFSET, REG_V_BAT_K);
}
//------------------------------------------------------------------------------

float MEASURE_IntPSVoltage()
{
	static uint16_t MeasureCounter = 0;
	static float DataArray[MEASURE_FILTER_SIZE];
	float DataSum = 0;

	DataArray[MeasureCounter] = MEASURE_VoltageX(ADC1_INT_PS_VOLTAGE_CHANNEL, REG_V_INT_PS_OFFSET, REG_V_INT_PS_K);

	MeasureCounter++;
	MeasureCounter &= MEASURE_FILTER_MASK;

	for (int i = 0; i < MEASURE_FILTER_SIZE; i++)
		DataSum += DataArray[i];

	return (DataSum / MEASURE_FILTER_SIZE);
}
//------------------------------------------------------------------------------

Int16U MEASURE_ConvertValxtoDAC(float Value, Int16U RegisterOffset, Int16U RegisterK, Int16U RegisterP2,  Int16U RegisterP1,  Int16U RegisterP0)
{
	float Offset = DataTable[RegisterOffset];
	float K = (float)DataTable[RegisterK] / 1000;
	float P2 = (float)((Int16S)DataTable[RegisterP2]) / 1e6;
	float P1 = (float)DataTable[RegisterP1] / 1000;
	float P0 = (float)((Int16S)DataTable[RegisterP0]);

	Value = Value * Value * P2 + Value * P1 + P0;

	return (Int16U)(Value * K + Offset);
}
//------------------------------------------------------------------------------

void MEASURE_ConvertADCtoValx(volatile uint16_t *InputArray, float *OutputArray, uint16_t ArrayOffset, uint16_t DataLength,
							  uint16_t RegisterOffset, uint16_t RegisterK, uint16_t RegisterP0, uint16_t RegisterP1, uint16_t RegisterP2)
{
	uint16_t i;
	float tmp;

	float Offset = (float)((int16_t)DataTable[RegisterOffset]);
	float K = (float)DataTable[RegisterK] / 1000;
	//
	float P0 = (float)((int16_t)DataTable[RegisterP0]);
	float P1 = (float)DataTable[RegisterP1] / 1000;
	float P2 = (float)((int16_t)DataTable[RegisterP2]) / 1e6;

	for (i = 0; i < DataLength; ++i)
	{
		tmp = ((float)InputArray[i] - Offset) * ADC_REF_VOLTAGE / ADC_RESOLUTION * K;
		tmp = tmp * tmp * P2 + tmp * P1 + P0;
		OutputArray[i * 2 + ArrayOffset] = (tmp > 0) ? tmp : 0;
	}
}
//------------------------------------------------------------------------------

void MEASURE_ConvertCurrentArr(volatile uint16_t *InputArray, float *OutputArray, uint16_t DataLength)
{
	MEASURE_ConvertADCtoValx(InputArray, OutputArray, 1, DataLength, REG_I_DUT_OFFSET, REG_I_DUT_K, REG_I_DUT_P0, REG_I_DUT_P1, REG_I_DUT_P2);
}
//------------------------------------------------------------------------------

void MEASURE_Start(bool State)
{
	State ? TIM_Start(TIM6) : TIM_Stop(TIM6);
}
//------------------------------------------------------------------------------
