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
#include "adc_us.h"

void vTaskDefault		(void *argument);
void vTaskDispenser (void *argument);
void vTaskLCD 			(void *argument);
void vTaskUART			(void *argument);
void vTaskKey 			(void *argument);

uint8_t  IsOsmosWashing 	    = 0;
uint16_t dispenser_mode	 			=	5;
uint16_t dispenser_flag	 			=	0;

uint8_t  fail_hydraSystem     = 0;

uint8_t  active_status = 0;
uint16_t drainage_switch_time = 0;
uint16_t drainage_switch_time2 = 0;
	
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
	//NC_portInit();
	//ADC1_Init();

	xTaskCreate(vTaskDefault, 	"Default",   256, NULL, 2, NULL);
	xTaskCreate(vTaskDispenser,	"Dispenser", 256, NULL, 2, NULL);
	xTaskCreate(vTaskLCD,     	"LCD",       128, NULL, 1, NULL);
	xTaskCreate(vTaskUART,    	"UART",      128, NULL, 1, NULL);
	xTaskCreate(vTaskKey,     	"KEY",       128, NULL, 1, NULL);
	
	vTaskStartScheduler();
	
	while(1){
	
	}
}

void vTaskDefault (void *argument)
{
	while(1)
	{
		//Pressure at the input is, but there is no output
		if(Is_InPressSensor() && (!Is_OutPressSensor()) && (!fail_hydraSystem))	
		{
			TRIAC_Enable (TR_WATER_SUPPLY); //Открыли входной клапан
			TRIAC_Enable (TR_WATER_PUMP);		//Вкючили насос нагнетания давления 
			dispenser_flag = 1;
			
			if (drainage_switch_time > 200) //ждем 5 секунд
			{
				TRIAC_Enable (TR_DRAINAGE);   //Открываем дренажный клапан
			}
			if (Is_DrainageFlow() && (drainage_switch_time > 200)) //Проверяем, сраболтал ли датчик потока после 10 сек
			{
				//Авария
				TRIAC_Disable (TR_WATER_SUPPLY); //Закрываем входной клапан
				TRIAC_Disable (TR_WATER_PUMP);	 //Выключаем насос
				dispenser_flag = 0;							 //Отключаем дозатор	
				fail_hydraSystem = 1;
				vTaskDelay(10000);							 //Ждем 10 секунд
				TRIAC_Disable (TR_DRAINAGE);		 //Закрываем дренажный клапан
				drainage_switch_time = 0;				 	
			}
			drainage_switch_time++;	
			//MOSFET_Enable(MF_WATER_PUMP);
		}else
		{
			TRIAC_Disable (TR_WATER_SUPPLY);
			TRIAC_Disable (TR_WATER_PUMP);
			dispenser_flag = 0;	             //Отключаем дозатор
			if (drainage_switch_time2 > 400) //Ждем 10 секунд
			{
				TRIAC_Disable (TR_DRAINAGE);  //Закрываем дренажный клапан
				drainage_switch_time2 = 0;
			}
			drainage_switch_time2++;	
			//MOSFET_Disable(MF_WATER_PUMP);
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
		vTaskDelay(25);
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

void vTaskKey (void *argument)
{
	while(1)
	{ 
		if(Is_ButtonUp())	  if (dispenser_mode < 10) dispenser_mode++;
		
		if(Is_ButtonDown())	if (dispenser_mode > 0)  dispenser_mode--;
		
		if(Is_ButtonLeft())
		{
			if(IsOsmosWashing)
			{
				TRIAC_Disable(TR_OSMOS_WASHING);
				IsOsmosWashing = 0;
			}else
			{
				TRIAC_Enable (TR_OSMOS_WASHING);
				IsOsmosWashing = 1;
			}
		}
		//Reset failture
		if(Is_ButtonRight())
		{
			fail_hydraSystem = 0; //Сброс аварии
			GPIO_ResetOutputPin(PORT_LED_FAILTURE, PIN_LED_FAILTURE);
		}
		vTaskDelay(150);
	}
}

void vTaskLCD (void *argument)
{	
	uint8_t active_st = 0;
	
	uint8_t mess_in[4] 		 = {0x42,0x78,0x6F,0xE3};
	uint8_t mess_os[5] 		 = {0x4F,0x63,0xBC,0x6F,0x63};
	uint8_t mess_ou[5]     = {0x42,0xC3,0x78,0x6F,0xE3};
	uint8_t mess_disper[4] = {0xE0,0x6F,0xB7,0x2E};
	uint8_t mess_osmos [5] = {0xA8,0x70,0x2E,0x6F,0x63};
//	uint8_t mess_liters[5] = {0xA7,0xB8,0xBF,0x70,0xC3};
	uint8_t mess_active[5] =  {0x43,0x6F,0x63,0xBF,0x2E};
	
	uint8_t fml1[5] = {'-','-','-','-','-'};
	uint8_t fml2[5] = {'-','-','-','-','-'};
	uint8_t fml3[5] = {'-','-','-','-','-'};

	float fml1_lit = 0.0;
	float fml2_lit = 0.0;
	float fml3_lit = 0.0;

	FML_data fml_data_struct;

	uint8_t disp_mode[2]  = {'-','-'};
	uint8_t osmos_flag[2] = {'-','-'};
	uint8_t litress[4]    = {'-','-','-','-'};
	
	uint8_t mess_ok [6]    = {0x48,0x6F,0x70,0xBC,0x2E,0x20};
	uint8_t mess_err[6]    = {0x41,0xB3,0x61,0x70,0xB8,0xC7};
	
	uint8_t  total_2line = 0;
	uint8_t  total_4line = 0;

	LCD_Init();
	LCD_Clear();	
	vTaskDelay(300);
	LCD_Init();
	LCD_Clear();	
	//In, OS, Out
	LCD_SetCursor(0, 0);
	LCD_SendString(mess_in, 4);
	LCD_SetCursor(0, 7);
	LCD_SendString(mess_os, 5);
	LCD_SetCursor(0, 14);
	LCD_SendString(mess_ou, 5);
	//Data flow	
	LCD_SetCursor(1, 0);
	LCD_SendString(fml1, 5);
	LCD_SendString((uint8_t*)"  ", 2);
	LCD_SendString(fml2, 5);
	LCD_SendString((uint8_t*)"  ", 2);
	LCD_SendString(fml3, 5);
	//Disper., clean os., litress
	LCD_SetCursor(2, 1);
	LCD_SendString(mess_disper, 4);
	LCD_SendString((uint8_t*)"  ", 2);
	LCD_SendString(mess_osmos, 5);
	LCD_SendString((uint8_t*)"  ", 2);
	LCD_SendString(mess_active, 5);

	while(1)
	{
		fml_data_struct = FLM_GetData();
		
		fml1_lit = fml_data_struct.FML1 / 450.0;
		fml2_lit = fml_data_struct.FML2 / 450.0;
		fml3_lit = fml_data_struct.FML3 / 450.0;
		
		if(fml1_lit >= 0.01) FloatToString(&fml1_lit, (char*)fml1, 3, 1, 2);
		if(fml2_lit >= 0.01) FloatToString(&fml2_lit, (char*)fml2, 3, 1, 2);
		if(fml3_lit >= 0.01) FloatToString(&fml3_lit, (char*)fml3, 3, 1, 2);

		if(total_2line != (fml1_lit + fml2_lit + fml3_lit))
		{
			LCD_SetCursor(1, 0);
			LCD_SendString(fml1, 5);
			LCD_SendString((uint8_t*)"  ", 2);
			LCD_SendString(fml2, 5);
			LCD_SendString((uint8_t*)"  ", 2);
			LCD_SendString(fml3, 5);
			total_2line = (fml1_lit + fml2_lit + fml3_lit);
		}

		if(total_4line != (dispenser_mode + IsOsmosWashing)) //+ litress
		{
			Int16ToString(dispenser_mode, disp_mode, 2);
			Int16ToString(IsOsmosWashing, osmos_flag, 2);
			//Int16ToString(litress_data, osmos_flag, 4);
			LCD_SetCursor(3, 2);
			LCD_SendString(disp_mode, 2); 
			LCD_SendString((uint8_t*)"     ", 5); 
			LCD_SendString(osmos_flag, 2); 
			LCD_SendString((uint8_t*)"    ", 4); 
			LCD_SendString(litress, 4); 
			total_4line = (dispenser_mode + IsOsmosWashing);
		}
		
		if(fail_hydraSystem && (!active_st))
		{
			Int16ToString(dispenser_mode, disp_mode, 2);
			Int16ToString(IsOsmosWashing, osmos_flag, 2);
			//Int16ToString(litress_data, osmos_flag, 4);
			LCD_SetCursor(3, 2);
			LCD_SendString(disp_mode, 2); 
			LCD_SendString((uint8_t*)"     ", 5); 
			LCD_SendString(osmos_flag, 2); 
			LCD_SendString((uint8_t*)"   ", 3); 
			LCD_SendString(mess_err, 6); 
			GPIO_SetOutputPin(PORT_LED_FAILTURE, PIN_LED_FAILTURE);
		}else
		{
			Int16ToString(dispenser_mode, disp_mode, 2);
			Int16ToString(IsOsmosWashing, osmos_flag, 2);
			//Int16ToString(litress_data, osmos_flag, 4);
			LCD_SetCursor(3, 2);
			LCD_SendString(disp_mode, 2); 
			LCD_SendString((uint8_t*)"     ", 5); 
			LCD_SendString(osmos_flag, 2); 
			LCD_SendString((uint8_t*)"   ", 3); 
			LCD_SendString(mess_ok, 6); 
		}
		vTaskDelay(300);	
	}
}

void vTaskUART (void *argument)
{
	while(1)
	{
		vTaskDelay(5000);
	}
}
