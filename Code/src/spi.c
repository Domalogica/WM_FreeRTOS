#include "spi.h"


#define		 CS_LOW 	GPIOB->BSRR = GPIO_BSRR_BR10;
#define 	 CS_HIGH 	GPIOB->BSRR = GPIO_BSRR_BS10;

void Spi_Init(void)
{
//включаем тактирование порта B и альтернативных функций 
	RCC->APB2ENR  |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;   
	
//13(SCK) и 15(MOSI) вывод - альтернативная функция  push pull, 14(MISO) вывод - Input floating, 10(CS) вывод - выход, push-pull
	GPIOB->CRH &= ~(GPIO_CRH_CNF13_0 | GPIO_CRH_CNF15_0 | GPIO_CRH_CNF10_0);  
	GPIOB->CRH |= GPIO_CRH_CNF13_1 | GPIO_CRH_CNF15_1;  	
	GPIOB->CRH |= GPIO_CRH_MODE10_0 | GPIO_CRH_MODE13_1 |	GPIO_CRH_MODE15_1;

//включаем тактирование SPI2
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;   
	
        SPI2->CR1 |= SPI_CR1_BR;                //Baud rate = Fpclk/256
        SPI2->CR1 &= ~SPI_CR1_CPOL;             //Polarity cls signal CPOL = 0;
        SPI2->CR1 &= ~SPI_CR1_CPHA;             //Phase cls signal    CPHA = 0;
        SPI2->CR1 |= SPI_CR1_DFF;               //16 bit data
        SPI2->CR1 &= ~SPI_CR1_LSBFIRST;         //MSB will be first
        SPI2->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;  //Software slave management & Internal slave select
	
        SPI2->CR1 |= SPI_CR1_MSTR;              //Mode Master
        SPI2->CR1 |= SPI_CR1_SPE;                //Enable SPI2
}

uint16_t Spi_Write_Data(uint16_t data)
{
        //ждём пока опустошится Tx буфер
	while(!(SPI2->SR & SPI_SR_TXE));
	//активируем Chip Select
	CS_LOW   
        //отправляем данные     
	SPI2->DR = data;  

        //ждём пока придёт ответ
	while(!(SPI2->SR & SPI_SR_RXNE));
        //считываем полученные данные
	data = SPI2->DR;  
	//деактивируем Chip Select
	CS_HIGH   
        //возвращаем то, что прочитали
       return data;  
}