#ifndef _GPIO_H_
#define _GPIO_H_

//GPIO_PIN PIN
#define GPIO_PIN_0                      (GPIO_BSRR_BS0 << 8)  | 0x00000001U  /*!< Select pin 0 */
#define GPIO_PIN_1                      (GPIO_BSRR_BS1 << 8)  | 0x00000002U  /*!< Select pin 1 */
#define GPIO_PIN_2                      (GPIO_BSRR_BS2 << 8)  | 0x00000004U  /*!< Select pin 2 */
#define GPIO_PIN_3                      (GPIO_BSRR_BS3 << 8)  | 0x00000008U  /*!< Select pin 3 */
#define GPIO_PIN_4                      (GPIO_BSRR_BS4 << 8)  | 0x00000010U  /*!< Select pin 4 */
#define GPIO_PIN_5                      (GPIO_BSRR_BS5 << 8)  | 0x00000020U  /*!< Select pin 5 */
#define GPIO_PIN_6                      (GPIO_BSRR_BS6 << 8)  | 0x00000040U  /*!< Select pin 6 */
#define GPIO_PIN_7                      (GPIO_BSRR_BS7 << 8)  | 0x00000080U  /*!< Select pin 7 */
#define GPIO_PIN_8                      (GPIO_BSRR_BS8 << 8)  | 0x04000001U  /*!< Select pin 8 */
#define GPIO_PIN_9                      (GPIO_BSRR_BS9 << 8)  | 0x04000002U  /*!< Select pin 9 */
#define GPIO_PIN_10                     (GPIO_BSRR_BS10 << 8) | 0x04000004U  /*!< Select pin 10 */
#define GPIO_PIN_11                     (GPIO_BSRR_BS11 << 8) | 0x04000008U  /*!< Select pin 11 */
#define GPIO_PIN_12                     (GPIO_BSRR_BS12 << 8) | 0x04000010U  /*!< Select pin 12 */
#define GPIO_PIN_13                     (GPIO_BSRR_BS13 << 8) | 0x04000020U  /*!< Select pin 13 */
#define GPIO_PIN_14                     (GPIO_BSRR_BS14 << 8) | 0x04000040U  /*!< Select pin 14 */
#define GPIO_PIN_15                     (GPIO_BSRR_BS15 << 8) | 0x04000080U  /*!< Select pin 15 */
#define GPIO_PIN_ALL                    (GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_2  | \
                                         GPIO_PIN_3  | GPIO_PIN_4  | GPIO_PIN_5  | \
                                         GPIO_PIN_6  | GPIO_PIN_7  | GPIO_PIN_8  | \
                                         GPIO_PIN_9  | GPIO_PIN_10 | GPIO_PIN_11 | \
                                         GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | \
                                         GPIO_PIN_15) /*!< Select all pins */
																					
//GPIO_MODE Mode
#define GPIO_MODE_ANALOG              0x00000000U   /*!< Select analog mode */
#define GPIO_MODE_FLOATING            GPIO_CRL_CNF0_0   /*!< Select floating mode */
#define GPIO_MODE_INPUT               GPIO_CRL_CNF0_1   /*!< Select input mode */
#define GPIO_MODE_OUTPUT              GPIO_CRL_MODE0_0   /*!< Select general purpose output mode */
#define GPIO_MODE_ALTERNATE           (GPIO_CRL_CNF0_1 | GPIO_CRL_MODE0_0) /*!< Select alternate function mode */


// GPIO_OUTPUT Output Type
#define GPIO_OUTPUT_PUSHPULL          0x00000000U /*!< Select push-pull as output type */
#define GPIO_OUTPUT_OPENDRAIN         GPIO_CRL_CNF0_0 /*!< Select open-drain as output type */

//GPIO_SPEED Output Speed
#define GPIO_MODE_OUTPUT_10MHz        GPIO_CRL_MODE0_0            /*!< Select Output mode, max speed 10 MHz */
#define GPIO_MODE_OUTPUT_2MHz         GPIO_CRL_MODE0_1            /*!< Select Output mode, max speed 20 MHz */
#define GPIO_MODE_OUTPUT_50MHz        GPIO_CRL_MODE0              /*!< Select Output mode, max speed 50 MHz */

