#include "commands.h"
#include "motion.h"

bool
motion_update_manual(uint16_t const commands, pathbot_motion_t * const p_motion)
{
    pathbot_motion_t current = *p_motion;

    if (commands_has_forward(commands))
    {
        p_motion->direction = PATHBOT_DIRECTION_FORWARD;
    }
    else if (commands_has_backward(commands))
    {
        p_motion->direction = PATHBOT_DIRECTION_BACKWARD;
    }
    else
    {
        p_motion->direction = PATHBOT_DIRECTION_NONE;
    }

    if (commands_has_left(commands) && commands_has_move(commands))
    {
        p_motion->correction = -50;
    }
    else if (commands_has_right(commands) && commands_has_move(commands))
    {
        p_motion->correction = 50;
    }
    else
    {
        p_motion->correction = 0;
    }

    return !motion_equals(p_motion, &current);
}

bool
motion_update_pid(int8_t const                     error,
                  stack_t const * const            p_past_errors,
                  pathbot_pid_conf_t const * const p_pid,
                  pathbot_motion_t * const         p_motion)
{
    pathbot_motion_t current = *p_motion;

    int16_t errors_sum     = stack_sum(p_past_errors);
    int8_t  previous_error = stack_peek_or(p_past_errors, 0);

    int16_t correction = p_pid->kp * error + p_pid->ki * errors_sum +
                         p_pid->kd * (error - previous_error);

    if (correction > 100)
    {
        correction = 100;
    }

    if (correction < -100)
    {
        correction = -100;
    }

    p_motion->direction  = PATHBOT_DIRECTION_FORWARD;
    p_motion->correction = (uint8_t)correction;

    return !motion_equals(p_motion, &current);
}

void
motion_stop(pathbot_motion_t * const p_motion)
{
    p_motion->correction = 0;
    p_motion->direction  = PATHBOT_DIRECTION_NONE;
}

bool
motion_equals(pathbot_motion_t const * const p_self,
              pathbot_motion_t const * const p_other)
{
    return p_self->correction == p_other->correction &&
           p_self->direction == p_other->direction;
}
