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
#define INTPS_ADC_TO_V_K				45
#define INTPS_ADC_TO_V_OFFSET			0
//
#define INTPS_VOLTAGE_MAX				1250.0f		// В * 10
#define INTPS_VOLTAGE_MIN				0			// В * 10
#define INTPS_VOLTAGE_DEF				500.0f		// В * 10
//
#define CURRENT_SETPOINT_MIN			0			// A
#define CURRENT_SETPOINT_MAX			2500		// A
#define CURRENT_SETPOINT_DEF			100			// A
//
#define SW_PULSE_WIDTH_MIN				100
#define SW_PULSE_WIDTH_MAX				15000
#define SW_PULSE_WIDTH_DEF				3500
//
#define INTPS_STAB_COUNTER_MAX			100
#define INTPS_STAB_COUNTER_DEF			60
//
#define ERR_FOR_FORCED_DISCHRG_MIN		1			// % * 10
#define ERR_FOR_FORCED_DISCHRG_MAX		100			// % * 10
#define ERR_FOR_FORCED_DISCHRG_DEF		20			// % * 10
//
#define INTPS_ALLOWED_ERR_MIN			1			// % * 10
#define INTPS_ALLOWED_ERR_MAX			1000		// % * 10
#define INTPS_ALLOWED_ERR_DEF			10			// % * 10
//
#define CTRL1_MAXIMUM_WIDTH_MAX			57000
#define CTRL1_MAXIMUM_WIDTH_DEF			26000
//
#define CTRL2_MAXIMUM_WIDTH_MAX			57000
#define CTRL2_MAXIMUM_WIDTH_DEF			26000
//
#define CTRL1_OFFSET_DEF				80
#define CTRL1_K_DEF						45000
//
#define CTRL2_OFFSET_DEF				2400
#define CTRL2_K_DEF						25000


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
