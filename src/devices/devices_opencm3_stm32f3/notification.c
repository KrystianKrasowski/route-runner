#include "notification.h"

static volatile bool notifications[NOTIFICATIONS_LENGTH];

void
notification_give(notification_t id)
{
    if (id < NOTIFICATIONS_LENGTH)
    {
        notifications[id] = true;
    }
}

bool
notification_take(notification_t id)
{
    if (id >= NOTIFICATIONS_LENGTH)
    {
        return false;
    }

    if (notifications[id])
    {
        notifications[id] = false;
        return true;
    }

    return false;
}
