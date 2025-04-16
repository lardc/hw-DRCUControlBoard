#include "Interrupts.h"
#include "InitConfig.h"
#include "SysConfig.h"
#include "DataTable.h"
#include "Constraints.h"
#include "BCCIxParams.h"

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

	// Конфигурация сервиса работы DataTable и EPROM
	EPROMServiceConfig EPROMService = { (FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT };

	// Инициализация DataTable
	DT_Init(EPROMService, false);
	DT_SaveFirmwareInfo(CAN_SLAVE_NID, 0);

	// Настройка портов
	INITCFG_ConfigIO();

	// Настройка внешних прерываний
	INITCFG_ConfigExtInterrupt();

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

	// Настройка Timer16 для формирования импульса синхронизации
	INITCFG_ConfigTimer16();

	// Начальная настройка АЦП
	INITCFG_ConfigADC();

	// Настройка DMA для АЦП
	if (DataTable[REG_UNIT_DRCU] == VERSION_DCU)
		INITCFG_ConfigDMA();

	// Настройка Timer6 тактирования АЦП(DCU) и для защиты от превышения длительности синхросигнала(RCU)
	INITCFG_ConfigTimer6();

	// Настройка сторожевого таймера
	INITCFG_ConfigWatchDog();

	// Инициализация логики контроллера
	InitializeController(false);

	// Фоновый цикл
	while (true)
		CONTROL_Idle();

	return 0;
}
