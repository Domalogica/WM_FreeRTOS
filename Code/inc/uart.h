#ifndef _UART_H_
#define _UART_H_

#define APB1CLK  72000000UL
#define BAUDRATE 9600UL

void UART3_Init (void);
void USART3_Send (uint8_t chr);
void USART3_Send_String (uint8_t* str);

#endif //_UART_H_
