#include "notification.h"
#include "qtrhd06a.h"
#include <errno.h>
#include <stdint.h>
#include <utils/pool.h>
#include <utils/result.h>

POOL_DECLARE(qtrhd06a, qtrhd06a_conf_t, DEVICE_QTRHD06A_INSTANCES_NUM)

static qtrhd06a_pool_t pool;

void
qtrhd06a_init(void)
{
    qtrhd06a_pool_init(&pool);
}

int
qtrhd06a_create(device_qtrhd06a_t const h_self, qtrhd06a_conf_t const *p_conf)
{
    if (!qtrhd06a_pool_alloc_at(&pool, h_self))
    {
        return -ENOMEM;
    }

    qtrhd06a_conf_t *p_self = qtrhd06a_pool_get(&pool, h_self);

    memcpy(p_self, p_conf, sizeof(*p_self));

    return RESULT_OK;
}

int
device_qtrhd06a_read(device_qtrhd06a_t const h_self, uint8_t values[])
{
    qtrhd06a_conf_t *p_self = qtrhd06a_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (!notification_take(NOTIFICATION_ROUTE_CONVERSIONS))
    {
        return RESULT_NOT_READY;
    }

    // TODO: handle values size
    uint16_t l3 = 0;
    uint16_t l2 = 0;
    uint16_t l1 = 0;
    uint16_t r1 = 0;
    uint16_t r2 = 0;
    uint16_t r3 = 0;

    for (uint8_t i = 0; i < p_self->raw_values_length; i += 4)
    {
        r1 += (p_self->p_raw_values[i] >> 8) & 0xff;
        r3 += (p_self->p_raw_values[i]) & 0xff;
        l1 += (p_self->p_raw_values[i + 1] >> 8) & 0xff;
        r2 += (p_self->p_raw_values[i + 1]) & 0xff;
        l2 += (p_self->p_raw_values[i + 2] >> 8) & 0xff;
        l3 += (p_self->p_raw_values[i + 3] >> 8) & 0xff;
    }

    values[0] = l3 / 10;
    values[1] = l2 / 10;
    values[2] = l1 / 10;
    values[3] = r1 / 10;
    values[4] = r2 / 10;
    values[5] = r3 / 10;

    return RESULT_OK;
}
