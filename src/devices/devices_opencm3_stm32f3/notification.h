#ifndef _DEVICES_OPENCM3_STM32F3_NOTIFICATION_H
#define _DEVICES_OPENCM3_STM32F3_NOTIFICATION_H

#include <stdbool.h>
typedef enum
{
    NOTIFICATION_ROUTE_CONVERSIONS = 0,
    NOTIFICATION_TIMEOUT_GUARD_ROUTE,
    NOTIFICATION_DUALSHOCK2,
    NOTIFICATION_SERIAL_IN,
} notification_t;

#define NOTIFICATIONS_LENGTH 3

void
notification_give(notification_t id);

bool
notification_take(notification_t id);

bool
notification_peek(notification_t id);

#endif
