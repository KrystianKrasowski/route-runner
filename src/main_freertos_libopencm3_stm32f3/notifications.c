#include "FreeRTOS.h"
#include "notifications.h"
#include "task.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define DICTIONARY_LENGTH 4

typedef struct
{
    device_notification_t keys[DICTIONARY_LENGTH];
    TaskHandle_t          values[DICTIONARY_LENGTH];
    uint8_t               free_index;
} notifications_dictionary_t;

static notifications_dictionary_t dictionary;

void
notifications_init(void)
{
    memset(&dictionary, 0, sizeof(dictionary));
}

void
notifications_put(device_notification_t id, TaskHandle_t h_task)
{
    if (dictionary.free_index < DICTIONARY_LENGTH)
    {
        dictionary.keys[dictionary.free_index]   = id;
        dictionary.values[dictionary.free_index] = h_task;
        dictionary.free_index++;
    }
}

void
devices_port_notification_give(device_notification_t id)
{
    BaseType_t   higher_priority_task_woken = pdFALSE;
    TaskHandle_t h_task                     = NULL;

    for (uint8_t i = 0; i < DICTIONARY_LENGTH; i++)
    {
        if (dictionary.keys[i] == id)
        {
            h_task = dictionary.values[i];
            break;
        }
    }

    if (NULL != h_task)
    {
        vTaskNotifyGiveFromISR(h_task, &higher_priority_task_woken);
        portYIELD_FROM_ISR(higher_priority_task_woken);
    }
}
