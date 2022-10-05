#ifndef __INITCONFIG_H
#define __INITCONFIG_H

#include "Board.h"

//Functions
//
void INITCFG_ConfigSystemClock();
void INITCFG_ConfigIO();
void INITCFG_ConfigCAN();
void INITCFG_ConfigUART();
void INITCFG_ConfigSPI();
void INITCFG_ConfigADC();
void INITCFG_ConfigTimer7();
void INITCFG_ConfigTimer6();
void INITCFG_ConfigDAC();
void INITCFG_ConfigDMA();
void INITCFG_ConfigWatchDog();
void InitializeController(Boolean GoodClock);
void INITCFG_ConfigTimer2_3();
void INITCFG_ConfigExtInterrupt();
void INITCFG_ConfigTimer16();

#endif //__INITCONFIG_H
