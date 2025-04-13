#include <l293.h>
#include <linebot/port.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tim3.h>

#define DUTY_CYCLE(pid) (abs(-2 * abs(pid) + 100))

static l293_t motor_left;
static l293_t motor_right;

static inline uint8_t
compute_duty_cycle_left(int8_t correction);

static inline uint8_t
compute_duty_cycle_right(int8_t correction);

static inline linebot_motion_direction_t
compute_direction_left(linebot_motion_direction_t direction, int8_t correction);

static inline linebot_motion_direction_t
compute_direction_right(linebot_motion_direction_t direction,
                        int8_t                     correction);

static inline void
apply_direction_left(linebot_motion_direction_t direction);

static inline void
apply_direction_right(linebot_motion_direction_t direction);

static linebot_motion_direction_t
flip_direction(linebot_motion_direction_t direction);

void
adapters_motion_init(void)
{
    l293_t channel_left  = l293_create_channel_left();
    l293_t channel_right = l293_create_channel_right();
    memcpy(&motor_left, &channel_left, sizeof(l293_t));
    memcpy(&motor_right, &channel_right, sizeof(l293_t));

    l293_init(&motor_left);
    l293_init(&motor_right);
}

void
linebot_port_motion_apply(linebot_motion_t const motion)
{
    l293_disable(&motor_left);
    l293_disable(&motor_right);

    int8_t correction = linebot_motion_get_correction(motion);
    linebot_motion_direction_t direction = linebot_motion_get_direction(motion);

    uint8_t duty_cycle_left  = compute_duty_cycle_left(correction);
    uint8_t duty_cycle_right = compute_duty_cycle_right(correction);

    linebot_motion_direction_t direction_left =
        compute_direction_left(direction, correction);
    linebot_motion_direction_t direction_right =
        compute_direction_right(direction, correction);

    tim3_pwm_set_duty_cycle(&motor_left.pwm_channel, duty_cycle_left);
    tim3_pwm_set_duty_cycle(&motor_right.pwm_channel, duty_cycle_right);
    apply_direction_left(direction_left);
    apply_direction_right(direction_right);

    l293_enable(&motor_left);
    l293_enable(&motor_right);
}

static inline uint8_t
compute_duty_cycle_left(int8_t correction)
{
    if (correction >= -100 && correction < 0)
    {
        return DUTY_CYCLE(correction);
    }
    else
    {
        return 100;
    }
}

static inline uint8_t
compute_duty_cycle_right(int8_t correction)
{
    if (correction > 0 && correction <= 100)
    {
        return DUTY_CYCLE(correction);
    }
    else
    {
        return 100;
    }
}

static inline linebot_motion_direction_t
compute_direction_left(linebot_motion_direction_t direction, int8_t correction)
{
    if (correction < -50)
    {
        return flip_direction(direction);
    }
    else
    {
        return direction;
    }
}

static inline linebot_motion_direction_t
compute_direction_right(linebot_motion_direction_t direction, int8_t correction)
{
    if (correction > 50)
    {
        return flip_direction(direction);
    }
    else
    {
        return direction;
    }
}

static inline void
apply_direction_left(linebot_motion_direction_t direction)
{
    switch (direction)
    {
        case LINEBOT_MOTION_FORWARD:
            l293_set_right(&motor_left);
            break;
        case LINEBOT_MOTION_BACKWARD:
            l293_set_left(&motor_left);
            break;
        case LINEBOT_MOTION_NONE:
        default:
            l293_set_stop(&motor_left);
    }
}

static inline void
apply_direction_right(linebot_motion_direction_t direction)
{
    switch (direction)
    {
        case LINEBOT_MOTION_FORWARD:
            l293_set_right(&motor_right);
            break;
        case LINEBOT_MOTION_BACKWARD:
            l293_set_left(&motor_right);
            break;
        case LINEBOT_MOTION_NONE:
        default:
            l293_set_stop(&motor_right);
    }
}

static linebot_motion_direction_t
flip_direction(linebot_motion_direction_t direction)
{
    switch (direction)
    {
        case LINEBOT_MOTION_FORWARD:
            return LINEBOT_MOTION_BACKWARD;
        case LINEBOT_MOTION_BACKWARD:
            return LINEBOT_MOTION_FORWARD;
        case LINEBOT_MOTION_NONE:
        default:
            return LINEBOT_MOTION_NONE;
    }
}