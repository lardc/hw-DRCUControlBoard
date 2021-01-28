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

// Types
//
typedef struct __SampleData
{
	float Voltage;
	float Current;
} SampleData, *pSampleData;

// Varibales
//
volatile uint16_t LOGIC_OutputPulse[PULSE_ARR_MAX_LENGTH];
volatile uint16_t LOGIC_DUTCurrentRaw[PULSE_ARR_MAX_LENGTH];
volatile uint16_t LOGIC_DUTVoltageRaw[PULSE_ARR_MAX_LENGTH];
volatile uint16_t LOGIC_DataCounter = 0;
SampleData LOGIC_DataArrays[PULSE_ARR_MAX_LENGTH];
uint16_t TimeOpAmpStabilize = 0, TimePreCurrentPlate = 0, TimeSyncShift = 0;
float TimePulseWidth = 0;
//
volatile HighSpeedState HS_State = HSS_None;
//
static uint16_t CounterPreCurrent = 0;

// Forward functions
//
void LOGIC_ClearDataArrays();
int LOGIC_SortCondition(const void *A, const void *B);

// Functions
//
// ����� ���������� ����� � ��������� �� ���������
void LOGIC_ResetHWToDefaults(bool StopPowerSupply)
{
	// ������� �� �����
	while (!LOGIC_IsPulseFinished());

	LL_ExternalLED(FALSE);


	// ������������ ��� � ��� � ������� �����
	DAC_SwitchToBase();
	DAC_SetValueCh1(DAC1, 0);
	//
	ADC_SwitchToBase();
}
//-------------------------------------------

// ��������� ������ �������
void LOGIC_StartBatteryCharge()
{

	//
	LL_PowerOn(TRUE);
}
//-------------------------------------------

// ���������� � ������������ ��������
void LOGIC_PrepareForPulse(float PrePulseCurrent, float PulseCurrent)
{
	LOGIC_ClearDataArrays();
	LOGIC_GeneratePulseForm(PrePulseCurrent, PulseCurrent);
	//
	LL_ExternalLED(TRUE);
}
//-------------------------------------------

// ��������� ����� ���������������� �������� ������������
void LOGIC_StartPulse()
{
	// ���������� ������������� ��������� ����������
	TimeOpAmpStabilize = DataTable[REG_OP_AMP_STAB_TIME];
	TimePreCurrentPlate = DataTable[REG_SET_PRE_PULSE_TIME];
	TimeSyncShift = DataTable[REG_SYNC_SHIFT];
	TimePulseWidth = (float)DataTable[REG_DAC_PULSE_WIDTH];

	// ��������� �������� ���������
	LL_PowerSupplyStop(TRUE);

	// ����� �� � ������� ����
	DAC_SetValueCh1(DAC1, DataTable[REG_DAC_BASE_OFFSET]);
	DAC_ForceSWTrigCh1(DAC1);

	// ���������� ��� � ��� ��� ������ �� �������
	DAC_SwitchToHighSpeed();
	ADC_SwitchToHighSpeed();

	// ���������� ��������� ������ DMA
	DMA_ChannelReload(DMA_ADC_DUT_I_CHANNEL, LOGIC_DataCounter);
	//
	DMA_ChannelEnable(DMA_ADC_DUT_I_CHANNEL, true);

	// ���������� ������������ ���
	ADC_SamplingTrig(ADC1);

	// ��������� ������� ������������� ���������� �����
	TIM_Config(TIM2, SYSCLK, ANALOG_OPTO_UNLOCK);

	// ����������� ���������� �����
	HS_State = HSS_AnalogUnlockOpto;
	LL_AmpLock(FALSE);
	TIM_Start(TIM2);
}
//-------------------------------------------

void LOGIC_PulseFinished()
{
	// ����������� ���������� �����
	LL_MuteChannel1(TRUE);
	LL_MuteChannel2(TRUE);

	// ��������� ��������
	DELAY_US(500);
	LL_AmpLock(TRUE);
	DELAY_US(200);

	// ������������ ��� � ��� � ������� �����
	DAC_SwitchToBase();
	DAC_SetValueCh1(DAC1, 0);
	//
	ADC_SwitchToBase();
}
//-------------------------------------------

bool LOGIC_IsPulseFinished()
{
	return (HS_State == HSS_None);
}
//-------------------------------------------

