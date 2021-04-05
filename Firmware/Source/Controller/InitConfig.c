// Header
#include "InitConfig.h"
//
// Includes
#include "Logic.h"

// Forward functions
//
void CONTROL_Init();

// Functions
//
void SysClk_Config()
{
	RCC_PLL_HSE_Config(QUARTZ_FREQUENCY, PREDIV_4, PLL_14);
	RCC_SysCfg_Clk_EN();
}
//------------------------------------------------------------------------------

void IO_Config()
{
	// Включение тактирования портов
	RCC_GPIO_Clk_EN(PORTA);
	RCC_GPIO_Clk_EN(PORTB);

	// Входы
	GPIO_Config (GPIOB, Pin_2, Input, PushPull, HighSpeed, NoPull);					// PB2 - вход внешнего триггера
	GPIO_Bit_Rst(GPIOB, Pin_2);
	//
	
	// Выходы
	GPIO_Config (GPIOB, Pin_13, Output, PushPull, HighSpeed, NoPull);				// PB13 - диапазон скорости 0
	GPIO_Bit_Rst(GPIOB, Pin_13);
	GPIO_Config (GPIOB, Pin_14, Output, PushPull, HighSpeed, NoPull);				// PB14 - диапазон скорости 1
	GPIO_Bit_Rst(GPIOB, Pin_14);
	GPIO_Config (GPIOB, Pin_15, Output, PushPull, HighSpeed, NoPull);				// PB15 - диапазон скорости 2
	GPIO_Bit_Rst(GPIOB, Pin_15);
	GPIO_Config (GPIOB, Pin_8, Output, PushPull, HighSpeed, NoPull);				// PB8
	GPIO_Bit_Rst(GPIOB, Pin_8);
	GPIO_Config (GPIOB, Pin_9, Output, PushPull, HighSpeed, NoPull);				// PB9
	GPIO_Bit_Rst(GPIOB, Pin_9);
	//
	
	// Альтернативные функции
	GPIO_Config (GPIOA, Pin_11, AltFn, PushPull, HighSpeed, NoPull);				// PA11(CAN RX)
	GPIO_AltFn  (GPIOA, Pin_11, AltFn_9);
	GPIO_Config (GPIOA, Pin_12, AltFn, PushPull, HighSpeed, NoPull);				// PA12(CAN TX)
	GPIO_AltFn  (GPIOA, Pin_12, AltFn_9);
	GPIO_Config (GPIOA, Pin_9,  AltFn, PushPull, HighSpeed, NoPull);				// PA9(USART1 TX)
	GPIO_AltFn  (GPIOA, Pin_9,  AltFn_7);
	GPIO_Config (GPIOA, Pin_10, AltFn, PushPull, HighSpeed, NoPull);				// PA10(USART1 RX)
	GPIO_AltFn  (GPIOA, Pin_10, AltFn_7);

	EXTI_Config(EXTI_PB, EXTI_2, BOTH_TRIG, 0);
	EXTI_EnableInterrupt(EXTI2_TSC_IRQn, 0, true);
}
//------------------------------------------------------------------------------

void CAN_Config()
{
	RCC_CAN_Clk_EN(CAN_1_ClkEN);
	NCAN_Init(SYSCLK, CAN_BAUDRATE, FALSE);
	NCAN_FIFOInterrupt(TRUE);
	NCAN_FilterInit(0, 0, 0);		// Фильтр 0 пропускает все сообщения
}
//------------------------------------------------------------------------------

void UART_Config()
{
	USART_Init(USART1, SYSCLK, USART_BAUDRATE);
	USART_Recieve_Interupt(USART1, 0, true);
}
//------------------------------------------------------------------------------

void SPI_Config()
{
	SPI_Init(SPI1, 3, false);
}
//------------------------------------------------------------------------------

void ADC_Config()
{
	RCC_ADC_Clk_EN(ADC_12_ClkEN);

	ADC_Calibration(ADC1);
	ADC_Calibration(ADC2);
	ADC_Enable(ADC1);
	ADC_Enable(ADC2);
	ADC_SoftTrigConfig(ADC1);
	ADC_SoftTrigConfig(ADC2);

	// Конфигурация и отключение DMA
	ADC_DMAConfig(ADC1);
	ADC_DMAEnable(ADC1, false);
}
//------------------------------------------------------------------------------

