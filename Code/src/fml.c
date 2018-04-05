#include "fml.h"

FML_data fml_data; 

FML_data FLM_GetData(void)
{
	return 	fml_data; 
}

void FLM_ResetData(void)
{	
	fml_data.FML1 = 0; 
	fml_data.FML2 = 0; 
	fml_data.FML3 = 0;
	fml_data.FML4 = 0;
} 

uint32_t FLM_GetTic(uint8_t fml_num)
{
	return 	(fml_num == 1) ? fml_data.FML1 : 
					(fml_num == 2) ? fml_data.FML2 : 
					(fml_num == 3) ? fml_data.FML3 :
					(fml_num == 4) ? fml_data.FML4 : 0x00;
}

void FLM_ResetTic(uint8_t fml_num)
{	
	switch (fml_num){
		case 1:  fml_data.FML1 = 0; break;  
		case 2:  fml_data.FML2 = 0; break;
		case 3:  fml_data.FML3 = 0; break;
		case 4:  fml_data.FML4 = 0; break;
		default: break;
	}
} 

