#include "rtc.h"

__STATIC_INLINE void APB1_GRP1_EnableClock(uint32_t Periphs);
ErrorStatus RTC_WaitForSynchro(RTC_TypeDef *RTCx);
ErrorStatus RTC_EnterInitMode(RTC_TypeDef *RTCx);
ErrorStatus RTC_ExitInitMode(RTC_TypeDef *RTCx);
ErrorStatus RTC_TIME_Init(RTC_TypeDef *RTCx, uint32_t RTC_Format, RTC_TimeTypeDef *RTC_TimeStruct);

void RTC_Init (void)
{	
	RTC_InitTypeDef RTC_InitStruct;
  RTC_TimeTypeDef RTC_TimeStruct;

	SET_BIT(PWR->CR, PWR_CR_DBP);
	
	//Enable BKP CLK enable for backup registers
	APB1_GRP1_EnableClock(RCC_APB1ENR_BKPEN);
	
	/* Peripheral clock enable */
	SET_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
	
	/**Initialize RTC and set the Time and Date */
  RTC_InitStruct.AsynchPrescaler = 0xFFFFFFFFU;
  RTC_StructInit(RTC, &RTC_InitStruct);
	
	MODIFY_REG(RTC->PRLH, RTC_PRLH_PRL, (0xFFFFFFFFU >> 16));
  MODIFY_REG(RTC->PRLL, RTC_PRLL_PRL, (0xFFFFFFFFU & RTC_PRLL_PRL));
	
	RTC_TimeStruct.Hours = 1;
  RTC_TimeStruct.Minutes = 1;
  RTC_TimeStruct.Seconds = 1;
	
	RTC_TIME_Init(RTC, RTC_FORMAT_BCD, &RTC_TimeStruct);
}

uint32_t RTC_TIME_Get(RTC_TypeDef *RTCx)
{
  register uint16_t high = 0, low = 0;

  high = READ_REG(RTCx->CNTH & RTC_CNTH_RTC_CNT);
  low  = READ_REG(RTCx->CNTL & RTC_CNTL_RTC_CNT);
  return ((uint32_t)(((uint32_t) high << 16U) | low));
}

__STATIC_INLINE void APB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1ENR, Periphs);
	
  //Delay after an RCC peripheral clock enabling
  tmpreg = READ_BIT(RCC->APB1ENR, Periphs);
  (void)tmpreg;
}

int8_t RTC_StructInit(RTC_TypeDef *RTCx, RTC_InitTypeDef *RTC_InitStruct)
{
	ErrorStatus status = SUCCESS;
  //Waiting for synchro
  if(RTC_WaitForSynchro(RTCx) != ERROR)
  {
    //Set Initialization mode
    if (RTC_EnterInitMode(RTCx) != ERROR)
    {
      //Clear Flag Bits
      CLEAR_BIT(RTCx->CRL, RTC_CRL_ALRF);
      CLEAR_BIT(RTCx->CRL, RTC_CRL_OWF);
      CLEAR_BIT(RTCx->CRL, RTC_CRL_SECF);
      
      if(RTC_InitStruct->OutPutSource != RTC_CALIB_OUTPUT_NONE)
      {
        //Disable the selected Tamper Pin
        CLEAR_BIT(BKP->CR, BKP_CR_TPE);
      }
      //Set the signal which will be routed to RTC Tamper Pin
			MODIFY_REG(BKP->RTCCR, (BKP_RTCCR_CCO | BKP_RTCCR_ASOE | BKP_RTCCR_ASOS), RTC_InitStruct->OutPutSource);
      
      //Configure Synchronous and Asynchronous prescaler factor
			MODIFY_REG(RTCx->PRLH, RTC_PRLH_PRL, (RTC_InitStruct->AsynchPrescaler >> 16));
			MODIFY_REG(RTCx->PRLL, RTC_PRLL_PRL, (RTC_InitStruct->AsynchPrescaler & RTC_PRLL_PRL));
			
      //Exit Initialization Mode
      RTC_ExitInitMode(RTCx);      
      
      status = SUCCESS;
    }
  }
  return status;
}

