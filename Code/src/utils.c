#include "utils.h"

uint16_t CRC16(uint8_t *pcBlock, uint16_t len)
{
	#define POLY  0x9EB2
	uint16_t crc = 0x00;
	uint8_t i;
	
	while (len--)
	{
		crc ^= (*pcBlock++) << 8;
		
		for (i = 0; i < 8; ++i)
		crc = crc & 0x8000 ? (crc << 1) ^ POLY : crc << 1;
	}
	
	return crc;
}

int8_t Int16ToString(uint16_t var16, uint8_t * str, uint8_t len)
{
	uint8_t *tmp_str_ptr = str + len - 1;
	int8_t size = (int8_t)len;
	
	while (len--)
	{
		*(tmp_str_ptr--) = (var16 % 10) + '0';
		var16 /= 10;
	}
	
	return size;
}

int8_t Int32ToString(uint32_t var32, uint8_t * str, uint8_t len)
{
	// 4294967295 max 10
	
	uint8_t *tmp_str_ptr = str + len - 1;
	int8_t size = (int8_t)len;
	
	while (len--)
	{
		*(tmp_str_ptr--) = (var32 % 10) + '0';
		var32 /= 10;
	}
	
	return size;
}

int16_t DoubleTOstring(double *dbl_val, char *str, uint8_t int_len, uint8_t frac_len, uint8_t dot)
{
	char *tmp_str_ptr;
	uint64_t tmp_ui64, ten_power;
	double tmp_dbl;
	int16_t cnt;
	int16_t str_size=0;
	
	tmp_dbl = 0.5;
	ten_power = 1;
	for (cnt=0; cnt < frac_len; cnt++)
	{
		tmp_dbl /= 10;
		ten_power *= 10;
	}

	if (*dbl_val < 0 )  // handle negative numbers
	{
		tmp_dbl = (*dbl_val * (-1)) + tmp_dbl;
		*str = '-';
		str_size++;
	}
	else tmp_dbl = *dbl_val + tmp_dbl;
	
	if (dot) str_size++;
	
	str_size += (int_len + frac_len);
	tmp_str_ptr = str + str_size - 1;
	
	tmp_ui64 = (uint64_t)((tmp_dbl - (double)((uint64_t)tmp_dbl)) * (double)ten_power);
	while (frac_len--)
	{
		*(tmp_str_ptr--) = (tmp_ui64 % 10) + '0';
		tmp_ui64 /= 10;
	}
	
	if(dot) *(tmp_str_ptr--) = '.';
	
	tmp_ui64 = (uint64_t)tmp_dbl;
	while (int_len--)
	{
		*(tmp_str_ptr--) = (tmp_ui64 % 10) + '0';
		tmp_ui64 /= 10;
	}
	
	return str_size;
}

int16_t FloatToString(float *flt_val, char *str, uint8_t int_len, uint8_t frac_len, uint8_t dot)
{
	char *tmp_str_ptr;
	uint32_t tmp_ui32, ten_power;
	float tmp_flt;
	int16_t cnt;
	int16_t str_size=0;
	
	tmp_flt = 0.5;
	ten_power = 1;
	for (cnt=0; cnt < frac_len; cnt++)
	{
		tmp_flt /= 10;
		ten_power *= 10;
	}

	if (*flt_val < 0 )  // handle negative numbers
	{
		tmp_flt = (*flt_val * (-1)) + tmp_flt;
		*str = '-';
		str_size++;
	}
	else tmp_flt = *flt_val + tmp_flt;
	
	if (dot) str_size++;
	
	str_size += (int_len + frac_len);
	tmp_str_ptr = str + str_size - 1;
	
	tmp_ui32 = (uint32_t)((tmp_flt - (float)((uint32_t)tmp_flt)) * (float)ten_power);
	while (frac_len--)
	{
		*(tmp_str_ptr--) = (tmp_ui32 % 10) + '0';
		tmp_ui32 /= 10;
	}
	
	if(dot) *(tmp_str_ptr--) = '.';
	
	tmp_ui32 = (uint32_t)tmp_flt;
	while (int_len--)
	{
		*(tmp_str_ptr--) = (tmp_ui32 % 10) + '0';
		tmp_ui32 /= 10;
	}
	
	return str_size;
}

int n_tu(int number, int count)
{
    int result = 1;
    while(count-- > 0)
        result *= number;

    return result;
}

/*
void FloatToString(float f, char r[])
{
    long long int length, length2, i, number, position, sign;
    float number2;

    sign = -1;   // -1 == positive number
    if (f < 0)
    {
        sign = '-';
        f *= -1;
    }

    number2 = f;
    number = f;
    length = 0;  // Size of decimal part
    length2 = 0; // Size of tenth

    //Calculate length2 tenth part 
    while( (number2 - (float)number) != 0.0 && !((number2 - (float)number) < 0.0) )
    {
         number2 = f * (n_tu(10.0, length2 + 1));
         number = number2;

         length2++;
    }

    // Calculate length decimal part
    for (length = (f > 1) ? 0 : 1; f > 1; length++)
        f /= 10;

    position = length;
    length = length + 1 + length2;
    number = number2;
    if (sign == '-')
    {
        length++;
        position++;
    }

    for (i = length; i >= 0 ; i--)
    {
        if (i == (length))
            r[i] = '\0';
        else if(i == (position))
            r[i] = '.';
        else if(sign == '-' && i == 0)
            r[i] = '-';
        else
        {
            r[i] = (number % 10) + '0';
            number /=10;
        }
    }
}
*/
void StringToInt(char *string, uint8_t len, int32_t *num)
{
	int32_t tmp_num  = 0;
	char *tmp_ptr = string + len - 1;
	while (((*tmp_ptr < 0x30) || (*tmp_ptr > 0x39)) && (string != tmp_ptr)) tmp_ptr--;
	
	uint32_t mult=1;
	while ((*tmp_ptr >= 0x30) && (*tmp_ptr <= 0x39))
	{
		tmp_num += (*tmp_ptr - 0x30) * mult;
		mult *= 10;
		tmp_ptr--;
	}
	
	if (*tmp_ptr == '-')
	{
		tmp_num*=-1;
	}
	
	*num = tmp_num;
}
