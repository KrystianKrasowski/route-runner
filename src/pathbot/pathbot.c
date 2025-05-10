#include "commands.h"
#include "coords.h"
#include "mode.h"
#include <pathbot.h>
#include <stddef.h>
#include <utils/result.h>

pathbot_mode_t
pathbot_update_mode_manual(pathbot_mode_t const current_mode,
                           uint16_t const       commands)
{
    pathbot_mode_t mode = current_mode;

    if (mode_is_tracking(current_mode) && commands_has_break(commands))
    {
        mode = PATHBOT_MODE_MANUAL;
    }
    else if (mode_is_detected(current_mode) && commands_has_follow(commands))
    {
        mode = PATHBOT_MODE_FOLLOWING;
    }

    return mode;
}

pathbot_mode_t
pathbot_update_mode_tracking(pathbot_mode_t const    current_mode,
                             pathbot_coords_t const *p_coords)
{
    pathbot_mode_t mode = current_mode;

    if (mode_is_manual(current_mode) && coords_is_on_route(p_coords))
    {
        mode = PATHBOT_MODE_DETECTED;
    }
    else if (mode_is_detected(current_mode) && !coords_is_on_route(p_coords))
    {
        mode = PATHBOT_MODE_MANUAL;
    }
    else if (mode_is_following(current_mode) && !coords_is_on_route(p_coords))
    {
        mode = PATHBOT_MODE_RECOVERING;
    }
    else if (mode_is_tracking(current_mode) && coords_is_on_finish(p_coords))
    {
        mode = PATHBOT_MODE_MANUAL;
    }
    else if (mode_is_recovering(current_mode) && coords_is_on_route(p_coords))
    {
        mode = PATHBOT_MODE_FOLLOWING;
    }

    return mode;
}

pathbot_motion_t
pathbot_create_motion_manual(pathbot_mode_t const current_mode,
                             uint16_t const       commands)
{
    pathbot_direction_t direction  = PATHBOT_DIRECTION_NONE;
    int8_t              correction = 0;

    if (!mode_is_tracking(current_mode))
    {
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
    }

    pathbot_motion_t motion = {
        .direction  = direction,
        .correction = correction,
    };

    return motion;
}

int8_t
pathbot_compute_position_error(pathbot_coords_t const *p_coords)
{
    return coords_compute_mass_center(p_coords);
}

pathbot_motion_t
pathbot_create_motion_pid(pathbot_mode_t const           current_mode,
                          pathbot_coords_t const * const p_coords,
                          pathbot_pid_conf_t * const     p_pid_conf)
{
    pathbot_direction_t direction  = PATHBOT_DIRECTION_FORWARD;
    int8_t              correction = 0;
    bool b_invalid_input           = NULL == p_coords || NULL == p_pid_conf;

    if (b_invalid_input || !mode_is_tracking(current_mode) ||
        coords_is_on_finish(p_coords))
    {
        direction  = PATHBOT_DIRECTION_NONE;
        correction = 0;
    }
    else
    {
        int8_t  error_current  = coords_compute_mass_center(p_coords);
        int16_t errors_sum     = stack_sum(p_pid_conf->p_errors);
        int16_t previous_error = 0;

        stack_peek(p_pid_conf->p_errors, &previous_error);

        direction  = PATHBOT_DIRECTION_FORWARD;
        correction = p_pid_conf->kp * error_current +
                     p_pid_conf->ki * errors_sum +
                     p_pid_conf->kd * (error_current - previous_error);

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
