#ifndef _UTILS_H_
#define _UTILS_H_

#include "stm32f1xx.h"

uint16_t CRC16(uint8_t *pcBlock, uint16_t len);
int8_t Int16ToString(uint16_t var16, uint8_t * str, uint8_t len);
int8_t Int32ToString(uint32_t var32, uint8_t * str, uint8_t len);
int16_t DoubleTOstring(double *dbl_val, char *str, uint8_t int_len, uint8_t frac_len, uint8_t dot);
int16_t FloatToString(float *flt_val, char *str, uint8_t int_len, uint8_t frac_len, uint8_t dot);
void StringToInt(char *string, uint8_t len, int32_t *num);

#endif //_UTILS_H_
