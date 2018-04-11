#include "timers.h"


extern FML_data fml_data; 
uint8_t counter = 0;
uint8_t sensorData = 0;
uint8_t sensorCounter = 0;
uint32_t drianageFlowData = 0;
uint32_t drianageFlowDataPrev = 0;

void InitTIM2 (void) 
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;					// Enable clock TIM2

	TIM2->PSC = 3600-1;												  // Prescaler
	TIM2->ARR = 1000-1;													// Period

	TIM2->DIER |= TIM_DIER_UIE;									// Enable interrupt
	TIM2->CR1  |= TIM_CR1_CEN;									// Enable counter

	NVIC_EnableIRQ(TIM2_IRQn);									// Interrupt
}

uint8_t IsDrinanageSensor(void)
{
		return sensorData;	
}

void TIM2_IRQHandler (void)
{
	TIM2->SR &= ~TIM_SR_UIF;
	
	drianageFlowData = FLM_GetTic(FLM_DRAINAGE);
	if(drianageFlowDataPrev != drianageFlowData) sensorCounter++; 
	else if(sensorCounter != 0) sensorCounter--;
	drianageFlowDataPrev = drianageFlowData;
	
	if(counter > 25)
	{
		if(sensorCounter > 10) sensorData = 0; 
		else sensorData = 1; 
		sensorCounter = 0; 
		counter = 0;
	}
	counter++;
}

