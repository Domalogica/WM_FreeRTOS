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
#include "flash.h"
#include "timers.h"

void vTaskDefault		(void *argument);
void vTaskDispenser 	(void *argument);
void vTaskFLASH			(void *argument);
void vTaskLCD 			(void *argument);
void vTaskKey 			(void *argument);

//Dispenser
uint8_t  IsOsmosWashing	= 0;
uint16_t dispenser_mode	=	5;
uint16_t dispenser_flag	=	0;
//System
uint8_t  status_system = 0;
uint8_t  status_code = 0;
uint16_t drainage_switch_time = 0;
uint8_t  manual_mode = 0;
//Lcd
uint8_t  operation_mode = 0;
uint8_t  in_valve = 0;
uint8_t  out_valve = 0;
uint8_t  drainage_valve = 0;
//Led
uint8_t  active_status = 0;
//TODO: debug
uint8_t input_sensor = 0;
uint8_t output_sensor = 0;
uint8_t drainage_sensor = 0;
	
int main (void)
{ 
	RCC_Init();
	//MCO_out(); Frequency testing (PIN_A8)
	GPIO_Init();
	TRIAC_PortInit();
	ULN_PortInit();
	IRQ_Init();
	FLM_ResetData();
	InitTIM2();
	LCD_Init();
	LCD_Clear();

	xTaskCreate(vTaskDefault, 	"Default",   256, NULL, 2, NULL);
	xTaskCreate(vTaskFLASH,    	"FLASH",     128, NULL, 1, NULL);
	xTaskCreate(vTaskLCD,     	"LCD",       128, NULL, 1, NULL);
	xTaskCreate(vTaskKey,     	"KEY",       128, NULL, 1, NULL);
	
	vTaskStartScheduler();
	
	while(1){
	
	}
}

void vTaskDefault (void *argument)
{
	while(1)
	{
		if (Is_InPressSensor() !=  input_sensor)
		{
			vTaskDelay(5);
			input_sensor = Is_InPressSensor();
		}

		if (Is_OutPressSensor() !=  output_sensor)
		{
			vTaskDelay(5);
			output_sensor = Is_OutPressSensor();
		}

		drainage_sensor = IsDrinanageSensor();
	
		if(!input_sensor)
		{
		  status_system = SYSTEM_FAILTURE;
		  status_code = ERR_NO_WATER;
		}		

		if(input_sensor && (status_code == ERR_NO_WATER))
		{
		  status_system = SYSTEM_OK;
		  status_code = STATUS_OK;
		}

		if((drainage_switch_time > 80) && (!drainage_sensor) && (status_code == STATUS_ACTIVE))
		{
		  status_system = SYSTEM_FAILTURE;
		  status_code = ERR_DRAINAGE_IS_BLOCKED;
		  drainage_switch_time = 0;
		}

		if((!output_sensor) && input_sensor && (status_system == SYSTEM_OK))
		{
		  TRIAC_Enable (TR_WATER_SUPPLY);
		  TRIAC_Enable (TR_DRAINAGE);
		  TRIAC_Enable (TR_WATER_PUMP);
		  status_code = STATUS_ACTIVE;
		  drainage_switch_time++;
		  //Debug to lcd
		  in_valve = 1;
		  out_valve = 1;
		  drainage_valve = 1;
		}
		else
		{
		  TRIAC_Disable(TR_WATER_PUMP);
		  TRIAC_Disable(TR_WATER_SUPPLY);
		  TRIAC_Disable(TR_DRAINAGE);
		  drainage_switch_time = 0;
		  if(status_code == STATUS_ACTIVE) status_code = STATUS_OK;
		  //Debug to lcd
		  in_valve = 0;
		  out_valve = 0;
		  drainage_valve = 0;
		}

		if(active_status > 25)
		{
			GPIO_TogglePin(PORT_LED_ACTIVE, PIN_LED_ACTIVE);
			//GPIO_TogglePin(PORT_LED_FAILTURE, PIN_LED_FAILTURE);
			active_status = 0;
		}
		active_status++;
		
		vTaskDelay(25);
	}
}

