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
float MEASURE_VoltageX(Int16U ADC1Channel, Int16U RegisterOffset, Int16U RegisterK)
{
	float Offset = (float)((Int16S)DataTable[RegisterOffset]);
	float K = (float)DataTable[RegisterK] / 10000;
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
	static Int16U MeasureCounter = 0;
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

Int16U MEASURE_ConvertValxtoDAC()
{
		float Offset = (float)((Int16S)DataTable[REG_V_TO_DAC_OFFSET]);

		return Offset;
}