//GPIO_PULL Pull Up Pull Down
#define GPIO_PULL_NO                  (0x00000000U)  /*!< Select I/O no pull */
#define GPIO_PULL_DOWN                (0x00000000U)    /*!< Select I/O pull down */
#define GPIO_PULL_UP                  GPIO_ODR_ODR0  /*!< Select I/O pull up */


//GPIO_EVENTOUT_PIN EVENTOUT Pin
#define GPIO_AF_EVENTOUT_PIN_0        AFIO_EVCR_PIN_PX0   /*!< EVENTOUT on pin 0 */
#define GPIO_AF_EVENTOUT_PIN_1        AFIO_EVCR_PIN_PX1   /*!< EVENTOUT on pin 1 */
#define GPIO_AF_EVENTOUT_PIN_2        AFIO_EVCR_PIN_PX2   /*!< EVENTOUT on pin 2 */
#define GPIO_AF_EVENTOUT_PIN_3        AFIO_EVCR_PIN_PX3   /*!< EVENTOUT on pin 3 */
#define GPIO_AF_EVENTOUT_PIN_4        AFIO_EVCR_PIN_PX4   /*!< EVENTOUT on pin 4 */
#define GPIO_AF_EVENTOUT_PIN_5        AFIO_EVCR_PIN_PX5   /*!< EVENTOUT on pin 5 */
#define GPIO_AF_EVENTOUT_PIN_6        AFIO_EVCR_PIN_PX6   /*!< EVENTOUT on pin 6 */
#define GPIO_AF_EVENTOUT_PIN_7        AFIO_EVCR_PIN_PX7   /*!< EVENTOUT on pin 7 */
#define GPIO_AF_EVENTOUT_PIN_8        AFIO_EVCR_PIN_PX8   /*!< EVENTOUT on pin 8 */
#define GPIO_AF_EVENTOUT_PIN_9        AFIO_EVCR_PIN_PX9   /*!< EVENTOUT on pin 9 */
#define GPIO_AF_EVENTOUT_PIN_10       AFIO_EVCR_PIN_PX10  /*!< EVENTOUT on pin 10 */
#define GPIO_AF_EVENTOUT_PIN_11       AFIO_EVCR_PIN_PX11  /*!< EVENTOUT on pin 11 */
#define GPIO_AF_EVENTOUT_PIN_12       AFIO_EVCR_PIN_PX12  /*!< EVENTOUT on pin 12 */
#define GPIO_AF_EVENTOUT_PIN_13       AFIO_EVCR_PIN_PX13  /*!< EVENTOUT on pin 13 */
#define GPIO_AF_EVENTOUT_PIN_14       AFIO_EVCR_PIN_PX14  /*!< EVENTOUT on pin 14 */
#define GPIO_AF_EVENTOUT_PIN_15       AFIO_EVCR_PIN_PX15  /*!< EVENTOUT on pin 15 */

//GPIO_EVENTOUT_PORT EVENTOUT Port
#define GPIO_AF_EVENTOUT_PORT_A       AFIO_EVCR_PORT_PA  /*!< EVENTOUT on port A */
#define GPIO_AF_EVENTOUT_PORT_B       AFIO_EVCR_PORT_PB  /*!< EVENTOUT on port B */
#define GPIO_AF_EVENTOUT_PORT_C       AFIO_EVCR_PORT_PC  /*!< EVENTOUT on port C */
#define GPIO_AF_EVENTOUT_PORT_D       AFIO_EVCR_PORT_PD  /*!< EVENTOUT on port D */
#define GPIO_AF_EVENTOUT_PORT_E       AFIO_EVCR_PORT_PE  /*!< EVENTOUT on port E */

