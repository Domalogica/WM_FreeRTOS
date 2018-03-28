#include "fml.h"

FML_data fml_data; 

void GPIO_FLM_InitIT(void)
{
	//Port clock setting 
	RCC->APB2ENR |= RCC_APB2ENR_IOPGEN; //Enabling the clock PORT G
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; //Enabling the clock PORT A
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; //Clock alternate port mode  enable
	
	EXTI->IMR &= ~EXTI_IMR_MR0;					//Clear bit interrupt channel 
	EXTI->EMR &= ~EXTI_EMR_MR0; 
	
	EXTI->IMR &= ~EXTI_IMR_MR1;
	EXTI->EMR &= ~EXTI_EMR_MR1;
	
	EXTI->IMR &= ~EXTI_IMR_MR2;
	EXTI->EMR &= ~EXTI_EMR_MR2;
	
	EXTI->IMR &= ~EXTI_IMR_MR3;
	EXTI->EMR &= ~EXTI_EMR_MR3;
	
	//Clock AFIO enable
	MODIFY_REG(AFIO->EXTICR[GPIO_AF_EXTI_LINE0 & 0xFF], 
						(GPIO_AF_EXTI_LINE0 >> 16), GPIO_AF_EXTI_PORTG << POSITION_VAL((GPIO_AF_EXTI_LINE0 >> 16)));
	MODIFY_REG(AFIO->EXTICR[GPIO_AF_EXTI_LINE1 & 0xFF], 
						(GPIO_AF_EXTI_LINE1 >> 16), GPIO_AF_EXTI_PORTG << POSITION_VAL((GPIO_AF_EXTI_LINE1 >> 16)));
	MODIFY_REG(AFIO->EXTICR[GPIO_AF_EXTI_LINE2 & 0xFF], 
						(GPIO_AF_EXTI_LINE2 >> 16), GPIO_AF_EXTI_PORTG << POSITION_VAL((GPIO_AF_EXTI_LINE2 >> 16)));
	MODIFY_REG(AFIO->EXTICR[GPIO_AF_EXTI_LINE3 & 0xFF], 
						(GPIO_AF_EXTI_LINE3 >> 16), GPIO_AF_EXTI_PORTG << POSITION_VAL((GPIO_AF_EXTI_LINE3 >> 16)));

	//AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0_PA;
	//AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA;

	// EXTI->RTSR |= EXTI_RTSR_TR0; //Rising mode
	// EXTI->RTSR |= EXTI_RTSR_TR1;
	// EXTI->RTSR |= EXTI_RTSR_TR2;
	// EXTI->RTSR |= EXTI_RTSR_TR3;

	EXTI->FTSR |= EXTI_FTSR_TR0;    //Faling mode
	EXTI->FTSR |= EXTI_FTSR_TR1;
	EXTI->FTSR |= EXTI_FTSR_TR2;
	EXTI->FTSR |= EXTI_FTSR_TR3;
	
	EXTI->IMR |= EXTI_IMR_MR0;			//Allow interrupt generation from the selected line
	EXTI->IMR |= EXTI_IMR_MR1;
	EXTI->IMR |= EXTI_IMR_MR2;
	EXTI->IMR |= EXTI_IMR_MR3;
	
	GPIO_SetPinMode(GPIOG, GPIO_PIN_0, GPIO_MODE_FLOATING); //GPIO in float mode
	GPIO_SetPinMode(GPIOG, GPIO_PIN_1, GPIO_MODE_FLOATING);
	GPIO_SetPinMode(GPIOG, GPIO_PIN_2, GPIO_MODE_FLOATING);
	GPIO_SetPinMode(GPIOG, GPIO_PIN_3, GPIO_MODE_FLOATING);

	NVIC_EnableIRQ(EXTI0_IRQn); 	//Enable IRQ 
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
}

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

void EXTI0_IRQHandler(void)
{
	if(EXTI->PR & EXTI_IMR_MR0)
	{
		fml_data.FML1++;
		EXTI->PR = EXTI_IMR_MR0;
	}
}

void EXTI1_IRQHandler(void)
{
	if(EXTI->PR & EXTI_IMR_MR1)
	{
		fml_data.FML2++;
		EXTI->PR = EXTI_IMR_MR1;
	}
}

void EXTI2_IRQHandler(void)
{
  if(EXTI->PR & EXTI_IMR_MR2)
	{
		fml_data.FML3++; 
		EXTI->PR = EXTI_IMR_MR2;
	}
}

void EXTI3_IRQHandler(void)
{
	if(EXTI->PR & EXTI_IMR_MR3)
	{
		fml_data.FML4++; 
		EXTI->PR = EXTI_IMR_MR3;
	}
}
