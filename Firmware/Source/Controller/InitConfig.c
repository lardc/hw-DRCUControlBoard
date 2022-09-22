// Header
#include "InitConfig.h"
//
// Includes
#include "Logic.h"
#include "Global.h"
#include "BCCIxParams.h"

// Forward functions
//
void CONTROL_Init();

// Functions
//
void INITCFG_ConfigSystemClock()
{
	RCC_PLL_HSE_Config(QUARTZ_FREQUENCY, PREDIV_4, PLL_14);
	RCC_SysCfg_Clk_EN();
}
//------------------------------------------------------------------------------

void INITCFG_ConfigIO()
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
	GPIO_InitInput(GPIO_SYNC, Pull_Down);
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
	GPIO_InitAltFunction(GPIO_ALT_MCU_SYNC, AltFn_1);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigExtInterrupt()
{
	// Вход PROTECTION
	EXTI_Config(EXTI_PC, EXTI_13, FALL_TRIG, 0);
	EXTI_EnableInterrupt(EXTI15_10_IRQn, 0, true);

	// Вход SYNC
	EXTI_Config(EXTI_PB, EXTI_6, BOTH_TRIG, 0);
	EXTI_EnableInterrupt(EXTI9_5_IRQn, 0, true);
}
//------------------------------------------------

void INITCFG_ConfigCAN()
{
	RCC_CAN_Clk_EN(CAN_1_ClkEN);
	NCAN_Init(SYSCLK, CAN_BAUDRATE, false);
	NCAN_FIFOInterrupt(true);
	NCAN_FilterInit(0, CAN_SLAVE_FILTER_ID, CAN_SLAVE_FILTER_ID);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigUART()
{
	USART_Init(USART1, SYSCLK, USART_BAUDRATE);
	USART_Recieve_Interupt(USART1, 0, true);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigSPI()
{
	SPI_Init8b(SPI1, 7, false);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigADC()
{
	RCC_ADC_Clk_EN(ADC_12_ClkEN);
	ADC_Calibration(ADC1);
	ADC_Enable(ADC1);
	ADC_TrigConfig(ADC1, ADC12_TIM6_TRGO, RISE);
	ADC_ChannelSeqReset(ADC1);
	ADC_ChannelSet_Sequence(ADC1, ADC1_CURRENT_CHANNEL, ADC_CURRENT_SEQ);
	ADC_ChannelSet_Sequence(ADC1, ADC1_BAT_VOLTAGE_CHANNEL, ADC_BAT_VOLTAGE_SEQ);
	ADC_ChannelSet_Sequence(ADC1, ADC1_INT_PS_VOLTAGE_CHANNEL, ADC_INTPS_VOLTAGE_SEQ);
	ADC_ChannelSeqLen(ADC1, ADC_CHANNELS);
	ADC_DMAConfig(ADC1);
	ADC_DMAEnable(ADC1, true);
	ADC_SamplingStart(ADC1);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigTimer2_3()
{
	// Timer2
	TIM_Clock_En(TIM_2);
	TIM_Config(TIM2, SYSCLK, TIMER2_3_uS);
	TIMx_PWM_ConfigChannel(TIM2, TIMx_CHANNEL3);
	TIM_InterruptEventConfig(TIM2, TIM_DIER_CC3IE, true);

	// Timer3
	TIM_Clock_En(TIM_3);
	TIM_Config(TIM3, SYSCLK, TIMER2_3_uS);
	TIMx_PWM_ConfigChannel(TIM3, TIMx_CHANNEL4);
	TIM_InterruptEventConfig(TIM3, TIM_DIER_CC4IE, true);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigTimer16()
{
	TIM_Clock_En(TIM_16);
	TIM_Config(TIM16, SYSCLK, TIMER16_uS);
	TIM_OnePulseMode(TIM16, true);
	TIMx_PWM_ConfigChannel(TIM16, TIMx_CHANNEL1);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigTimer7()
{
	TIM_Clock_En(TIM_7);
	TIM_Config(TIM7, SYSCLK, TIMER7_uS);
	TIM_Interupt(TIM7, 0, true);
	TIM_Start(TIM7);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigTimer6()
{
	TIM_Clock_En(TIM_6);
	TIM_Config(TIM6, SYSCLK, TIMER6_uS);
	TIM_DMA(TIM6, DMAEN);
	TIM_MasterMode(TIM6, MMS_UPDATE);
	TIM_Start(TIM6);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigDAC()
{
	DAC_ClkEnable(DAC1);
	DAC_Reset(DAC1);
	DAC_EnableCh1(DAC1);
	DAC_BufferCh1(DAC1, true);
	DAC_TriggerConfigCh1(DAC1, TRIG1_SOFTWARE, TRIG1_ENABLE);
	DAC_SetValueCh1(DAC1, 0);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigDMA()
{
	DMA_Clk_Enable(DMA1_ClkEN);

	// DMA для АЦП тока на DUT
	DMA_Reset(DMA_ADC1_CHANNEL);
	DMAChannelX_DataConfig(DMA_ADC1_CHANNEL, (Int32U)&LOGIC_ADCRaw[0], (Int32U)(&ADC1->DR), ADC_CHANNELS);
	DMAChannelX_Config(DMA_ADC1_CHANNEL, DMA_MEM2MEM_DIS, DMA_LvlPriority_LOW, DMA_MSIZE_16BIT, DMA_PSIZE_16BIT,
						DMA_MINC_EN, DMA_PINC_DIS, DMA_CIRCMODE_EN, DMA_READ_FROM_PERIPH);
	DMA_Interrupt(DMA_ADC1_CHANNEL, DMA_TRANSFER_COMPLETE, 0, true);
	DMA_ChannelEnable(DMA_ADC1_CHANNEL, true);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigWatchDog()
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
