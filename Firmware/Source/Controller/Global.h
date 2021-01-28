// -----------------------------------------
// Global definitions
// ----------------------------------------

#ifndef __GLOBAL_H
#define __GLOBAL_H

// Include
#include "stdinc.h"
#include "SysConfig.h"

// Definitions
// 
// Global miscellaneous parameters
#define	SCCI_TIMEOUT_TICKS				1000						// (� ��)
// Password to unlock non-volatile area for write
#define ENABLE_LOCKING					FALSE
// -----------------------------------------------
#define EP_WRITE_COUNT					0							// ���������� �������� ��� ������
#define EP_COUNT						7							// ���������� �������� ��� ������
#define VALUES_x_SIZE					PULSE_ARR_MAX_LENGTH		// ������ �������� ��������
#define ENABLE_LOCKING					FALSE
// -----------------------------------------------

// ��������� ���������
#define TIME_LED_BLINK					500							// ������ �������� ���������� �� ����� (� ��)
#define	TIME_DEMGNTZ					1000						// ����� ��������������� ���������� � ��������� ���������� (� ��)
#define TIME_SW_RELEASE_TIME			50							// ����� �� ���������� ���� ��������������� (� ��)
#define TIMEOUT_P2P_VOLTAGE				5000						// ������� ������ �� ���������� ����� �������� (����������� � TIME_DEMGNTZ) (� ��)
// -----------------------------------------------

// ��������� ������������ ��������� ��������
#define PI_VALUE						3.1416f						// �������� ����� ��
#define DAC_MAIN_PULSE_STOP				20.0f						// ����� ����� ��������� �������� ��� ��������� 0 �� ������� (� ���)
#define DAC_TIME_STEP					TIMER6_uS					// �������� ������� ��� (� ���)
#define MEASURE_AVG						10							// ���������� ������� ��� ���������� �����������
#define LOAD_R_STDEV					1							// ������������������ ���������� ������������� ��� ���������
#define ANALOG_OPTO_UNLOCK				500							// �������� ���������� ��������, ����������� �� �� (� ���)
//
#define PULSES_MAX						10							// ������������ ���������� ��������� �� ���������
#define PULSES_START_I					1000.0f						// ��������� ��� ��� ������ �� �������� (� ��)
#define PULSES_POWER_MAX_ERR			0.05f						// ���������� ������ �� �������� (� %)
#define PULSES_POWER_ERR_STOP			0.5f						// ������ �� ��������, ���������� � ��������� �������� (� %)
// -----------------------------------------------

// ��������� ������ �������
#define	BAT_CHARGE_TIMEOUT				30000						// ����� �������� ������ ����� ������ ������� (� ��)
#define	BAT_CHARGE_SHORT_TIMEOUT		5000						// ����� �������� ������ ����� ���������� (� ��)
#define BAT1_ADC1_CH					3							// ����� ������ ��� ������� 1
#define BAT2_ADC1_CH					4							// ����� ������ ��� ������� 2
#define BAT_VOLTAGE_DELTA				5.0f						// ���������� ����������� ���������� (� �)
// -----------------------------------------------

// ��������� ���������
#define ADC_REF_VOLTAGE					3300.0f						// ������� ���������� (� �)
#define ADC_RESOLUTION					4095						// ���������� ���
// -----------------------------------------------

// ������� ���������� ���������
// ��
#define MEAS_BREAK_IDLE_V				9500.0f						// ������������ ������� ���������� (� �)

// ��
#define MEAS_BREAK_SHORT_V				100.0f						// ����������� ������� ���������� (� �)
// -----------------------------------------------

#endif //  __GLOBAL_H
