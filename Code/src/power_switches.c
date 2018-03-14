#include "stm32f1xx.h"
#include "gpio.h"
#include "gpio_user.h"
#include "power_switches.h"
#include "error_handler.h"

void TriacPortInit(void){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; 
	
	//TRIAC gpio pin  config
	GPIO_SetPinMode (PORT_TRIAC_1, PIN_TRIAC_1, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_TRIAC_1, PIN_TRIAC_1, GPIO_MODE_OUTPUT_10MHz);
	
	GPIO_SetPinMode (PORT_TRIAC_2, PIN_TRIAC_2, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_TRIAC_2, PIN_TRIAC_2, GPIO_MODE_OUTPUT_10MHz);

	GPIO_SetPinMode (PORT_TRIAC_3, PIN_TRIAC_3, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_TRIAC_3, PIN_TRIAC_3, GPIO_MODE_OUTPUT_10MHz);
	
	GPIO_SetPinMode (PORT_TRIAC_4, PIN_TRIAC_4, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_TRIAC_4, PIN_TRIAC_4, GPIO_MODE_OUTPUT_10MHz);
	
	GPIO_SetPinMode (PORT_TRIAC_5, PIN_TRIAC_5, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_TRIAC_5, PIN_TRIAC_5, GPIO_MODE_OUTPUT_10MHz);
	
	GPIO_SetPinMode (PORT_TRIAC_6, PIN_TRIAC_6, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_TRIAC_6, PIN_TRIAC_6, GPIO_MODE_OUTPUT_10MHz);
	
	GPIO_SetPinMode (PORT_TRIAC_7, PIN_TRIAC_7, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_TRIAC_7, PIN_TRIAC_7, GPIO_MODE_OUTPUT_10MHz);
	
	GPIO_SetPinMode (PORT_TRIAC_8, PIN_TRIAC_8, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_TRIAC_8, PIN_TRIAC_8, GPIO_MODE_OUTPUT_10MHz);
	
	GPIO_SetPinMode (PORT_TRIAC_9, PIN_TRIAC_9, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_TRIAC_9, PIN_TRIAC_9, GPIO_MODE_OUTPUT_10MHz);
	
	//MOSFET gpio pin config
}

int8_t TriacEnable(uint32_t triac_num){

	if(triac_num <= 9 && triac_num >= 1){
		switch (triac_num){
			case 1: GPIO_SetOutputPin(PORT_TRIAC_1,  PIN_TRIAC_1); break;  
			case 2: GPIO_SetOutputPin(PORT_TRIAC_2,  PIN_TRIAC_2); break;
			case 3: GPIO_SetOutputPin(PORT_TRIAC_3,  PIN_TRIAC_3); break; 
			case 4: GPIO_SetOutputPin(PORT_TRIAC_4,  PIN_TRIAC_4); break; 
			case 5: GPIO_SetOutputPin(PORT_TRIAC_5,  PIN_TRIAC_5); break; 
			case 6: GPIO_SetOutputPin(PORT_TRIAC_6,  PIN_TRIAC_6); break; 
			case 7: GPIO_SetOutputPin(PORT_TRIAC_7,  PIN_TRIAC_7); break; 
			case 8: GPIO_SetOutputPin(PORT_TRIAC_8,  PIN_TRIAC_8); break; 
			case 9: GPIO_SetOutputPin(PORT_TRIAC_9,  PIN_TRIAC_9); break; 
			default: return ERR_NOT_FOUND; 
		}
	}else return ERR_INVALID_ARG;
	
	return STATUS_OK;
}

int8_t TriacDisable(uint32_t triac_num){
	
	if(triac_num <= 9 && triac_num >= 1){
		switch (triac_num){
			case 1: GPIO_ResetOutputPin(PORT_TRIAC_1,  PIN_TRIAC_1); break;  
			case 2: GPIO_ResetOutputPin(PORT_TRIAC_2,  PIN_TRIAC_2); break;
			case 3: GPIO_ResetOutputPin(PORT_TRIAC_3,  PIN_TRIAC_3); break; 
			case 4: GPIO_ResetOutputPin(PORT_TRIAC_4,  PIN_TRIAC_4); break; 
			case 5: GPIO_ResetOutputPin(PORT_TRIAC_5,  PIN_TRIAC_5); break; 
			case 6: GPIO_ResetOutputPin(PORT_TRIAC_6,  PIN_TRIAC_6); break; 
			case 7: GPIO_ResetOutputPin(PORT_TRIAC_7,  PIN_TRIAC_7); break; 
			case 8: GPIO_ResetOutputPin(PORT_TRIAC_8,  PIN_TRIAC_8); break; 
			case 9: GPIO_ResetOutputPin(PORT_TRIAC_9,  PIN_TRIAC_9); break; 
			default: return ERR_NOT_FOUND; 
		}
	}else return ERR_INVALID_ARG;
	
	return STATUS_OK;
}

/*
int8_t TRIAC_IsEnable(uint32_t triac_num){
	
}

void MOSFET_Enable(uint32_t triac_num){
	
}

void MOSFET_Disable(uint32_t triac_num){
	
}

int8_t MOSFET_IsEnable(uint32_t triac_num){
	
}
*/
