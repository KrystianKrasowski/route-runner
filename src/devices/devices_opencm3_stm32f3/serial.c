#include "data_store.h"
#include "notification.h"
#include "serial.h"
#include <errno.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    notification_t notification_id;
} serial_t;

POOL_DECLARE(serial, serial_t, DEVICE_SERIAL_INSTANCES_NUM)

static serial_pool_t pool;

int
device_serial_read(device_serial_t const h_self, char const command)
{
    serial_t const *p_self = serial_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    data_store_t *p_store         = data_store_get();
    bool          b_command_match = p_store->serial_request == command;

    if (b_command_match && notification_take(p_self->notification_id))
    {
        return RESULT_OK;
    }

    return RESULT_NOT_READY;
}

void
serial_init(void)
{
    serial_pool_init(&pool);
}

int
serial_create(device_serial_t const h_self,
              notification_t const  notification_id)
{
    if (!serial_pool_alloc_at(&pool, h_self))
    {
        return -ENOMEM;
    }

    serial_t *p_self = serial_pool_get(&pool, h_self);

    p_self->notification_id = notification_id;

    return RESULT_OK;
}
