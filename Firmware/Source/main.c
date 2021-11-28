#include "Interrupts.h"
#include "InitConfig.h"
#include "SysConfig.h"

// Functions
//
void CONTROL_Idle();

int main()
{
	__disable_irq();
	SCB->VTOR = (Int32U)BOOT_LOADER_MAIN_PR_ADDR;
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

	// Настройка Timer7 общего назначения
	INITCFG_ConfigTimer7();

	// Настройка Timer2,3 в режиме одиночного запуска
	INITCFG_ConfigTimer2_3();

	// Настройка Timer16 для формирования импульса синхронизации
	INITCFG_ConfigTimer16();

	// Начальная настройка АЦП
	INITCFG_ConfigADC();

	// Настройка ЦАПа
	INITCFG_ConfigDAC();

	// Настройка сторожевого таймера
	INITCFG_ConfigWatchDog();

	// Инициализация логики контроллера
	InitializeController(false);

	// Фоновый цикл
	while (true)
		CONTROL_Idle();

	return 0;
}
