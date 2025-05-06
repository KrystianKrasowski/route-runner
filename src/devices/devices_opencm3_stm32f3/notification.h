#ifndef _DEVICES_OPENCM3_STM32F3_NOTIFICATION_H
#define _DEVICES_OPENCM3_STM32F3_NOTIFICATION_H

#include <stdbool.h>
typedef enum
{
    NOTIFICATION_ROUTE_CONVERSIONS = 0,
    NOTIFICATION_ROUTE_GUARD,
} notification_t;

#define NOTIFICATIONS_LENGTH 2

void
notification_give(notification_t notification);

bool
notification_take(notification_t notification);

#endif
