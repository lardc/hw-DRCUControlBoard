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
float MEASURE_VoltageX(Int16U ADC1Channel, Int16U RegisterOffset, Int16U RegisterK);
float MEASURE_ConvertADCtoValx(Int16U ADCValue, Int16U RegisterOffset, Int16U RegisterK, Int16U RegisterP0, Int16U RegisterP1, Int16U RegisterP2);

// Functions
//
float MEASURE_VoltageX(Int16U ADCValue, Int16U RegisterOffset, Int16U RegisterK)
{
	float Offset = (float)((Int16S)DataTable[RegisterOffset]);
	float K = (float)DataTable[RegisterK] / 10000;
	float result = (ADCValue - Offset) * ADC_REF_VOLTAGE / ADC_RESOLUTION * K;

	return (result > 0) ? result : 0;
}
//------------------------------------------------------------------------------

float MEASURE_ConvertBatteryVoltage(Int16U ADCValue)
{
	return MEASURE_VoltageX(ADCValue, REG_V_BAT_OFFSET, REG_V_BAT_K);
}
//------------------------------------------------------------------------------

float MEASURE_ConvertIntPsVoltage(Int16U ADCValue)
{
	static Int16U MeasureCounter = 0;
	static float DataArray[MEASURE_FILTER_SIZE];
	float DataSum = 0;

	DataArray[MeasureCounter] = MEASURE_VoltageX(ADCValue, REG_V_INT_PS_OFFSET, REG_V_INT_PS_K);

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

float MEASURE_ConvertADCtoValx(Int16U ADCValue, Int16U RegisterOffset, Int16U RegisterK,
		Int16U RegisterP0, Int16U RegisterP1, Int16U RegisterP2)
{
	float Result;

	float Offset = (float)((Int16S)DataTable[RegisterOffset]);
	float K = (float)DataTable[RegisterK] / 1000;
	//
	float P0 = (float)((Int16S)DataTable[RegisterP0]);
	float P1 = (float)DataTable[RegisterP1] / 1000;
	float P2 = (float)((Int16S)DataTable[RegisterP2]) / 1e6;

	Result = ((float)ADCValue - Offset) * ADC_REF_VOLTAGE / ADC_RESOLUTION * K;
	Result = Result * Result * P2 + Result * P1 + P0;

	return Result;
}
//------------------------------------------------------------------------------

float MEASURE_ConvertCurrent(Int16U ADCValue)
{
	return MEASURE_ConvertADCtoValx(ADCValue, REG_I_DUT_OFFSET, REG_I_DUT_K, REG_I_DUT_P0, REG_I_DUT_P1, REG_I_DUT_P2);
}
//------------------------------------------------------------------------------
