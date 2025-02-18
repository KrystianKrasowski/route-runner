#include <core.h>
#include <l293.h>
#include <stdbool.h>
#include <string.h>

static l293_t motor_left;
static l293_t motor_right;

static inline bool
is_forward_stright(core_motion_t *motion);

static inline bool
is_forward_left(core_motion_t *motion);

static inline bool
is_forward_right(core_motion_t *motion);

static inline bool
is_backward_stright(core_motion_t *motion);

static inline bool
is_backward_left(core_motion_t *motion);

static inline bool
is_backward_right(core_motion_t *motion);

static inline bool
is_stop(core_motion_t *motion);

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

    if (is_stop(motion))
    {
        l293_set_stop(&motor_left);
        l293_set_stop(&motor_right);
    }
    else if (is_forward_stright(motion))
    {
        l293_set_right(&motor_left);
        l293_set_right(&motor_right);
    }
    else if (is_forward_left(motion))
    {
        l293_set_stop(&motor_left);
        l293_set_right(&motor_right);
    }
    else if (is_forward_right(motion))
    {
        l293_set_right(&motor_left);
        l293_set_stop(&motor_right);
    }
    else if (is_backward_stright(motion))
    {
        l293_set_left(&motor_left);
        l293_set_left(&motor_right);
    }
    else if (is_backward_left(motion))
    {
        l293_set_stop(&motor_left);
        l293_set_left(&motor_right);
    }
    else if (is_backward_right(motion))
    {
        l293_set_left(&motor_left);
        l293_set_stop(&motor_right);
    }

    l293_enable(&motor_left);
    l293_enable(&motor_right);
}

static inline bool
is_forward_stright(core_motion_t *motion)
{
    return motion->direction == CORE_MOTION_FORWARD && motion->angle == 0;
}

static inline bool
is_forward_left(core_motion_t *motion)
{
    return motion->direction == CORE_MOTION_FORWARD && motion->angle == -90;
}

static inline bool
is_forward_right(core_motion_t *motion)
{
    return motion->direction == CORE_MOTION_FORWARD && motion->angle == 90;
}

static inline bool
is_backward_stright(core_motion_t *motion)
{
    return motion->direction == CORE_MOTION_BACKWARD && motion->angle == 0;
}

static inline bool
is_backward_left(core_motion_t *motion)
{
    return motion->direction == CORE_MOTION_BACKWARD && motion->angle == -90;
}

static inline bool
is_backward_right(core_motion_t *motion)
{
    return motion->direction == CORE_MOTION_BACKWARD && motion->angle == 90;
}

static inline bool
is_stop(core_motion_t *motion)
{
    return motion->direction == CORE_MOTION_NONE;
}