#ifndef _SPI_H_
#define _SPI_H_

#include "stm32f1xx.h"
#include "gpio.h"

#define SPI_PRESCALER_DIV2      0x00000000U                                  // BaudRate control equal to fPCLK/2   
#define SPI_PRESCALER_DIV4      (SPI_CR1_BR_0)                               // BaudRate control equal to fPCLK/4   
#define SPI_PRESCALER_DIV8      (SPI_CR1_BR_1)                               // BaudRate control equal to fPCLK/8   
#define SPI_PRESCALER_DIV16     (SPI_CR1_BR_1 | SPI_CR1_BR_0)                // BaudRate control equal to fPCLK/16  
#define SPI_PRESCALER_DIV32     (SPI_CR1_BR_2)                               // BaudRate control equal to fPCLK/32  
#define SPI_PRESCALER_DIV64     (SPI_CR1_BR_2 | SPI_CR1_BR_0)                // BaudRate control equal to fPCLK/64  
#define SPI_PRESCALER_DIV128    (SPI_CR1_BR_2 | SPI_CR1_BR_1)                // BaudRate control equal to fPCLK/128 
#define SPI_PRESCALER_DIV256    (SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0) // BaudRate control equal to fPCLK/256 

void SPI1_Init(void);
uint16_t SPI1_WriteData(uint16_t data);

void SPI2_Init(void);
uint16_t SPI2_WriteData(uint16_t data);

#endif //_SPI_H_