void LOGIC_ClearDataArrays()
{
	uint16_t i;

	for (i = 0; i < PULSE_ARR_MAX_LENGTH; ++i)
	{
		LOGIC_OutputPulse[i] = 0;
		LOGIC_DUTCurrentRaw[i] = 0;
		LOGIC_DUTVoltageRaw[i] = 0;
	}
	LOGIC_DataCounter = 0;
}
//-------------------------------------------

void LOGIC_GeneratePulseForm(float PrePulseCurrent, float PulseCurrent)
{
	uint16_t i;

	// ����� �������� ������� ���
	float DACBaseOffset = (float)DataTable[REG_DAC_BASE_OFFSET];

	// �������� ������ �������� ���������������� ����
	float DACPreCurrentGain = (float)DataTable[REG_DAC_PRE_CURR_GAIN] / 10;

	// ������ �������� �� ������ 50%
	float PulseWidth = (float)DataTable[REG_DAC_PULSE_WIDTH];

	// ������� ������������ � ����� ��� ���������������� � ��������� ��������
	CounterPreCurrent = (uint16_t)((float)DataTable[REG_SET_PRE_PULSE_TIME] / DAC_TIME_STEP);
	uint16_t CounterCurrent = (uint16_t)(PulseWidth / DAC_TIME_STEP);

	// ������� �������� ��� ��� ���������������� �������� � ��������� ���������
	float CurrentToDAC_K = (float)DataTable[REG_I_TO_DAC_K] / 1000;
	float CurrentToDAC_Offset = (float)((int16_t)DataTable[REG_I_TO_DAC_OFFSET]);
	//
	float ValDAC_PreCurrent = PrePulseCurrent * CurrentToDAC_K + CurrentToDAC_Offset;
	float ValDAC_Current = PulseCurrent * CurrentToDAC_K + CurrentToDAC_Offset;

	// �������� ������ ���� ��������������
	ValDAC_PreCurrent = (ValDAC_PreCurrent > 0) ? ValDAC_PreCurrent : 0;
	ValDAC_Current = (ValDAC_Current > 0) ? ValDAC_Current : 0;

	// ���������� ������� ���������������� �������� � �������������
	uint16_t PreCurrentCounterTop = CounterPreCurrent + CounterCurrent / 2;
	for (i = 0; i < PreCurrentCounterTop; ++i)
		LOGIC_OutputPulse[i] = (uint16_t)(ValDAC_PreCurrent * (1 + DACPreCurrentGain * (PreCurrentCounterTop - i) / PreCurrentCounterTop) + DACBaseOffset);

	// ���������� �������� ���������
	for (i = 0; i < CounterCurrent; ++i)
	{
		uint16_t PulseValue = (uint16_t)(ValDAC_Current * sin(PI_VALUE * i * DAC_TIME_STEP / PulseWidth) + DACBaseOffset);

		// ������� �������� ���������� ���������
		if (PulseValue > LOGIC_OutputPulse[CounterPreCurrent + i])
			LOGIC_OutputPulse[CounterPreCurrent + i] = PulseValue;
	}

	// ����������� ������� � EP
	LOGIC_DataCounter = CounterPreCurrent + CounterCurrent + (uint16_t)(DAC_MAIN_PULSE_STOP / DAC_TIME_STEP);
	//
	for (i = 0; i < LOGIC_DataCounter; ++i)
		CONTROL_Values_Setpoint[i] = LOGIC_OutputPulse[i];
	CONTROL_Values_SetCounter = LOGIC_DataCounter;
}
//-------------------------------------------

