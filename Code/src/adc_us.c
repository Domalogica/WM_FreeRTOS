#include "adc_us.h"

void ADC1_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 														//Enabling the clock PORT A
	
	GPIO_SetPinMode (GPIOA, GPIO_PIN_5, GPIO_MODE_ANALOG);					//ADC channel 6 analog mode
	GPIO_SetPinMode (GPIOA, GPIO_PIN_6, GPIO_MODE_ANALOG);					//ADC channel 7 analog mode
	GPIO_SetPinMode (GPIOA, GPIO_PIN_7, GPIO_MODE_ANALOG);					//ADC channel 8 analog mode

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->APB2ENR |= RCC_CFGR_ADCPRE_DIV2;
	
	ADC_StructInit(&ADC_InitStructure);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //  одиночный, независимый
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; // just measuring | измерить один канал
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // 
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // without external trigger | без внешнего триггера
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //how it write the bits | выравнивание битов. прижатие вправо
	ADC_InitStructure.ADC_NbrOfChannel = 1; //number of the chanels | количество каналов 
	ADC_Init(ADC1, &ADC_InitStructure);
 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 2, ADC_SampleTime_55Cycles5);
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 2, ADC_SampleTime_55Cycles5);
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 3, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);
 
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1));
 
}
/*
uint16_t ACD3_GetResult(uint8_t num) {
	return dataBuffer[num];
}
*/
