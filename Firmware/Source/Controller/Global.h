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
#define ADC_AVG_SAMPLES					5							// Количество точек усреднения
// -----------------------------------------------

// Параметры таймеров
#define TIM2_3_MAX_VALUE				63630						// Максимальное значение таймеров
#define TIM16_MAX_VALUE					58330

//
#define UNIT_TQ_MEASURE_PULSES			11							// (в импульсах) + 1
#define UNIT_TQ_EXTRA_PULSES			15							// в импульсах
#define UNIT_MAX_NUM_OF_PULSES			(UNIT_TQ_MEASURE_PULSES + UNIT_TQ_EXTRA_PULSES)	// в импульсах
#define UNIT_PULSE_DELAY_MIN			500							// мс

// Параметры внутреннего источника
#define INTPS_VOLTAGE_MAX				1500.0f						// Максимальное напряжение внутреннего источника формирователя (В * 10)
#define INTPS_VOLTAGE_MIN				900.0f						// Минимальное напряжение внутреннего источника формирователя (В * 10)

// Параметры заряда конденсатора
#define BAT_VOLTAGE_HYST				30							// Разница включения дозарядки батареи

// Раскомментировать, если блок DCU
//#define TYPE_UNIT_DCU

#endif //  __GLOBAL_H
