#ifndef __SYSCONFIG_H
#define __SYSCONFIG_H

#include "stdinc.h"

// Flash loader options
#define BOOT_LOADER_VARIABLE			(*((volatile uint32_t *)0x20000000))
#define BOOT_LOADER_REQUEST				0x12345678
#define BOOT_LOADER_MAIN_PR_ADDR		0x08008000
//-----------------------------------------------

// System clock
#define SYSCLK							70000000	// Тактовая частота системной шины процессора
#define QUARTZ_FREQUENCY				20000000	// Частота кварца
// ----------------------------------------------

// USART
#define USART_BAUDRATE					115200		// Скорость USART
#define USART_FIFOlen					32			// Длина FIFO USART
// ----------------------------------------------

// Timers
#define TIMER6_uS                		10.0f		// Таймер тактирования ЦАП и АЦП
#define TIMER7_uS                  		1000		// Таймер общего назначения
#define TIMER2_3_uS						2500		// Таймеры для формирования управляющих импульсов
#define TIMER16_uS						5000		// Таймеры для формирования импульса синхронизации
// ----------------------------------------------

// CAN
#define CAN_BAUDRATE					1000000		// Битрейт CAN
// ----------------------------------------------

// ADC
#define DMA_ADC1_CHANNEL				DMA1_Channel1	// Канал DMA для АЦП тока
#define ADC1_CURRENT_CHANNEL			3				// АЦП1 номер канала тока
#define ADC1_BAT_VOLTAGE_CHANNEL		2				// АЦП1 канал измерения напряжения на батарее
#define ADC1_INT_PS_VOLTAGE_CHANNEL		1				// АЦП1 канал измерения напряжени на внутреннем БП
// ----------------------------------------------

#endif // __SYSCONFIG_H
