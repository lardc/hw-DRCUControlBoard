// -----------------------------------------
// Global definitions
// ----------------------------------------

#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Global.h"


//Definitions
//
#define GAIN_COEFFICIENT_MIN			1
#define GAIN_COEFFICIENT_MAX			60000
#define GAIN_COEFFICIENT_DEF			1000
//
#define INTPS_ADC_TO_V_K				45
#define INTPS_ADC_TO_V_OFFSET			0
//
#define VBAT_ADC_TO_V_K					64
#define VBAT_ADC_TO_V_OFFSET			0
//
#define I_DUT_ADC_TO_I_K				183
#define I_DUT_ADC_TO_I_OFFSET			2
//
#define FULL_CHARGE_TIME_MIN			5000		// ��
#define FULL_CHARGE_TIME_MAX			60000 		// ��
#define FULL_CHARGE_TIME_DEF			30000		// ��
//
#define RECHARGE_TIMEOUT_MIN			1000		// ��
#define RECHARGE_TIMEOUT_MAX			10000		// ��
#define RECHARGE_TIMEOUT_DEF			5000		// ��
//
#define CONF_STATE_TIMEOUT_MIN			3000		// ��
#define CONF_STATE_TIMEOUT_MAX			10000		// ��
#define CONF_STATE_TIMEOUT_DEF			5000		// ��
//
#define MAXIMUM_UNIT_CURRENT_MIN		0			// A
#define MAXIMUM_UNIT_CURRENT_MAX		1100		// A
#define MAXIMUM_UNIT_CURRENT_DEF		400			// A
//
#define CURRENT_SETPOINT_MIN			100			// A
#define CURRENT_SETPOINT_MAX			400			// A
#define CURRENT_SETPOINT_DEF			100			// A
//
#define CURRENT_RATE_MIN				50			// A / us / 100
#define CURRENT_RATE_MAX				5000		// A / us / 100
#define CURRENT_RATE_DEF				50			// A / us / 100
//
#define AFTER_PULSE_TIMEOUT_MIN			1000		// ��
#define AFTER_PULSE_TIMEOUT_MAX			10000		// ��
#define AFTER_PULSE_TIMEOUT_DEF			1000		// ��
//
#define FAN_OPERATE_PERIOD_MIN			60			// �
#define FAN_OPERATE_PERIOD_MAX			2000		// �
#define FAN_OPERATE_PERIOD_DEF			300			// �
//
#define FAN_OPERATE_TIME_MIN			10			// �
#define FAN_OPERATE_TIME_MAX			2000		// �
#define FAN_OPERATE_TIME_DEF			60			// �
//
#define V_BAT_THRESHOLD_MIN				0			// � * 10
#define V_BAT_THRESHOLD_MAX				1400		// � * 10
#define V_BAT_THRESHOLD_DEF				1400		// � * 10
//
#define ERR_FOR_FORCED_DISCHRG_MIN		1			// % * 10
#define ERR_FOR_FORCED_DISCHRG_MAX		100			// % * 10
#define ERR_FOR_FORCED_DISCHRG_DEF		20			// % * 10
//
#define INTPS_ALLOWED_ERR_MIN			1			// % * 10
#define INTPS_ALLOWED_ERR_MAX			1000		// % * 10
#define INTPS_ALLOWED_ERR_DEF			10			// % * 10
//
#define CTRL1_MAX_WIDTH_050_MAX			57000
#define CTRL1_MAX_WIDTH_050_DEF			22000
#define CTRL1_MAX_WIDTH_075_MAX			57000
#define CTRL1_MAX_WIDTH_075_DEF			15000
#define CTRL1_MAX_WIDTH_100_MAX			57000
#define CTRL1_MAX_WIDTH_100_DEF			11000
#define CTRL1_MAX_WIDTH_250_MAX			57000
#define CTRL1_MAX_WIDTH_250_DEF			4000
#define CTRL1_MAX_WIDTH_500_MAX			57000
#define CTRL1_MAX_WIDTH_500_DEF			1850
#define CTRL1_MAX_WIDTH_750_MAX			57000
#define CTRL1_MAX_WIDTH_750_DEF			1300
#define CTRL1_MAX_WIDTH_1000_MAX		57000
#define CTRL1_MAX_WIDTH_1000_DEF		1000
#define CTRL1_MAX_WIDTH_1500_MAX		57000
#define CTRL1_MAX_WIDTH_1500_DEF		600
#define CTRL1_MAX_WIDTH_2500_MAX		57000
#define CTRL1_MAX_WIDTH_2500_DEF		350
#define CTRL1_MAX_WIDTH_3000_MAX		57000
#define CTRL1_MAX_WIDTH_3000_DEF		300
#define CTRL1_MAX_WIDTH_5000_MAX		57000
#define CTRL1_MAX_WIDTH_5000_DEF		145
#define CTRL2_MAX_WIDTH_MAX				57000
#define CTRL2_MAX_WIDTH_DEF				500
//
#define INTPS_STAB_COUNTER_MAX			100
#define INTPS_STAB_COUNTER_DEF			60
//
#define INTPS_VOLTAGE_050_DEF			1150		// � * 10
#define INTPS_VOLTAGE_075_DEF			1170		// � * 10
#define INTPS_VOLTAGE_100_DEF			1100		// � * 10
#define INTPS_VOLTAGE_250_DEF			1080		// � * 10
#define INTPS_VOLTAGE_500_DEF			1100		// � * 10
#define INTPS_VOLTAGE_750_DEF			1030		// � * 10
#define INTPS_VOLTAGE_1000_DEF			1080		// � * 10
#define INTPS_VOLTAGE_1500_DEF			1040		// � * 10
#define INTPS_VOLTAGE_2500_DEF			1050		// � * 10
#define INTPS_VOLTAGE_3000_DEF			1150		// � * 10
#define INTPS_VOLTAGE_5000_DEF			1050		// � * 10
//
#define CTRL1_050_OFFSET_DEF			50
#define CTRL1_050_K_DEF					45000
#define CTRL1_075_OFFSET_DEF			45
#define CTRL1_075_K_DEF					30000
#define CTRL1_100_OFFSET_DEF			50
#define CTRL1_100_K_DEF					21500
#define CTRL1_250_OFFSET_DEF			40
#define CTRL1_250_K_DEF					8700
#define CTRL1_500_OFFSET_DEF			40
#define CTRL1_500_K_DEF					3800
#define CTRL1_750_OFFSET_DEF			10
#define CTRL1_750_K_DEF					2900
#define CTRL1_1000_OFFSET_DEF			0
#define CTRL1_1000_K_DEF				2300
#define CTRL1_1500_OFFSET_DEF			0
#define CTRL1_1500_K_DEF				1385
#define CTRL1_2500_OFFSET_DEF			65516
#define CTRL1_2500_K_DEF				800
#define CTRL1_3000_OFFSET_DEF			65496
#define CTRL1_3000_K_DEF				750
#define CTRL1_5000_OFFSET_DEF			65441
#define CTRL1_5000_K_DEF				428
#define CTRL2_OFFSET_DEF				75
#define CTRL2_K_DEF						813


// Types
//
typedef struct __TableItemConstraint
{
	Int16U Min;
	Int16U Max;
	Int16U Default;
} TableItemConstraint;


// Variables
//
extern const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE];
extern const TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START];


#endif // __CONSTRAINTS_H