//GPIO_EXTI_PORT GPIO EXTI PORT
#define GPIO_AF_EXTI_PORTA            (uint32_t)0   /*!< EXTI PORT A */
#define GPIO_AF_EXTI_PORTB            (uint32_t)1   /*!< EXTI PORT B */
#define GPIO_AF_EXTI_PORTC            (uint32_t)2   /*!< EXTI PORT C */
#define GPIO_AF_EXTI_PORTD            (uint32_t)3   /*!< EXTI PORT D */
#define GPIO_AF_EXTI_PORTE            (uint32_t)4   /*!< EXTI PORT E */
#define GPIO_AF_EXTI_PORTF            (uint32_t)5   /*!< EXTI PORT F */
#define GPIO_AF_EXTI_PORTG            (uint32_t)6   /*!< EXTI PORT G */

//GPIO_LL_EC_EXTI_LINE GPIO EXTI LINE
#define GPIO_AF_EXTI_LINE0            (uint32_t)(0x000FU << 16 | 0)  /*!< EXTI_POSITION_0  | EXTICR[0] */
#define GPIO_AF_EXTI_LINE1            (uint32_t)(0x00F0U << 16 | 0)  /*!< EXTI_POSITION_4  | EXTICR[0] */
#define GPIO_AF_EXTI_LINE2            (uint32_t)(0x0F00U << 16 | 0)  /*!< EXTI_POSITION_8  | EXTICR[0] */
#define GPIO_AF_EXTI_LINE3            (uint32_t)(0xF000U << 16 | 0)  /*!< EXTI_POSITION_12 | EXTICR[0] */
#define GPIO_AF_EXTI_LINE4            (uint32_t)(0x000FU << 16 | 1)  /*!< EXTI_POSITION_0  | EXTICR[1] */
#define GPIO_AF_EXTI_LINE5            (uint32_t)(0x00F0U << 16 | 1)  /*!< EXTI_POSITION_4  | EXTICR[1] */
#define GPIO_AF_EXTI_LINE6            (uint32_t)(0x0F00U << 16 | 1)  /*!< EXTI_POSITION_8  | EXTICR[1] */
#define GPIO_AF_EXTI_LINE7            (uint32_t)(0xF000U << 16 | 1)  /*!< EXTI_POSITION_12 | EXTICR[1] */
#define GPIO_AF_EXTI_LINE8            (uint32_t)(0x000FU << 16 | 2)  /*!< EXTI_POSITION_0  | EXTICR[2] */
#define GPIO_AF_EXTI_LINE9            (uint32_t)(0x00F0U << 16 | 2)  /*!< EXTI_POSITION_4  | EXTICR[2] */
#define GPIO_AF_EXTI_LINE10           (uint32_t)(0x0F00U << 16 | 2)  /*!< EXTI_POSITION_8  | EXTICR[2] */
#define GPIO_AF_EXTI_LINE11           (uint32_t)(0xF000U << 16 | 2)  /*!< EXTI_POSITION_12 | EXTICR[2] */
#define GPIO_AF_EXTI_LINE12           (uint32_t)(0x000FU << 16 | 3)  /*!< EXTI_POSITION_0  | EXTICR[3] */
#define GPIO_AF_EXTI_LINE13           (uint32_t)(0x00F0U << 16 | 3)  /*!< EXTI_POSITION_4  | EXTICR[3] */
#define GPIO_AF_EXTI_LINE14           (uint32_t)(0x0F00U << 16 | 3)  /*!< EXTI_POSITION_8  | EXTICR[3] */
#define GPIO_AF_EXTI_LINE15           (uint32_t)(0xF000U << 16 | 3)  /*!< EXTI_POSITION_12 | EXTICR[3] */

