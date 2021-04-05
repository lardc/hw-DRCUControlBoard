#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H


// ACTIONS
//
#define ACT_ENABLE_POWER						1		// �������� ������� �����
#define ACT_DISABLE_POWER						2		// ��������� ������� �����
#define ACT_CLR_FAULT							3		// ������� ������
#define ACT_CLR_WARNING							4		// ������� ��������������
//
#define ACT_DBG_FAN								50		// ���������� ����� - ����������
#define ACT_DBG_LAMP							51		// ���������� ����� - ������� ���������
#define ACT_DBG_RELAY_MECH						52		// ���������� ����� - ������������ ����
#define ACT_DBG_RELAY_SOLID						53		// ���������� ����� - ������������� ����
#define ACT_DBG_INT_PS_CONTROL					54		// ���������� ����� - ���������� ���������� ��
#define ACT_DBG_INT_PS_DISCHARGE				55		// ���������� ����� - ������ ����������� ��
#define ACT_DBG_PROTECTION_RESET				56		// ���������� ����� - ����� ������ �� �������������� �� ����������� ������
#define ACT_DBG_OUTPUT_LOCK_CONTROL				57		// ���������� ����� - ���������� ����������� ������
#define ACT_DBG_SYNC							58		// ���������� ����� - ������������ �������� �������������
//
#define ACT_CONFIG_UNIT							100		// ������������ �����
#define ACT_SOFTWARE_START						101		// ����������� ������
//
#define ACT_SAVE_TO_ROM							200		// ���������� ���������������� ������ �� FLASH ����������
#define ACT_RESTORE_FROM_ROM					201		// �������������� ������ �� FLASH
#define ACT_RESET_TO_DEFAULT					202		// ����� DataTable � ��������� �� ���������
//
#define ACT_BOOT_LOADER_REQUEST					320		// ���������� ���������� � ����� ��������������������


// REGISTERS
//
#define REG_V_BAT_OFFSET						0		// �������� ������������ �������� ���������� �������
#define REG_V_BAT_K								1		// ����������� ��������� ��� � ����������, ��
#define REG_V_INT_PS_OFFSET						2		// �������� ������������ �������� ���������� ����������� ���������
#define REG_V_INT_PS_K							3		// ����������� ��������� ��� � ����������, ��
//
#define REG_I_DUT_OFFSET						10		// �������� ������������ �������� ����
#define REG_I_DUT_K								11		// ����������� ��������� ��� � ���, �
#define REG_I_DUT_P0							12		// �������� ������ ���������� �0
#define REG_I_DUT_P1							13		// ����������� ������ ���������� �1
#define REG_I_DUT_P2							14		// ����������� ������ ���������� �2
//
#define REG_BATTERY_FULL_CHRAGE_TIMEOUT			20		// ������� ������� ������ �������,��
#define REG_BATTERY_RECHRAGE_TIMEOUT			21		// ������� �������� �������,��
#define REG_BAT_VOLTAGE_THRESHOLD				22		// ����������� ����� ������ �������, � *10
#define REG_CURRENT_BOARD_QUANTITY				23		// ���������� ������� ����
// -----------------------------------------------

#define REG_CURRENT_SETPOINT					128		// ��������� ����������� ����, �
#define REG_CURRENT_RATE						129		// �������� ��������� ����, �/���

#define REG_DBG									150		// ���������� �������
// -----------------------------------------------

#define REG_DEV_STATE							96		// ������ ������ �����
#define REG_FAULT_REASON						97		// ������ ������ �����
#define REG_DISABLE_REASON						98		// ������� ���������� �����
#define REG_WARNING								99		// ��������������
#define REG_PROBLEM								100		// ������� Problem
//
#define REG_BAT_VOLTAGE							103		// ���������� �� �������������� ������� 1 (� � �10)
//
#define REG_CURRENT								111		// ���������� �������� ��������� ���� (� ��)


// ENDPOINTS
//
#define EP_DUT_I								1		// ������������ ������ ���� DUT (� ��)


// FAULT & DISABLE
//
#define DF_NONE									0
#define DF_BATTERY								1		// ������ ������ �������

// WARNINGS
//
#define WARNING_NONE							0

// User Errors
// 
#define ERR_NONE								0
#define ERR_CONFIGURATION_LOCKED				1		// ���������� �������� �� ������
#define ERR_OPERATION_BLOCKED					2		// �������� �� ����� ���� ��������� � ������� ��������� ����������
#define ERR_DEVICE_NOT_READY					3		// ���������� �� ������ ��� ����� ���������
#define ERR_WRONG_PWD							4		// ������������ ����


#endif // __DEV_OBJ_DIC_H
