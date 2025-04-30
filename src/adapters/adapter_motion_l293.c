#include "devices/l293.h"
#include "linebot/motion.h"
#include <adapters/motion_l293.h>
#include <errno.h>
#include <linebot/port.h>
#include <stdint.h>
#include <stdlib.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    device_l293_t motor_left;
    device_l293_t motor_right;
} adapter_instance_t;

POOL_DECLARE(adapter_motion_l293, adapter_instance_t, 1)

#define DUTY_CYCLE(pid) (abs(-2 * abs(pid) + 100))

static adapter_motion_l293_pool_t pool;

static inline uint8_t
duty_cycle_left_compute(linebot_motion_t const *p_motion);

static inline uint8_t
duty_cycle_right_compute(linebot_motion_t const *p_motion);

static inline linebot_direction_t
direction_left_compute(linebot_motion_t const *p_motion);

static inline linebot_direction_t
direction_right_compute(linebot_motion_t const *p_motion);

static void
rotation_apply(device_l293_t h_motor, linebot_direction_t direction);

void
adapter_motion_l293_init(void)
{
    adapter_motion_l293_pool_init(&pool);
}

int
adapter_motion_l293_acquire(device_l293_t const    h_motor_left,
                            device_l293_t const    h_motor_right,
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

void
adapter_motion_l293_release(linebot_port_motion_t const h_self)
{
    adapter_motion_l293_pool_free(&pool, h_self);
}

int
linebot_port_motion_apply(linebot_port_motion_t const h_self,
                          linebot_motion_t const     *p_motion)
{
    adapter_instance_t *p_self = adapter_motion_l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -EINVAL;
    }

    // maybe I should validate devices here ?
    device_l293_disable(p_self->motor_left);
    device_l293_disable(p_self->motor_right);

    uint8_t             duty_cycle_left  = duty_cycle_left_compute(p_motion);
    uint8_t             duty_cycle_right = duty_cycle_right_compute(p_motion);
    linebot_direction_t dir_left         = direction_left_compute(p_motion);
    linebot_direction_t dir_right        = direction_right_compute(p_motion);

    rotation_apply(p_self->motor_left, dir_left);
    rotation_apply(p_self->motor_right, dir_right);

    device_l293_enable(p_self->motor_left, duty_cycle_left);
    device_l293_enable(p_self->motor_right, duty_cycle_right);

    return RESULT_OK;
}

static inline uint8_t
duty_cycle_left_compute(linebot_motion_t const *p_motion)
{
    if (LINEBOT_DIRECTION_NONE == p_motion->direction)
    {
        return 0;
    }
    else if (p_motion->correction >= -100 && p_motion->correction < 0)
    {
        return DUTY_CYCLE(p_motion->correction);
    }
    else
    {
        return 100;
    }
}

static inline uint8_t
duty_cycle_right_compute(linebot_motion_t const *p_motion)
{
    if (LINEBOT_DIRECTION_NONE == p_motion->direction)
    {
        return 0;
    }
    else if (p_motion->correction > 0 && p_motion->correction <= 100)
    {
        return DUTY_CYCLE(p_motion->correction);
    }
    else
    {
        return 100;
    }
}

static inline linebot_direction_t
direction_left_compute(linebot_motion_t const *p_motion)
{
    if (p_motion->correction < -50)
    {
        return linebot_motion_invert_direction(p_motion);
    }
    else if (-50 == p_motion->correction)
    {
        return LINEBOT_DIRECTION_NONE;
    }
    else
    {
        return p_motion->direction;
    }
}

static inline linebot_direction_t
direction_right_compute(linebot_motion_t const *p_motion)
{
    if (p_motion->correction > 50)
    {
        return linebot_motion_invert_direction(p_motion);
    }
    else if (50 == p_motion->correction)
    {
        return LINEBOT_DIRECTION_NONE;
    }
    else
    {
        return p_motion->direction;
    }
}

static void
rotation_apply(device_l293_t h_motor, linebot_direction_t direction)
{
    // ommit result value - adapter object dependencies should be already
    // validated
    switch (direction)
    {
        case LINEBOT_DIRECTION_FORWARD:
            (void)device_l293_rotate(h_motor, DEVICE_L293_ROTATION_RIGHT);
            break;

        case LINEBOT_DIRECTION_BACKWARD:
            (void)device_l293_rotate(h_motor, DEVICE_L293_ROTATION_LEFT);
            break;

        case LINEBOT_DIRECTION_NONE:
        default:
            (void)device_l293_rotate(h_motor, DEVICE_L293_ROTATION_STOP);
    }
}