ErrorStatus RTC_WaitForSynchro(RTC_TypeDef *RTCx)
{
  __IO uint32_t timeout = RTC_SYNCHRO_TIMEOUT;
  ErrorStatus status = SUCCESS;
  uint32_t tmp = 0U;

  //Clear RSF flag
	CLEAR_BIT(RTCx->CRL, RTC_CRL_RSF);

  //Wait the registers to be synchronised
  tmp = (READ_BIT(RTCx->CRL, RTC_CRL_RSF) == (RTC_CRL_RSF));
	
  while ((timeout != 0U) && (tmp != 0U))
  {
    if (((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == (SysTick_CTRL_COUNTFLAG_Msk)) == 1U)
    {
      timeout--;
    }
    tmp = (READ_BIT(RTCx->CRL, RTC_CRL_RSF) == (RTC_CRL_RSF));
    if (timeout == 0U)
    {
      status = ERROR;
    }
  }
  return (status);
}

ErrorStatus RTC_EnterInitMode(RTC_TypeDef *RTCx)
{
  __IO uint32_t timeout = RTC_INITMODE_TIMEOUT;
  ErrorStatus status = SUCCESS;
  uint32_t tmp = 0U;

	//Wait till RTC is in INIT state and if Time out is reached exit
	tmp = (READ_BIT(RTCx->CRL, RTC_CRL_RTOFF) == (RTC_CRL_RTOFF));
	while ((timeout != 0U) && (tmp != 1U))
	{
		if (((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == (SysTick_CTRL_COUNTFLAG_Msk)) == 1U)
		{
			timeout --;
		}
		tmp = (READ_BIT(RTCx->CRL, RTC_CRL_RTOFF) == (RTC_CRL_RTOFF));
		if (timeout == 0U)
		{
			status = ERROR;
		}
	}

	//Disable the write protection for RTC registers
	SET_BIT(RTCx->CRL, RTC_CRL_CNF);

  return status;
}

ErrorStatus RTC_ExitInitMode(RTC_TypeDef *RTCx)
{
  __IO uint32_t timeout = RTC_INITMODE_TIMEOUT;
  ErrorStatus status = SUCCESS;
  uint32_t tmp = 0U;

  //Disable initialization mode
	CLEAR_BIT(RTCx->CRL, RTC_CRL_CNF);
  
  //Wait till RTC is in INIT state and if Time out is reached exit
  tmp = (READ_BIT(RTCx->CRL, RTC_CRL_RTOFF) == (RTC_CRL_RTOFF));
  while ((timeout != 0U) && (tmp != 1U))
  {
    if (((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == (SysTick_CTRL_COUNTFLAG_Msk)) == 1U)
    {
      timeout --;
    }
    tmp = (READ_BIT(RTCx->CRL, RTC_CRL_RTOFF) == (RTC_CRL_RTOFF));
    if (timeout == 0U)
    {
      status = ERROR;
    }
  }
  return status;
}

ErrorStatus RTC_TIME_Init(RTC_TypeDef *RTCx, uint32_t RTC_Format, RTC_TimeTypeDef *RTC_TimeStruct)
{
  ErrorStatus status = ERROR;
  uint32_t counter_time = 0U;

  //Enter Initialization mode
  if (RTC_EnterInitMode(RTCx) != ERROR)
  {
    //Check the input parameters format
    if (RTC_Format != RTC_FORMAT_BIN)
    {
			counter_time = (uint32_t)(((uint32_t)RTC_TimeStruct->Hours * 3600U) + \
											((uint32_t)RTC_TimeStruct->Minutes * 60U) + \
											((uint32_t)RTC_TimeStruct->Seconds));
			//Set RTC COUNTER MSB word
			WRITE_REG(RTCx->CNTH, (counter_time >> 16U));
			//Set RTC COUNTER LSB word
			WRITE_REG(RTCx->CNTL, (counter_time & RTC_CNTL_RTC_CNT));
    }
    else
    {
			counter_time = (((uint32_t)(_RTC_CONVERT_BCD2BIN(RTC_TimeStruct->Hours)) * 3600U) + \
											((uint32_t)(_RTC_CONVERT_BCD2BIN(RTC_TimeStruct->Minutes)) * 60U) + \
											((uint32_t)(_RTC_CONVERT_BCD2BIN(RTC_TimeStruct->Seconds))));
			//Set RTC COUNTER MSB word
			WRITE_REG(RTCx->CNTH, (counter_time >> 16U));
			//Set RTC COUNTER LSB word
			WRITE_REG(RTCx->CNTL, (counter_time & RTC_CNTL_RTC_CNT));
    }
    status = SUCCESS;
  }
  //Exit Initialization mode
  RTC_ExitInitMode(RTCx);

  return status;
}
