#ifndef _UART_H_
#define _UART_H_

#include "stm32f1xx.h"
#include "gpio.h"

#define APB1CLK  72000000UL
#define BAUDRATE 9600UL

void UART1_Init (void);
void USART1_Send (uint8_t chr);
void USART1_Send_String (uint8_t* str);

void UART2_Init (void);
void USART2_Send (uint8_t chr);
void USART2_Send_String (uint8_t* str);

void UART3_Init (void);
void USART3_Send (uint8_t chr);
void USART3_Send_String (uint8_t* str);

#endif //_UART_H_
