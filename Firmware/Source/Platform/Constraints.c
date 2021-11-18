// Header
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
		{SW_PULSE_WIDTH_MIN, SW_PULSE_WIDTH_MAX, SW_PULSE_WIDTH_DEF},							// 9
		{0, INTPS_STAB_COUNTER_MAX, INTPS_STAB_COUNTER_DEF},									// 10
		{ERR_FOR_FORCED_DISCHRG_MIN, ERR_FOR_FORCED_DISCHRG_MAX, ERR_FOR_FORCED_DISCHRG_DEF},	// 11
		{INTPS_ALLOWED_ERR_MIN, INTPS_ALLOWED_ERR_MAX, INTPS_ALLOWED_ERR_DEF},					// 12
		{FULL_CHARGE_TIME_MIN, FULL_CHARGE_TIME_MAX, FULL_CHARGE_TIME_DEF},						// 13
		{RECHARGE_TIMEOUT_MIN, RECHARGE_TIMEOUT_MAX, RECHARGE_TIMEOUT_DEF},						// 14
		{V_BAT_THRESHOLD_MIN, V_BAT_THRESHOLD_MAX, V_BAT_THRESHOLD_DEF},						// 15
		{MAXIMUM_UNIT_CURRENT_MIN, MAXIMUM_UNIT_CURRENT_MAX, MAXIMUM_UNIT_CURRENT_DEF},			// 16
		{CONF_STATE_TIMEOUT_MIN, CONF_STATE_TIMEOUT_MAX, CONF_STATE_TIMEOUT_DEF},				// 17
		{AFTER_PULSE_TIMEOUT_MIN, AFTER_PULSE_TIMEOUT_MAX, AFTER_PULSE_TIMEOUT_DEF},			// 18
		{false, true, false},																	// 19
		{FAN_OPERATE_PERIOD_MIN, FAN_OPERATE_PERIOD_MAX, FAN_OPERATE_PERIOD_DEF},				// 20
		{FAN_OPERATE_TIME_MIN, FAN_OPERATE_TIME_MAX, FAN_OPERATE_TIME_DEF},						// 21
		{0, INT16U_MAX, ERROR_COUNTER_DEF},														// 22
		{ALLOWED_ERROR_MIN, ALLOWED_ERROR_MAX, ALLOWED_ERROR_DEF},								// 23
		{0, 0, 0},																				// 24
		{0, CTRL1_MAX_WIDTH_050_MAX, CTRL1_MAX_WIDTH_050_DEF},									// 25
		{0, CTRL1_MAX_WIDTH_075_MAX, CTRL1_MAX_WIDTH_075_DEF},									// 26
		{0, CTRL1_MAX_WIDTH_100_MAX, CTRL1_MAX_WIDTH_100_DEF},									// 27
		{0, CTRL1_MAX_WIDTH_250_MAX, CTRL1_MAX_WIDTH_250_DEF},									// 28
		{0, CTRL1_MAX_WIDTH_500_MAX, CTRL1_MAX_WIDTH_500_DEF},									// 29
		{0, CTRL1_MAX_WIDTH_750_MAX, CTRL1_MAX_WIDTH_750_DEF},									// 30
		{0, CTRL1_MAX_WIDTH_1000_MAX, CTRL1_MAX_WIDTH_1000_DEF},								// 31
		{0, CTRL1_MAX_WIDTH_1500_MAX, CTRL1_MAX_WIDTH_1500_DEF},								// 32
		{0, CTRL1_MAX_WIDTH_2500_MAX, CTRL1_MAX_WIDTH_2500_DEF},								// 33
		{0, CTRL1_MAX_WIDTH_3000_MAX, CTRL1_MAX_WIDTH_3000_DEF},								// 34
		{0, CTRL1_MAX_WIDTH_5000_MAX, CTRL1_MAX_WIDTH_5000_DEF},								// 35
		{0, CTRL2_MAX_WIDTH_MAX, CTRL2_MAX_WIDTH_DEF},											// 36
		{0, 0, 0},																				// 37
		{0, 0, 0},																				// 38
		{0, 0, 0},																				// 39
		{0, 0, 0},																				// 40
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 41
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 42
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 43
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 44
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 45
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 46
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 47
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 48
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 49
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 50
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 51
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 52
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 53
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 54
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 55
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 56
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 57
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 58
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 59
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 60
		{0, INT16U_MAX, I_TO_V_INTPS_OFFSET_DEF},												// 61
		{0, INT16U_MAX, I_TO_V_INTPS_K_DEF},													// 62
		{0, INT16U_MAX, CTRL1_050_OFFSET_DEF},													// 63
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_050_K_DEF},							// 64
		{0, INT16U_MAX, CTRL1_075_OFFSET_DEF},													// 65
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_075_K_DEF},							// 66
		{0, INT16U_MAX, CTRL1_100_OFFSET_DEF}, 													// 67
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_100_K_DEF},							// 68
		{0, INT16U_MAX, CTRL1_250_OFFSET_DEF},													// 69
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_250_K_DEF},							// 70
		{0, INT16U_MAX, CTRL1_500_OFFSET_DEF},													// 71
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_500_K_DEF},							// 72
		{0, INT16U_MAX, CTRL1_750_OFFSET_DEF},													// 73
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_750_K_DEF},							// 74
		{0, INT16U_MAX, CTRL1_1000_OFFSET_DEF},													// 75
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_1000_K_DEF},							// 76
		{0, INT16U_MAX, CTRL1_1500_OFFSET_DEF},													// 77
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_1500_K_DEF},							// 78
		{0, INT16U_MAX, CTRL1_2500_OFFSET_DEF},													// 79
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_2500_K_DEF},							// 80
		{0, INT16U_MAX, CTRL1_3000_OFFSET_DEF},													// 81
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_3000_K_DEF},							// 82
		{0, INT16U_MAX, CTRL1_5000_OFFSET_DEF},													// 83
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL1_5000_K_DEF},							// 84
		{0, INT16U_MAX, CTRL2_OFFSET_DEF},														// 85
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, CTRL2_K_DEF},								// 86
		{0, INT16U_MAX, 0},																		// 87
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, GAIN_COEFFICIENT_DEF},						// 88
		{0, INT16U_MAX, 0},																		// 89
		{0, INT16U_MAX, 0},																		// 90
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, GAIN_COEFFICIENT_DEF},						// 91
		{0, INT16U_MAX, 0},																		// 92
		{0, INT16U_MAX, 0},																		// 93
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, GAIN_COEFFICIENT_DEF},						// 94
		{0, INT16U_MAX, 0},																		// 95
		{0, INT16U_MAX, 0},																		// 96
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, GAIN_COEFFICIENT_DEF},						// 97
		{0, INT16U_MAX, 0},																		// 98
		{0, INT16U_MAX, 0},																		// 99
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, GAIN_COEFFICIENT_DEF},						// 100
		{0, INT16U_MAX, 0},																		// 101
		{0, INT16U_MAX, 0},																		// 102
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, GAIN_COEFFICIENT_DEF},						// 103
		{0, INT16U_MAX, 0},																		// 104
		{0, INT16U_MAX, 0},																		// 105
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, GAIN_COEFFICIENT_DEF},						// 106
		{0, INT16U_MAX, 0},																		// 107
		{0, INT16U_MAX, 0},																		// 108
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, GAIN_COEFFICIENT_DEF},						// 109
		{0, INT16U_MAX, 0},																		// 110
		{0, INT16U_MAX, 0},																		// 111
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, GAIN_COEFFICIENT_DEF},						// 112
		{0, INT16U_MAX, 0},																		// 113
		{0, INT16U_MAX, 0},																		// 114
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, GAIN_COEFFICIENT_DEF},						// 115
		{0, INT16U_MAX, 0},																		// 116
		{0, INT16U_MAX, 0},																		// 117
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, GAIN_COEFFICIENT_DEF},						// 118
		{0, INT16U_MAX, 0},																		// 119
		{0, INT16U_MAX, I_DUT_TO_DAC_OFFSET},													// 120
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, I_DUT_TO_DAC_K},							// 121
		{0, INT16U_MAX, 0},																		// 122
		{GAIN_COEFFICIENT_MIN, GAIN_COEFFICIENT_MAX, GAIN_COEFFICIENT_DEF},						// 123
		{0, INT16U_MAX, 0},																		// 124
		{0, 0, 0},																				// 125
		{0, 0, 0},																				// 126
		{0, 0, 0}																				// 127
};

const TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START] = {
		{CURRENT_SETPOINT_MIN, CURRENT_SETPOINT_MAX, CURRENT_SETPOINT_DEF},						// 128
		{CURRENT_RATE_MIN, CURRENT_RATE_MAX, CURRENT_RATE_DEF},									// 129
		{0, INTPS_VOLTAGE_MAX, 0},																// 130
		{0, 0, 0},																				// 131
		{0, 0, 0},																				// 132
		{0, 0, 0},																				// 133
		{0, 0, 0},																				// 134
		{0, 0, 0},																				// 135
		{0, 0, 0},																				// 136
		{0, 0, 0},																				// 137
		{0, 0, 0},																				// 138
		{0, 0, 0},																				// 139
		{0, 0, 0},																				// 140
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
		{0, 0, 0},																				// 152
		{0, 0, 0},																				// 153
		{0, 0, 0},																				// 154
		{0, 0, 0},																				// 155
		{0, 0, 0},																				// 156
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
