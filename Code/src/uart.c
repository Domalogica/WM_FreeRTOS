#include "stm32f1xx.h"
#include "gpio.h"
#include "uart.h"

void UART3_Init (void){
	
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN; //Clock source UART3 enable
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;   //Clock source port A enable 
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;   //Clock source port C enable 
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;		//Clock alternate port mode  enable
	
	GPIOC->CRH |= GPIO_CRH_CNF10_1;       //TX_PC10
	GPIOC->CRH |= GPIO_CRH_MODE10;				
	
	GPIOC->CRH |= GPIO_CRH_CNF11_0;				//RX_PC11
	GPIOC->CRH &= ~GPIO_CRH_MODE11;
	
	CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_USART3_REMAP);
  SET_BIT(AFIO->MAPR, AFIO_MAPR_USART3_REMAP_PARTIALREMAP); 
	
	USART3->BRR =(APB1CLK+BAUDRATE/2)/BAUDRATE;
	
	USART3->CR1 |= USART_CR1_TE;
	USART3->CR1 |= USART_CR1_RE;
	USART3->CR1 |= USART_CR1_UE;
	
	USART3->CR1 |= USART_CR1_RXNEIE;	
	NVIC_EnableIRQ(USART3_IRQn);
}

void USART3_Send (uint8_t chr)
{
	while (!(USART3->SR & USART_SR_TC));
	USART3->DR = chr;
}

void USART3_Send_String (uint8_t* str)
{
	uint8_t i = 0;
	
	while(str[i])	
	USART3_Send (str[i++]);
}

void USART3_IRQHandler (void){
	
	if(USART3->SR & USART_SR_RXNE)
	{
		USART3->SR &= ~USART_SR_RXNE;
		
		if(USART3->DR == '0')
		{
			USART3_Send_String ((uint8_t*)"OFF\r\n");
			GPIO_ResetOutputPin(GPIOB, GPIO_PIN_8);
		}
		
		if(USART3->DR == '1')
		{
			USART3_Send_String ((uint8_t*)"ON\r\n");
			GPIO_SetOutputPin(GPIOB, GPIO_PIN_8);
		}
	}
}
