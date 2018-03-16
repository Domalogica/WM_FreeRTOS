#ifndef _LCD_DISPLAY_H_
#define _LCD_DISPLAY_H_

#define BISY_TIME       3000 //TODO: set min bisy time

#define LCD_RS_PIN			GPIO_PIN_5
#define LCD_EN_PIN			GPIO_PIN_4
#define LCD_DB4_PIN			GPIO_PIN_0
#define LCD_DB5_PIN			GPIO_PIN_1	
#define LCD_DB6_PIN			GPIO_PIN_2	
#define LCD_DB7_PIN			GPIO_PIN_3	
#define LCD_DATA_PORT		GPIOE

#define LCD_LIGHT_PIN		GPIO_PIN_12
#define LCD_LIGHT_PORT	GPIOB

void LCD_Clear (void);
void LCD_Init  (void);
void LCD_SendCommand (uint8_t command);
void LCD_SendChar 	 (uint8_t data);
void LCD_SendString  (uint8_t *str, uint8_t size);
void LCD_SetCursor 	 (uint8_t row, uint8_t col);
void LCD_LightON (void);
void LCD_LightOff (void);
uint8_t LCD_GetRusChar(uint8_t num);

#endif //_LCD_DISPLAY_H_
