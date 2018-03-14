#ifndef _GPIO_USER_H_
#define _GPIO_USER_H_

#if defined(STM32F103xE)

	#define PORT_LED_ACTIVE     GPIOF
	#define PIN_LED_ACTIVE      GPIO_PIN_10

	#define PORT_LED_FAILTURE   GPIOB
	#define PIN_LED_FAILTURE    GPIO_PIN_8

#endif

void GPIO_Init (void);

#endif //_GPIO_USER_H_