void vTaskFLASH (void *argument)
{
	uint32_t fml_dataKey = 0;
	uint32_t oldFlashData[3] = {0,0,0};
	uint32_t newFlashData[3] = {0,0,0};

	fml_dataKey = FlashReadData(FML_FLASH_FLAG_ADRESS);
	
	if(fml_dataKey == FML_FLASH_KEY)
	{
		oldFlashData[0] = FlashReadData(IN_FML_DATA_ADRESS);
		oldFlashData[1] = FlashReadData(DRAIN_FML_DATA_ADRESS);
		oldFlashData[2] = FlashReadData(OUT_FML_DATA_ADRESS);
		
		FLM_SetTic(oldFlashData[0], oldFlashData[1], oldFlashData[2], 0x00000000);
	}else
	{
		FlashUnlock();
		FlashErase(FML_FLASH_PAGE);
		FlashWriteData(FML_FLASH_FLAG_ADRESS, FML_FLASH_KEY);
		FlashLock();
	}

	while(1)
	{
		oldFlashData[0] = FlashReadData(IN_FML_DATA_ADRESS);
		oldFlashData[1] = FlashReadData(DRAIN_FML_DATA_ADRESS);
		oldFlashData[2] = FlashReadData(OUT_FML_DATA_ADRESS);
		
		newFlashData[0] = FLM_GetTic(FLM_IN);
		newFlashData[1] = FLM_GetTic(FLM_DRAINAGE);
		newFlashData[2] = FLM_GetTic(FLM_OUT);
		
		if((newFlashData[0] != oldFlashData[0]) || (newFlashData[1] != oldFlashData[1]) || (newFlashData[2] != oldFlashData[2]))
			{
				FlashUnlock();
				FlashErase(FML_FLASH_PAGE);
				
				FlashWriteData(IN_FML_DATA_ADRESS, 		newFlashData[0]);
				FlashWriteData(DRAIN_FML_DATA_ADRESS, newFlashData[1]);
				FlashWriteData(OUT_FML_DATA_ADRESS, 	newFlashData[2]);
				
				FlashWriteData(FML_FLASH_FLAG_ADRESS, FML_FLASH_KEY);
				FlashUnlock();
			}
			
		vTaskDelay(10000);
	}
}

