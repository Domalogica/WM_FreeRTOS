#include "spi.h"

void SPI1_Init(void)
{
	RCC->APB2ENR  |= RCC_APB2ENR_IOPBEN;		//Clock source port B enable 
	RCC->APB2ENR  |= RCC_APB2ENR_AFIOEN;   	//Clock alternate port mode  enable

	/*SPI1 GPIO Configuration  
  PB3   ------> SPI1_SCK
  PB4   ------> SPI1_MISO
  PB5   ------> SPI1_MOSI */

	GPIOB->CRL &= ~(GPIO_CRL_CNF3_0 | GPIO_CRL_CNF5_0);  //Port configuration
	GPIOB->CRL |= GPIO_CRL_CNF3_1   | GPIO_CRL_CNF5_1;  	
	GPIOB->CRL |= GPIO_CRL_MODE3_1  |	GPIO_CRL_MODE5_1;	

	AFIO->MAPR |= AFIO_MAPR_SPI1_REMAP;			//Port remaping
	
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;     //Clock source SPI1 enable
	
	SPI1->CR1 |= SPI_PRESCALER_DIV32;       //Baud rate
	SPI1->CR1 &= ~SPI_CR1_CPOL;             //Polarity cls signal CPOL = 0;
	SPI1->CR1 &= ~SPI_CR1_CPHA;             //Phase cls signal    CPHA = 0;
	SPI1->CR1 |= SPI_CR1_DFF;               //16 bit data
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;         //MSB will be first
	SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI; //Software slave management & Internal slave select

	SPI1->CR1 |= SPI_CR1_MSTR;              //Mode Master
	SPI1->CR1 |= SPI_CR1_SPE;               //Enable SPI1 
}

void SPI2_Init(void)
{
	RCC->APB2ENR  |= RCC_APB2ENR_IOPBEN;		//Clock source port B enable 
	RCC->APB2ENR  |= RCC_APB2ENR_AFIOEN;  	//Clock alternate port mode  enable

	/*SPI2 GPIO Configuration  
  PB13   ------> SPI2_SCK
  PB14   ------> SPI2_MISO
  PB15   ------> SPI2_MOSI */	
	
	GPIOB->CRH &= ~(GPIO_CRH_CNF13_0 | GPIO_CRH_CNF15_0);  //Port configuration
	GPIOB->CRH |= GPIO_CRH_CNF13_1 | GPIO_CRH_CNF15_1;  	
	GPIOB->CRH |= GPIO_CRH_MODE13_1 |	GPIO_CRH_MODE15_1;
	GPIOB->CRH |= GPIO_CRH_CNF14_0;				
	GPIOB->CRH &= ~GPIO_CRH_MODE14;
	
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;     //Clock source SPI2 enable
	
	SPI2->CR1 |= SPI_PRESCALER_DIV32;       //Baud rate
	SPI2->CR1 &= ~SPI_CR1_CPOL;             //Polarity cls signal CPOL = 0;
	SPI2->CR1 &= ~SPI_CR1_CPHA;             //Phase cls signal    CPHA = 0;
	SPI2->CR1 |= SPI_CR1_DFF;               //16 bit data
	SPI2->CR1 &= ~SPI_CR1_LSBFIRST;         //MSB will be first
	SPI2->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI; //Software slave management & Internal slave select

	SPI2->CR1 |= SPI_CR1_MSTR;              //Mode Master
	SPI2->CR1 |= SPI_CR1_SPE;               //Enable SPI2
}

uint16_t SPI1_WriteData(uint16_t data)
{
	while(!(SPI1->SR & SPI_SR_TXE));
	//CS_ON
	SPI1->DR = data;  											//Send data
	while(!(SPI1->SR & SPI_SR_RXNE));				//Waiting for an answer
	data = SPI1->DR;  											//Recive data
	//CS_OFF
	return data;
}

uint16_t SPI2_WriteData(uint16_t data)
{
	while(!(SPI2->SR & SPI_SR_TXE));
	//CS_ON
	SPI2->DR = data;  											//Send data
	while(!(SPI2->SR & SPI_SR_RXNE));				//Waiting for an answer
	data = SPI2->DR;  											//Recive data
	//CS_OFF
	return data;
}
