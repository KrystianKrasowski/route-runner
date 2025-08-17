#pragma once

// Clock configuration
#define APP_SYSTEM_CLOCK_FREQUENCY 16000000UL
#define APP_AHB_FREQUENCY          APP_SYSTEM_CLOCK_FREQUENCY
#define APP_APB1_FREQUENCY         (APP_SYSTEM_CLOCK_FREQUENCY / 2)
#define APP_APB2_FREQUENCY         APP_SYSTEM_CLOCK_FREQUENCY
#define APP_SYSTICK_FREQUENCY      1000000UL

// FreeRTOS task memory configuration
// Those values were determined by monitored task high watermark with 15-20%
// margin added, but no less than 16 words
#define TASK_MEM_DOMAIN_DUMP          97
#define TASK_MEM_IMMEDIATE_STOP       45
#define TASK_MEM_MANUAL_DISPATCH      47
#define TASK_MEM_MANUAL_MODE_SWITCH   56
#define TASK_MEM_MANUAL_MOTION        56
#define TASK_MEM_MANUAL_PID_TUNE      56
#define TASK_MEM_ROUTE_GUARD_TOGGLE   56
#define TASK_MEM_SHELL_COMMAND        44
#define TASK_MEM_SHELL_OUTPUT         60
#define TASK_MEM_TRACKING_DISPATCH    54
#define TASK_MEM_TRACKING_MODE_SWITCH 60
#define TASK_MEM_TRACKING_MOTION      56
#define TASK_MEM_USAGE_DUMP           226

