#ifndef _RGB_H_
#define _RGB_H_

#include "stm32f1xx.h"
#include "power_switches.h"

//private
#define LED_GREEN_POS			6
#define LED_RED_POS				5
#define LED_BLUE_POS			4

//public
#define LED_GREEN					1
#define LED_RED						2
#define LED_BLUE					3
#define LED_YELOW					4
#define LED_MAGENTA				5 
#define LED_CYAN					6
#define LED_WHITE					7
#define LED_OFF					  8

int8_t RGB_ColorSet (uint8_t color);

#endif //_RGB_H_
