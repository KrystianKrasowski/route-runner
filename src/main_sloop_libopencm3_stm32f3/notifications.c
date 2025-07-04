#include "notifications.h"
#include <devices/port.h>
#include <stdbool.h>
#include <string.h>
#include <utils/result.h>

static inline void
notifications_give(notification_t id);

static bool notifications[NOTIFICATIONS_NUM];

void
notifications_init(void)
{
    memset(notifications, 0, sizeof(notifications));
}

int
notifications_take(notification_t id)
{
    if (id >= NOTIFICATIONS_NUM)
    {
        return RESULT_NOT_READY;
    }

    if (notifications[id])
    {
        notifications[id] = false;
        return RESULT_OK;
    }

    return RESULT_NOT_READY;
}

void
devices_port_isr_notification_give(device_notification_t id)
{
    switch (id)
    {
        case DEVICE_NOTIFICATION_ROUTE_CONVERTIONS:
            notifications_give(NOTIFICATION_ROUTE_TRACKING);
            break;

        case DEVICE_NOTIFICATION_TIMEOUT_GUARD_ROUTE:
            notifications_give(NOTIFICATION_IMMEDIATE_STOP);
            break;

        case DEVICE_NOTIFICATION_SERIAL_REQUEST:
            notifications_give(NOTIFICATION_DOMAIN_DUMP);
            break;

        default:
        case DEVICE_NOTIFICATION_DUALSHOCK2:
            notifications_give(NOTIFICATION_MANUAL_CONTROL);
            break;
    }
}

static inline void
notifications_give(notification_t id)
{
    if (id < NOTIFICATIONS_NUM)
    {
        notifications[id] = true;
    }
}
