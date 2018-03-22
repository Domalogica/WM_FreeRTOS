#include "power_switches.h"

void TRIAC_PortInit(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; //Enabling the clock PORT D
	
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
}

int8_t TRIAC_Enable(uint32_t triac_num)
{
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
		default: return ERR_INVALID_ARG; 
	}
	return STATUS_OK;
}

int8_t TRIAC_Disable(uint32_t triac_num)
{
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
	return STATUS_OK;
}

void MOSFET_PortInit(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPFEN; //Enabling the clock PORT F
	
	GPIO_SetPinMode (PORT_MOSFET_1, PIN_MOSFET_1, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_MOSFET_1, PIN_MOSFET_1, GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_MOSFET_2, PIN_MOSFET_2, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_MOSFET_2, PIN_MOSFET_2, GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_MOSFET_3, PIN_MOSFET_3, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_MOSFET_3, PIN_MOSFET_3, GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_MOSFET_4, PIN_MOSFET_4, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_MOSFET_4, PIN_MOSFET_4, GPIO_MODE_OUTPUT_10MHz);
}

int8_t MOSFET_Enable(uint32_t mosfet_num)
{
	switch (mosfet_num){
		case 1: GPIO_SetOutputPin(PORT_MOSFET_1,  PIN_MOSFET_1); break;  
		case 2: GPIO_SetOutputPin(PORT_MOSFET_2,  PIN_MOSFET_2); break;
		case 3: GPIO_SetOutputPin(PORT_MOSFET_3,  PIN_MOSFET_3); break; 
		case 4: GPIO_SetOutputPin(PORT_MOSFET_4,  PIN_MOSFET_4); break; 
		default: return ERR_NOT_FOUND; 
	}
	return STATUS_OK;
}

int8_t MOSFET_Disable(uint32_t mosfet_num)
{
	switch (mosfet_num){
		case 1: GPIO_ResetOutputPin(PORT_MOSFET_1,  PIN_MOSFET_1); break;  
		case 2: GPIO_ResetOutputPin(PORT_MOSFET_2,  PIN_MOSFET_2); break;
		case 3: GPIO_ResetOutputPin(PORT_MOSFET_3,  PIN_MOSFET_3); break; 
		case 4: GPIO_ResetOutputPin(PORT_MOSFET_4,  PIN_MOSFET_4); break; 
		default: return ERR_NOT_FOUND; 
	}
	return STATUS_OK;
}

