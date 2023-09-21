﻿// Header
#include "Constraints.h"

// Constants
const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE] = {
		{0, INT16U_MAX, VBAT_ADC_TO_V_OFFSET},													// 0
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, VBAT_ADC_TO_V_K},							// 1
		{0, INT16U_MAX, INTPS_ADC_TO_V_OFFSET},													// 2
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, INTPS_ADC_TO_V_K},							// 3
		{0, INT16U_MAX, I_DUT_ADC_TO_I_OFFSET},													// 4
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, I_DUT_ADC_TO_I_K},							// 5
		{0, INT16U_MAX, 0},																		// 6
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, GAIN_COEFFICIENT_DEF},						// 7
		{0, INT16U_MAX, 0},																		// 8
		{0, 0, 0},																				// 9
		{0, INTPS_STAB_COUNTER_MAX, INTPS_STAB_COUNTER_DEF},									// 10
		{ERR_FOR_FORCED_DISCHRG_MIN, ERR_FOR_FORCED_DISCHRG_MAX, ERR_FOR_FORCED_DISCHRG_DEF},	// 11
		{INTPS_ALLOWED_ERR_MIN, INTPS_ALLOWED_ERR_MAX, INTPS_ALLOWED_ERR_DEF},					// 12
		{FULL_CHARGE_TIME_MIN, FULL_CHARGE_TIME_MAX, FULL_CHARGE_TIME_DEF},						// 13
		{RECHARGE_TIMEOUT_MIN, RECHARGE_TIMEOUT_MAX, RECHARGE_TIMEOUT_DEF},						// 14
		{V_BAT_THRESHOLD_MIN, V_BAT_THRESHOLD_MAX, V_BAT_THRESHOLD_DEF},						// 15
		{MAXIMUM_UNIT_CURRENT_MIN, MAXIMUM_UNIT_CURRENT_MAX, MAXIMUM_UNIT_CURRENT_DEF},			// 16
		{CONF_STATE_TIMEOUT_MIN, CONF_STATE_TIMEOUT_MAX, CONF_STATE_TIMEOUT_DEF},				// 17
		{0,0,0},																				// 18
		{false, true, false},																	// 19
		{FAN_OPERATE_PERIOD_MIN, FAN_OPERATE_PERIOD_MAX, FAN_OPERATE_PERIOD_DEF},				// 20
		{FAN_OPERATE_TIME_MIN, FAN_OPERATE_TIME_MAX, FAN_OPERATE_TIME_DEF},						// 21
		{0, 0, 0},																				// 22
		{0, 0, 0},																				// 23
		{0, 0, 0},																				// 24
		{0, CTRL1_MAX_WIDTH_R0_MAX, CTRL1_MAX_WIDTH_R0_DEF},									// 25
		{0, CTRL1_MAX_WIDTH_R1_MAX, CTRL1_MAX_WIDTH_R1_DEF},									// 26
		{0, CTRL1_MAX_WIDTH_R2_MAX, CTRL1_MAX_WIDTH_R2_DEF},									// 27
		{0, CTRL1_MAX_WIDTH_R3_MAX, CTRL1_MAX_WIDTH_R3_DEF},									// 28
		{0, CTRL1_MAX_WIDTH_R4_MAX, CTRL1_MAX_WIDTH_R4_DEF},									// 29
		{0, CTRL1_MAX_WIDTH_R5_MAX, CTRL1_MAX_WIDTH_R5_DEF},									// 30
		{0, CTRL1_MAX_WIDTH_R6_MAX, CTRL1_MAX_WIDTH_R6_DEF},									// 31
		{0, CTRL1_MAX_WIDTH_R7_MAX, CTRL1_MAX_WIDTH_R7_DEF},									// 32
		{0, CTRL1_MAX_WIDTH_R8_MAX, CTRL1_MAX_WIDTH_R8_DEF},									// 33
		{0, CTRL1_MAX_WIDTH_R9_MAX, CTRL1_MAX_WIDTH_R9_DEF},									// 34
		{0, CTRL1_MAX_WIDTH_R10_MAX, CTRL1_MAX_WIDTH_R10_DEF},									// 35
		{0, CTRL2_MAX_WIDTH_MAX, CTRL2_MAX_WIDTH_DEF},											// 36
		{TQ_TIMEOUT_MIN, TQ_TIMEOUT_MAX, TQ_TIMEOUT_DEF},										// 37
		{PULSE_DELAY_TQ_MIN, PULSE_DELAY_TQ_MAX, PULSE_DELAY_TQ_DEF},							// 38
		{0, 0, 0},																				// 39
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 40
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 41
		{0, INT16U_MAX, I_TO_V_INTPS_K2_DEF},													// 42
		{0, INT16U_MAX, I_TO_V_INTPS_K4_DEF},													// 43
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 44
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 45
		{0, INT16U_MAX, I_TO_V_INTPS_K2_DEF},													// 46
		{0, INT16U_MAX, I_TO_V_INTPS_K4_DEF},													// 47
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 48
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 49
		{0, INT16U_MAX, I_TO_V_INTPS_K2_DEF},													// 50
		{0, INT16U_MAX, I_TO_V_INTPS_K4_DEF},													// 51
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 52
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 53
		{0, INT16U_MAX, I_TO_V_INTPS_K2_DEF},													// 54
		{0, INT16U_MAX, I_TO_V_INTPS_K4_DEF},													// 55
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 56
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 57
		{0, INT16U_MAX, I_TO_V_INTPS_K2_DEF},													// 58
		{0, INT16U_MAX, I_TO_V_INTPS_K4_DEF},													// 59
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 60
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 61
		{0, INT16U_MAX, I_TO_V_INTPS_K2_DEF},													// 62
		{0, INT16U_MAX, I_TO_V_INTPS_K4_DEF},													// 63
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 64
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 65
		{0, INT16U_MAX, I_TO_V_INTPS_K2_DEF},													// 66
		{0, INT16U_MAX, I_TO_V_INTPS_K4_DEF},													// 67
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 68
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 69
		{0, INT16U_MAX, I_TO_V_INTPS_K2_DEF},													// 70
		{0, INT16U_MAX, I_TO_V_INTPS_K4_DEF},													// 71
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 72
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 73
		{0, INT16U_MAX, I_TO_V_INTPS_K2_DEF},													// 74
		{0, INT16U_MAX, I_TO_V_INTPS_K4_DEF},													// 75
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 76
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 77
		{0, INT16U_MAX, I_TO_V_INTPS_K2_DEF},													// 78
		{0, INT16U_MAX, I_TO_V_INTPS_K4_DEF},													// 79
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 80
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 81
		{0, INT16U_MAX, I_TO_V_INTPS_K2_DEF},													// 82
		{0, INT16U_MAX, I_TO_V_INTPS_K4_DEF},													// 83
		{0, INT16U_MAX, CTRL1_R0_OFFSET_DEF},													// 84
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_R0_K_DEF},							// 85
		{0, INT16U_MAX, CTRL1_R1_OFFSET_DEF},													// 86
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_R1_K_DEF},							// 87
		{0, INT16U_MAX, CTRL1_R2_OFFSET_DEF}, 													// 88
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_R2_K_DEF},							// 89
		{0, INT16U_MAX, CTRL1_R3_OFFSET_DEF},													// 90
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_R3_K_DEF},							// 91
		{0, INT16U_MAX, CTRL1_R4_OFFSET_DEF},													// 92
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_R4_K_DEF},							// 93
		{0, INT16U_MAX, CTRL1_R5_OFFSET_DEF},													// 94
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_R5_K_DEF},							// 95
		{0, INT16U_MAX, CTRL1_R6_OFFSET_DEF},													// 96
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_R6_K_DEF},							// 97
		{0, INT16U_MAX, CTRL1_R7_OFFSET_DEF},													// 98
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_R7_K_DEF},							// 99
		{0, INT16U_MAX, CTRL1_R8_OFFSET_DEF},													// 100
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_R8_K_DEF},							// 101
		{0, INT16U_MAX, CTRL1_R9_OFFSET_DEF},													// 102
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_R9_K_DEF},							// 103
		{0, INT16U_MAX, CTRL1_R10_OFFSET_DEF},													// 104
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_R10_K_DEF},							// 105
		{0, INT16U_MAX, CTRL2_OFFSET_DEF},														// 106
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL2_K_DEF},								// 107
		{0, 0, 0},																				// 108
		{0, 0, 0},																				// 109
		{0, 0, 0},																				// 110
		{0, 0, 0},																				// 111
		{0, 0, 0},																				// 112
		{0, 0, 0},																				// 113
		{0, 0, 0},																				// 114
		{0, 0, 0},																				// 115
		{0, 0, 0},																				// 116
		{0, 0, 0},																				// 117
		{0, 0, 0},																				// 118
		{0, 0, 0},																				// 119
		{0, INT16U_MAX, 0},																		// 120
		{0, 0, 0},																				// 121
		{0, 0, 0},																				// 122
		{0, 0, 0},																				// 123
		{0, 0, 0},																				// 124
		{0, 0, 0},																				// 125
		{0, 0, 0},																				// 126
		{0, 0, 0}																				// 127
};

const TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START] = {
		{CURRENT_SETPOINT_MIN, CURRENT_SETPOINT_MAX, CURRENT_SETPOINT_DEF},						// 128
		{CURRENT_RATE_MIN, CURRENT_RATE_MAX, CURRENT_RATE_DEF},									// 129
		{0, INTPS_VOLTAGE_MAX, 0},																// 130
		{PULSE_WIDTH_MIN, PULSE_WIDTH_MAX, PULSE_WIDTH_DEF},									// 131
		{0, INT16U_MAX, I_TO_V_INTPS_EXT_OFFSET_DEF},											// 132
		{0, INT16U_MAX, I_TO_V_INTPS_EXT_K_DEF},												// 133
		{0, INT16U_MAX, I_TO_V_INTPS_EXT_K2_DEF},												// 134
		{0, INT16U_MAX, CTRL1_EXT_OFFSET_DEF},													// 135
		{0, INT16U_MAX, CTRL1_EXT_K_DEF},														// 136
		{0, 0, 0},																				// 137
		{0, 0, 0},																				// 138
		{0, 0, 0},																				// 139
		{NO, YES, NO},																			// 140
		{0, 0, 0},																				// 141
		{0, 0, 0},																				// 142
		{0, 0, 0},																				// 143
		{0, 0, 0},																				// 144
		{0, 0, 0},																				// 145
		{0, 0, 0},																				// 146
		{0, 0, 0},																				// 147
		{0, 0, 0},																				// 148
		{0, 0, 0},																				// 149
		{0, INT16U_MAX, 0},																		// 150
		{0, INT16U_MAX, 0},																		// 151
		{0, INT16U_MAX, 0},																		// 152
		{0, INT16U_MAX, 0},																		// 153
		{0, INT16U_MAX, 0},																		// 154
		{0, INT16U_MAX, 0},																		// 155
		{0, INT16U_MAX, 0},																		// 156
		{0, 0, 0},																				// 157
		{0, 0, 0},																				// 158
		{0, 0, 0},																				// 159
		{0, 0, 0},																				// 160
		{0, 0, 0},																				// 161
		{0, 0, 0},																				// 162
		{0, 0, 0},																				// 163
		{0, 0, 0},																				// 164
		{0, 0, 0},																				// 165
		{0, 0, 0},																				// 166
		{0, 0, 0},																				// 167
		{0, 0, 0},																				// 168
		{0, 0, 0},																				// 169
		{0, 0, 0},																				// 170
		{0, 0, 0},																				// 171
		{0, 0, 0},																				// 172
		{0, 0, 0},																				// 173
		{0, 0, 0},																				// 174
		{0, 0, 0},																				// 175
		{0, 0, 0},																				// 176
		{0, 0, 0},																				// 177
		{0, 0, 0},																				// 178
		{0, 0, 0},																				// 179
		{0, 0, 0},																				// 180
		{0, 0, 0},																				// 181
		{0, 0, 0},																				// 182
		{0, 0, 0},																				// 183
		{0, 0, 0},																				// 184
		{0, 0, 0},																				// 185
		{0, 0, 0},																				// 186
		{0, 0, 0},																				// 187
		{0, 0, 0},																				// 188
		{0, 0, 0},																				// 189
		{0, 0, 0},																				// 190
		{0, 0, 0}																				// 191
};
