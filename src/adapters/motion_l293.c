#include "linebot/port.h"
#include <adapters/motion_l293.h>
#include <errno.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    l293_t motor_left;
    l293_t motor_right;
} adapter_instance_t;

POOL_DECLARE(adapter_motion_l293, adapter_instance_t, 1)

static adapter_motion_l293_pool_t pool;

void
adapters_motion_l293_init(void)
{
    adapter_motion_l293_pool_init(&pool);
}

int
adapters_motion_l293_acquire(l293_t const           h_motor_left,
                             l293_t const           h_motor_right,
                             linebot_port_motion_t *ph_self)
{
    if (!adapter_motion_l293_pool_alloc(&pool, ph_self))
    {
        return -ENOMEM;
    }

    adapter_instance_t *p_self = adapter_motion_l293_pool_get(&pool, *ph_self);

    p_self->motor_left  = h_motor_left;
    p_self->motor_right = h_motor_right;

    return RESULT_OK;
}
