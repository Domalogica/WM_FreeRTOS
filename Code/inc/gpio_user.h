#ifndef _GPIO_USER_H_
#define _GPIO_USER_H_

#if defined(STM32F103xE)

	#define PORT_LED_ACTIVE     GPIOF
	#define PIN_LED_ACTIVE      10

	#define PORT_LED_FAILTURE   GPIOB
	#define PIN_LED_FAILTURE    8




	#define PORT_TRIAC_1        GPIOD
	#define PIN_TRIAC_1         GPIO_PIN_8
	#define PORT_TRIAC_2        GPIOD
	#define PIN_TRIAC_2         GPIO_PIN_14
	#define PORT_TRIAC_3        GPIOD
	#define PIN_TRIAC_3         GPIO_PIN_15
	#define PORT_TRIAC_4        GPIOD
	#define PIN_TRIAC_4         GPIO_PIN_10
	#define PORT_TRIAC_5        GPIOD
	#define PIN_TRIAC_5         GPIO_PIN_12
	#define PORT_TRIAC_6        GPIOD
	#define PIN_TRIAC_6         GPIO_PIN_7
	#define PORT_TRIAC_7        GPIOD
	#define PIN_TRIAC_7         GPIO_PIN_9
	#define PORT_TRIAC_8        GPIOD
	#define PIN_TRIAC_8         GPIO_PIN_11
	#define PORT_TRIAC_9        GPIOD
	#define PIN_TRIAC_9         GPIO_PIN_13

	#define PORT_MOSFET_1       //GPIOx
	#define PIN_MOSFET_1        //x
	#define PORT_MOSFET_2       //GPIOx
	#define PIN_MOSFET_2        //x
	#define PORT_MOSFET_3       //GPIOx
	#define PIN_MOSFET_3        //x
	#define PORT_MOSFET_4       //GPIOx
	#define PIN_MOSFET_4        //x

	#define PORT_ULN_CH_1       //GPIOx
	#define PIN_ULN_CH_1        //x
	#define PORT_ULN_CH_2       //GPIOx
	#define PIN_ULN_CH_2        //x
	#define PORT_ULN_CH_3       //GPIOx
	#define PIN_ULN_CH_3        //x
	#define PORT_ULN_CH_4       //GPIOx
	#define PIN_ULN_CH_4        //x
	#define PORT_ULN_CH_5       //GPIOx
	#define PIN_ULN_CH_5        //x
	#define PORT_ULN_CH_6       //GPIOx
	#define PIN_ULN_CH_6        //x
	#define PORT_ULN_CH_7       //GPIOx
	#define PIN_ULN_CH_7        //x
	#define PORT_ULN_CH_8       //GPIOx
	#define PIN_ULN_CH_8        //x
	#define PORT_ULN_CH_9       //GPIOx
	#define PIN_ULN_CH_9        //x
	#define PORT_ULN_CH_10      //GPIOx
	#define PIN_ULN_CH_10       //x
	#define PORT_ULN_CH_11      //GPIOx
	#define PIN_ULN_CH_11       //x
	#define PORT_ULN_CH_12      //GPIOx
	#define PIN_ULN_CH_12       //x
	#define PORT_ULN_CH_13      //GPIOx
	#define PIN_ULN_CH_13       //x
	#define PORT_ULN_CH_14      //GPIOx
	#define PIN_ULN_CH_14       //x

#endif

	void GPIO_Init (void);


#endif //_GPIO_USER_H_
