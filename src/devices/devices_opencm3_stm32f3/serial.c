#include "data_store.h"
#include "devices/serial.h"
#include "notification.h"
#include "serial.h"
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <utils/pool.h>
#include <utils/result.h>

POOL_DECLARE(serial, serial_conf_t, DEVICE_SERIAL_INSTANCES_NUM)

static serial_pool_t pool;

int
device_serial_read(device_serial_t const h_self, char const command)
{
    serial_conf_t const *p_self = serial_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    volatile char serial_request = data_store_get_serial_request();

    if (serial_request == command && notification_take(p_self->notification_id))
    {
        return RESULT_OK;
    }

    return RESULT_NOT_READY;
}

int
device_serial_send(device_serial_t const h_self,
                   char const            message[],
                   uint8_t               length)
{
    serial_conf_t const *p_self = serial_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (length > DEVICE_SERIAL_MAX_LINE_LENGTH)
    {
        length = DEVICE_SERIAL_MAX_LINE_LENGTH;
    }

    return RESULT_OK;
}

void
serial_init(void)
{
    serial_pool_init(&pool);
}

int
serial_create(device_serial_t const h_self, serial_conf_t const *p_conf)
{
    if (!serial_pool_alloc_at(&pool, h_self))
    {
        return -ENOMEM;
    }

    serial_conf_t *p_self = serial_pool_get(&pool, h_self);

    memcpy(p_self, p_conf, sizeof(*p_self));

    return RESULT_OK;
}
