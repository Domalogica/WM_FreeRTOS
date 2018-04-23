#include "uart.h"
#include "power_switch.h"

void UART1_Init (void)
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;	//Clock source UART1 enable
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;		//Clock source port C enable
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;		//Clock alternate port mode  enable
	
	GPIOA->CRH |= GPIO_CRH_CNF9_1;        	//TX_PA9
	GPIOA->CRH |= GPIO_CRH_MODE9;				
	
	GPIOA->CRH |= GPIO_CRH_CNF10_0;			//RX_PA10
	GPIOA->CRH &= ~GPIO_CRH_MODE10;
	
	//CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_USART3_REMAP);
	//SET_BIT(AFIO->MAPR, AFIO_MAPR_USART3_REMAP_PARTIALREMAP);
	
	USART1->BRR =(APB1CLK+BAUDRATE/2)/BAUDRATE;
	
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_RE;
	USART1->CR1 |= USART_CR1_UE;
	
	USART1->CR1 |= USART_CR1_RXNEIE;	
	NVIC_EnableIRQ(USART1_IRQn);
}

void UART2_Init (void)
{
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;		//Clock source UART2 enable
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;   		//Clock source port C enable
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;			//Clock alternate port mode  enable
	
	GPIOC->CRH |= GPIO_CRL_CNF5_1;        		//TX_PD5
	GPIOC->CRH |= GPIO_CRL_MODE5;				
	
	GPIOC->CRH |= GPIO_CRL_CNF6_0;				//RX_PD6
	GPIOC->CRH &= ~GPIO_CRL_MODE6;
	
	CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_USART2_REMAP);	
	SET_BIT(AFIO->MAPR, AFIO_MAPR_USART2_REMAP);
	 
	USART2->BRR =(APB1CLK+BAUDRATE/2)/BAUDRATE;
	
	USART2->CR1 |= USART_CR1_TE;
	USART2->CR1 |= USART_CR1_RE;
	USART2->CR1 |= USART_CR1_UE;
	
	USART2->CR1 |= USART_CR1_RXNEIE;	
	NVIC_EnableIRQ(USART2_IRQn);
}

void UART3_Init (void)
{
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN; 	//Clock source UART3 enable
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;   	//Clock source port C enable
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;		//Clock alternate port mode  enable
	
	GPIOC->CRH |= GPIO_CRH_CNF10_1;       	//TX_PC10
	GPIOC->CRH |= GPIO_CRH_MODE10;				
	
	GPIOC->CRH |= GPIO_CRH_CNF11_0;			//RX_PC11
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

void USART1_Send (uint8_t chr)
{
	while (!(USART1->SR & USART_SR_TC));
	USART1->DR = chr;
}

void USART1_Send_String (uint8_t* str)
{
	uint8_t i = 0;

	while(str[i])	
	USART1_Send (str[i++]);
}

void USART2_Send (uint8_t chr)
{
	while (!(USART2->SR & USART_SR_TC));
	USART2->DR = chr;
}

void USART2_Send_String (uint8_t* str)
{
	uint8_t i = 0;
	
	while(str[i])	
	USART2_Send (str[i++]);
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

void USART1_IRQHandler (void)
{
	if(USART1->SR & USART_SR_RXNE)
	{
		USART1->SR &= ~USART_SR_RXNE;			//Clear IRQ flag
		//USART1->DR receive data
		//Example if(USART1->DR == '0') actions
		//        if(USART1->DR == '1') actions
	}
}

void USART2_IRQHandler (void)
{
	if(USART2->SR & USART_SR_RXNE)
	{
		USART2->SR &= ~USART_SR_RXNE;			//Clear IRQ flag
		//USART3->DR receive data
		//Example if(USART2->DR == '0') actions
		//        if(USART2->DR == '1') actions
	}
}

void USART3_IRQHandler (void)
{
	if(USART3->SR & USART_SR_RXNE)
	{
		USART3->SR &= ~USART_SR_RXNE;			//Clear IRQ flag
		//USART3->DR receive data
		//Example if(USART3->DR == '0') actions
		//        if(USART3->DR == '1') actions
	}
}