//************************************************************************************************************
//	GPIO_WRITE_READ Common Write and read registers Macros
/**
  * @brief  Write a value in GPIO register
  * @param  __INSTANCE__ GPIO Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define GPIO_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in GPIO register
  * @param  __INSTANCE__ GPIO Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define GPIO_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)

//**********************************************************************************************************

//GPIO_Functions and Port_Configuration
/* @note   I/O mode can be Analog, Floating input, Input with pull-up/pull-down, 
					 General purpose Output, Alternate function Output.
   @param  Pin This parameter can be one of the following values:
           GPIO_PIN_0,  GPIO_PIN_1,  GPIO_PIN_2,  GPIO_PIN_3,
			GPIO_PIN_4,  GPIO_PIN_5,  GPIO_PIN_6,  GPIO_PIN_7,
					 GPIO_PIN_8,  GPIO_PIN_9,  GPIO_PIN_10, GPIO_PIN_11,
           GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15
   @param  Mode This parameter can be one of the following values:
           GPIO_MODE_ANALOG
           GPIO_MODE_FLOATING
           GPIO_MODE_INPUT
           GPIO_MODE_OUTPUT
           GPIO_MODE_ALTERNATE
	 @param  OutputType This parameter can be one of the following values:
           @arg GPIO_OUTPUT_PUSHPULL
           @arg GPIO_OUTPUT_OPENDRAIN
	 @param  Pull This parameter can be one of the following values:
           @arg GPIO_PULL_DOWN
           @arg GPIO_PULL_UP   */
	
//	Configure gpio mode for a dedicated pin on dedicated port.
//	Warning:  only one pin can be passed as parameter.
__STATIC_INLINE void GPIO_SetPinMode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode)
{
  register uint32_t *pReg = (uint32_t *)((uint32_t)((uint32_t)(&GPIOx->CRL) + (Pin>>24)));
  MODIFY_REG(*pReg, ((GPIO_CRL_CNF0|GPIO_CRL_MODE0) << (POSITION_VAL(Pin) * 4U)), (Mode << (POSITION_VAL(Pin) * 4U)));
}


//	Return gpio mode for a dedicated pin on dedicated port.
__STATIC_INLINE uint32_t GPIO_GetPinMode(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  register uint32_t *pReg = (uint32_t *)((uint32_t)((uint32_t)(&GPIOx->CRL) + (Pin>>24)));
  return (uint32_t)(READ_BIT(*pReg, ((GPIO_CRL_CNF0|GPIO_CRL_MODE0) << (POSITION_VAL(Pin) * 4U))) >> (POSITION_VAL(Pin) * 4U));
}


//	Speed This parameter can be one of the following values:
__STATIC_INLINE void GPIO_SetPinSpeed(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t  Speed)
{
  register uint32_t *pReg = (uint32_t *)((uint32_t)((uint32_t)(&GPIOx->CRL) + (Pin>>24)));
  MODIFY_REG(*pReg, (GPIO_CRL_MODE0 << (POSITION_VAL(Pin) * 4U)), (Speed << (POSITION_VAL(Pin) * 4U)));
}


//	Returned value can be one of the following values:
__STATIC_INLINE uint32_t GPIO_GetPinSpeed(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  register uint32_t *pReg = (uint32_t *)((uint32_t)((uint32_t)(&GPIOx->CRL) + (Pin>>24)));
  return (uint32_t)(READ_BIT(*pReg, (GPIO_CRL_MODE0 << (POSITION_VAL(Pin) * 4U))) >> (POSITION_VAL(Pin) * 4U));
}


//OutputType This parameter can be one of the following values:
__STATIC_INLINE void GPIO_SetPinOutputType(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t OutputType)
{
  register uint32_t *pReg = (uint32_t *)((uint32_t)((uint32_t)(&GPIOx->CRL) + (Pin>>24)));
  MODIFY_REG(*pReg, (GPIO_CRL_CNF0_0 << (POSITION_VAL(Pin) * 4U)), (OutputType << (POSITION_VAL(Pin) * 4U)));
}


//	Returned value can be one of the following values:
//	@arg GPIO_OUTPUT_PUSHPULL
//	@arg GPIO_OUTPUT_OPENDRAIN
__STATIC_INLINE uint32_t GPIO_GetPinOutputType(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  register uint32_t *pReg = (uint32_t *)((uint32_t)((uint32_t)(&GPIOx->CRL) + (Pin>>24)));
  return (uint32_t)(READ_BIT(*pReg, (GPIO_CRL_CNF0_0 << (POSITION_VAL(Pin) * 4U))) >> (POSITION_VAL(Pin) * 4U));

}


