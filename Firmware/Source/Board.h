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

// Определения для выходных портов
GPIO_PortPinSettingMacro GPIO_OUTPUT_LOCK		= {GPIOB, Pin_4};
GPIO_PortPinSettingMacro GPIO_LED				= {GPIOB, Pin_12};
GPIO_PortPinSettingMacro GPIO_INT_PS			= {GPIOB, Pin_9};
GPIO_PortPinSettingMacro GPIO_PROTECTION_RST	= {GPIOB, Pin_7};
GPIO_PortPinSettingMacro GPIO_INT_PS_DISCHARGE	= {GPIOB, Pin_8};

// Определения для входных портов
GPIO_PortPinSettingMacro GPIO_SYNC				= {GPIOB, Pin_6};
GPIO_PortPinSettingMacro GPIO_PROTECTION		= {GPIOC, Pin_13};

// Определения для аналоговых портов
GPIO_PortPinSettingMacro GPIO_MEASURE_INT_PS 	= {GPIOA, Pin_0};

// Определения для портов альтернативных функций
GPIO_PortPinSettingMacro GPIO_ALT_CAN_RX		= {GPIOA, Pin_11};
GPIO_PortPinSettingMacro GPIO_ALT_CAN_TX		= {GPIOA, Pin_12};
GPIO_PortPinSettingMacro GPIO_ALT_UART1_TX		= {GPIOA, Pin_9};
GPIO_PortPinSettingMacro GPIO_ALT_UART1_RX		= {GPIOA, Pin_10};
GPIO_PortPinSettingMacro GPIO_ALT_CTRL1			= {GPIOB, Pin_1};
GPIO_PortPinSettingMacro GPIO_ALT_CTRL2			= {GPIOB, Pin_10};
GPIO_PortPinSettingMacro GPIO_ALT_MCU_SYNC		= {GPIOA, Pin_6};

#endif // __BOARD_H
