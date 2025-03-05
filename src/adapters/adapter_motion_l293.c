#include <core.h>
#include <l293.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tim3.h>

#define MIN_DUTY_CYCLE 0
#define MAX_DUTY_CYCLE 100

static l293_t motor_left;
static l293_t motor_right;

static inline void
apply_duty_cycle(core_motion_t *motion);

static inline void
apply_direction(core_motion_t *motion);

static uint8_t
compute_duty_cycle(uint8_t correction);

void
core_port_motion_init(void)
{
    l293_t channel_left  = l293_create_channel_left();
    l293_t channel_right = l293_create_channel_right();
    memcpy(&motor_left, &channel_left, sizeof(l293_t));
    memcpy(&motor_right, &channel_right, sizeof(l293_t));

    l293_init(&motor_left);
    l293_init(&motor_right);
}

void
core_port_motion_apply(core_motion_t *motion)
{
    l293_disable(&motor_left);
    l293_disable(&motor_right);

    apply_duty_cycle(motion);
    apply_direction(motion);

    l293_enable(&motor_left);
    l293_enable(&motor_right);
}

static inline void
apply_duty_cycle(core_motion_t *motion)
{
    uint8_t duty_cycle = compute_duty_cycle(abs(motion->correction));

    if (motion->correction < 0)
    {
        tim3_pwm_set_duty_cycle(&motor_left.pwm_channel, duty_cycle);
        tim3_pwm_set_duty_cycle(&motor_right.pwm_channel, MAX_DUTY_CYCLE);
    }
    else if (motion->correction > 0)
    {
        tim3_pwm_set_duty_cycle(&motor_left.pwm_channel, MAX_DUTY_CYCLE);
        tim3_pwm_set_duty_cycle(&motor_right.pwm_channel, duty_cycle);
    }
    else
    {
        tim3_pwm_set_duty_cycle(&motor_left.pwm_channel, MAX_DUTY_CYCLE);
        tim3_pwm_set_duty_cycle(&motor_right.pwm_channel, MAX_DUTY_CYCLE);
    }
}

static inline void
apply_direction(core_motion_t *motion)
{
    if (motion->direction == CORE_MOTION_FORWARD)
    {
        l293_set_right(&motor_left);
        l293_set_right(&motor_right);
    }
    else if (motion->direction == CORE_MOTION_BACKWARD)
    {
        l293_set_left(&motor_left);
        l293_set_left(&motor_right);
    }
    else
    {
        l293_set_stop(&motor_left);
        l293_set_stop(&motor_right);
    }
}

static uint8_t
compute_duty_cycle(uint8_t correction)
{
    uint8_t duty_cycle;
    uint8_t duty_cycle_range = MAX_DUTY_CYCLE - MIN_DUTY_CYCLE;

    duty_cycle = MAX_DUTY_CYCLE - ((duty_cycle_range * correction) / MAX_DUTY_CYCLE);

    return duty_cycle;
}