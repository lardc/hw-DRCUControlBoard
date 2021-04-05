// Header
#include "InitConfig.h"
//
// Includes
#include "Logic.h"
#include "BCCIxParams.h"

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
	RCC_GPIO_Clk_EN(PORTC);
	
	// Аналоговые порты
	GPIO_InitAnalog(GPIO_MEASURE_INT_PS);
	GPIO_InitAnalog(GPIO_MEASURE_BAT);
	GPIO_InitAnalog(GPIO_MEASURE_CURRENT);
	GPIO_InitAnalog(GPIO_COMPENSATION_SET);
	//

	// Входы
	GPIO_InitInput(GPIO_SYNC, NoPull);
	GPIO_InitInput(GPIO_PROTECTION, NoPull);
	//
	
	// Выходы
	GPIO_InitPushPullOutput(GPIO_OUTPUT_COMPENS);
	GPIO_InitPushPullOutput(GPIO_RELAY_MECH);
	GPIO_InitPushPullOutput(GPIO_RELAY_SOLID);
	GPIO_InitPushPullOutput(GPIO_OUTPUT_LOCK);
	GPIO_InitPushPullOutput(GPIO_FAN);
	GPIO_InitPushPullOutput(GPIO_LAMP);
	GPIO_InitPushPullOutput(GPIO_CURRENT_READY);
	GPIO_InitPushPullOutput(GPIO_LED);
	GPIO_InitPushPullOutput(GPIO_INT_PS);
	GPIO_InitPushPullOutput(GPIO_INT_PS_DISCHARGE);
	GPIO_InitPushPullOutput(GPIO_SPI_RCK);
	GPIO_InitPushPullOutput(GPIO_SYNC_OUT);
	//
	
	// Выходы с OpenDrain
	GPIO_InitOpenDrainOutput(GPIO_PROTECTION_RST, NoPull);

	// Альтернативные функции
	GPIO_InitAltFunction(GPIO_ALT_CAN_RX, AltFn_9);
	GPIO_InitAltFunction(GPIO_ALT_CAN_TX, AltFn_9);
	GPIO_InitAltFunction(GPIO_ALT_UART1_RX, AltFn_7);
	GPIO_InitAltFunction(GPIO_ALT_UART1_TX, AltFn_7);
	GPIO_InitAltFunction(GPIO_ALT_SPI1_SCK, AltFn_5);
	GPIO_InitAltFunction(GPIO_ALT_SPI1_DATA, AltFn_5);
	GPIO_InitAltFunction(GPIO_ALT_CTRL1, AltFn_2);
	GPIO_InitAltFunction(GPIO_ALT_CTRL2, AltFn_1);
}
//------------------------------------------------------------------------------

void CAN_Config()
{
	RCC_CAN_Clk_EN(CAN_1_ClkEN);
	NCAN_Init(SYSCLK, CAN_BAUDRATE, FALSE);
	NCAN_FIFOInterrupt(TRUE);
	NCAN_FilterInit(0, CAN_SLAVE_FILTER_ID, CAN_SLAVE_FILTER_ID);
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
	SPI_Init8b(SPI1, 3, false);
}
//------------------------------------------------------------------------------

void ADC_Config()
{
	RCC_ADC_Clk_EN(ADC_12_ClkEN);

	ADC_Calibration(ADC1);
	ADC_Enable(ADC1);
	ADC_SoftTrigConfig(ADC1);

	// Конфигурация и отключение DMA
	ADC_DMAConfig(ADC1);
	ADC_DMAEnable(ADC1, false);
}
//------------------------------------------------------------------------------

void ADC_SwitchToHighSpeed()
{
	ADC_Calibration(ADC1);
	ADC_Enable(ADC1);
	ADC_TrigConfig(ADC1, ADC12_TIM6_TRGO, RISE);

	ADC_ChannelSeqReset(ADC1);
	ADC_ChannelSet_Sequence(ADC1, ADC1_CURRENT_CHANNEL, 1);
	ADC_ChannelSeqLen(ADC1, 1);

	ADC_DMAEnable(ADC1, true);
}
//------------------------------------------------------------------------------

void ADC_SwitchToBase()
{
	ADC_Calibration(ADC1);
	ADC_Enable(ADC1);
	ADC_SoftTrigConfig(ADC1);

	ADC_DMAEnable(ADC1, false);
}
//------------------------------------------------------------------------------

void Timer2_3_Config()
{
	TIM_Clock_En(TIM_2);
	TIM_Config(TIM2, SYSCLK, TIMER2_3_uS);
	TIM_OnePulseMode(TIM2, true);

	TIM_Clock_En(TIM_3);
	TIM_Config(TIM3, SYSCLK, TIMER2_3_uS);
	TIM_OnePulseMode(TIM3, true);
}
//------------------------------------------------------------------------------

void Timer7_Config()
{
	TIM_Clock_En(TIM_7);
	TIM_Config(TIM7, SYSCLK, TIMER7_uS);
	TIM_Interupt(TIM7, 0, true);
	TIM_Start(TIM7);
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
	DAC_BufferCh1(DAC1, false);
	DAC_TriggerConfigCh1(DAC1, TRIG1_SOFTWARE, TRIG1_ENABLE);
	DAC_SetValueCh1(DAC1, 0);
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