void ADC_SwitchToHighSpeed()
{
	ADC1_2_SetDualMode(true);

	ADC_Calibration(ADC1);
	ADC_Calibration(ADC2);
	ADC_Enable(ADC1);
	ADC_Enable(ADC2);
	ADC_TrigConfig(ADC1, ADC12_TIM6_TRGO, RISE);

	ADC_ChannelSeqReset(ADC1);
	ADC_ChannelSet_Sequence(ADC1, ADC1_VOLTAGE_CHANNEL, 1);
	ADC_ChannelSeqLen(ADC1, 1);

	ADC_ChannelSeqReset(ADC2);
	ADC_ChannelSet_Sequence(ADC2, ADC2_CURRENT_CHANNEL, 1);
	ADC_ChannelSeqLen(ADC2, 1);

	ADC_DMAEnable(ADC1, true);
	ADC_DMAEnable(ADC2, true);
}
//------------------------------------------------------------------------------

void ADC_SwitchToBase()
{
	ADC1_2_SetDualMode(false);

	ADC_Calibration(ADC1);
	ADC_Calibration(ADC2);
	ADC_Enable(ADC1);
	ADC_Enable(ADC2);
	ADC_SoftTrigConfig(ADC1);
	ADC_SoftTrigConfig(ADC2);

	ADC_DMAEnable(ADC1, false);
	ADC_DMAEnable(ADC2, false);
}
//------------------------------------------------------------------------------

void Timer3_Config()
{
	TIM_Clock_En(TIM_3);
	TIM_Config(TIM3, SYSCLK, TIMER3_uS);
	TIM_Interupt(TIM3, 0, true);
	TIM_Start(TIM3);
}
//------------------------------------------------------------------------------

void Timer6_Config()
{
	TIM_Clock_En(TIM_6);
	TIM_Config(TIM6, SYSCLK, TIMER6_uS);
	TIM_DMA(TIM6, DMAEN);
	TIM_MasterMode(TIM6, MMS_UPDATE);
}
//------------------------------------------------------------------------------

void DAC_Config()
{
	DAC_ClkEnable(DAC1);
	DAC_Reset(DAC1);

	DAC_EnableCh1(DAC1);
	DAC_EnableCh2(DAC1);

	DAC_BufferCh1(DAC1, false);
	DAC_BufferCh2(DAC1, false);

	DAC_TriggerConfigCh1(DAC1, TRIG1_SOFTWARE, TRIG1_ENABLE);
	DAC_TriggerConfigCh2(DAC1, TRIG2_SOFTWARE, TRIG2_ENABLE);

	DAC_SetValueCh1(DAC1, 0);
	DAC_SetValueCh2(DAC1, 0);
}
//------------------------------------------------------------------------------

void DAC_SwitchToHighSpeed()
{
	DAC_DMAConfigCh1(DAC1, true, true);
	DAC_TriggerConfigCh1(DAC1, TRIG1_TIMER6, TRIG1_ENABLE);
}
//------------------------------------------------------------------------------

void DAC_SwitchToBase()
{
	DAC_DMAConfigCh1(DAC1, false, false);
	DAC_TriggerConfigCh1(DAC1, TRIG1_SOFTWARE, TRIG1_ENABLE);
}
//------------------------------------------------------------------------------

void DMA_Config()
{
	DMA_Clk_Enable(DMA1_ClkEN);

	// DMA для АЦП тока на DUT
	DMA_Reset(DMA_ADC_DUT_I_CHANNEL);
	DMAChannelX_DataConfig(DMA_ADC_DUT_I_CHANNEL, (uint32_t)LOGIC_DUTCurrentRaw, (uint32_t)(&ADC1->DR), PULSE_ARR_MAX_LENGTH);
	DMAChannelX_Config(DMA_ADC_DUT_I_CHANNEL, DMA_MEM2MEM_DIS, DMA_LvlPriority_LOW, DMA_MSIZE_16BIT, DMA_PSIZE_16BIT,
						DMA_MINC_EN, DMA_PINC_DIS, DMA_CIRCMODE_DIS, DMA_READ_FROM_PERIPH);
}
//------------------------------------------------------------------------------

void WatchDog_Config()
{
	IWDG_Config();
	IWDG_ConfigureFastUpdate();
}
//------------------------------------------------------------------------------

void InitializeController(Boolean GoodClock)
{
	CONTROL_Init();
}
// -----------------------------------------------------------------------------
