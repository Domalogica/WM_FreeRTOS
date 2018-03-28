#include "gpio.h"
#include "gpio_user.h"

void GPIO_Init (void)
{
	//Port clock setting 
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; //Enabling the clock PORT B
	RCC->APB2ENR |= RCC_APB2ENR_IOPFEN; //Enabling the clock PORT F

	//User LED gpio pin config
	GPIO_SetPinMode (PORT_LED_ACTIVE, PIN_LED_ACTIVE, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_LED_ACTIVE, PIN_LED_ACTIVE, GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_LED_FAILTURE, PIN_LED_FAILTURE, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_LED_FAILTURE, PIN_LED_FAILTURE, GPIO_MODE_OUTPUT_10MHz);
}
