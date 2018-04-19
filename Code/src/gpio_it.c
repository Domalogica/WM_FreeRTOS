#include "gpio_it.h"

extern BILL_data money_data;
extern FML_data fml_data; 

void IRQ_Init(void)
{	
	RCC->APB2ENR |= RCC_APB2ENR_IOPGEN; 											//Enabling the clock PORT G
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; 											//Clock alternate port mode  enable

	EXTI->IMR &= ~EXTI_IMR_MR0;																//Clear bit interrupt channel FML
	EXTI->EMR &= ~EXTI_EMR_MR0; 
	EXTI->IMR &= ~EXTI_IMR_MR1;
	EXTI->EMR &= ~EXTI_EMR_MR1;
	EXTI->IMR &= ~EXTI_IMR_MR2;
	EXTI->EMR &= ~EXTI_EMR_MR2;
	EXTI->IMR &= ~EXTI_IMR_MR3;
	EXTI->EMR &= ~EXTI_EMR_MR3;
	EXTI->IMR &= ~EXTI_IMR_MR5;																//Clear bit interrupt channel BILL
	EXTI->EMR &= ~EXTI_EMR_MR5; 
	EXTI->IMR &= ~EXTI_IMR_MR7;					
	EXTI->EMR &= ~EXTI_EMR_MR7; 
	
	//Clock AFIO enable FML line																													
	MODIFY_REG(AFIO->EXTICR[GPIO_AF_EXTI_LINE0 & 0xFF], 
						(GPIO_AF_EXTI_LINE0 >> 16), GPIO_AF_EXTI_PORTG << POSITION_VAL((GPIO_AF_EXTI_LINE0 >> 16)));
	MODIFY_REG(AFIO->EXTICR[GPIO_AF_EXTI_LINE1 & 0xFF], 
						(GPIO_AF_EXTI_LINE1 >> 16), GPIO_AF_EXTI_PORTG << POSITION_VAL((GPIO_AF_EXTI_LINE1 >> 16)));
	MODIFY_REG(AFIO->EXTICR[GPIO_AF_EXTI_LINE2 & 0xFF], 
						(GPIO_AF_EXTI_LINE2 >> 16), GPIO_AF_EXTI_PORTG << POSITION_VAL((GPIO_AF_EXTI_LINE2 >> 16)));
	MODIFY_REG(AFIO->EXTICR[GPIO_AF_EXTI_LINE3 & 0xFF], 
						(GPIO_AF_EXTI_LINE3 >> 16), GPIO_AF_EXTI_PORTG << POSITION_VAL((GPIO_AF_EXTI_LINE3 >> 16)));
	//Clock AFIO enable BILL line																														
	MODIFY_REG(AFIO->EXTICR[GPIO_AF_EXTI_LINE5 & 0xFF], 
						(GPIO_AF_EXTI_LINE5 >> 16), GPIO_AF_EXTI_PORTG << POSITION_VAL((GPIO_AF_EXTI_LINE5 >> 16)));
	MODIFY_REG(AFIO->EXTICR[GPIO_AF_EXTI_LINE7 & 0xFF], 
						(GPIO_AF_EXTI_LINE7 >> 16), GPIO_AF_EXTI_PORTG << POSITION_VAL((GPIO_AF_EXTI_LINE7 >> 16)));

	//AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0_PA;
	//AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA;
	
	//EXTI->RTSR |= EXTI_RTSR_TR0; 														//Example rising mode

	EXTI->FTSR |= EXTI_FTSR_TR0;    													//Faling mode FML line
	EXTI->FTSR |= EXTI_FTSR_TR1;
	EXTI->FTSR |= EXTI_FTSR_TR2;
	EXTI->FTSR |= EXTI_FTSR_TR3;
	EXTI->FTSR |= EXTI_FTSR_TR5;    													//Faling mode	BILL line
	EXTI->FTSR |= EXTI_FTSR_TR7;    			
															
	EXTI->IMR |= EXTI_IMR_MR0;																//Allow interrupt generation from the FML line
	EXTI->IMR |= EXTI_IMR_MR1;
	EXTI->IMR |= EXTI_IMR_MR2;
	EXTI->IMR |= EXTI_IMR_MR3;
	EXTI->IMR |= EXTI_IMR_MR5;																//Allow interrupt generation from the BILL line
	EXTI->IMR |= EXTI_IMR_MR7;	
	
	GPIO_SetPinMode(GPIOG, GPIO_PIN_5,  GPIO_MODE_FLOATING); 	//GPIO in float mode (Data money)
	GPIO_SetPinMode(GPIOG, GPIO_PIN_7,  GPIO_MODE_FLOATING); 	//GPIO in float mode (Data coin)
	GPIO_SetPinMode(GPIOG, GPIO_PIN_0,  GPIO_MODE_FLOATING); 	//GPIO in float mode FML_1
	GPIO_SetPinMode(GPIOG, GPIO_PIN_1,  GPIO_MODE_FLOATING);	//GPIO in float mode FML_2
	GPIO_SetPinMode(GPIOG, GPIO_PIN_2,  GPIO_MODE_FLOATING);	//GPIO in float mode FML_3
	GPIO_SetPinMode(GPIOG, GPIO_PIN_3,  GPIO_MODE_FLOATING);	//GPIO in float mode FML_4

	NVIC_EnableIRQ(EXTI0_IRQn); 	//Enable IRQ 
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	//NVIC_EnableIRQ(EXTI4_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	//NVIC_EnableIRQ(EXTI15_10_IRQn);
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

void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & EXTI_IMR_MR5)
	{
		money_data.money ++;
		EXTI->PR = EXTI_IMR_MR5;
	}
	
	if(EXTI->PR & EXTI_IMR_MR7)
	{
		money_data.coin++; 
		EXTI->PR = EXTI_IMR_MR5;
	}
}


