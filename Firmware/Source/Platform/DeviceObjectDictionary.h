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
#define ACT_DBG_EXT_REG_WRITE_DATA				59		// ���������� ����� - ������ ������ �� ������� �������
#define ACT_DBG_GENERATE_PULSE					60		// ���������� ����� - ������������ ��������
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
#define REG_I_TO_DAC_OFFSET						15		// �������� �������������� ���->���
#define REG_I_TO_DAC_K							16		// ����������� �������������� ���->���
#define REG_I_TO_DAC_P0							17		// ������� ������ ���������� �0
#define REG_I_TO_DAC_P1							18		// ������� ������ ���������� �1
#define REG_I_TO_DAC_P2							19		// ������� ������ ���������� �2
//
#define REG_INTPS_STAB_COUNTER_VALUE			20		// ����. �������� �������� ��� ������� ���������� ����������� ���������
#define REG_ERR_FOR_FORCED_DISCHARGE			21		// ������, ��� ������� ���������� ������������� ������ ����������� ��������� (% * 10)
#define REG_INTPS_ALLOWED_ERROR					22		// ���������� ���������� ������ ������� ���������� ����������� ��������� (% * 10)
#define REG_BATTERY_FULL_CHRAGE_TIMEOUT			23		// ������� ������� ������ �������,��
#define REG_BATTERY_RECHRAGE_TIMEOUT			24		// ������� �������� �������,��
#define REG_BAT_VOLTAGE_THRESHOLD				25		// ����������� ����� ������ �������, � *10
#define REG_MAXIMUM_UNIT_CURRENT				26		// ������������ �������� ���� � �����
#define REG_CONFIG_RDY_STATE_TIMEOUT			27		// ������� ���������� ����� � ��������� ConfigReady
#define REG_ERROR_COUNTER_MAX					28		// ������������ �������� �������� ��� ����������� ������ ���� �� �������
#define REG_ALLOWED_ERROR						29		// ���������� ������ ����������� ������ ���� �� ������� (% * 10)
#define REG_AFTER_PULSE_PAUSE					30		// ����� ����� ��������, ��
#define REG_FAN_CTRL							31		// ���������� ������ ������������
#define REG_FAN_OPERATE_PERIOD					32		// ������ ������ �����������, �
#define REG_FAN_OPERATE_TIME					33		// ������������ ������ �����������, �
//
#define REG_CTRL1_MAX_WIDTH_050					40		// ������������ ������������ �������� CTRL1 ��� 0.5�/���
#define REG_CTRL1_MAX_WIDTH_075					41		// ������������ ������������ �������� CTRL1 ��� 0.75�/���
#define REG_CTRL1_MAX_WIDTH_100					42		// ������������ ������������ �������� CTRL1 ��� 1�/���
#define REG_CTRL1_MAX_WIDTH_250					43		// ������������ ������������ �������� CTRL1 ��� 2.5�/���
#define REG_CTRL1_MAX_WIDTH_500					44		// ������������ ������������ �������� CTRL1 ��� 5�/���
#define REG_CTRL1_MAX_WIDTH_750					45		// ������������ ������������ �������� CTRL1 ��� 7.5�/���
#define REG_CTRL1_MAX_WIDTH_1000				46		// ������������ ������������ �������� CTRL1 ��� 10�/���
#define REG_CTRL1_MAX_WIDTH_1500				47		// ������������ ������������ �������� CTRL1 ��� 15�/���
#define REG_CTRL1_MAX_WIDTH_2500				48		// ������������ ������������ �������� CTRL1 ��� 25�/���
#define REG_CTRL1_MAX_WIDTH_3000				49		// ������������ ������������ �������� CTRL1 ��� 30�/���
#define REG_CTRL1_MAX_WIDTH_5000				50		// ������������ ������������ �������� CTRL1 ��� 50�/���
#define REG_CTRL2_MAX_WIDTH						51		// ������������ ������������ �������� CTRL2
//
#define REG_INTPS_VOLTAGE_050					52		// ���������� ����������� ��������� ��� �������� 0.50 �/���
#define REG_INTPS_VOLTAGE_075					53		// ���������� ����������� ��������� ��� �������� 0.75 �/���
#define REG_INTPS_VOLTAGE_100					54		// ���������� ����������� ��������� ��� �������� 1.00 �/���
#define REG_INTPS_VOLTAGE_250					55		// ���������� ����������� ��������� ��� �������� 2.50 �/���
#define REG_INTPS_VOLTAGE_500					56		// ���������� ����������� ��������� ��� �������� 5.00 �/���
#define REG_INTPS_VOLTAGE_750					57		// ���������� ����������� ��������� ��� �������� 7.50 �/���
#define REG_INTPS_VOLTAGE_1000					58		// ���������� ����������� ��������� ��� �������� 10.0 �/���
#define REG_INTPS_VOLTAGE_1500					59		// ���������� ����������� ��������� ��� �������� 15.0 �/���
#define REG_INTPS_VOLTAGE_2500					60		// ���������� ����������� ��������� ��� �������� 25.0 �/���
#define REG_INTPS_VOLTAGE_3000					61		// ���������� ����������� ��������� ��� �������� 30.0 �/���
#define REG_INTPS_VOLTAGE_5000					62		// ���������� ����������� ��������� ��� �������� 50.0 �/���
//
#define REG_CTRL1_050_OFFSET					63		// �������� ������ ���������� ���� ��� ������� ����� 0.50 �/���
#define REG_CTRL1_050_K							64		// ����������� ������ ���������� ���� ��� ������� ����� 0.50 �/���
#define REG_CTRL1_075_OFFSET					65		// �������� ������ ���������� ���� ��� ������� ����� 0.75 �/���
#define REG_CTRL1_075_K							66		// ����������� ������ ���������� ���� ��� ������� ����� 0.75 �/���
#define REG_CTRL1_100_OFFSET					67		// �������� ������ ���������� ���� ��� ������� ����� 1.00 �/���
#define REG_CTRL1_100_K							68		// ����������� ������ ���������� ���� ��� ������� ����� 1.00 �/���
#define REG_CTRL1_250_OFFSET					69		// �������� ������ ���������� ���� ��� ������� ����� 2.50 �/���
#define REG_CTRL1_250_K							70		// ����������� ������ ���������� ���� ��� ������� ����� 2.50 �/���
#define REG_CTRL1_500_OFFSET					71		// �������� ������ ���������� ���� ��� ������� ����� 5.00 �/���
#define REG_CTRL1_500_K							72		// ����������� ������ ���������� ���� ��� ������� ����� 5.00 �/���
#define REG_CTRL1_750_OFFSET					73		// �������� ������ ���������� ���� ��� ������� ����� 7.50 �/���
#define REG_CTRL1_750_K							74		// ����������� ������ ���������� ���� ��� ������� ����� 7.50 �/���
#define REG_CTRL1_1000_OFFSET					75		// �������� ������ ���������� ���� ��� ������� ����� 10.0 �/���
#define REG_CTRL1_1000_K						76		// ����������� ������ ���������� ���� ��� ������� ����� 10.0 �/���
#define REG_CTRL1_1500_OFFSET					77		// �������� ������ ���������� ���� ��� ������� ����� 15.0 �/���
#define REG_CTRL1_1500_K						78		// ����������� ������ ���������� ���� ��� ������� ����� 15.0 �/���
#define REG_CTRL1_2500_OFFSET					79		// �������� ������ ���������� ���� ��� ������� ����� 25.0 �/���
#define REG_CTRL1_2500_K						80		// ����������� ������ ���������� ���� ��� ������� ����� 25.0 �/���
#define REG_CTRL1_3000_OFFSET					81		// �������� ������ ���������� ���� ��� ������� ����� 30.0 �/���
#define REG_CTRL1_3000_K						82		// ����������� ������ ���������� ���� ��� ������� ����� 30.0 �/���
#define REG_CTRL1_5000_OFFSET					83		// �������� ������ ���������� ���� ��� ������� ����� 50.0 �/���
#define REG_CTRL1_5000_K						84		// ����������� ������ ���������� ���� ��� ������� ����� 50.0 �/���
#define REG_CTRL2_OFFSET						85		// �������� ������ ���������� ����
#define REG_CTRL2_K								86		// ����������� ������ ���������� ����
//
#define REG_I_RATE_COMPENS_050					87		// ����������� ����������� ����������� dI/dt �� ��������� ���� ������� ��� 0.50 A/us
#define REG_I_RATE_COMPENS_075					88		// ����������� ����������� ����������� dI/dt �� ��������� ���� ������� ��� 0.75 A/us
#define REG_I_RATE_COMPENS_100					89		// ����������� ����������� ����������� dI/dt �� ��������� ���� ������� ��� 1.00 A/us
#define REG_I_RATE_COMPENS_250					90		// ����������� ����������� ����������� dI/dt �� ��������� ���� ������� ��� 2.50 A/us
#define REG_I_RATE_COMPENS_500					91		// ����������� ����������� ����������� dI/dt �� ��������� ���� ������� ��� 5.00 A/us
#define REG_I_RATE_COMPENS_750					92		// ����������� ����������� ����������� dI/dt �� ��������� ���� ������� ��� 7.50 A/us
#define REG_I_RATE_COMPENS_1000					93		// ����������� ����������� ����������� dI/dt �� ��������� ���� ������� ��� 10.0 A/us
#define REG_I_RATE_COMPENS_1500					94		// ����������� ����������� ����������� dI/dt �� ��������� ���� ������� ��� 15.0 A/us
#define REG_I_RATE_COMPENS_2500					95		// ����������� ����������� ����������� dI/dt �� ��������� ���� ������� ��� 25.0 A/us
#define REG_I_RATE_COMPENS_3000					96		// ����������� ����������� ����������� dI/dt �� ��������� ���� ������� ��� 30.0 A/us
#define REG_I_RATE_COMPENS_5000					97		// ����������� ����������� ����������� dI/dt �� ��������� ���� ������� ��� 50.0 A/us

