#include "stm32f1xx.h"
#include "gpio_user.h"
#include "gpio.h"

void GPIO_Init (void){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;

	GPIOB->CRH &= ~GPIO_CRH_CNF8;
	GPIOB->CRH |= GPIO_CRH_MODE8_0;
	
	GPIOF->CRH &= ~GPIO_CRH_CNF10;
	GPIOF->CRH |= GPIO_CRH_MODE10_0;
	
}
