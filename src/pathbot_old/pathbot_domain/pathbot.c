#include "coords.h"
#include "mode.h"
#include "motion.h"
#include <pathbot/domain.h>
#include <stddef.h>
#include <stdint.h>

bool
pathbot_mode_is_tracking(pathbot_mode_t const mode)
{
    return mode_is_tracking(mode);
}

bool
pathbot_update_mode_manual(uint16_t const         commands,
                           pathbot_mode_t * const p_mode)
{
    if (NULL != p_mode)
    {
        return mode_update_manual(commands, p_mode);
    }

    return false;
}

bool
pathbot_update_mode_tracking(pathbot_coords_t * const p_coords,
                             pathbot_mode_t * const   p_mode)
{
    if (NULL != p_coords && NULL != p_mode)
    {
        return mode_update_tracking(p_coords, p_mode);
    }

    return false;
}

bool
pathbot_update_motion_manual(uint16_t const           commands,
                             pathbot_motion_t * const p_motion)
{
    pathbot_motion_t current_motion = *p_motion;

    *p_motion = motion_create_manual(commands);

    return !motion_equals(p_motion, &current_motion);
}

int8_t
pathbot_compute_position_error(pathbot_coords_t * const p_coords)
{
    int8_t error = 0;

    if (NULL != p_coords)
    {
        error = coords_compute_mass_center(p_coords);
    }

    return error;
}

pathbot_motion_t
pathbot_create_motion_pid(int8_t const                     error,
                          stack_t const * const            p_past_errors,
                          pathbot_pid_conf_t const * const p_conf)
{
    if (NULL == p_past_errors || NULL == p_conf)
    {
        return motion_create_manual(PATHBOT_COMMAND_NONE);
    }
    else
    {
        return motion_create_pid(error, p_past_errors, p_conf);
    }
}
