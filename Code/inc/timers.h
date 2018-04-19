#ifndef _TIMERS_H_
#define _TIMERS_H_

#include "stm32f1xx.h"
#include "gpio_us.h"
#include "fml.h"

void InitTIM2 (void);
void InitTIM3 (void);
uint8_t IsDrinanageSensor(void);
uint8_t IsPressureSensor(void);

#endif //_TIMERS_H_
