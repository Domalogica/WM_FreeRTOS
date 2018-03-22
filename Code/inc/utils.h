#ifndef _UTILS_H_
#define _UTILS_H_

#include "stm32f1xx.h"

uint16_t CRC16(uint8_t *pcBlock, uint16_t len);
int8_t i32toa_fixlen(uint32_t var32, uint8_t * str, uint8_t len);
int8_t i16toa_fixlen(uint16_t var16, uint8_t * str, uint8_t len);
int16_t double2string(double *dbl_val, char *str, uint8_t int_len, uint8_t frac_len, uint8_t dot);
int16_t float2string(float *flt_val, char *str, uint8_t int_len, uint8_t frac_len, uint8_t dot);
void str2int(char *string, uint8_t len, int32_t *num);

#endif //_UTILS_H_
