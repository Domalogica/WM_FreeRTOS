#include "stm32f1xx.h"
#include "gpio.h"
#include "lcd_display.h"

void RS_GPIO_SET   (void);
void RS_GPIO_RESET (void);
void EN_GPIO_SET   (void); 
void EN_GPIO_RESET (void); 
void DB4_GPIO_SET  (void); 
void DB4_GPIO_RESET(void); 
void DB5_GPIO_SET  (void);
void DB5_GPIO_RESET(void); 
void DB6_GPIO_SET  (void); 
void DB6_GPIO_RESET(void); 
void DB7_GPIO_SET  (void); 
void DB7_GPIO_RESET(void); 
void Delay(uint32_t count);

void LCD_Send(uint8_t buf)
{
	if ( (buf & 0x01) == 1) DB4_GPIO_SET(); 
  else DB4_GPIO_RESET();
	
	if ( ((buf >> 1) & 0x01) == 1) DB5_GPIO_SET();
  else DB5_GPIO_RESET();
	
	if ( ((buf >> 2) & 0x01) == 1) DB6_GPIO_SET(); 
  else DB6_GPIO_RESET();
	
	if ( ((buf >> 3) & 0x01) == 1) DB7_GPIO_SET();
	else DB7_GPIO_RESET();
}

void LCD_SendCommand (uint8_t command)
{
	RS_GPIO_RESET();
	LCD_Send(command>>4);
	EN_GPIO_SET();
	Delay(BISY_TIME);
	EN_GPIO_RESET();
	LCD_Send(command);
	EN_GPIO_SET();
	Delay(BISY_TIME);
	EN_GPIO_RESET();
	Delay(BISY_TIME);
}

void LCD_SendChar (uint8_t data)
{
	RS_GPIO_SET();
	LCD_Send(data>>4);
	EN_GPIO_SET();
	Delay(BISY_TIME);
	
	EN_GPIO_RESET();;
	LCD_Send(data);
	EN_GPIO_SET();
	Delay(BISY_TIME);
	
	EN_GPIO_RESET();;
	Delay(BISY_TIME);
}

void LCD_SendString (uint8_t *str, uint8_t size)
{
	for (int8_t i = 0; i < size; i++) 
	{
		LCD_SendChar(str[i]);
	}
}

void LCD_SetCursor (uint8_t row, uint8_t col)
{
	uint8_t cursor_pos = 0x80;
	
	if (row == 2) 
	{
		cursor_pos |= 0x40;
	} else 
	{ 
		cursor_pos |= 0x00;
	}

	if (col < 16) 
	{
		cursor_pos |= col;
	} else 
	{ 
		cursor_pos |= 0x00;
	}
	
	LCD_SendCommand(cursor_pos);
}

void LCD_Clear (void)
{
	LCD_SendCommand (0x01); 
	Delay(BISY_TIME);
}

