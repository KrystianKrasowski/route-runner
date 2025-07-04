#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION                    1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
#define configUSE_TICKLESS_IDLE                 0
#define configCPU_CLOCK_HZ                      16000000
#define configSYSTICK_CLOCK_HZ                  1000000
#define configTICK_RATE_HZ                      250
#define configMAX_PRIORITIES                    4
#define configMINIMAL_STACK_SIZE                32
#define configMAX_TASK_NAME_LEN                 16
#define configUSE_16_BIT_TICKS                  0
#define configIDLE_SHOULD_YIELD                 0
#define configUSE_TASK_NOTIFICATIONS            1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES   1
#define configUSE_MUTEXES                       0
#define configUSE_RECURSIVE_MUTEXES             0
#define configUSE_COUNTING_SEMAPHORES           0
#define configQUEUE_REGISTRY_SIZE               10
#define configUSE_QUEUE_SETS                    0
#define configUSE_TIME_SLICING                  1
#define configUSE_NEWLIB_REENTRANT              0
#define configENABLE_BACKWARD_COMPATIBILITY     0
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 1
#define configUSE_MINI_LIST_ITEM                1
#define configSTACK_DEPTH_TYPE                  uint16_t
#define configMESSAGE_BUFFER_LENGTH_TYPE        size_t
#define configHEAP_CLEAR_MEMORY_ON_FREE         1

// Memory allocation related definitions

#define configSUPPORT_STATIC_ALLOCATION           1
#define configKERNEL_PROVIDED_STATIC_MEMORY       1
#define configSUPPORT_DYNAMIC_ALLOCATION          1
#define configTOTAL_HEAP_SIZE                     4096
#define configAPPLICATION_ALLOCATED_HEAP          0
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP 0

// Hook functions related definitions

#define configUSE_IDLE_HOOK                0
#define configUSE_TICK_HOOK                0
#define configCHECK_FOR_STACK_OVERFLOW     2
#define configUSE_MALLOC_FAILED_HOOK       0
#define configUSE_DAEMON_TASK_STARTUP_HOOK 0
#define configUSE_SB_COMPLETED_CALLBACK    0

// Runtime and task stats gathering related definitions

#define configGENERATE_RUN_TIME_STATS        0
#define configUSE_TRACE_FACILITY             0
#define configUSE_STATS_FORMATTING_FUNCTIONS 0

// Co-routine related definitions

#define configUSE_CO_ROUTINES           0
#define configMAX_CO_ROUTINE_PRIORITIES 1

// Software timer related definitions

#define configUSE_TIMERS             0
#define configTIMER_TASK_PRIORITY    3
#define configTIMER_QUEUE_LENGTH     10
#define configTIMER_TASK_STACK_DEPTH configMINIMAL_STACK_SIZE

// Interrupt nesting behaviour configuration
#define BASEPRI_BITS                         4
#define BASEPRI_POS                          (8 - BASEPRI_BITS)
#define configKERNEL_INTERRUPT_PRIORITY      (15 << BASEPRI_POS)
#define configMAX_SYSCALL_INTERRUPT_PRIORITY (5 << BASEPRI_POS)

// Define to trap errors during development - TODO

// FreeRTOS MPU specific definitions

#define configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS 0
#define configTOTAL_MPU_REGIONS                                16
#define configTEX_S_C_B_FLASH                                  0x07UL
#define configTEX_S_C_B_SRAM                                   0x07UL
#define configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY            1
#define configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS             0
#define configENABLE_ERRATA_837070_WORKAROUND                  1

// API functions to include

#define INCLUDE_vTaskPrioritySet  1
#define INCLUDE_uxTaskPriorityGet 1
#define INCLUDE_vTaskDelete       1
#define INCLUDE_vTaskSuspend      1
#define INCLUDE_vTaskDelay        1
#define INCLUDE_vTaskDelayUntil   1

// libopencm3 handlers

#define vPortSVCHandler     sv_call_handler
#define xPortPendSVHandler  pend_sv_handler
#define xPortSysTickHandler sys_tick_handler

#endif /* FREERTOS_CONFIG_H */