//	Pull This parameter can be one of the following values:
//	@arg GPIO_PULL_DOWN
//	@arg GPIO_PULL_UP
__STATIC_INLINE void GPIO_SetPinPull(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Pull)
{
  MODIFY_REG(GPIOx->ODR, (Pin>>8) , Pull << (POSITION_VAL(Pin>>8)));
}


//	Warning: only one pin can be passed as parameter.
//	Returned value can be one of the following values:
//	@arg GPIO_PULL_DOWN
//  @arg GPIO_PULL_UP
__STATIC_INLINE uint32_t GPIO_GetPinPull(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->ODR, (GPIO_ODR_ODR0 << (POSITION_VAL(Pin>>8)))) >> (POSITION_VAL(Pin>>8)));
}


//	Lock configuration of several pins for a dedicated port.
__STATIC_INLINE void GPIO_LockPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  __IO uint32_t temp;
  WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | ((PinMask >> 8) & 0x0000FFFFU));
  WRITE_REG(GPIOx->LCKR, ((PinMask >>8 ) & 0x0000FFFFU));
  WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | ((PinMask>>8) & 0x0000FFFFU));
  temp = READ_REG(GPIOx->LCKR);
  (void) temp;
}


//	Return 1 if all pins passed as parameter, of a dedicated port, are locked. else Return 0.
  __STATIC_INLINE uint32_t GPIO_IsPinLocked(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return (READ_BIT(GPIOx->LCKR, ((PinMask >> 8 ) & 0x0000FFFFU)) == ((PinMask >>8 ) & 0x0000FFFFU));
}


//	Return 1 if one of the pin of a dedicated port is locked. else return 0.
__STATIC_INLINE uint32_t GPIO_IsAnyPinLocked(GPIO_TypeDef *GPIOx)
{
  return (READ_BIT(GPIOx->LCKR, GPIO_LCKR_LCKK) == (GPIO_LCKR_LCKK));
}


//	Return full input data register value for a dedicated port.
__STATIC_INLINE uint32_t GPIO_ReadInputPort(GPIO_TypeDef *GPIOx)
{
  return (uint32_t)(READ_REG(GPIOx->IDR));
}


//	Return if input data level for several pins of dedicated port is high or low.
//	Return state of bit (1 or 0)
__STATIC_INLINE uint32_t GPIO_IsInputPinSet(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return (READ_BIT(GPIOx->IDR, (PinMask >> 8 ) & 0x0000FFFFU) == ((PinMask >> 8 ) & 0x0000FFFFU));
}


//	Write output data register for the port.
__STATIC_INLINE void GPIO_WriteOutputPort(GPIO_TypeDef *GPIOx, uint32_t PortValue)
{
  WRITE_REG(GPIOx->ODR, PortValue);
}


//	Return full output data register value for a dedicated port.
__STATIC_INLINE uint32_t GPIO_ReadOutputPort(GPIO_TypeDef *GPIOx)
{
  return (uint32_t)(READ_REG(GPIOx->ODR));
}


//	Return if input data level for several pins of dedicated port is high or low.
//	Return state of bit (1 or 0).
__STATIC_INLINE uint32_t GPIO_IsOutputPinSet(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return (READ_BIT(GPIOx->ODR, (PinMask >> 8 ) & 0x0000FFFFU) == ((PinMask >> 8 ) & 0x0000FFFFU));
}


// Set several pins to high level on dedicated gpio port.
__STATIC_INLINE void GPIO_SetOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  WRITE_REG(GPIOx->BSRR, (PinMask >> 8) & 0x0000FFFFU);
}


//	Set several pins to low level on dedicated gpio port.
__STATIC_INLINE void GPIO_ResetOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  WRITE_REG(GPIOx->BRR, (PinMask >> 8 ) & 0x0000FFFFU);
}


//	Toggle data value for several pin of dedicated port.
__STATIC_INLINE void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  WRITE_REG(GPIOx->ODR, READ_REG(GPIOx->ODR) ^ ((PinMask >> 8 ) & 0x0000FFFFU));
}

#endif //_GPIO_H_
