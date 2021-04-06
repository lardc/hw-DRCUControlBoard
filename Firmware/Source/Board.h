#ifndef __BOARD_H
#define __BOARD_H

#include "stm32f30x.h"

#include "ZwRCC.h"
#include "ZwGPIO.h"
#include "ZwNCAN.h"
#include "ZwTIM.h"
#include "ZwDAC.h"
#include "ZwDMA.h"
#include "ZwADC.h"
#include "ZwEXTI.h"
#include "ZwSCI.h"
#include "ZwIWDG.h"
#include "ZwNFLASH.h"
#include "ZwSPI.h"

// ����������� ��� �������� ������
GPIO_PortPinSettingMacro GPIO_OUTPUT_COMPENS	= {GPIOC, Pin_14};
GPIO_PortPinSettingMacro GPIO_RELAY_SOLID		= {GPIOA, Pin_8};
GPIO_PortPinSettingMacro GPIO_RELAY_MECH		= {GPIOB, Pin_15};
GPIO_PortPinSettingMacro GPIO_OUTPUT_LOCK		= {GPIOB, Pin_4};
GPIO_PortPinSettingMacro GPIO_FAN				= {GPIOB, Pin_13};
GPIO_PortPinSettingMacro GPIO_LAMP				= {GPIOB, Pin_14};
GPIO_PortPinSettingMacro GPIO_CURRENT_READY		= {GPIOB, Pin_11};
GPIO_PortPinSettingMacro GPIO_LED				= {GPIOB, Pin_12};
GPIO_PortPinSettingMacro GPIO_INT_PS			= {GPIOB, Pin_9};
GPIO_PortPinSettingMacro GPIO_SYNC_OUT			= {GPIOA, Pin_6};
GPIO_PortPinSettingMacro GPIO_PROTECTION_RST	= {GPIOB, Pin_7};
GPIO_PortPinSettingMacro GPIO_INT_PS_DISCHARGE	= {GPIOB, Pin_8};
GPIO_PortPinSettingMacro GPIO_SPI_RCK			= {GPIOA, Pin_15};

// ����������� ��� ������� ������
GPIO_PortPinSettingMacro GPIO_SYNC				= {GPIOB, Pin_6};
GPIO_PortPinSettingMacro GPIO_PROTECTION		= {GPIOC, Pin_13};

// ����������� ��� ���������� ������
GPIO_PortPinSettingMacro GPIO_MEASURE_INT_PS 	= {GPIOA, Pin_0};
GPIO_PortPinSettingMacro GPIO_MEASURE_BAT		= {GPIOA, Pin_1};
GPIO_PortPinSettingMacro GPIO_MEASURE_CURRENT	= {GPIOA, Pin_2};
GPIO_PortPinSettingMacro GPIO_COMPENSATION_SET	= {GPIOA, Pin_4};

// ����������� ��� ������ �������������� �������
GPIO_PortPinSettingMacro GPIO_ALT_CAN_RX		= {GPIOA, Pin_11};
GPIO_PortPinSettingMacro GPIO_ALT_CAN_TX		= {GPIOA, Pin_12};
GPIO_PortPinSettingMacro GPIO_ALT_UART1_TX		= {GPIOA, Pin_9};
GPIO_PortPinSettingMacro GPIO_ALT_UART1_RX		= {GPIOA, Pin_10};
GPIO_PortPinSettingMacro GPIO_ALT_SPI1_SCK		= {GPIOB, Pin_3};
GPIO_PortPinSettingMacro GPIO_ALT_SPI1_DATA		= {GPIOB, Pin_5};
GPIO_PortPinSettingMacro GPIO_ALT_CTRL1			= {GPIOB, Pin_1};
GPIO_PortPinSettingMacro GPIO_ALT_CTRL2			= {GPIOB, Pin_10};

#endif // __BOARD_H
