#include "stm32f1xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"
#include "system.h"
#include "gpio.h"
#include "gpio_us.h"
#include "gpio_it.h"
#include "power_switch.h"
#include "lcd.h"
#include "uart.h"
#include "spi.h"
#include "fml.h"
#include "utils.h"
#include "rgb.h"
#include "bill_acceptor.h"
#include "adc.h"

void vTaskDefault		(void *argument);
void vTaskDispenser (void *argument);
void vTaskFLM 			(void *argument);
void vTaskUART			(void *argument);
void vTaskKey 			(void *argument);

uint8_t  IsDrainage  		      = 0;
uint8_t  IsWaterDelivery      = 0;
uint16_t dispenser_on_time	  = 200;
uint16_t dispenser_off_time   = 200;
	
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
	IRQ_Init();
	FLM_ResetData();
	BILL_PortInit();
	ADC_Init();

	xTaskCreate(vTaskDefault, 	"Default",   256, NULL, 2, NULL);
	xTaskCreate(vTaskDispenser,	"Dispenser", 256, NULL, 2, NULL);
	xTaskCreate(vTaskFLM,     	"FLM",       256, NULL, 1, NULL);
	xTaskCreate(vTaskUART,    	"UART",      128, NULL, 1, NULL);
	xTaskCreate(vTaskKey,     	"KEY",       128, NULL, 1, NULL);
	
	vTaskStartScheduler();
	
	while(1){
	
	}
}

void vTaskDefault (void *argument)
{
	uint8_t active_status = 0;
	
	while(1)
	{
		//Pressure at the input is, but there is no output
		if(Is_InPressSensor() && (!Is_OutPressSensor()))	
		{
			TRIAC_Enable (TR_WATER_SUPPLY);
			TRIAC_Enable (TR_WATER_PUMP);
			MOSFET_Enable(MF_WATER_PUMP);
		}else
		{
			TRIAC_Disable (TR_WATER_SUPPLY);
			TRIAC_Disable (TR_WATER_PUMP);
			MOSFET_Disable(MF_WATER_PUMP);
		}
	
		if(active_status > 10)
		{
			GPIO_SetOutputPin(PORT_LED_ACTIVE, PIN_LED_ACTIVE);
		}
		if(active_status > 20)
		{
			GPIO_ResetOutputPin(PORT_LED_ACTIVE, PIN_LED_ACTIVE);
			active_status = 0;
		}
		active_status++;
		vTaskDelay(50);
	}
}

void vTaskDispenser (void *argument)
{
	while(1)
	{ 
		TRIAC_Disable(TR_DISPENSER);
		vTaskDelay(dispenser_off_time);
		TRIAC_Enable (TR_DISPENSER);
		vTaskDelay(dispenser_on_time);	
	}
}

void vTaskKey (void *argument)
{
	
	while(1)
	{ 
		if(Is_ButtonUp())
		{
			if (dispenser_on_time > 20) dispenser_on_time = (dispenser_on_time - 10);
			if (dispenser_on_time == 20) 
			{
				if(dispenser_off_time < 400) dispenser_off_time = (dispenser_off_time + 10);
			}	
		}
		
		if(Is_ButtonDown())
		{
			if (dispenser_off_time > 20) dispenser_off_time = (dispenser_off_time - 10);
			if (dispenser_off_time == 20) 
			{
				if(dispenser_on_time < 400) dispenser_on_time = (dispenser_on_time + 10);
			}	
		}

		if(Is_ButtonLeft())
		{
			if(IsDrainage)
			{
				TRIAC_Enable (TR_DRAINAGE);
				IsDrainage = 0;
			}else
			{
				TRIAC_Disable(TR_DRAINAGE);

				IsDrainage = 1;
			}
		}
		
		if(Is_ButtonRight())
		{
			if(IsWaterDelivery)
			{
				TRIAC_Enable (TR_WATER_DELIVERY);
				IsWaterDelivery = 0;
			}else
			{
				TRIAC_Disable(TR_WATER_DELIVERY);
				IsWaterDelivery = 1;
			}
		}
		vTaskDelay(125);
	}
}

void vTaskFLM (void *argument)
{
	uint8_t fml1[5];
	uint8_t fml2[5];
	uint8_t fml3[5];
	
	//uint8_t adc[5];
	
	FML_data fml_data_struct; 

	LCD_Init();
	LCD_Clear();	
	vTaskDelay(200);
	LCD_Init();
	LCD_Clear();	

	LCD_SetCursor(0, 2);
	LCD_SendString((uint8_t*)"IN ",  3);
	LCD_SetCursor(0, 9);
	LCD_SendString((uint8_t*)"OS ",  3);
	LCD_SetCursor(0, 16);
	LCD_SendString((uint8_t*)"OUT ", 4);
	
	
	

				
	while(1)
	{
		fml_data_struct = FLM_GetData();
		
		Int16ToString((uint16_t)fml_data_struct.FML1, fml1, 5);
		Int16ToString((uint16_t)fml_data_struct.FML2, fml2, 5);
		Int16ToString((uint16_t)fml_data_struct.FML3, fml3, 5);

		LCD_SetCursor(1, 1);
		LCD_SendString(fml1, 5);
		LCD_SendString((uint8_t*)"  ", 2);
		LCD_SendString(fml2, 5);
		LCD_SendString((uint8_t*)"  ", 2);
		LCD_SendString(fml3, 5);
		if(IsDrainage) 
		{
			LCD_SetCursor(2, 0);
			LCD_SendString((uint8_t*)"DRAINAGE OFF", 12);
		}else
		{
			LCD_SetCursor(2, 0);
			LCD_SendString((uint8_t*)"DRAINAGE ON ", 12);
		}
		
		if(IsWaterDelivery) 
		{
			LCD_SetCursor(3, 0);
			LCD_SendString((uint8_t*)"WATER    OFF", 12);
		}else
		{
			LCD_SetCursor(3, 0);
			LCD_SendString((uint8_t*)"WATER    ON ", 12);
		}
		
		vTaskDelay(100);	
	}
}

void vTaskUART (void *argument)
{
	while(1)
	{
		vTaskDelay(1000);
	}
}
