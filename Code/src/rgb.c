#include "rgb.h"

int8_t RGB_ColorSet (uint8_t color)
{
	switch (color){
		case 1: ULN_Enable (LED_GREEN_POS); 
						ULN_Disable(LED_BLUE_POS); 
						ULN_Disable(LED_RED_POS);
						break;
		case 2: ULN_Disable(LED_GREEN_POS); 
						ULN_Disable(LED_BLUE_POS); 
						ULN_Enable (LED_RED_POS);
						break;  
		case 3: ULN_Disable(LED_GREEN_POS); 
						ULN_Enable (LED_BLUE_POS); 
						ULN_Disable(LED_RED_POS);
						break;  
		case 4: ULN_Enable (LED_GREEN_POS); 
						ULN_Disable(LED_BLUE_POS); 
						ULN_Enable (LED_RED_POS);
						break;  
		case 5: ULN_Disable(LED_GREEN_POS); 
						ULN_Enable (LED_BLUE_POS); 
						ULN_Enable (LED_RED_POS);
						break;  
		case 6: ULN_Enable (LED_GREEN_POS); 
						ULN_Enable (LED_BLUE_POS); 
						ULN_Disable(LED_RED_POS);
						break;  
		case 7: ULN_Enable (LED_GREEN_POS); 
						ULN_Enable (LED_BLUE_POS); 
						ULN_Enable (LED_RED_POS);
						break;  
		case 8: ULN_Disable(LED_GREEN_POS); 
						ULN_Disable(LED_BLUE_POS); 
						ULN_Disable(LED_RED_POS);
						break;  						
		default: return ERR_NOT_FOUND; 
	}
	return STATUS_OK;
}
