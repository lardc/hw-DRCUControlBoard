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

// ��������� ���������
#define ADC_REF_VOLTAGE					3300.0f						// ������� ���������� (� �)
#define ADC_RESOLUTION					4095						// ���������� ���
// -----------------------------------------------

#endif //  __GLOBAL_H
