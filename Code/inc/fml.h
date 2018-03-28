#ifndef _GPIO_IT_H_
#define _GPIO_IT_H_

#include "stm32f1xx.h"
#include "gpio.h"
#include "error_handler.h"

typedef struct
{
	uint32_t FML1;
	uint32_t FML2;
	uint32_t FML3;
	uint32_t FML4;
} FML_data;

void GPIO_FLM_InitIT(void);
void FLM_ResetData(void);
void FLM_ResetTic(uint8_t fml_num);

FML_data FLM_GetData(void);
uint32_t FLM_GetTic(uint8_t fml_num);


#define FLM_1                					1
#define FLM_2                					2
#define FLM_3                					3
#define FLM_4                					4

#define EXTI_MODE_IT                 ((uint8_t)0x00) /*!< Interrupt Mode */
#define EXTI_MODE_EVENT              ((uint8_t)0x01) /*!< Event Mode */
#define EXTI_MODE_IT_EVENT           ((uint8_t)0x02) /*!< Interrupt & Event Mode */

#define GPIO_AF_EXTI_PORTA            (uint32_t)0   /*!< EXTI PORT A */
#define GPIO_AF_EXTI_PORTB            (uint32_t)1   /*!< EXTI PORT B */
#define GPIO_AF_EXTI_PORTC            (uint32_t)2   /*!< EXTI PORT C */
#define GPIO_AF_EXTI_PORTD            (uint32_t)3   /*!< EXTI PORT D */
#define GPIO_AF_EXTI_PORTE            (uint32_t)4   /*!< EXTI PORT E */
#define GPIO_AF_EXTI_PORTF            (uint32_t)5   /*!< EXTI PORT F */
#define GPIO_AF_EXTI_PORTG            (uint32_t)6   /*!< EXTI PORT G */

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

#define EXTI_TRIGGER_NONE            ((uint8_t)0x00) /*!< No Trigger Mode */
#define EXTI_TRIGGER_RISING          ((uint8_t)0x01) /*!< Trigger Rising Mode */
#define EXTI_TRIGGER_FALLING         ((uint8_t)0x02) /*!< Trigger Falling Mode */
#define EXTI_TRIGGER_RISING_FALLING  ((uint8_t)0x03) /*!< Trigger Rising & Falling Mode */

#define EXTI_LINE_0                 EXTI_IMR_IM0           /*!< Extended line 0 */
#define EXTI_LINE_1                 EXTI_IMR_IM1           /*!< Extended line 1 */
#define EXTI_LINE_2                 EXTI_IMR_IM2           /*!< Extended line 2 */
#define EXTI_LINE_3                 EXTI_IMR_IM3           /*!< Extended line 3 */
#define EXTI_LINE_4                 EXTI_IMR_IM4           /*!< Extended line 4 */
#define EXTI_LINE_5                 EXTI_IMR_IM5           /*!< Extended line 5 */
#define EXTI_LINE_6                 EXTI_IMR_IM6           /*!< Extended line 6 */
#define EXTI_LINE_7                 EXTI_IMR_IM7           /*!< Extended line 7 */
#define EXTI_LINE_8                 EXTI_IMR_IM8           /*!< Extended line 8 */
#define EXTI_LINE_9                 EXTI_IMR_IM9           /*!< Extended line 9 */
#define EXTI_LINE_10                EXTI_IMR_IM10          /*!< Extended line 10 */
#define EXTI_LINE_11                EXTI_IMR_IM11          /*!< Extended line 11 */
#define EXTI_LINE_12                EXTI_IMR_IM12          /*!< Extended line 12 */
#define EXTI_LINE_13                EXTI_IMR_IM13          /*!< Extended line 13 */
#define EXTI_LINE_14                EXTI_IMR_IM14          /*!< Extended line 14 */
#define EXTI_LINE_15                EXTI_IMR_IM15          /*!< Extended line 15 */

#endif //_GPIO_IT_H_
