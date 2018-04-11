#ifndef _GPIO_USER_H_
#define _GPIO_USER_H_

#include "stm32f1xx.h"
#include "gpio.h"

#if defined(STM32F103xE)

	#define PORT_LED_ACTIVE     			GPIOF
	#define PIN_LED_ACTIVE      			GPIO_PIN_10

	#define PORT_LED_FAILTURE   			GPIOB
	#define PIN_LED_FAILTURE    			GPIO_PIN_8
	
	#define PORT_INPUT_PRESS_SENSOR  	GPIOF
	#define PIN_INPUT_PRESS_SENSOR   	GPIO_PIN_6
	#define DATA_INPUT_PRESS_SENSOR   GPIO_IDR_IDR6
	
	#define PORT_OUTPUT_PRESS_SENSOR  GPIOF
	#define PIN_OUTPUT_PRESS_SENSOR		GPIO_PIN_7
	#define DATA_OUTPUT_PRESS_SENSOR  GPIO_IDR_IDR7
	
	#define PORT_DRAINAGE_FLOW        GPIOF
	#define PIN_DRAINAGE_FLOW					GPIO_PIN_8
	#define DATA_DRAINAGE_FLOW 				GPIO_IDR_IDR8
	
	#define PORT_BUTTON_DOWN  				GPIOC
	#define PIN_BUTTON_DOWN						GPIO_PIN_13
	#define DATA_BUTTON_DOWN  				GPIO_IDR_IDR13
	
	#define PORT_BUTTON_UP  					GPIOC
	#define PIN_BUTTON_UP							GPIO_PIN_14
	#define DATA_BUTTON_UP	  				GPIO_IDR_IDR14
	
	#define PORT_BUTTON_LEFT  				GPIOC
	#define PIN_BUTTON_LEFT						GPIO_PIN_15
	#define DATA_BUTTON_LEFT  				GPIO_IDR_IDR15
	
	#define PORT_BUTTON_RIGHT  				GPIOE
	#define PIN_BUTTON_RIGHT					GPIO_PIN_6
	#define DATA_BUTTON_RIGHT 				GPIO_IDR_IDR6

#endif

void GPIO_Init (void);
uint8_t Is_InPressSensor(void);
uint8_t Is_OutPressSensor(void);
//uint8_t Is_DrainageFlow(void);

uint8_t Is_ButtonLeft(void);
uint8_t Is_ButtonRight(void);
uint8_t Is_ButtonUp(void);
uint8_t Is_ButtonDown(void);

#endif //_GPIO_USER_H_