void LCD_Init (void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPEEN; //Enabling the clock PORT E
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; //Enabling the clock PORT B

	GPIO_SetPinMode (LCD_DATA_PORT, LCD_RS_PIN, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(LCD_DATA_PORT, LCD_RS_PIN, GPIO_MODE_OUTPUT_10MHz);

	GPIO_SetPinMode (LCD_DATA_PORT, LCD_EN_PIN, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(LCD_DATA_PORT, LCD_EN_PIN, GPIO_MODE_OUTPUT_10MHz);

	GPIO_SetPinMode (LCD_DATA_PORT, LCD_DB4_PIN, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(LCD_DATA_PORT, LCD_DB4_PIN, GPIO_MODE_OUTPUT_10MHz);

	GPIO_SetPinMode (LCD_DATA_PORT, LCD_DB5_PIN, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(LCD_DATA_PORT, LCD_DB5_PIN, GPIO_MODE_OUTPUT_10MHz);

	GPIO_SetPinMode (LCD_DATA_PORT, LCD_DB6_PIN, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(LCD_DATA_PORT, LCD_DB6_PIN, GPIO_MODE_OUTPUT_10MHz);

	GPIO_SetPinMode (LCD_DATA_PORT, LCD_DB7_PIN, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(LCD_DATA_PORT, LCD_DB7_PIN, GPIO_MODE_OUTPUT_10MHz);

	GPIO_SetPinMode (LCD_LIGHT_PORT, LCD_LIGHT_PIN, GPIO_MODE_OUTPUT);
	GPIO_SetPinSpeed(LCD_LIGHT_PORT, LCD_LIGHT_PIN, GPIO_MODE_OUTPUT_10MHz);

	RS_GPIO_RESET (); 
	EN_GPIO_RESET ();
	DB4_GPIO_RESET(); 
	DB5_GPIO_RESET();
	DB6_GPIO_RESET(); 
	DB7_GPIO_RESET(); 
	LCD_LightON();
	
	//Display init command
	Delay(BISY_TIME);
	EN_GPIO_RESET();
	
	LCD_Send(0x03);		
	EN_GPIO_SET();
	Delay(BISY_TIME);
	
	EN_GPIO_RESET();
	Delay(BISY_TIME);
	
	LCD_Send(0x03);		
	EN_GPIO_SET();	
	Delay(BISY_TIME);
	
	EN_GPIO_RESET(); 	
	Delay(BISY_TIME);
	LCD_Send(0x03);	
	
	EN_GPIO_SET(); 
	Delay(BISY_TIME);
	
	EN_GPIO_RESET();	
	Delay(BISY_TIME);

	LCD_Send(0x02);
	EN_GPIO_SET (); 	
	Delay(BISY_TIME);
	
	EN_GPIO_RESET(); 
	Delay(BISY_TIME);

	LCD_SendCommand (0x28); 
	Delay(BISY_TIME);

	LCD_SendCommand (0x08); 
	Delay(BISY_TIME);

	LCD_SendCommand (0x01); 
	Delay(BISY_TIME);

	LCD_SendCommand (0x03); 
	Delay(BISY_TIME);

	LCD_SendCommand (0x0C); 
	Delay(BISY_TIME);
}

void Delay(uint32_t count)
{
	while(count--);
}

uint8_t LCD_GetRusChar(uint8_t num)
{
	uint8_t ANSI1251_CO_FF [] = {
		 0x41,       //код 0xC0, символ 'А' //0
		 0xA0,       //код 0xC1, символ 'Б' //1
		 0x42,       //код 0xC2, символ 'В' //2
		 0xA1,       //код 0xC3, символ 'Г' //3
		 0xE0,       //код 0xC4, символ 'Д' //4
		 0x45,       //код 0xC5, символ 'Е' //5
		 0xA3,       //код 0xC6, символ 'Ж' //6
		 0xA4,       //код 0xC7, символ 'З' //7
		 0xA5,       //код 0xC8, символ 'И' //8
		 0xA6,       //код 0xC9, символ 'Й' //9
		 0x4B,       //код 0xCA, символ 'К' //10
		 0xA7,       //код 0xCB, символ 'Л' //11
		 0x4D,       //код 0xCC, символ 'М'	//12
		 0x48,       //код 0xCD, символ 'Н'	//13
		 0x4F,       //код 0xCE, символ 'О'	//14
		 0xA8,       //код 0xCF, символ 'П'	//15
		 0x50,       //код 0xD0, символ 'Р'	//16
		 0x43,       //код 0xD1, символ 'С'	//17
		 0x54,       //код 0xD2, символ 'Т'	//18
		 0xA9,       //код 0xD3, символ 'У'	//19
		 0xAA,       //код 0xD4, символ 'Ф'	//20
		 0x58,       //код 0xD5, символ 'Х'	//21
		 0xE1,       //код 0xD6, символ 'Ц'	//22
		 0xAB,       //код 0xD7, символ 'Ч'	//23
		 0xAC,       //код 0xD8, символ 'Ш'	//24
		 0xE2,       //код 0xD9, символ 'Щ'	//25
		 0xAD,       //код 0xDA, символ 'Ъ'	//26
		 0xAE,       //код 0xDB, символ 'Ы'	//27
		 0x62,       //код 0xDC, символ 'Ь'	//28
		 0xAF,       //код 0xDD, символ 'Э'	//29
		 0xB0,       //код 0xDE, символ 'Ю'	//30
		 0xB1,       //код 0xDF, символ 'Я'	//31
		 0x61,       //код 0xE0, символ 'а'	//32
		 0xB2,       //код 0xE1, символ 'б'	//33
		 0xB3,       //код 0xE2, символ 'в'	//34
		 0xB4,       //код 0xE3, символ 'г'	//35
		 0xE3,       //код 0xE4, символ 'д'	//36
		 0x65,       //код 0xE5, символ 'е'	//37
		 0xB6,       //код 0xE6, символ 'ж'	//38
		 0xB7,       //код 0xE7, символ 'з'	//39
		 0xB8,       //код 0xE8, символ 'и'	//40
		 0xB9,       //код 0xE9, символ 'й'	//41
		 0xBA,       //код 0xEA, символ 'к'	//42
		 0xBB,       //код 0xEB, символ 'л'	//43
		 0xBC,       //код 0xEC, символ 'м'	//44
		 0xBD,       //код 0xED, символ 'н'	//45
		 0x6F,       //код 0xEE, символ 'о'	//46
		 0xBE,       //код 0xEF, символ 'п'	//47
		 0x70,       //код 0xF0, символ 'р'	//48
		 0x63,       //код 0xF1, символ 'с'	//49
		 0xBF,       //код 0xF2, символ 'т'	//50
		 0x79,       //код 0xF3, символ 'у'	//51
		 0xE4,       //код 0xF4, символ 'ф'	//52
		 0x78,       //код 0xF5, символ 'х'	//53
		 0xE5,       //код 0xF6, символ 'ц'	//54
		 0xC0,       //код 0xF7, символ 'ч'	//55
		 0xC1,       //код 0xF8, символ 'ш'	//56
		 0xE6,       //код 0xF9, символ 'щ'	//57
		 0xC2,       //код 0xFA, символ 'ъ'	//58
		 0xC3,       //код 0xFB, символ 'ы'	//59
		 0xC4,       //код 0xFC, символ 'ь'	//60
		 0xC5,       //код 0xFD, символ 'э'	//61
		 0xC6,       //код 0xFE, символ 'ю'	//62
		 0xC7        //код 0xFF, символ 'я'	//63
	};
	return  ANSI1251_CO_FF[num];
}

void LCD_LightON (void)
{
	GPIO_SetOutputPin  (LCD_LIGHT_PORT, GPIO_PIN_12);
}

void LCD_LightOff (void)
{
	GPIO_ResetOutputPin(LCD_LIGHT_PORT, GPIO_PIN_12);
}

void RS_GPIO_SET  (void)
{ 
	GPIO_SetOutputPin  (LCD_DATA_PORT,   LCD_RS_PIN);
}

void RS_GPIO_RESET(void)
{
	GPIO_ResetOutputPin(LCD_DATA_PORT,   LCD_RS_PIN);
}

void EN_GPIO_SET  (void)
{
	GPIO_SetOutputPin  (LCD_DATA_PORT,   LCD_EN_PIN);
}
void EN_GPIO_RESET(void)
{
	GPIO_ResetOutputPin(LCD_DATA_PORT,   LCD_EN_PIN);
}

void DB4_GPIO_SET  (void)
{
	GPIO_SetOutputPin  (LCD_DATA_PORT,  LCD_DB4_PIN);
}

void DB4_GPIO_RESET(void)
{
	GPIO_ResetOutputPin(LCD_DATA_PORT,  LCD_DB4_PIN);
}

void DB5_GPIO_SET  (void)
{
	GPIO_SetOutputPin  (LCD_DATA_PORT,  LCD_DB5_PIN);
}

void DB5_GPIO_RESET(void)
{
	GPIO_ResetOutputPin(LCD_DATA_PORT,  LCD_DB5_PIN);
}

void DB6_GPIO_SET  (void)
{
	GPIO_SetOutputPin  (LCD_DATA_PORT,  LCD_DB6_PIN);
}

void DB6_GPIO_RESET(void)
{
	GPIO_ResetOutputPin(LCD_DATA_PORT,  LCD_DB6_PIN);
}

void DB7_GPIO_SET  (void)
{
	GPIO_SetOutputPin  (LCD_DATA_PORT,  LCD_DB7_PIN);
}

void DB7_GPIO_RESET(void)
{
	GPIO_ResetOutputPin(LCD_DATA_PORT,  LCD_DB7_PIN);
}
