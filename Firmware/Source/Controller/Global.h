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
#define ENABLE_LOCKING					false
// -----------------------------------------------
#define EP_WRITE_COUNT					0							// ���������� �������� ��� ������
#define EP_COUNT						1							// ���������� �������� ��� ������
#define VALUES_x_SIZE					2000						// ������ �������� ��������
#define ENABLE_LOCKING					false
// -----------------------------------------------

// ��������� ���������
#define TIME_LED_BLINK					500							// ������ �������� ���������� �� ����� (� ��)
// -----------------------------------------------

// ��������� ������ �������
#define	BAT_CHARGE_TIMEOUT				30000						// ����� �������� ������ ����� ������ ������� (� ��)
#define	BAT_CHARGE_SHORT_TIMEOUT		5000						// ����� �������� ������ ����� ���������� (� ��)
// -----------------------------------------------

// ��������� ���������
#define ADC_REF_VOLTAGE					3300.0f						// ������� ���������� (� �)
#define ADC_RESOLUTION					4095						// ���������� ���
#define ADC_AVG_SAMPLES					5							// ���������� ����� ����������
// -----------------------------------------------

#define INTPS_VOLTAGE_MAX				1250.0f						// ������������ ���������� ����������� ��������� ������������� (� * 10)
#define INTPS_VOLTAGE_MIN				900.0f						// ����������� ���������� ����������� ��������� ������������� (� * 10)

#endif //  __GLOBAL_H
