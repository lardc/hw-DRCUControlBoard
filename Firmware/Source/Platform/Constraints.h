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

#define TQ_TIMEOUT_MIN					2000
#define TQ_TIMEOUT_MAX					5000
#define TQ_TIMEOUT_DEF					2000
//
#define PULSE_DELAY_TQ_MIN				500
#define PULSE_DELAY_TQ_MAX				2000
#define PULSE_DELAY_TQ_DEF				500
//
#define COOLING_TIME_MIN				500
#define COOLING_TIME_MAX				2000
#define COOLING_TIME_DEF				1000
//
#define REG_PULSE_TO_PULSE_DELAY_MAX
//
#define PULSE_WIDTH_MIN					10
#define PULSE_WIDTH_MAX					15
#define PULSE_WIDTH_DEF					10
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
#define FULL_CHARGE_TIME_MIN			5000		// мс
#define FULL_CHARGE_TIME_MAX			60000 		// мс
#define FULL_CHARGE_TIME_DEF			30000		// мс
//
#define RECHARGE_TIMEOUT_MIN			1000		// мс
#define RECHARGE_TIMEOUT_MAX			10000		// мс
#define RECHARGE_TIMEOUT_DEF			5000		// мс
//
#define CONF_STATE_TIMEOUT_MIN			3000		// мс
#define CONF_STATE_TIMEOUT_MAX			10000		// мс
#define CONF_STATE_TIMEOUT_DEF			5000		// мс
//
#define MAXIMUM_UNIT_CURRENT_MIN		0			// A
#define MAXIMUM_UNIT_CURRENT_MAX		1100		// A
#define MAXIMUM_UNIT_CURRENT_DEF		500			// A
//
#define CURRENT_SETPOINT_MIN			100			// A
#define CURRENT_SETPOINT_MAX			1100			// A
#define CURRENT_SETPOINT_DEF			100			// A
//
#define CURRENT_RATE_MIN				0
#define CURRENT_RATE_MAX				10
#define CURRENT_RATE_DEF				0
//
#define FAN_OPERATE_PERIOD_MIN			60			// с
#define FAN_OPERATE_PERIOD_MAX			2000		// с
#define FAN_OPERATE_PERIOD_DEF			300			// с
//
#define FAN_OPERATE_TIME_MIN			10			// с
#define FAN_OPERATE_TIME_MAX			2000		// с
#define FAN_OPERATE_TIME_DEF			60			// с
//
#define V_BAT_THRESHOLD_MIN				0			// В * 10
#define V_BAT_THRESHOLD_MAX				1400		// В * 10
#define V_BAT_THRESHOLD_DEF				1400		// В * 10
//
#define ERR_FOR_FORCED_DISCHRG_MIN		1			// % * 10
#define ERR_FOR_FORCED_DISCHRG_MAX		100			// % * 10
#define ERR_FOR_FORCED_DISCHRG_DEF		20			// % * 10
//
#define INTPS_ALLOWED_ERR_MIN			1			// % * 10
#define INTPS_ALLOWED_ERR_MAX			1000		// % * 10
#define INTPS_ALLOWED_ERR_DEF			10			// % * 10
//
#define CTRL1_MAX_WIDTH_R0_MAX			57000
#define CTRL1_MAX_WIDTH_R0_DEF			26000
#define CTRL1_MAX_WIDTH_R1_MAX			57000
#define CTRL1_MAX_WIDTH_R1_DEF			19000
#define CTRL1_MAX_WIDTH_R2_MAX			57000
#define CTRL1_MAX_WIDTH_R2_DEF			13000
#define CTRL1_MAX_WIDTH_R3_MAX			57000
#define CTRL1_MAX_WIDTH_R3_DEF			5500
#define CTRL1_MAX_WIDTH_R4_MAX			57000
#define CTRL1_MAX_WIDTH_R4_DEF			2500
#define CTRL1_MAX_WIDTH_R5_MAX			57000
#define CTRL1_MAX_WIDTH_R5_DEF			1700
#define CTRL1_MAX_WIDTH_R6_MAX			57000
#define CTRL1_MAX_WIDTH_R6_DEF			1200
#define CTRL1_MAX_WIDTH_R7_MAX			57000
#define CTRL1_MAX_WIDTH_R7_DEF			800
#define CTRL1_MAX_WIDTH_R8_MAX			57000
#define CTRL1_MAX_WIDTH_R8_DEF			500
#define CTRL1_MAX_WIDTH_R9_MAX			57000
#define CTRL1_MAX_WIDTH_R9_DEF			350
#define CTRL1_MAX_WIDTH_R10_MAX			57000
#define CTRL1_MAX_WIDTH_R10_DEF			170
#define CTRL2_MAX_WIDTH_MAX				57000
#define CTRL2_MAX_WIDTH_DEF				500
//
#define INTPS_STAB_COUNTER_MAX			100
#define INTPS_STAB_COUNTER_DEF			60
//
#define CTRL1_R0_OFFSET_DEF				80
#define CTRL1_R0_K_DEF					45000
#define CTRL1_R1_OFFSET_DEF				80
#define CTRL1_R1_K_DEF					30000
#define CTRL1_R2_OFFSET_DEF				80
#define CTRL1_R2_K_DEF					21500
#define CTRL1_R3_OFFSET_DEF				70
#define CTRL1_R3_K_DEF					8700
#define CTRL1_R4_OFFSET_DEF				70
#define CTRL1_R4_K_DEF					3800
#define CTRL1_R5_OFFSET_DEF				50
#define CTRL1_R5_K_DEF					2800
#define CTRL1_R6_OFFSET_DEF				40
#define CTRL1_R6_K_DEF					2200
#define CTRL1_R7_OFFSET_DEF				30
#define CTRL1_R7_K_DEF					1385
#define CTRL1_R8_OFFSET_DEF				0
#define CTRL1_R8_K_DEF					820
#define CTRL1_R9_OFFSET_DEF				65511
#define CTRL1_R9_K_DEF					760
#define CTRL1_R10_OFFSET_DEF			65441
#define CTRL1_R10_K_DEF					428
#define CTRL2_OFFSET_DEF				75
#define CTRL2_K_DEF						813
//
#define I_TO_V_INTPS_K4_DEF				1000
#define I_TO_V_INTPS_K2_DEF				0
#define I_TO_V_INTPS_K_DEF				200
#define I_TO_V_INTPS_OFFSET_DEF			1000
//
#define NO								0
#define YES								1
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
