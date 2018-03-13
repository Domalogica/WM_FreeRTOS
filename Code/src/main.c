#include "stm32f1xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"
#include "gpio.h"
#include "gpio_user.h"
#include "power_switches.h"

void vTaskDefault (void *argument);
void vTaskTriac (void *argument);
void vTaskDebug (void *argument);

int main (void){

	GPIO_Init();
	
	xTaskCreate(vTaskDefault, "Default", 128, NULL, 1, NULL);
	xTaskCreate(vTaskTriac,   "Triac",   128, NULL, 1, NULL);
	xTaskCreate(vTaskDebug,   "Debug",   128, NULL, 1, NULL);
	
	vTaskStartScheduler();
	
	while(1){
	
	}
	
}

void vTaskDefault (void *argument){

	while(1)
	{
		GPIO_SetOutputPin(PORT_LED_ACTIVE, PIN_LED_ACTIVE);
		vTaskDelay(100);
		GPIO_ResetOutputPin(PORT_LED_ACTIVE, PIN_LED_ACTIVE);
		vTaskDelay(100);
		
	}
}

void vTaskTriac (void *argument){
	
	uint16_t switch_time = 20;
	
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

void vTaskDebug (void *argument){
	
	while(1)
	{	
		GPIO_SetOutputPin(PORT_LED_FAILTURE, PIN_LED_FAILTURE);
		vTaskDelay(50);
		GPIO_ResetOutputPin(PORT_LED_FAILTURE, PIN_LED_FAILTURE);
		vTaskDelay(1000);
	}
}
