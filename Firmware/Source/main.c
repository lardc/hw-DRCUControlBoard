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

	// ��������� ��������� ������� ������������
	INITCFG_ConfigSystemClock();

	// ��������� ������
	INITCFG_ConfigIO();

	// ��������� ������� ����������
	INITCFG_ConfigExtInterrupt();

	// ��������� CAN
	INITCFG_ConfigCAN();

	// ��������� UART
	INITCFG_ConfigUART();

	// ��������� Timer7 ������ ����������
	INITCFG_ConfigTimer7();

	// ��������� Timer2,3 � ������ ���������� �������
	INITCFG_ConfigTimer2_3();

	// ��������� Timer16 ��� ������������ �������� �������������
	INITCFG_ConfigTimer16();

	// ��������� ��������� ���
	INITCFG_ConfigADC();

	// ��������� ����
	INITCFG_ConfigDAC();

	// ��������� ����������� �������
	INITCFG_ConfigWatchDog();

	// ������������� ������ �����������
	InitializeController(false);

	// ������� ����
	while (true)
		CONTROL_Idle();

	return 0;
}
