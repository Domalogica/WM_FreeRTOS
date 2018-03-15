#include "stm32f1xx.h"
#include "system.h"


void RCC_Init (void){
	
	RCC->CR |= ((uint32_t)RCC_CR_HSEON); 												// Enable HSE
	while (!(RCC->CR & RCC_CR_HSERDY));													// Ready start HSE		
	
	FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;					// Cloclk Flash memory
	
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;														// AHB = SYSCLK/1
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;														// APB1 = HCLK/1
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;														// APB2 = HCLK/1
	
	RCC->CFGR &= ~RCC_CFGR_PLLMULL;               							// clear PLLMULL bits
	RCC->CFGR &= ~RCC_CFGR_PLLSRC;															// clearn PLLSRC bits
	RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;														// clearn PLLXTPRE bits
	
	RCC->CFGR |= RCC_CFGR_PLLSRC; 															// source HSE
	RCC->CFGR |= RCC_CFGR_PLLXTPRE_HSE; 												// source HSE/2 = 4 MHz  //RCC_CFGR_PLLXTPRE_HSE_DIV2
	RCC->CFGR |= RCC_CFGR_PLLMULL6; 														// PLL x6: clock = 4 MHz * 6 = 24 MHz

	RCC->CR |= RCC_CR_PLLON;                      							// enable PLL
	while((RCC->CR & RCC_CR_PLLRDY) == 0) {}      							// wait till PLL is ready
	
	RCC->CFGR &= ~RCC_CFGR_SW;                   							 	// clear SW bits
  RCC->CFGR |= RCC_CFGR_SW_PLL;                 							// select source SYSCLK = PLL
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) {} 			// wait till PLL is used
		
}

void MCO_out (void){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;                       	// enable clock for port A
	
	GPIOA->CRH &= ~GPIO_CRH_CNF8_0;															// setting out alternative push-pull for PA8
	GPIOA->CRH |= GPIO_CRH_CNF8_1;
	GPIOA->CRH |= (GPIO_CRH_MODE8_0 | GPIO_CRH_MODE8_1);				// gpio speed 50 MHz
	
	RCC->CFGR |= RCC_CFGR_MCO_SYSCLK;														// select source clokc SYSCLK
	
}



/*
void System_Init(void){

	
  RCC_PLL_ConfigDomain_SYS(RCC_CFGR_PLLSRC, RCC_CFGR_PLLMULL9);

  RCC_PLL_Enable();

  //Wait till PLL is ready 
  while(RCC_PLL_IsReady() != 1)
  {
    
  }
  RCC_SetAHBPrescaler(RCC_CFGR_HPRE_DIV1);

  RCC_SetAPB1Prescaler(RCC_CFGR_PPRE1_DIV2);

  RCC_SetAPB2Prescaler(RCC_CFGR_PPRE2_DIV1);

  RCC_SetSysClkSource(RCC_CFGR_SW_PLL);

  //Wait till System clock is ready 
  while(RCC_GetSysClkSource() != RCC_CFGR_SWS_PLL)
  {
  
  }
  InitTick(72000000, 1000U);

  SYSTICK_SetClkSource(SysTick_CTRL_CLKSOURCE_Msk);

  SetSystemCoreClock(72000000);

  // SysTick_IRQn interrupt configuration 
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
}
*/