ProcessResult LOGIC_ProcessOutputData()
{
	uint16_t i;
	float ResAvg = 0, ResAvgSq = 0;
	float Max_dVdt = 0, Vmax = 0;
	float Vbr = 0, Vrsm = 0, Irsm = 0, Prsm = 0;

	// �������� �������� ��� � ��� � ����������
	MEASURE_ConvertVoltageArr(LOGIC_DUTVoltageRaw, (float *)LOGIC_DataArrays, LOGIC_DataCounter);
	MEASURE_ConvertCurrentArr(LOGIC_DUTCurrentRaw, (float *)LOGIC_DataArrays, LOGIC_DataCounter);

	// �������� ���������� � EP
	for (i = 0; i < LOGIC_DataCounter; ++i)
	{
		CONTROL_Values_DUTVoltage[i] = (uint16_t)LOGIC_DataArrays[i].Voltage;
		CONTROL_Values_DUTCurrent[i] = (uint16_t)LOGIC_DataArrays[i].Current;
	}
	CONTROL_Values_ADCCounter = LOGIC_DataCounter;

	// ��������������� ����������
	uint16_t ResAvgCounter = 0;
	for (i = 0; i < LOGIC_DataCounter; ++i)
	{
		// ������� �������� ������������� (���� �������������)
		if ((LOGIC_DataArrays[i].Current > 0) && (LOGIC_DataArrays[i].Voltage > 0))
		{
			ResAvg += LOGIC_DataArrays[i].Voltage / LOGIC_DataArrays[i].Current;
			++ResAvgCounter;
		}

		// ������������ ����������
		if (LOGIC_DataArrays[i].Voltage > Vmax)
			Vmax = LOGIC_DataArrays[i].Voltage;

		// ������������ �������� ���������� ����������
		if (i < (LOGIC_DataCounter - 1))
		{
			float tmp = fabs(LOGIC_DataArrays[i].Voltage - LOGIC_DataArrays[i + 1].Voltage);
			if (tmp > Max_dVdt)
				Max_dVdt = tmp;
		}
	}
	ResAvg /= ResAvgCounter;

	// ������ ������������������� ���������� �������� �������������
	for (i = 0; i < LOGIC_DataCounter; ++i)
	{
		// ���� �������������
		if ((LOGIC_DataArrays[i].Current > 0) && (LOGIC_DataArrays[i].Voltage > 0))
			ResAvgSq += pow(LOGIC_DataArrays[i].Voltage / LOGIC_DataArrays[i].Current - ResAvg, 2);
	}
	ResAvgSq = sqrt(ResAvgSq / ResAvgCounter);

	// ��������� ���������� �����������������
	uint16_t TimeSyncShiftCounter = (uint16_t)((float)TimeSyncShift / DAC_TIME_STEP);
	for (i = (CounterPreCurrent + TimeSyncShiftCounter - MEASURE_AVG); i < (CounterPreCurrent + TimeSyncShiftCounter); ++i)
		Vbr += LOGIC_DataArrays[i].Voltage;
	Vbr /= MEASURE_AVG;

	// ���������� ����������� ��������� �� �������� ����
	qsort((void *)LOGIC_DataArrays, LOGIC_DataCounter, sizeof(SampleData), &LOGIC_SortCondition);

	// ��������� ������� ��������
	for (i = (LOGIC_DataCounter - MEASURE_AVG); i < LOGIC_DataCounter; ++i)
	{
		Vrsm += LOGIC_DataArrays[i].Voltage;
		Irsm += LOGIC_DataArrays[i].Current;
	}
	Vrsm /= MEASURE_AVG;
	Irsm /= MEASURE_AVG;
	Prsm = Vrsm * Irsm / 1000;

	// ������� ����������
	ProcessResult ret;
	ret.Vbr  = Vbr;
	ret.Vrsm = Vrsm;
	ret.Irsm = Irsm;
	ret.Prsm = Prsm;
	ret.Max_dVdt = Max_dVdt;
	ret.Vmax = Vmax;
	ret.LoadR = (ResAvgSq < LOAD_R_STDEV) ? true : false;

	return ret;
}
//-------------------------------------------

int LOGIC_SortCondition(const void *A, const void *B)
{
	return ((int)(((pSampleData)A)->Current) - (int)(((pSampleData)B)->Current));
}
//-----------------------------------------

void LOGIC_DiagPulseDAC()
{
	// ���������� ����������
	LL_ExternalLED(TRUE);
	LL_Contactor(TRUE);
	LL_Demagnitization(TRUE);
	Delay_mS(1000);
	LL_Demagnitization(FALSE);
	Delay_mS(10);

	// ������ ������������
	LL_Sync(TRUE);
	LL_PowerSupplyStop(TRUE);

	// ������������ ������ ���
	DAC_SetValueCh1(DAC1, DataTable[REG_DIAG_DAC_PULSE]);
	DAC_ForceSWTrigCh1(DAC1);

	// ���������� ���������� ����������� ������
	LL_MuteChannel1(FALSE);
	LL_MuteChannel2(FALSE);
	LL_AmpLock(FALSE);

	DELAY_US(300);

	LL_MuteChannel1(TRUE);
	LL_MuteChannel2(TRUE);
	LL_AmpLock(TRUE);

	LL_Sync(FALSE);

	// ���������� ����������
	LL_PowerSupplyStop(FALSE);
	LL_ExternalLED(FALSE);
	LL_Contactor(FALSE);
}
//-----------------------------------------
