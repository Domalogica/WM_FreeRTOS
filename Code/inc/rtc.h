#ifndef _RTC_H_
#define _RTC_H_

#include "stm32f1xx.h"

// Values used for timeout 
#define RTC_INITMODE_TIMEOUT         		1000U // 1s when tick set to 1ms
#define RTC_SYNCHRO_TIMEOUT          		1000U // 1s when tick set to 1ms

#define RTC_CALIB_OUTPUT_NONE           (0x00000000U)                       // Calibration output disabled
#define RTC_CALIB_OUTPUT_RTCCLOCK       BKP_RTCCR_CCO                       // Calibration output is RTC Clock with a frequency divided by 64 on the TAMPER Pin
#define RTC_CALIB_OUTPUT_ALARM          BKP_RTCCR_ASOE                      // Calibration output is Alarm pulse signal on the TAMPER pin
#define RTC_CALIB_OUTPUT_SECOND        (BKP_RTCCR_ASOS | BKP_RTCCR_ASOE)    // Calibration output is Second pulse signal on the TAMPER pin

#define RTC_FORMAT_BIN                  (0x000000000U) // Binary data format
#define RTC_FORMAT_BCD                  (0x000000001U) // BCD data format

#define _RTC_CONVERT_BIN2BCD(__VALUE__) (uint8_t)((((__VALUE__) / 10U) << 4U) | ((__VALUE__) % 10U))
#define _RTC_CONVERT_BCD2BIN(__VALUE__) (uint8_t)(((uint8_t)((__VALUE__) & (uint8_t)0xF0U) >> (uint8_t)0x4U) * 10U + ((__VALUE__) & (uint8_t)0x0FU))

typedef struct
{
  uint8_t Hours;       /*!< Specifies the RTC Time Hours.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 23 */
  uint8_t Minutes;     /*!< Specifies the RTC Time Minutes.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 59 */
  uint8_t Seconds;     /*!< Specifies the RTC Time Seconds.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 59 */
} RTC_TimeTypeDef;

typedef struct
{
  uint32_t AsynchPrescaler; /*!< Specifies the RTC Asynchronous Predivider value.
                              This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFFFFF */
  uint32_t OutPutSource;    /*!< Specifies which signal will be routed to the RTC Tamper pin.
                                 This parameter can be a value of @ref LL_RTC_Output_Source  */
} RTC_InitTypeDef;


void RTC_Init (void);
uint32_t RTC_TIME_Get(RTC_TypeDef *RTCx);
int8_t RTC_StructInit(RTC_TypeDef *RTCx, RTC_InitTypeDef *RTC_InitStruct);

#endif //_RTC_H_
