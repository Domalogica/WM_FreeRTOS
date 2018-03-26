#include "stm32f1xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"
#include "gpio.h"
#include "gpio_user.h"
#include "power_switches.h"
#include "lcd_display.h"
#include "system_init.h"
#include "utils.h"
#include "uart.h"
#include "spi.h"
#include "rgb.h"
#include "gpio_it.h"
//#include "rtc.h"

void vTaskDefault	(void *argument);
void vTaskFLM 		(void *argument);
void vTaskUART		(void *argument);
void vTaskSPI	  	(void *argument);
void vTaskTriac	 	(void *argument);
void vTaskDebug 	(void *argument);
void vTaskRGB 		(void *argument);

int main (void)
{
	RCC_Init();
	//MCO_out(); Frequency testing (PIN_A8)
	GPIO_Init();
	UART3_Init();
	SPI2_Init();
	TRIAC_PortInit();
	MOSFET_PortInit();
	ULN_PortInit();
	GPIO_FLM_InitIT();
	FLM_ResetData();

	xTaskCreate(vTaskDefault, "Default", 128, NULL, 1, NULL);
	xTaskCreate(vTaskFLM,     "FLM",     128, NULL, 2, NULL);
	xTaskCreate(vTaskUART,    "UART",    128, NULL, 1, NULL);
	xTaskCreate(vTaskSPI,     "SPI",     128, NULL, 1, NULL);
	xTaskCreate(vTaskTriac,   "Triac",   128, NULL, 1, NULL);
	xTaskCreate(vTaskDebug,   "Debug",   128, NULL, 1, NULL);
	xTaskCreate(vTaskRGB,     "RGB",     128, NULL, 1, NULL);

	vTaskStartScheduler();
	
	while(1){
	
	}
}

void vTaskDefault (void *argument)
{
	while(1)
	{
		GPIO_SetOutputPin(PORT_LED_ACTIVE, PIN_LED_ACTIVE);
		vTaskDelay(500);
		GPIO_ResetOutputPin(PORT_LED_ACTIVE, PIN_LED_ACTIVE);
		vTaskDelay(500);
	}
}

void vTaskFLM (void *argument)
{
	FML_data fml_data_struct; 
	
	uint8_t str1[3];
	uint8_t str2[3];
	uint8_t str3[3];
	uint8_t str4[3];
	
	while(1)
	{
		fml_data_struct = FLM_GetData();
		i32toa_fixlen(fml_data_struct.FML1, str1, 3);
		i32toa_fixlen(fml_data_struct.FML2, str2, 3);
		i32toa_fixlen(fml_data_struct.FML3, str3, 3);
		i32toa_fixlen(fml_data_struct.FML4, str4, 3);
		/*
		if (fml_data_struct.FML1 | fml_data_struct.FML2 | fml_data_struct.FML3 | fml_data_struct.FML4)
		{*/
			USART3_Send_String (str1); 
			USART3_Send_String ((uint8_t*)"  ");
			USART3_Send_String (str2); 
			USART3_Send_String ((uint8_t*)"  ");
			USART3_Send_String (str3); 
			USART3_Send_String ((uint8_t*)"  ");
			USART3_Send_String (str4); 
			USART3_Send_String ((uint8_t*)"\r");
		//}
		
		FLM_ResetData();
		vTaskDelay(1000);	
	}
}

void vTaskSPI (void *argument)
{
	while(1)
	{
		vTaskDelay(10);	
		SPI2_WriteData(0x1234);
	}
}

void vTaskUART (void *argument)
{
	while(1)
	{
		vTaskDelay(1000);
		//USART3_Send_String ((uint8_t*)"Debug\n\r");		
	}
}

void vTaskTriac (void *argument)
{
	uint16_t switch_time = 200;
	while(1)
	{	
		TRIAC_Enable(1);
		vTaskDelay(switch_time);
		TRIAC_Disable(1);
		
		TRIAC_Enable(7);
		vTaskDelay(switch_time);
		TRIAC_Disable(7);
		
		TRIAC_Enable(4);
		vTaskDelay(switch_time);
		TRIAC_Disable(4);
		
		TRIAC_Enable(8);
		vTaskDelay(switch_time);
		TRIAC_Disable(8);
		
		TRIAC_Enable(5);
		vTaskDelay(switch_time);
		TRIAC_Disable(5);
		
		TRIAC_Enable(9);
		vTaskDelay(switch_time);
		TRIAC_Disable(9);
		
		TRIAC_Enable(2);
		vTaskDelay(switch_time);
		TRIAC_Disable(2);
		
		TRIAC_Enable(3);
		vTaskDelay(switch_time);
		TRIAC_Disable(3);
		
		TRIAC_Enable(6);
		vTaskDelay(switch_time);
		TRIAC_Disable(6);
	}
}

void vTaskDebug (void *argument)
{
	vTaskDelay(100);
	LCD_Init();
	LCD_Clear();
	LCD_SetCursor(0, 1);
	LCD_SendString((uint8_t*)"WM_FreeRTOS (CMIS)", 18);

	while(1)
	{
		LCD_SetCursor(1, 5);
		LCD_SendString((uint8_t*)"DEBUG MODE", 10);
		vTaskDelay(1000);
		LCD_SetCursor(1, 5);
		LCD_SendString((uint8_t*)"          ", 10);
		vTaskDelay(1000);
	}
}

void vTaskRGB (void *argument)
{
	uint16_t switch_time = 1500;
	
	while(1)
	{
		RGB_ColorSet(LED_GREEN);
		vTaskDelay(switch_time);
		RGB_ColorSet(LED_RED);
		vTaskDelay(switch_time);
		RGB_ColorSet(LED_BLUE);
		vTaskDelay(switch_time);
		RGB_ColorSet(LED_YELOW);
		vTaskDelay(switch_time);
		RGB_ColorSet(LED_MAGENTA);
		vTaskDelay(switch_time);
		RGB_ColorSet(LED_CYAN);
		vTaskDelay(switch_time);
		RGB_ColorSet(LED_WHITE);
	}
}