#define REG_CURRENT_SETPOINT					128		// ��������� ����������� ����, �
#define REG_CURRENT_RATE						129		// �������� ��������� ����, �/���

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
#define REG_BAT_VOLTAGE							200		// ���������� �� �������������� ������� 1 (� � �10)
#define REG_CURRENT								201		// ���������� �������� ��������� ���� (� ��)
#define REG_INT_PS_VOLTAGE						202
// -----------------------------
#define REG_FWINFO_SLAVE_NID			256	// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID			257	// Device CAN master node ID (if presented)
// 258 - 259
#define REG_FWINFO_STR_LEN				260	// Length of the information string record
#define REG_FWINFO_STR_BEGIN			261	// Begining of the information string record


// ENDPOINTS
//
#define EP_DUT_I								1		// ������������ ������ ���� DUT (� ��)


// FAULT & DISABLE
//
#define DF_NONE									0
#define DF_BATTERY								1		// ������ ������ �������
#define DF_PROTECTION							2		// ������ �� �������������� � ���� ����������

// WARNINGS
//
#define WARNING_NONE							0
#define WARNING_CURRENT_NOT_READY				1		// ��� �� ����� �� �������� �������

// User Errors
// 
#define ERR_NONE								0
#define ERR_CONFIGURATION_LOCKED				1		// ���������� �������� �� ������
#define ERR_OPERATION_BLOCKED					2		// �������� �� ����� ���� ��������� � ������� ��������� ����������
#define ERR_DEVICE_NOT_READY					3		// ���������� �� ������ ��� ����� ���������
#define ERR_WRONG_PWD							4		// ������������ ����


#endif // __DEV_OBJ_DIC_H
