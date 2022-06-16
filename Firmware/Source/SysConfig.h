#ifndef __SYSCONFIG_H
#define __SYSCONFIG_H

#include "stdinc.h"

// Flash loader options
#define BOOT_LOADER_VARIABLE			(*((volatile uint32_t *)0x20000000))
#define BOOT_LOADER_REQUEST				0x12345678
#define BOOT_LOADER_MAIN_PR_ADDR		0x08008000
//-----------------------------------------------

// System clock
#define SYSCLK							70000000	// �������� ������� ��������� ���� ����������
#define QUARTZ_FREQUENCY				20000000	// ������� ������
// ----------------------------------------------

// USART
#define USART_BAUDRATE					115200		// �������� USART
#define USART_FIFOlen					32			// ����� FIFO USART
// ----------------------------------------------

// Timers
#define TIMER6_uS                		10.0f		// ������ ������������ ��� � ���
#define TIMER7_uS                  		1000		// ������ ������ ����������
#define TIMER2_3_uS						2500		// ������� ��� ������������ ����������� ���������
#define TIMER16_uS						5000		// ������� ��� ������������ �������� �������������
// ----------------------------------------------

// CAN
#define CAN_BAUDRATE					1000000		// ������� CAN
// ----------------------------------------------

// ADC
#define DMA_ADC1_CHANNEL				DMA1_Channel1	// ����� DMA ��� ��� ����
#define ADC1_CURRENT_CHANNEL			3				// ���1 ����� ������ ����
#define ADC1_BAT_VOLTAGE_CHANNEL		2				// ���1 ����� ��������� ���������� �� �������
#define ADC1_INT_PS_VOLTAGE_CHANNEL		1				// ���1 ����� ��������� ��������� �� ���������� ��
// ----------------------------------------------

#endif // __SYSCONFIG_H
