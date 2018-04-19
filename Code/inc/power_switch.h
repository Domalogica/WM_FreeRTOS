#ifndef _POWER_SWITCHES_H_
#define _POWER_SWITCHES_H_

#include "stm32f1xx.h"
#include "gpio.h"
#include "err_handler.h"

#define 	TR_WATER_SUPPLY			1
#define 	TR_WATER_DELIVERY		4
#define 	TR_WATER_PUMP				7
#define   TR_OSMOS_WASHING		2
#define 	TR_DISPENSER				8
#define 	TR_DRAINAGE					9

#define 	MF_WATER_PUMP				1


#if defined(STM32F103xE)

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

	#define PORT_MOSFET_1       GPIOF
	#define PIN_MOSFET_1        GPIO_PIN_12
	#define PORT_MOSFET_2       GPIOF
	#define PIN_MOSFET_2        GPIO_PIN_14
	#define PORT_MOSFET_3       GPIOF
	#define PIN_MOSFET_3        GPIO_PIN_15
	#define PORT_MOSFET_4       GPIOF
	#define PIN_MOSFET_4        GPIO_PIN_13

	#define PORT_ULN_CH_1       GPIOG
	#define PIN_ULN_CH_1        GPIO_PIN_9
	#define PORT_ULN_CH_2       GPIOG
	#define PIN_ULN_CH_2        GPIO_PIN_10
	#define PORT_ULN_CH_3       GPIOG
	#define PIN_ULN_CH_3        GPIO_PIN_11
	#define PORT_ULN_CH_4       GPIOG
	#define PIN_ULN_CH_4        GPIO_PIN_12
	#define PORT_ULN_CH_5       GPIOG
	#define PIN_ULN_CH_5        GPIO_PIN_13
	#define PORT_ULN_CH_6       GPIOG
	#define PIN_ULN_CH_6        GPIO_PIN_14
	#define PORT_ULN_CH_7       GPIOG
	#define PIN_ULN_CH_7        GPIO_PIN_15
	
	#define PORT_ULN_CH_8       GPIOE
	#define PIN_ULN_CH_8        GPIO_PIN_9
	#define PORT_ULN_CH_9       GPIOE
	#define PIN_ULN_CH_9        GPIO_PIN_10
	#define PORT_ULN_CH_10      GPIOE
	#define PIN_ULN_CH_10       GPIO_PIN_11
	#define PORT_ULN_CH_11      GPIOE
	#define PIN_ULN_CH_11       GPIO_PIN_12
	#define PORT_ULN_CH_12      GPIOE
	#define PIN_ULN_CH_12       GPIO_PIN_13
	#define PORT_ULN_CH_13      GPIOE
	#define PIN_ULN_CH_13       GPIO_PIN_14
	#define PORT_ULN_CH_14      GPIOE
	#define PIN_ULN_CH_14       GPIO_PIN_15

#endif

void   TRIAC_PortInit(void);
int8_t TRIAC_Enable  (uint32_t triac_num);
int8_t TRIAC_Disable (uint32_t triac_num);

void MOSFET_PortInit(void);
int8_t MOSFET_Enable(uint32_t mosfet_num);
int8_t MOSFET_Disable(uint32_t mosfet_num);

void ULN_PortInit(void);
int8_t ULN_Enable(uint32_t uln_num);
int8_t ULN_Disable(uint32_t uln_num);

#endif //_POWER_SWITCHES_H_
