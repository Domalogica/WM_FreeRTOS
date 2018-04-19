#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION		                1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 	0
#define configUSE_TICKLESS_IDLE                 	0
#define configUSE_IDLE_HOOK			                0
#define configUSE_TICK_HOOK			                0
#define configCPU_CLOCK_HZ			                ((unsigned long) 72000000)
#define configTICK_RATE_HZ			                ((TickType_t) 1000)
#define configMAX_PRIORITIES		                (7)
#define configMINIMAL_STACK_SIZE	              	((uint16_t)128)
#define configTOTAL_HEAP_SIZE		                ((size_t)10240) //10Kb (Total 20Kb)
#define configMAX_TASK_NAME_LEN		              	(16)
#define configUSE_TRACE_FACILITY	              	1 				//Whether we use debugging gadgets OS
#define configUSE_16_BIT_TICKS		              	0				//Size of the OS timer. 1-16 bits, 0-32 bits. The STM32 SysTick is 24-bit, so leave 0 here.
#define configIDLE_SHOULD_YIELD		              	1
#define configUSE_TASK_NOTIFICATIONS            	1
#define configUSE_MUTEXES                       	0
#define configUSE_RECURSIVE_MUTEXES             	0
#define configUSE_COUNTING_SEMAPHORES           	0

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		              	0
#define configMAX_CO_ROUTINE_PRIORITIES         	(2)

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet                    1
#define INCLUDE_uxTaskPriorityGet                   1
#define INCLUDE_vTaskDelete                         1
#define INCLUDE_vTaskSuspend                        1
#define INCLUDE_xResumeFromISR                      1
#define INCLUDE_vTaskDelayUntil                     1
#define INCLUDE_vTaskDelay                          1
#define INCLUDE_xTaskGetSchedulerState              1
#define INCLUDE_xTaskGetCurrentTaskHandle           1
#define INCLUDE_uxTaskGetStackHighWaterMark         0
#define INCLUDE_xTaskGetIdleTaskHandle              0
#define INCLUDE_eTaskGetState                       0
#define INCLUDE_xEventGroupSetBitFromISR            1
#define INCLUDE_xTimerPendFunctionCall              0
#define INCLUDE_xTaskAbortDelay                     0
#define INCLUDE_xTaskGetHandle                      0
#define INCLUDE_xTaskResumeFromISR                  1

#define xPortSysTickHandler 						SysTick_Handler
#define xPortPendSVHandler 							PendSV_Handler
#define vPortSVCHandler 							SVC_Handler

#define configKERNEL_INTERRUPT_PRIORITY 			255
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 		191 /* equivalent to 0xb0, or priority 11. */
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY		15

#endif /* FREERTOS_CONFIG_H */

