#include "commands.h"
#include "coords.h"
#include "mode.h"
#include <pathbot.h>
#include <stddef.h>
#include <stdint.h>
#include <utils/stack.h>

pathbot_mode_t
pathbot_update_mode_manual(pathbot_mode_t const current_mode,
                           uint16_t const       commands)
{
    return mode_update_manual(current_mode, commands);
}

pathbot_mode_t
pathbot_update_mode_tracking(pathbot_mode_t const           current_mode,
                             pathbot_coords_t const * const p_coords)
{
    if (NULL == p_coords)
    {
        return current_mode;
    }
    else
    {
        return mode_update_tracking(current_mode, p_coords);
    }
}

pathbot_motion_t
pathbot_create_motion_manual(uint16_t const commands)
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

int8_t
pathbot_compute_position_error(pathbot_coords_t const * const p_coords)
{
    if (NULL == p_coords)
    {
        return 0;
    }

    return coords_compute_mass_center(p_coords);
}

pathbot_motion_t
pathbot_create_motion_pid(int8_t const                     error,
                          stack_t const * const            p_past_errors,
                          pathbot_pid_conf_t const * const p_conf)
{
    pathbot_direction_t direction  = PATHBOT_DIRECTION_NONE;
    int8_t              correction = 0;

    if (p_past_errors && p_conf)
    {
        int16_t errors_sum     = stack_sum(p_past_errors);
        int16_t previous_error = 0;

        stack_peek(p_past_errors, &previous_error);

        direction  = PATHBOT_DIRECTION_FORWARD;
        correction = p_conf->kp * error + p_conf->ki * errors_sum +
                     p_conf->kd * (error - previous_error);

        if (correction > 100)
        {
            correction = 100;
        }

        if (correction < -100)
        {
            correction = -100;
        }
    }

    pathbot_motion_t motion = {
        .direction  = direction,
        .correction = correction,
    };

    return motion;
}
