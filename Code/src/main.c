#include "stm32f1xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"
#include "gpio.h"

void vTaskDefault (void *argument);
void vTaskDebug (void *argument);

int main (void){

	GPIO_Init();
	
	xTaskCreate(vTaskDefault, "Default", 128, NULL, 1, NULL);
	xTaskCreate(vTaskDebug,   "Debug",   128, NULL, 1, NULL);
	
	vTaskStartScheduler();
	
	while(1){
	
	}
	
}

void vTaskDefault (void *argument){
	
	while(1)
	{
		GPIOF->BSRR |= GPIO_BSRR_BS10;
		vTaskDelay(100);
		GPIOF->BSRR |= GPIO_BSRR_BR10;
		vTaskDelay(100);
	}
	
}

void vTaskDebug (void *argument){
	
	while(1)
	{
		GPIOB->BSRR |= GPIO_BSRR_BS8;
		vTaskDelay(50);
		GPIOB->BSRR |= GPIO_BSRR_BR8;
		vTaskDelay(1000);
	}
}