void ULN_PortInit(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPEEN; //Enabling the clock PORT E
	RCC->APB2ENR |= RCC_APB2ENR_IOPGEN; //Enabling the clock PORT G
	//ULN 1
	GPIO_SetPinMode (PORT_ULN_CH_1,  PIN_ULN_CH_1,  GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_ULN_CH_1,  PIN_ULN_CH_1,  GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_ULN_CH_2,  PIN_ULN_CH_2,  GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_ULN_CH_2,  PIN_ULN_CH_2,  GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_ULN_CH_3,  PIN_ULN_CH_3,  GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_ULN_CH_3,  PIN_ULN_CH_3,  GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_ULN_CH_4,  PIN_ULN_CH_4,  GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_ULN_CH_4,  PIN_ULN_CH_4,  GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_ULN_CH_5,  PIN_ULN_CH_5,  GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_ULN_CH_5,  PIN_ULN_CH_5,  GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_ULN_CH_6,  PIN_ULN_CH_6,  GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_ULN_CH_6,  PIN_ULN_CH_6,  GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_ULN_CH_7,  PIN_ULN_CH_7,  GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_ULN_CH_7,  PIN_ULN_CH_7,  GPIO_MODE_OUTPUT_10MHz);
	//ULN 2
	GPIO_SetPinMode (PORT_ULN_CH_8,  PIN_ULN_CH_8,  GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_ULN_CH_8,  PIN_ULN_CH_8,  GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_ULN_CH_9,  PIN_ULN_CH_9,  GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_ULN_CH_9,  PIN_ULN_CH_9,  GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_ULN_CH_10, PIN_ULN_CH_10, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_ULN_CH_10, PIN_ULN_CH_10, GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_ULN_CH_11, PIN_ULN_CH_11, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_ULN_CH_11, PIN_ULN_CH_11, GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_ULN_CH_12, PIN_ULN_CH_12, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_ULN_CH_12, PIN_ULN_CH_12, GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_ULN_CH_13, PIN_ULN_CH_13, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_ULN_CH_13, PIN_ULN_CH_13, GPIO_MODE_OUTPUT_10MHz);
	GPIO_SetPinMode (PORT_ULN_CH_14, PIN_ULN_CH_14, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(PORT_ULN_CH_14, PIN_ULN_CH_14, GPIO_MODE_OUTPUT_10MHz);
}

int8_t ULN_Enable(uint32_t uln_num)
{
	switch (uln_num){
		case 1:  GPIO_SetOutputPin(PORT_ULN_CH_1,  PIN_ULN_CH_1);  break;  
		case 2:  GPIO_SetOutputPin(PORT_ULN_CH_2,  PIN_ULN_CH_2);  break;
		case 3:  GPIO_SetOutputPin(PORT_ULN_CH_3,  PIN_ULN_CH_3);  break; 
		case 4:  GPIO_SetOutputPin(PORT_ULN_CH_4,  PIN_ULN_CH_4);  break; 
		case 5:  GPIO_SetOutputPin(PORT_ULN_CH_5,  PIN_ULN_CH_5);  break;  
		case 6:  GPIO_SetOutputPin(PORT_ULN_CH_6,  PIN_ULN_CH_6);  break;
		case 7:  GPIO_SetOutputPin(PORT_ULN_CH_7,  PIN_ULN_CH_7);  break; 
		case 8:  GPIO_SetOutputPin(PORT_ULN_CH_8,  PIN_ULN_CH_8);  break; 
		case 9:  GPIO_SetOutputPin(PORT_ULN_CH_9,  PIN_ULN_CH_9);  break;  
		case 10: GPIO_SetOutputPin(PORT_ULN_CH_10, PIN_ULN_CH_10); break;
		case 11: GPIO_SetOutputPin(PORT_ULN_CH_11, PIN_ULN_CH_11); break; 
		case 12: GPIO_SetOutputPin(PORT_ULN_CH_12, PIN_ULN_CH_12); break; 
		case 13: GPIO_SetOutputPin(PORT_ULN_CH_13, PIN_ULN_CH_13); break; 
		case 14: GPIO_SetOutputPin(PORT_ULN_CH_14, PIN_ULN_CH_14); break; 
		default: return ERR_NOT_FOUND; 
	}
	return STATUS_OK;
}

int8_t ULN_Disable(uint32_t uln_num)
{
	switch (uln_num){
		case 1:  GPIO_ResetOutputPin(PORT_ULN_CH_1,  PIN_ULN_CH_1);  break;  
		case 2:  GPIO_ResetOutputPin(PORT_ULN_CH_2,  PIN_ULN_CH_2);  break;
		case 3:  GPIO_ResetOutputPin(PORT_ULN_CH_3,  PIN_ULN_CH_3);  break; 
		case 4:  GPIO_ResetOutputPin(PORT_ULN_CH_4,  PIN_ULN_CH_4);  break; 
		case 5:  GPIO_ResetOutputPin(PORT_ULN_CH_5,  PIN_ULN_CH_5);  break;  
		case 6:  GPIO_ResetOutputPin(PORT_ULN_CH_6,  PIN_ULN_CH_6);  break;
		case 7:  GPIO_ResetOutputPin(PORT_ULN_CH_7,  PIN_ULN_CH_7);  break; 
		case 8:  GPIO_ResetOutputPin(PORT_ULN_CH_8,  PIN_ULN_CH_8);  break; 
		case 9:  GPIO_ResetOutputPin(PORT_ULN_CH_9,  PIN_ULN_CH_9);  break;  
		case 10: GPIO_ResetOutputPin(PORT_ULN_CH_10, PIN_ULN_CH_10); break;
		case 11: GPIO_ResetOutputPin(PORT_ULN_CH_11, PIN_ULN_CH_11); break; 
		case 12: GPIO_ResetOutputPin(PORT_ULN_CH_12, PIN_ULN_CH_12); break; 
		case 13: GPIO_ResetOutputPin(PORT_ULN_CH_13, PIN_ULN_CH_13); break; 
		case 14: GPIO_ResetOutputPin(PORT_ULN_CH_14, PIN_ULN_CH_14); break; 
		default: return ERR_NOT_FOUND; 
	}
	return STATUS_OK;
}
