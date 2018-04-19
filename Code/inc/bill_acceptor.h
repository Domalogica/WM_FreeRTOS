#ifndef _BILL_ACCEPTOR_H_
#define _BILL_ACCEPTOR_H_

#include "stm32f1xx.h"
#include "gpio.h"
#include "gpio_us.h"

typedef struct
{
	uint32_t money;
	uint32_t coin;
} BILL_data;

void BILL_PortInit(void);
BILL_data BILL_GetData(void);
void BILL_ResetData(void);

void Money_on(void);
void Money_off(void);
void Coin_off(void);
void Coin_on(void);

#endif //_BILL_ACCEPTOR_H_
