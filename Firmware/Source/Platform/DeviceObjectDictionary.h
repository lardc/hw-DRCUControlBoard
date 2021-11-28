#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H


// ACTIONS
//
#define ACT_ENABLE_POWER						1		// �������� ������� �����
#define ACT_DISABLE_POWER						2		// ��������� ������� �����
#define ACT_CLR_FAULT							3		// ������� ������
#define ACT_CLR_WARNING							4		// ������� ��������������
//
#define ACT_DBG_INT_PS_CONTROL					50		// ���������� ����� - ���������� ���������� ��
#define ACT_DBG_INT_PS_DISCHARGE				51		// ���������� ����� - ������ ����������� ��
#define ACT_DBG_PROTECTION_RESET				52		// ���������� ����� - ����� ������ �� �������������� �� ����������� ������
#define ACT_DBG_OUTPUT_LOCK_CONTROL				53		// ���������� ����� - ���������� ����������� ������
#define ACT_DBG_SYNC							54		// ���������� ����� - ������������ �������� �������������
#define ACT_DBG_GENERATE_PULSE					55		// ���������� ����� - ������������ ��������
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
#define REG_V_INT_PS_OFFSET						0		// �������� ������������ �������� ���������� ����������� ���������
#define REG_V_INT_PS_K							1		// ����������� ��������� ��� � ����������, ��
#define REG_SW_PULSE_WIDTH						2		// ������������ �������� � ������ ������������ �������, ���
#define REG_INTPS_STAB_COUNTER_VALUE			3		// ����. �������� �������� ��� ������� ���������� ����������� ���������
#define REG_ERR_FOR_FORCED_DISCHARGE			4		// ������, ��� ������� ���������� ������������� ������ ����������� ��������� (% * 10)
#define REG_INTPS_ALLOWED_ERROR					5		// ���������� ���������� ������ ������� ���������� ����������� ��������� (% * 10)
#define REG_V_INTPS_DEF							6		// ���������� ����������� ��������� �� ��������� � ������� ������ (� * 10)
//
#define REG_CTRL1_MAX_WIDTH						10		// ������������ ������������ �������� CTRL1 ��� 50�/���
#define REG_CTRL2_MAX_WIDTH						11		// ������������ ������������ �������� CTRL2
//
#define REG_CTRL1_OFFSET						12		// �������� ������ ���������� ���� ��� ������� ����� 50.0 �/���
#define REG_CTRL1_K								13		// ����������� ������ ���������� ���� ��� ������� ����� 50.0 �/���
#define REG_CTRL2_OFFSET						14		// �������� ������ ���������� ����
#define REG_CTRL2_K								15		// ����������� ������ ���������� ����
//
#define REG_I_TO_DAC_OFFSET						20
#define REG_I_TO_DAC_K							21
#define REG_I_TO_DAC_P2							22
#define REG_I_TO_DAC_P1							23
#define REG_I_TO_DAC_P0							24
//
#define REG_CURRENT_SETPOINT					128		// ��������� ����������� ����, �
#define REG_V_INTPS_SETPOINT					129		// �������������� ��������� ���������� ����������� ���������, � * 10

#define REG_DBG									150		// ���������� ������� 1
#define REG_DBG2								151		// ���������� ������� 2
// -----------------------------------------------

#define REG_DEV_STATE							192		// ������ ������ �����
#define REG_FAULT_REASON						193		// ������ ������ �����
#define REG_DISABLE_REASON						194		// ������� ���������� �����
#define REG_WARNING								195		// ��������������
#define REG_PROBLEM								196		// ������� Problem
#define REG_DEV_SUBSTATE						197		// ��������� ������ �����
//
#define REG_INT_PS_VOLTAGE						200		// ���������� ��������� �������������, (� � �10)
// -----------------------------
#define REG_FWINFO_SLAVE_NID					256	// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID					257	// Device CAN master node ID (if presented)
// 258 - 259
#define REG_FWINFO_STR_LEN						260	// Length of the information string record
#define REG_FWINFO_STR_BEGIN					261	// Begining of the information string record


// FAULT & DISABLE
//
#define DF_NONE									0
#define DF_PROTECTION							1		// ������ �� �������������� � ���� ����������

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
