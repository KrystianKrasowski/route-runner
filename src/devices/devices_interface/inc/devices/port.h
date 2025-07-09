#ifndef _DEVICES_PORT_H
#define _DEVICES_PORT_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    DEVICE_NOTIFICATION_ROUTE_CONVERTIONS = 0,
    DEVICE_NOTIFICATION_TIMEOUT_GUARD_ROUTE,
    DEVICE_NOTIFICATION_DUALSHOCK2,
    DEVICE_NOTIFICATION_SERIAL_REQUEST,
} device_notification_t;

void
devices_port_isr_notification_give(device_notification_t id);

#ifdef __cplusplus
}
#endif

#endif
