#include "timers.h"

extern FML_data fml_data; 

uint8_t counterTim2 = 0;
uint8_t sensorData = 0;
uint8_t sensorCounter = 0;
uint32_t drianageFlowData = 0;
uint32_t drianageFlowDataPrev = 0;

uint8_t counterTim3 = 0;
uint8_t counterInPressure = 0;
uint8_t sensorInPressure = 0;

uint8_t IsDrinanageSensor(void)
{
	return sensorData;
}

uint8_t IsPressureSensor(void)
{
	return sensorInPressure;
}

void InitTIM2 (void) 
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;					// Enable clock TIM2

	TIM2->PSC = 1800-1;									// Prescaler
	TIM2->ARR = 1000-1;									// Period

	TIM2->DIER |= TIM_DIER_UIE;							// Enable interrupt
	TIM2->CR1  |= TIM_CR1_CEN;							// Enable counter

	NVIC_EnableIRQ(TIM2_IRQn);							// Interrupt
}

void TIM2_IRQHandler (void)
{
	TIM2->SR &= ~TIM_SR_UIF;
	
	drianageFlowData = FLM_GetTic(FLM_DRAINAGE);
	if(drianageFlowDataPrev != drianageFlowData) sensorCounter++; 
	else if(sensorCounter != 0) sensorCounter--;
	drianageFlowDataPrev = drianageFlowData;
	
	if(counterTim2 > 15)
	{
		if(sensorCounter > 10) sensorData = 1; 
		else sensorData = 0; 
		sensorCounter = 0; 
		counterTim2 = 0;
	}
	counterTim2++;
}

void InitTIM3 (void) 
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;					// Enable clock TIM2

	TIM3->PSC = 1800-1;									// Prescaler
	TIM3->ARR = 1000-1;									// Period

	TIM3->DIER |= TIM_DIER_UIE;							// Enable interrupt
	TIM3->CR1  |= TIM_CR1_CEN;							// Enable counter

	NVIC_EnableIRQ(TIM3_IRQn);							// Interrupt
}

void TIM3_IRQHandler (void)
{
	TIM3->SR &= ~TIM_SR_UIF;
	
	if(Is_InPressSensor()) counterInPressure++; 
	else if(counterInPressure != 0) counterInPressure--;

	if(counterTim3 > 50)
	{
		if(counterInPressure > 10) sensorInPressure = 0; 
		else sensorInPressure = 1; 
		counterInPressure = 0; 
		counterTim3 = 0;
	}
	counterTim3++;
}
