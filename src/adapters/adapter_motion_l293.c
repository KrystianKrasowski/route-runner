#include <devices/l293.h>
#include <errno.h>
#include <pathbot/api.h>
#include <pathbot/port.h>
#include <stdint.h>
#include <stdlib.h>
#include <utils/result.h>

#define MOTOR_LEFT  DEVICE_L293_CHANNEL_12
#define MOTOR_RIGHT DEVICE_L293_CHANNEL_34

#define DUTY_CYCLE(pid) (abs(-2 * abs(pid) + 100))

static inline uint8_t
duty_cycle_left_compute(pathbot_motion_t const *p_motion);

static inline uint8_t
duty_cycle_right_compute(pathbot_motion_t const *p_motion);

static inline pathbot_direction_t
direction_left_compute(pathbot_motion_t const *p_motion);

static inline pathbot_direction_t
direction_right_compute(pathbot_motion_t const *p_motion);

static void
rotation_apply(device_l293_t h_motor, pathbot_direction_t direction);

void
pathbot_port_motion_apply(pathbot_motion_t const *p_motion)
{
    device_l293_disable(MOTOR_LEFT);
    device_l293_disable(MOTOR_RIGHT);

    uint8_t             duty_cycle_left  = duty_cycle_left_compute(p_motion);
    uint8_t             duty_cycle_right = duty_cycle_right_compute(p_motion);
    pathbot_direction_t dir_left         = direction_left_compute(p_motion);
    pathbot_direction_t dir_right        = direction_right_compute(p_motion);

    rotation_apply(MOTOR_LEFT, dir_left);
    rotation_apply(MOTOR_RIGHT, dir_right);

    device_l293_enable(MOTOR_LEFT, duty_cycle_left);
    device_l293_enable(MOTOR_RIGHT, duty_cycle_right);
}

static inline uint8_t
duty_cycle_left_compute(pathbot_motion_t const *p_motion)
{
    if (PATHBOT_DIRECTION_NONE == p_motion->direction)
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
duty_cycle_right_compute(pathbot_motion_t const *p_motion)
{
    if (PATHBOT_DIRECTION_NONE == p_motion->direction)
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

static inline pathbot_direction_t
direction_left_compute(pathbot_motion_t const *p_motion)
{
    if (p_motion->correction < -50)
    {
        return pathbot_motion_invert_direction(p_motion);
    }
    else if (-50 == p_motion->correction)
    {
        return PATHBOT_DIRECTION_NONE;
    }
    else
    {
        return p_motion->direction;
    }
}

static inline pathbot_direction_t
direction_right_compute(pathbot_motion_t const *p_motion)
{
    if (p_motion->correction > 50)
    {
        return pathbot_motion_invert_direction(p_motion);
    }
    else if (50 == p_motion->correction)
    {
        return PATHBOT_DIRECTION_NONE;
    }
    else
    {
        return p_motion->direction;
    }
}

static void
rotation_apply(device_l293_t h_motor, pathbot_direction_t direction)
{
    // ommit result value - adapter object dependencies should be already
    // validated
    switch (direction)
    {
        case PATHBOT_DIRECTION_FORWARD:
            (void)device_l293_rotate(h_motor, DEVICE_L293_ROTATION_RIGHT);
            break;

        case PATHBOT_DIRECTION_BACKWARD:
            (void)device_l293_rotate(h_motor, DEVICE_L293_ROTATION_LEFT);
            break;

        case PATHBOT_DIRECTION_NONE:
        default:
            (void)device_l293_rotate(h_motor, DEVICE_L293_ROTATION_STOP);
    }
}
