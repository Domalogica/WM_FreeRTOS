#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f1xx.h"

void ADC_Init(void);
uint16_t ReadADC(uint8_t numb);

#endif //_ADC_H_
