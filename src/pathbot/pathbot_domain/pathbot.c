#include "coords.h"
#include "mode.h"
#include "motion.h"
#include <pathbot/domain.h>
#include <stddef.h>
#include <stdint.h>

pathbot_mode_t
pathbot_update_mode_manual(pathbot_mode_t const current_mode,
                           uint16_t const       commands)
{
    return mode_update_manual(current_mode, commands);
}

pathbot_mode_t
pathbot_update_mode_tracking(pathbot_mode_t const     current_mode,
                             pathbot_coords_t * const p_coords)
{
    pathbot_mode_t mode = current_mode;

    if (NULL != p_coords)
    {
        mode = mode_update_tracking(current_mode, p_coords);
    }

    return mode;
}

pathbot_motion_t
pathbot_create_motion_manual(uint16_t const commands)
{
    return motion_create_manual(commands);
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
