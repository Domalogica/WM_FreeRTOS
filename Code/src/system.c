#include "stm32f1xx.h"
#include "system.h"

void System_Init(void){

	FLASH_SetLatency(FLASH_ACR_LATENCY_1);

   if(FLASH_GetLatency() != FLASH_ACR_LATENCY_1)
  {
    //TODO: Error_Handler();  
  }
  RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(RCC_HSE_IsReady() != 1)
  {
    
  }
	
  RCC_PLL_ConfigDomain_SYS(RCC_CFGR_PLLSRC, RCC_CFGR_PLLMULL9);

  RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(RCC_PLL_IsReady() != 1)
  {
    
  }
  RCC_SetAHBPrescaler(RCC_CFGR_HPRE_DIV1);

  RCC_SetAPB1Prescaler(RCC_CFGR_PPRE1_DIV2);

  RCC_SetAPB2Prescaler(RCC_CFGR_PPRE2_DIV1);

  RCC_SetSysClkSource(RCC_CFGR_SW_PLL);

   /* Wait till System clock is ready */
  while(RCC_GetSysClkSource() != RCC_CFGR_SWS_PLL)
  {
  
  }
  InitTick(72000000, 1000U);

  SYSTICK_SetClkSource(SysTick_CTRL_CLKSOURCE_Msk);

  SetSystemCoreClock(72000000);

  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
}
