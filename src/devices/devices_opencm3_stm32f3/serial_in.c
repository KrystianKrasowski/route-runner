#include "data_store.h"
#include "notification.h"
#include "serial_in.h"
#include <errno.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    notification_t notification_id;
} serial_in_t;

POOL_DECLARE(serial_in, serial_in_t, DEVICE_SERIAL_IN_INSTANCES_NUM)

static serial_in_pool_t pool;

int
device_serial_in_read(device_serial_in_t const h_self, char const command)
{
    serial_in_t const *p_self = serial_in_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    data_store_t *p_store         = data_store_get();
    bool          b_command_match = p_store->serial_in_request == command;

    if (b_command_match && notification_take(p_self->notification_id))
    {
        return RESULT_OK;
    }

    return RESULT_NOT_READY;
}

void
serial_in_init(void)
{
    serial_in_pool_init(&pool);
}

int
serial_in_create(device_serial_in_t const h_self,
                 notification_t const     notification_id)
{
    if (!serial_in_pool_alloc_at(&pool, h_self))
    {
        return -ENOMEM;
    }

    serial_in_t *p_self = serial_in_pool_get(&pool, h_self);

    p_self->notification_id = notification_id;

    return RESULT_OK;
}
