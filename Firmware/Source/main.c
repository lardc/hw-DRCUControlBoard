#include "Interrupts.h"
#include "InitConfig.h"
#include "SysConfig.h"

// Functions
//
void CONTROL_Idle();

int main()
{
	__disable_irq();
	SCB->VTOR = (uint32_t)BOOT_LOADER_MAIN_PR_ADDR;
	__enable_irq();

	// Настройка системной частоты тактирования
	INITCFG_ConfigSystemClock();

	// Настройка портов
	INITCFG_ConfigIO();

	// Настройка внешних прерываний
	INITCFG_ConfigExtInterrupt();

	// Настройка CAN
	INITCFG_ConfigCAN();

	// Настройка UART
	INITCFG_ConfigUART();

	// SPI config
	INITCFG_ConfigSPI();

	// Настройка ЦАПа
	INITCFG_ConfigDAC();

	// Настройка Timer7 общего назначения
	INITCFG_ConfigTimer7();

	// Настройка Timer2,3 в режиме одиночного запуска
	INITCFG_ConfigTimer2_3();

	// Настройка Timer6 тактирования ЦАП и АЦП
	INITCFG_ConfigTimer6();

	// Начальная настройка АЦП
	INITCFG_ConfigADC();

	// Настройка DMA для ЦАП и АЦП
	INITCFG_ConfigDMA();

	// Настройка сторожевого таймера
	INITCFG_ConfigWatchDog();

	// Инициализация логики контроллера
	InitializeController(false);

	// Фоновый цикл
	while (TRUE)
		CONTROL_Idle();

	return 0;
}
