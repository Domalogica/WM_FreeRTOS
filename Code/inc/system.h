#ifndef _SYSTEM_H_
#define _SYSTEM_H_


void System_Init(void);

void SetSystemCoreClock(uint32_t HCLKFrequency)
{
  /* HCLK clock frequency */
  SystemCoreClock = HCLKFrequency;
}

__STATIC_INLINE void InitTick(uint32_t HCLKFrequency, uint32_t Ticks)
{
  /* Configure the SysTick to have interrupt in 1ms time base */
  SysTick->LOAD  = (uint32_t)((HCLKFrequency / Ticks) - 1UL);  /* set reload register */
  SysTick->VAL   = 0UL;                                       /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_ENABLE_Msk;                   /* Enable the Systick Timer */
}

__STATIC_INLINE void SYSTICK_SetClkSource(uint32_t Source)
{
  if (Source == SysTick_CTRL_CLKSOURCE_Msk)
  {
    SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk);
  }
  else
  {
    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk);
  }
}

//*****************************************************************RCC
__STATIC_INLINE void RCC_HSE_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEON);
}

__STATIC_INLINE uint32_t RCC_HSE_IsReady(void)
{
  return (READ_BIT(RCC->CR, RCC_CR_HSERDY) == (RCC_CR_HSERDY));
}

__STATIC_INLINE uint32_t RCC_GetSysClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_SWS));
}
//*****************************************************************PLL
__STATIC_INLINE void RCC_PLL_ConfigDomain_SYS(uint32_t Source, uint32_t PLLMul)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL,
             (Source & (RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE)) | PLLMul);
#if defined(RCC_CFGR2_PREDIV1)
#if defined(RCC_CFGR2_PREDIV1SRC)
  MODIFY_REG(RCC->CFGR2, (RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC),
             (Source & RCC_CFGR2_PREDIV1) | ((Source & (RCC_CFGR2_PREDIV1SRC << 4U)) >> 4U));
#else
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PREDIV1, (Source & RCC_CFGR2_PREDIV1));
#endif /*RCC_CFGR2_PREDIV1SRC*/
#endif /*RCC_CFGR2_PREDIV1*/
}

__STATIC_INLINE void RCC_PLL_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_PLLON);
}

__STATIC_INLINE uint32_t RCC_PLL_IsReady(void)
{
  return (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == (RCC_CR_PLLRDY));
}
//*****************************************************************Prescaler
__STATIC_INLINE void RCC_SetAHBPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, Prescaler);
}

__STATIC_INLINE void RCC_SetAPB1Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, Prescaler);
}

__STATIC_INLINE void RCC_SetAPB2Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, Prescaler);
}

__STATIC_INLINE void RCC_SetSysClkSource(uint32_t Source)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, Source);
}
//*****************************************************************FLASH
__STATIC_INLINE void FLASH_SetLatency(uint32_t Latency)
{
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, Latency);
}

__STATIC_INLINE uint32_t FLASH_GetLatency(void)
{
  return (uint32_t)(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY));
}

#endif //_SYSTEM_H_
