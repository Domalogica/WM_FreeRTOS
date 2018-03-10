#include "stm32f1xx.h"
#include "gpio.h"
#include "gpio_user.h"
#include "power_switches.h"
#include "error_handler.h"

uint8_t TRIAC_Enable(uint32_t triac_num){
	
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
			default: return (uint8_t)ERR_NOT_FOUND; 
		}
	}else return (uint8_t)ERR_INVALID_ARG;
	
	return STATUS_OK;
}
        
/*
void TRIAC_Disable(uint32_t triac_num){
	
}

uint8_t TRIAC_IsEnable(uint32_t triac_num){
	
}

void MOSFET_Enable(uint32_t triac_num){
	
}

void MOSFET_Disable(uint32_t triac_num){
	
}

uint8_t MOSFET_IsEnable(uint32_t triac_num){
	
}
*/


