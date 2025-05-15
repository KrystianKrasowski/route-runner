#include "commands.h"
#include "motion.h"

bool
motion_equals(pathbot_motion_t const * const p_self,
              pathbot_motion_t const * const p_other)
{
    return p_self->correction == p_other->correction &&
           p_self->direction == p_other->direction;
}

pathbot_motion_t
motion_create_manual(uint16_t const commands)
{
    pathbot_direction_t direction  = PATHBOT_DIRECTION_NONE;
    int8_t              correction = 0;

    if (commands_has_forward(commands))
    {
        direction = PATHBOT_DIRECTION_FORWARD;
    }

    if (commands_has_backward(commands))
    {
        direction = PATHBOT_DIRECTION_BACKWARD;
    }

    if (commands_has_left(commands) && commands_has_move(commands))
    {
        correction = -50;
    }

    if (commands_has_right(commands) && commands_has_move(commands))
    {
        correction = 50;
    }

    pathbot_motion_t motion = {
        .direction  = direction,
        .correction = correction,
    };

    return motion;
}

pathbot_motion_t
motion_create_pid(int8_t const                     error,
                  stack_t const * const            p_past_errors,
                  pathbot_pid_conf_t const * const p_pid_conf)
{
    int16_t errors_sum     = stack_sum(p_past_errors);
    int8_t  previous_error = stack_peek_or(p_past_errors, 0);

    int8_t correction = p_pid_conf->kp * error + p_pid_conf->ki * errors_sum +
                        p_pid_conf->kd * (error - previous_error);

    if (correction > 100)
    {
        correction = 100;
    }

    if (correction < -100)
    {
        correction = -100;
    }

    pathbot_motion_t motion = {
        .direction  = PATHBOT_DIRECTION_FORWARD,
        .correction = correction,
    };

    return motion;
}
