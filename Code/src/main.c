#include "stm32f1xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"
#include "system_init.h"
#include "gpio.h"
#include "gpio_user.h"
#include "power_switch.h"
#include "lcd_display.h"
#include "uart.h"
#include "spi.h"
#include "fml.h"
#include "utils.h"
#include "rgb.h"

void vTaskDefault	(void *argument);
void vTaskFLM 		(void *argument);
void vTaskUART		(void *argument);
void vTaskSPI	  	(void *argument);
void vTaskDebug 	(void *argument);

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
	xTaskCreate(vTaskDebug,   "Debug",   128, NULL, 1, NULL);
	
	vTaskStartScheduler();
	
	while(1){
	
	}
}

void vTaskDefault (void *argument)
{
	//TODO: TRIAC_Enable(1);
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
	//TODO: FML_data fml_data_struct; 
	
	while(1)
	{
		//TODO: fml_data_struct = FLM_GetData();
		vTaskDelay(100);	
	}
}

void vTaskSPI (void *argument)
{
	while(1)
	{ 
		//TODO: SPI2_WriteData(0xFFFF);
		vTaskDelay(10);	
	}
}

void vTaskUART (void *argument)
{
	while(1)
	{
		//TODO: USART3_Send_String ((uint8_t*)"Debug\n\r");		
		vTaskDelay(1000);
	}
}

void vTaskDebug (void *argument)
{	
	FML_data fml_data_struct; 
	
	uint8_t str1[10];
	uint8_t str2[10];
	uint8_t str3[10];
	uint8_t str4[10];
	
	vTaskDelay(100);
	LCD_Init();
	LCD_Clear();
	LCD_SetCursor(0, 1);
	LCD_SendString((uint8_t*)"WM_FreeRTOS (CMIS)", 18);
	LCD_SetCursor(1, 5);
	LCD_SendString((uint8_t*)"DEBUG MODE", 10);
	
	while(1)
	{
		fml_data_struct = FLM_GetData();
		Int32ToString(fml_data_struct.FML1, str1, 10);
		Int32ToString(fml_data_struct.FML2, str2, 10);
		Int32ToString(fml_data_struct.FML3, str3, 10);
		Int32ToString(fml_data_struct.FML4, str4, 10);

		USART3_Send_String ((uint8_t*)"FML1 --> ");
		USART3_Send_String (str1); 
		USART3_Send_String ((uint8_t*)"  FML2 --> ");
		USART3_Send_String (str2); 
		USART3_Send_String ((uint8_t*)"  FML3 --> ");
		USART3_Send_String (str3); 
		USART3_Send_String ((uint8_t*)"  FML4 --> ");
		USART3_Send_String (str4); 
		USART3_Send_String ((uint8_t*)"\r");

		//FLM_ResetData();
		GPIO_ResetOutputPin(GPIOB, GPIO_PIN_8);
		vTaskDelay(100); 
		GPIO_SetOutputPin(GPIOB, GPIO_PIN_8);
	}
	
}