void vTaskLCD (void *argument)
{
	uint8_t text_ItReady[20]  = {0x20,0x20,0x20,0xA1,0x6F,0xBF,0x6F,0xB3,0x20,0xBA,0x20,0xB3,0xC3,0xE3,0x61,0xC0,0x65,0x20,0x20,0x20};
	uint8_t text_Delivery[20] = {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x42,0xC3,0xE3,0x61,0xC0,0x61,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
	uint8_t text_NoWater[20]  = {0x20,0x20,0x41,0xB3,0x61,0x70,0xB8,0xC7,0x3A,0x20,0xBD,0x65,0xBF,0x20,0xB3,0x6F,0xE3,0xC3,0x20,0x20};
	uint8_t text_ClDrain[20]  = {0x41,0xB3,0x61,0x70,0xB8,0xC7,0x3A,0x20,0xE3,0x70,0x65,0xBD,0x61,0xB6,0x20,0xB7,0x61,0xBA,0x70,0x2E};
	uint8_t text_Error[16]    = {0x20,0x41,0xB3,0x61,0x70,0xB8,0xC7,0x3A,0x20,0x6F,0xC1,0xB8,0xB2,0xBA,0x61,0x20};

	uint8_t text_LitersMin[15] = {0xA7,0xB8,0xBF,0x70,0x6F,0xB3,0x2F,0xBC,0xB8,0xBD,0x2E,0x3A,0x20,0x20,0x20};
	uint8_t text_OutTotals[15] = {0x42,0xC3,0xE3,0x61,0xBD,0x6F,0x20,0xB3,0x63,0x65,0xB4,0x6F,0x3A,0x20,0x20}; 
	
	uint8_t textDataLitersMin[5] = {'*','*','*','*','*'};
	uint8_t textDataLitTotals[5] = {'*','*','*','*','*'};
	uint8_t textDataErrCode[2]   = {'N','C'};
	
	float literMinPrevious = 0.0;
	float literMinResult = 0.0;
	
	//Service mode text
	uint8_t text_ServiceMode[15] = {0x43,0x65,0x70,0xB3,0xB8,0x63,0xBD,0xC3,0xB9,0x20,0x70,0x65,0xB6,0xB8,0xBC};
	uint8_t text_Input[7] 		 = {0x42,0x78,0x6F,0xE3,0x3A,0x20,0x20};
	uint8_t text_Output[7] 		 = {0x42,0xC3,0x78,0x6F,0xE3,0x3A,0x20};
	uint8_t text_Drainage[7] 	 = {0xE0,0x70,0x65,0xBD,0x61,0xB6,0x3A};
	uint8_t textFmlInLiters[5] 	 = {'*','*','*','*','*'};
	uint8_t textFmlOutLiters[5]	 = {'*','*','*','*','*'};
	uint8_t textFmlDrainageLiters[5] = {'*','*','*','*','*'};

	//Flowmeter data variable
	float fmlInLiters = 0.0;
	float fmlOutLiters = 0.0;
	float fmlDrainageLiters = 0.0;

	LCD_Init();
	LCD_Clear();	
	vTaskDelay(300);
	LCD_Init();
	LCD_Clear();	
	
	for(;;)
	{
		if(operation_mode == NORMAL_MODE)
		{
			fmlOutLiters = FLM_GetTic(FLM_OUT) / FLM_OUT_COEF;

			if(fmlOutLiters >= 0.01)
			{	
				if(fmlOutLiters - literMinPrevious) literMinResult = (fmlOutLiters - literMinPrevious) * 60;
				else literMinResult = 0.0;

				literMinPrevious = fmlOutLiters;
				FloatToString(&fmlOutLiters, (char*)textDataLitTotals,	3, 1, 1);
				FloatToString(&literMinResult,(char*)textDataLitersMin, 1, 3, 1);
			}

			//Line 0
			LCD_SetCursor(0, 0);
			LCD_SendString((uint8_t*)"                    ", 20);

			//Line 1
			LCD_SetCursor(1, 0);
			switch(status_code)
			{
				case STATUS_OK: LCD_SendString(text_ItReady, 20); break;
				case STATUS_ACTIVE: LCD_SendString(text_Delivery, 20); break;
				case ERR_NO_WATER: LCD_SendString(text_NoWater, 20); break;
				case ERR_DRAINAGE_IS_BLOCKED: LCD_SendString(text_ClDrain, 20); break;
				default:LCD_SendString(text_Error, 16);
						Int16ToString((uint8_t)status_code, textDataErrCode, 2);
						LCD_SendString(textDataErrCode, 2); break;
			}

		  //Line 2
		  LCD_SetCursor(2, 0);
		  LCD_SendString(text_LitersMin, 15);
		  LCD_SendString(textDataLitersMin, 5);

		  //Line 3
		  LCD_SetCursor(3, 0);
		  LCD_SendString(text_OutTotals, 15);
		  LCD_SendString(textDataLitTotals, 5);
		}

		if(operation_mode == SERVICE_MODE)
		{
			fmlInLiters = FLM_GetTic(FLM_IN) / FLM_IN_COEF;
			fmlOutLiters = FLM_GetTic(FLM_OUT) / FLM_OUT_COEF;
			fmlDrainageLiters = FLM_GetTic(FLM_DRAINAGE) / FLM_DRAINAGE_COEF;

			if(fmlInLiters >= 0.01) FloatToString(&fmlInLiters, (char*)textFmlInLiters, 3, 1, 1);
			if(fmlOutLiters >= 0.01) FloatToString(&fmlOutLiters, (char*)textFmlOutLiters, 3, 1, 1);
			if(fmlDrainageLiters >= 0.01) FloatToString(&fmlDrainageLiters, (char*)textFmlDrainageLiters, 3, 1, 1);

			//Line 0
			LCD_SetCursor(0, 3);
			LCD_SendString(text_ServiceMode, 15);

			//Line 1
			LCD_SetCursor(1, 0);
			LCD_SendString(text_Input, 7);
			LCD_SendString(textFmlInLiters, 5);
			LCD_SendString((uint8_t*)", K. ", 5);
			if(in_valve)LCD_SendString((uint8_t*)"ON ", 3);
			else LCD_SendString((uint8_t*)"OFF", 3);

			//Line 2
			LCD_SetCursor(2, 0);
			LCD_SendString(text_Output, 7);
			LCD_SendString(textFmlOutLiters, 5);
			LCD_SendString((uint8_t*)", K. ", 5);
			if(out_valve)LCD_SendString((uint8_t*)"ON ", 3);
			else LCD_SendString((uint8_t*)"OFF", 3);

			//Line 3
			LCD_SetCursor(3, 0);
			LCD_SendString(text_Drainage, 7);
			LCD_SendString(textFmlDrainageLiters, 5);
			LCD_SendString((uint8_t*)", K. ", 5);
			if(drainage_valve)LCD_SendString((uint8_t*)"ON ", 3);
			else LCD_SendString((uint8_t*)"OFF", 3);
		}
		vTaskDelay(1000);	
	}
}

void vTaskKey (void *argument)
{
	uint8_t  key_count = 0;
	while(1)
	{
		if(!Is_ExtButFailDown())
		{
			status_code = STATUS_OK;
			status_system = SYSTEM_OK;
			if (key_count > 20)
			{
				operation_mode = !operation_mode;
				key_count = 0;
			}
			key_count++;
		 }
	vTaskDelay(150);
	}
}

void vTaskDispenser (void *argument)
{
	while(1)
	{
		if(dispenser_flag)
		{
			switch(dispenser_mode){
				case 0: TRIAC_Disable(TR_DISPENSER);
								vTaskDelay(500);
								break;
				case 1: TRIAC_Disable(TR_DISPENSER);
								vTaskDelay(400);
								TRIAC_Enable (TR_DISPENSER);
								vTaskDelay(40);
								break;
				case 2: TRIAC_Disable(TR_DISPENSER);
								vTaskDelay(400);
								TRIAC_Enable (TR_DISPENSER);
								vTaskDelay(80);
								break;
				case 3: TRIAC_Disable(TR_DISPENSER);
								vTaskDelay(400);
								TRIAC_Enable (TR_DISPENSER);
								vTaskDelay(120);
								break;
				case 4: TRIAC_Disable(TR_DISPENSER);
								vTaskDelay(400);
								TRIAC_Enable (TR_DISPENSER);
								vTaskDelay(160);
								break;
				case 5: TRIAC_Disable(TR_DISPENSER);
								vTaskDelay(360);
								TRIAC_Enable (TR_DISPENSER);
								vTaskDelay(200);
								break;
				case 6: TRIAC_Disable(TR_DISPENSER);
								vTaskDelay(320);
								TRIAC_Enable (TR_DISPENSER);
								vTaskDelay(200);
								break;
				case 7: TRIAC_Disable(TR_DISPENSER);
								vTaskDelay(180);
								TRIAC_Enable (TR_DISPENSER);
								vTaskDelay(200);
								break;
				case 8: TRIAC_Disable(TR_DISPENSER);
								vTaskDelay(120);
								TRIAC_Enable (TR_DISPENSER);
								vTaskDelay(200);
								break;
				case 9: TRIAC_Disable(TR_DISPENSER);
								vTaskDelay(80);
								TRIAC_Enable (TR_DISPENSER);
								vTaskDelay(200);
								break;
				case 10:TRIAC_Enable (TR_DISPENSER);
								vTaskDelay(500);
								break;
				default://Failture message
								vTaskDelay(500);
								break;
			}
		}else  TRIAC_Disable(TR_DISPENSER);
		
		vTaskDelay(20);
	}
}
