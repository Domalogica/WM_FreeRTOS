#include "bill_acceptor.h"

BILL_data money_data;

void BILL_PortInit(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPGEN; //Enabling the clock PORT F
	
	GPIO_SetPinMode (GPIOG, GPIO_PIN_4, GPIO_MODE_OUTPUT);					//Inhibit money output mode
	GPIO_SetPinSpeed(GPIOG, GPIO_PIN_4, GPIO_MODE_OUTPUT_10MHz);

	GPIO_SetPinMode (GPIOG, GPIO_PIN_6, GPIO_MODE_OUTPUT);					//Inhibit coin output mode
	GPIO_SetPinSpeed(GPIOG, GPIO_PIN_6, GPIO_MODE_OUTPUT_10MHz);
}

void Money_off(void)
{
	GPIO_ResetOutputPin(GPIOG, GPIO_PIN_4); 
}

void Money_on(void)
{
	GPIO_SetOutputPin(GPIOG, GPIO_PIN_4); 
}

void Coin_off(void)
{
	GPIO_ResetOutputPin(GPIOG, GPIO_PIN_6); 
}

void Coin_on(void)
{
	GPIO_SetOutputPin(GPIOG, GPIO_PIN_6); 
}

BILL_data BILL_GetData(void)
{
	return 	money_data; 
}

void BILL_ResetData(void)
{	
	money_data.coin = 0; 
	money_data.money = 0; 
} 
