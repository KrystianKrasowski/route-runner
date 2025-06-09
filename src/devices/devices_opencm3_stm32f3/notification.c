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
    if (notification_peek(id))
    {
        notifications[id] = false;
        return true;
    }

    return false;
}

bool
// cppcheck-suppress staticFunction
notification_peek(notification_t id)
{
    if (id >= NOTIFICATIONS_LENGTH)
    {
        return false;
    }

    if (notifications[id])
    {
        return true;
    }

    return false;
}
