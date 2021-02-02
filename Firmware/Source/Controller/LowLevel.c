// Header
#include "LowLevel.h"

// Functions
//
// LED on board
void LL_ToggleBoardLED()
{

}
//------------------------------------------------------------------------------

// External LED
void LL_ExternalLED(bool State)
{
	State ? GPIO_Bit_Set(GPIOB, Pin_4) : GPIO_Bit_Rst(GPIOB, Pin_4);
}
//------------------------------------------------------------------------------

// External FAN
void LL_ExternalFAN(bool State)
{
	State ? GPIO_Bit_Set(GPIOA, Pin_15) : GPIO_Bit_Rst(GPIOA, Pin_15);
}
//------------------------------------------------------------------------------

// External DC Ready
void LL_External_DC_RDY(bool State)
{
	State ? GPIO_Bit_Set(GPIOB, Pin_10) : GPIO_Bit_Rst(GPIOB, Pin_10);
}
//------------------------------------------------------------------------------

// Software trigger
void LL_SW_Trig(bool State)
{
	State ? GPIO_Bit_Set(GPIOA, Pin_6) : GPIO_Bit_Rst(GPIOA, Pin_6);
}
//------------------------------------------------------------------------------

// Rate range 0 set
void LL_R0_Set()
{
	GPIO_Bit_Set(GPIOB, Pin_13);
	GPIO_Bit_Rst(GPIOB, Pin_14);
	GPIO_Bit_Rst(GPIOB, Pin_15);
}
//------------------------------------------------------------------------------

// Rate range 1 set
void LL_R1_Set()
{
	GPIO_Bit_Rst(GPIOB, Pin_13);
	GPIO_Bit_Set(GPIOB, Pin_14);
	GPIO_Bit_Rst(GPIOB, Pin_15);
}
//------------------------------------------------------------------------------

// Rate range 2 set
void LL_R2_Set()
{
	GPIO_Bit_Rst(GPIOB, Pin_13);
	GPIO_Bit_Rst(GPIOB, Pin_14);
	GPIO_Bit_Set(GPIOB, Pin_15);
}
//------------------------------------------------------------------------------

// DAC
void LL_DAC_Write(uint16_t Data)
{
	Data |= 1<<14;

	GPIO_Bit_Rst(GPIOB, Pin_0);
	SPI_WriteByte(SPI1, Data);
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	GPIO_Bit_Set(GPIOB, Pin_0);

	GPIO_Bit_Rst(GPIOB, Pin_1);
	GPIO_Bit_Set(GPIOB, Pin_1);
}
//------------------------------------------------------------------------------

void LL_PowerOnMechRelay(bool State)
{
	if(State)
		GPIO_Bit_Set(GPIOB, Pin_8);
	else
		GPIO_Bit_Rst(GPIOB, Pin_8);
}
//------------------------------------------------------------------------------

void LL_PowerOnSolidStateRelay(bool State)
{
	if(State)
		GPIO_Bit_Set(GPIOB, Pin_9);
	else
		GPIO_Bit_Rst(GPIOB, Pin_9);
}
//------------------------------------------------------------------------------
