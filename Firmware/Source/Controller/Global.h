﻿// -----------------------------------------
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

#define INTPS_VOLTAGE_MAX				1250.0f						// Максимальное напряжение внутреннего источника формирователя (В * 10)
#define INTPS_VOLTAGE_MIN				900.0f						// Минимальное напряжение внутреннего источника формирователя (В * 10)

// Раскомментировать, если блок DCU
#define TYPE_UNIT_DCU

#endif //  __GLOBAL_H
