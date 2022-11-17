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
#define	SCCI_TIMEOUT_TICKS				1000						// (в мс)
// Password to unlock non-volatile area for write
#define ENABLE_LOCKING					false
// -----------------------------------------------
#define EP_WRITE_COUNT					0							// Количество массивов для записи
#define EP_COUNT						1							// Количество массивов для чтения
#define VALUES_x_SIZE					2000						// Размер выходных массивов
#define ENABLE_LOCKING					false
// -----------------------------------------------

// Временные параметры
#define TIME_LED_BLINK					500							// Период моргания светодиода на плате (в мс)
// -----------------------------------------------

// Параметры заряда батареи
#define	BAT_CHARGE_TIMEOUT				30000						// Время ожидания заряда после подачи питания (в мс)
#define	BAT_CHARGE_SHORT_TIMEOUT		5000						// Время ожидания заряда между импульсами (в мс)
// -----------------------------------------------

// Параметры оцифровки
#define ADC_REF_VOLTAGE					3300.0f						// Опорное напряжение (в В)
#define ADC_RESOLUTION					4095						// Разрешение АЦП
#define ADC_CHANNELS					3							// Количество каналов преобразования АЦП
#define ADC_CURRENT_POS					0							// Позиция семплов тока в буфере DMA
#define ADC_BAT_VOLTAGE_POS				1							// Позиция семплов напряжения на батарее в буфере DMA
#define ADC_INTPS_VOLTAGE_POS			2							// Позиция семплов напряжения формирователя в буфере DMA
#define ADC_CURRENT_SEQ					(ADC_CURRENT_POS + 1)		// Номер последовательности преобразования АЦП
#define ADC_BAT_VOLTAGE_SEQ				(ADC_BAT_VOLTAGE_POS + 1)	// Номер последовательности преобразования АЦП
#define ADC_INTPS_VOLTAGE_SEQ			(ADC_INTPS_VOLTAGE_POS + 1)	// Номер последовательности преобразования АЦП
// -----------------------------------------------

// Параметры таймеров
#define TIM2_3_MAX_VALUE		63630								// Максимальное значение таймеров
#define TIM16_MAX_VALUE			58330
// -----------------------------------------------

// Параметры силовых плат QRRCurrentBoard
#define PPD_MOSFETS_PER_CURR_BOARD		32
#define PPD_BATTERY_VOLTAGE				100
#define PPD_SOURCE_RESISTOR				3.3f
//
#define PPD_FAULT_DELAY					15000
// -----------------------------------------------

// Параметры транзисторов
#define PPD_T_J_MAX						150
#define PPD_T_AMB_MAX					35
#define PPD_T_MARGIN					15
//
#define PPD_RTH_J_A						62.5	// in C/W
#define PPD_ZTH_MAX						0.125f	// in C/W
// -----------------------------------------------

#define INTPS_VOLTAGE_MAX				1250.0f						// Максимальное напряжение внутреннего источника формирователя (В * 10)
#define INTPS_VOLTAGE_MIN				800.0f						// Минимальное напряжение внутреннего источника формирователя (В * 10)

#endif //  __GLOBAL_H
