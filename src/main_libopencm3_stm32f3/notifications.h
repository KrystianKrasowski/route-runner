#ifndef _MAIN_BASIC_NOTIFICATIONS_H
#define _MAIN_BASIC_NOTIFICATIONS_H

#define NOTIFICATIONS_NUM 4

typedef enum
{
    NOTIFICATION_MANUAL_CONTROL = 0,
    NOTIFICATION_ROUTE_TRACKING,
    NOTIFICATION_IMMEDIATE_STOP,
    NOTIFICATION_DOMAIN_DUMP,
} notification_t;

void
notifications_init(void);

int
notifications_take(notification_t id);

#endif
